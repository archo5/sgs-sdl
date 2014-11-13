
import bpy
from mathutils import *
from pprint import pprint
import math
import struct


""" FORMAT
	
	BUFFER: (min size = 4)
	- uint32 size
	- uint8 data[size]
	
	SMALLBUF: (min size = 1)
	- uint8 size
	- uint8 data[size]
	
	PART: (min size = 19)
	- uint32 voff
	- uint32 vcount
	- uint32 ioff
	- uint32 icount
	- uint16 flags
	- uint8 texcount
	- smallbuf shader
	- smallbuf textures[texcount]
	
	MESH:
	- magic "SS3DMESH"
	- uint32 flags
	
	- float boundsmin[3]
	- float boundsmax[3]
	
	- buffer vdata
	- buffer idata
	- smallbuf format
	- uint8 numparts
	- part parts[numparts]
	
	minimum size = 12+24+10 = 46
"""


bl_info = {
	"name": "SS3DMESH Mesh Format (.ssm)",
	"author": "Arvīds Kokins",
	"version": (0, 4, 2),
	"blender": (2, 6, 9),
	"api": 38019,
	"location": "File > Export > SS3DMESH (.ssm)",
	"description": "SS3DMESH Mesh Export (.ssm)",
	"warning": "",
	"wiki_url": "http://cragegames.com",
	"tracker_url": "http://cragegames.com",
	"category": "Import-Export"
}


def write_smallbuf( f, bytebuf ):
	if len( bytebuf ) > 255:
		raise Exception( "smallbuf too big" )
	if type( bytebuf ) == str:
		bytebuf = bytes( bytebuf, "UTF-8" )
	f.write( struct.pack( "B", len( bytebuf ) ) )
	f.write( bytebuf )
#

def write_buffer( f, bytebuf ):
	if len( bytebuf ) > 0xffffffff:
		raise Exception( "smallbuf too big" )
	if type( bytebuf ) == str:
		bytebuf = bytes( bytebuf, "UTF-8" )
	f.write( struct.pack( "L", len( bytebuf ) ) )
	f.write( bytebuf )
#

def write_part( f, part ):
	if len( part["textures"] ) > 8:
		raise Exception( "too many textures (max. 8 allowed)" )
	f.write( struct.pack( "LLLLB", part["voff"], part["vcount"], part["ioff"], part["icount"], len( part["textures"] ) ) )
	write_smallbuf( f, bytes( part["shader"], "UTF-8" ) )
	for tex in part["textures"]:
		write_smallbuf( f, tex )
#

def write_mesh( f, meshdata ):
	is_transparent = meshdata["is_transparent"]
	is_unlit = meshdata["is_unlit"]
	is_nocull = meshdata["is_nocull"]
	bbmin = meshdata["bbmin"]
	bbmax = meshdata["bbmax"]
	vertices = meshdata["vertices"]
	indices = meshdata["indices"]
	format = meshdata["format"]
	parts = meshdata["parts"]
	
	if len( parts ) > 255:
		raise Exception( "too many parts (max. 255 allowed)" )
	
	is_i32 = len( vertices ) > 65535
	
	print( "--- MESH STATS ---" )
	print( "Transparent: %s" % ( "true" if is_transparent else "false" ) )
	print( "Unlit: %s" % ( "true" if is_unlit else "false" ) )
	print( "No culling: %s" % ( "true" if is_nocull else "false" ) )
	print( "Vertex count: %d" % ( len(vertices) ) )
	print( "Index count: %d" % ( len(indices) ) )
	print( "Format string: " + format )
	print( "Part count: %d" % ( len(parts) ) )
	for part_id, part in enumerate( parts ):
		print( "- part %d: voff=%d vcount=%d ioff=%d icount=%d texcount=%d shader='%s'" % ( part_id, part["voff"], part["vcount"], part["ioff"], part["icount"], len( part["textures"] ), part["shader"] ) )
	
	f.write( bytes( "SS3DMESH", "UTF-8" ) )
	f.write( struct.pack( "L", (1 if is_i32 else 0) * 0x01 + (1 if is_transparent else 0) * 0x10 + (1 if is_unlit else 0) * 0x20 + (1 if is_nocull else 0) * 0x40 ) ) # flags
	f.write( struct.pack( "6f", bbmin.x, bbmin.y, bbmin.z, bbmax.x, bbmax.y, bbmax.z ) )
	
	vdata = bytes()
	for vertex in vertices:
		vdata += vertex
	write_buffer( f, vdata )
	
	idata = bytes()
	if( is_i32 ):
		for index in indices:
			idata += struct.pack( "L", index )
	else:
		for index in indices:
			idata += struct.pack( "H", index )
	write_buffer( f, idata )
	
	write_smallbuf( f, format )
	f.write( struct.pack( "B", len(parts) ) )
	for part in parts:
		write_part( f, part )
	
	return
#

def addCached( olist, o, minpos = 0 ):
	try:
		return olist[ minpos: ].index( o )
	except:
		olist.append( o )
		return len( olist ) - 1 - minpos
#

def find_in_userdata( obj, key, default = None ):
	for prop in obj.items():
		if type( prop[ 1 ] ) in ( int, str, float, bool ):
			if prop[ 0 ] == key:
				return prop[ 1 ]
	return default
#

def parse_geometry( MESH, materials ):
	# SORT BY MATERIAL
	flim = {}
	ficm = {}
	fiim = []
	for face in MESH.polygons:
	
		if face.material_index not in flim:
			flim[ face.material_index ] = []
		flim[ face.material_index ].append( face )
		
		if face.material_index not in ficm:
			ficm[ face.material_index ] = 0
		ficm[ face.material_index ] += len( face.vertices )
		
		if face.material_index not in fiim:
			fiim.append( face.material_index )
	
	fiim.sort()
	
	# GENERATE COMPACT DATA
	Plist = []
	Nlist = []
	Tlists = [ [] for tl in MESH.uv_layers ]
	Clists = [ [] for cl in MESH.vertex_colors ]
	genParts = [] # array of Part ( array of Face ( array of Vertex ( position index, normal index, texcoord indices, color indices ) ) )
	foundMIDs = []
	
	if len( Tlists ) > 2:
		print( "Too many UV layers" )
		Tlists = Tlists[:1]
	if len( Clists ) > 1:
		print( "Too many color layers" )
		Clists = Clists[:1]
	
	for flist_id in flim:
		genPart = []
		flist = flim[ flist_id ]
		m_id = 0
		for face in flist:
			m_id = face.material_index
			if flist_id != m_id:
				continue
			
			genFace = []
			
			for vid in range( len( face.vertices ) ):
				v_id = face.vertices[ vid ]
				l_id = face.loop_start + vid
				
				pos_id = addCached( Plist, MESH.vertices[ v_id ].co )
				if face.use_smooth != False:
					nrm_id = addCached( Nlist, MESH.vertices[ v_id ].normal )
				else:
					nrm_id = addCached( Nlist, face.normal )
				
				genVertex = [ pos_id, nrm_id ]
				
				for si in range( len( Tlists ) ):
					txc_id = addCached( Tlists[ si ], MESH.uv_layers[ si ].data[ l_id ].uv )
					genVertex.append( txc_id )
				for si in range( len( Clists ) ):
					col_id = addCached( Clists[ si ], MESH.vertex_colors[ si ].data[ l_id ].color )
					genVertex.append( col_id )
				
				genFace.append( genVertex )
			genPart.append( genFace )
		genParts.append( genPart )
		foundMIDs.append( m_id )
	#
	
	# VALIDATION
	if len( Plist ) <= 0:
		raise Exception( "Mesh has no vertices!" )
	#
	
	# CONVERT TO VERTEX BUFFER FORMAT
	vertices = []
	indices = []
	parts = []
	
	mtl_num = -1
	for part in genParts:
		mtl_num += 1
		mtl_id = foundMIDs[ mtl_num ]
		vroot = len(vertices)
		outpart = { "voff": len(vertices), "vcount": 0, "ioff": len(indices), "icount": 0, "shader": materials[ mtl_id ]["shader"], "textures": materials[ mtl_id ]["textures"] }
		
		for face in part:
			tmpidcs = []
			for vertex in face:
				P = Plist[ vertex[0] ]
				N = Nlist[ vertex[1] ]
				vertexdata = struct.pack( "3f3f", P.x, P.y, P.z, N.x, N.y, N.z )
				vip = 2
				for si in range( len( Tlists ) ):
					T = Tlists[ si ][ vertex[ vip ] ]
					vip += 1
					vertexdata += struct.pack( "2f", T.x, 1 - T.y )
				for si in range( len( Clists ) ):
					C = Clists[ si ][ vertex[ vip ] ]
					vip += 1
					vertexdata += struct.pack( "4B", int(C.r * 255), int(C.g * 255), int(C.b * 255), 255 )
				tmpidcs.append( addCached( vertices, vertexdata, vroot ) )
			#
			for i in range( 2, len( tmpidcs ) ):
				indices.append( tmpidcs[ 0 ] )
				indices.append( tmpidcs[ i - 1 ] )
				indices.append( tmpidcs[ i ] )
			#
		#
		
		outpart["vcount"] = len(vertices) - outpart["voff"]
		outpart["icount"] = len(indices) - outpart["ioff"]
		parts.append( outpart )
	#
	
	# TANGENT SPACE CALC
	if len( Tlists ) > 0:
		tan1list = [ Vector([0,0,0]) for i in range(len(vertices)) ]
		tan2list = [ Vector([0,0,0]) for i in range(len(vertices)) ]
		
		for part in parts:
			voff = part["voff"]
			ioff = part["ioff"]
			for i in range( 0, part["icount"], 3 ):
				i1 = indices[ ioff + i + 0 ] + voff
				i2 = indices[ ioff + i + 1 ] + voff
				i3 = indices[ ioff + i + 2 ] + voff
				
				Pdc1 = struct.unpack( "3f", vertices[ i1 ][ :12 ] )
				Pdc2 = struct.unpack( "3f", vertices[ i2 ][ :12 ] )
				Pdc3 = struct.unpack( "3f", vertices[ i3 ][ :12 ] )
				
				v1 = Vector([ Pdc1[0], Pdc1[1], Pdc1[2] ])
				v2 = Vector([ Pdc2[0], Pdc2[1], Pdc2[2] ])
				v3 = Vector([ Pdc3[0], Pdc3[1], Pdc3[2] ])
				
				Tdc1 = struct.unpack( "2f", vertices[ i1 ][ 24:32 ] )
				Tdc2 = struct.unpack( "2f", vertices[ i2 ][ 24:32 ] )
				Tdc3 = struct.unpack( "2f", vertices[ i3 ][ 24:32 ] )
				
				w1 = Vector([ Tdc1[0], Tdc1[1], 0 ])
				w2 = Vector([ Tdc2[0], Tdc2[1], 0 ])
				w3 = Vector([ Tdc3[0], Tdc3[1], 0 ])
				
				x1 = v2.x - v1.x;
				x2 = v3.x - v1.x;
				y1 = v2.y - v1.y;
				y2 = v3.y - v1.y;
				z1 = v2.z - v1.z;
				z2 = v3.z - v1.z;
				
				s1 = w2.x - w1.x;
				s2 = w3.x - w1.x;
				t1 = w2.y - w1.y;
				t2 = w3.y - w1.y;
				
				ir = s1 * t2 - s2 * t1
				if abs( ir ) > 0.001:
					r = 1.0 / ir
					sdir = Vector([(t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r])
					tdir = Vector([(s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r])
					
					tan1list[ i1 ] += sdir
					tan1list[ i2 ] += sdir
					tan1list[ i3 ] += sdir
					
					tan2list[ i1 ] += tdir
					tan2list[ i2 ] += tdir
					tan2list[ i3 ] += tdir
				#
			#
		#
		
		for v_id, vertex in enumerate( vertices ):
			Ndc = struct.unpack( "3f", vertex[ 12:24 ] )
			n = Vector([ Ndc[0], Ndc[1], Ndc[2] ])
			t = tan1list[ v_id ]
			t2 = tan2list[ v_id ]
			
			outtan = ( t - n * n.dot( t ) ).normalized()
			sign = -1.0 if n.cross( t ).dot( t2 ) < 0.0 else 1.0
			vertices[ v_id ] = vertex[ :24 ] + struct.pack( "4f", outtan.x, outtan.y, outtan.z, sign ) + vertex[ 24: ]
		#
	#
	
	# AABB
	bbmin = Plist[0].copy()
	bbmax = Plist[0].copy()
	for pos in Plist:
		if bbmin.x > pos.x:
			bbmin.x = pos.x
		if bbmin.y > pos.y:
			bbmin.y = pos.y
		if bbmin.z > pos.z:
			bbmin.z = pos.z
		if bbmax.x < pos.x:
			bbmax.x = pos.x
		if bbmax.y < pos.y:
			bbmax.y = pos.y
		if bbmax.z < pos.z:
			bbmax.z = pos.z
	#
	
	# FORMAT STRING
	format = "pf3nf3tf4"
	for si in range( len( Tlists ) ):
		format += "%df2" % ( si )
	for si in range( len( Clists ) ): # only one expected
		format += "cb4"
	#
	
	return {
		"is_transparent": find_in_userdata( MESH, "transparent", False ) != False,
		"is_unlit": find_in_userdata( MESH, "unlit", False ) != False,
		"is_nocull": find_in_userdata( MESH, "nocull", False ) != False,
		"bbmin": bbmin, "bbmax": bbmax, "vertices": vertices, "indices": indices, "format": format, "parts": parts
	}
#

def write_ss3dmesh( ctx, filepath ):
	print( "\n\\\\\n>>> SS3DMESH Exporter v0.4!\n//\n\n" )
	print( "Exporting..." )
	
	textures = {}
	print( "Parsing textures... ", end="" )
	for tex in bpy.data.textures:
		texpath = ""
		if hasattr( tex, "image" ) and tex.image != None:
			texpath = tex.image.filepath[ 2: ]
		textures[ tex.name ] = texpath
	print( "OK!" )
	
	print( "Parsing nodes... ", end="" )
	geom_node = bpy.context.active_object
	if geom_node == None:
		scene = ctx.scene
		for node in scene.objects:
			if node.type == "MESH":
				geom_node = node
				break
	#
	if geom_node == None:
		print( "ERROR: no MESH nodes!" )
		return {'FAILED'}
	print( "OK!" )
	
	materials = []
	print( "Parsing materials... ", end="" )
	for mtl in geom_node.data.materials:
		outmtl = { "textures": [], "shader": "default" }
		for tex in  mtl.texture_slots:
			outmtl["textures"].append( textures[ tex.name ] if tex != None else "" )
		while len(outmtl["textures"]) and outmtl["textures"][-1] == "":
			outmtl["textures"].pop()
		shdr = find_in_userdata( mtl, "shader" )
		if type( shdr ) == str:
			outmtl["shader"] = shdr
		materials.append( outmtl )
	print( "OK!" )
	
	print( "Generating geometry... ", end="" )
	meshdata = parse_geometry( geom_node.data, materials )
	print( "OK!" )
	
	print( "Writing everything... " )
	f = open( filepath, 'wb' )
	write_mesh( f, meshdata )
	f.close()
	
	print( "\n\\\\\n>>> Done!\n//\n\n" )

	return {'FINISHED'}
#

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty


class ExportSS3DMESH( bpy.types.Operator, ExportHelper ):
	'''SS3DMESH Exporter'''
	bl_idname = "export.ss3dmesh"
	bl_label = "Export .ssm"

	# ExportHelper mixin class uses this
	filename_ext = ".ssm"

	filter_glob = StringProperty(
			default = "*.ssm",
			options = {'HIDDEN'},
		)

	@classmethod
	def poll( cls, ctx ):
		return ctx.active_object is not None

	def execute( self, ctx ):
		return write_ss3dmesh( ctx, self.filepath )


# Only needed if you want to add into a dynamic menu
def menu_func_export( self, ctx ):
	self.layout.operator( ExportSS3DMESH.bl_idname, text="SS3DMESH Exporter" )


def register():
	bpy.utils.register_class( ExportSS3DMESH )
	bpy.types.INFO_MT_file_export.append( menu_func_export )


def unregister():
	bpy.utils.unregister_class( ExportSS3DMESH )
	bpy.types.INFO_MT_file_export.remove( menu_func_export )


if __name__ == "__main__":
	register()

	# test call
	bpy.ops.export.some_data('INVOKE_DEFAULT')
