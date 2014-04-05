
import bpy
from mathutils import *
from struct import *
from pprint import pprint
import math


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
	f.write( struct.pack( "B", len( bytebuf ) ) )
	f.write( bytebuf )

def write_buffer( f, bytebuf ):
	if len( bytebuf ) > 0xffffffff:
		raise Exception( "smallbuf too big" )
	f.write( struct.pack( "L", len( bytebuf ) ) )
	f.write( bytebuf )

def write_part( f, part ):
	if len( part.textures ) > 8:
		raise Exception( "too many textures (max. 8 allowed)" )
	f.write( struct.pack( "LLLLHB", part.voff, part.vcount, part.ioff, part.icount, part.flags, len( part.textures ) ) )
	write_smallbuf( f, bytes( part.shader, "UTF-8" ) )

def write_mesh( f, is_transparent, bbmin, bbmax, vertices, indices, format, parts ):
	if len( parts ) > 255:
		raise Exception( "too many parts (max. 255 allowed)" )
	
	is_i32 = len( vertices ) > 65535
	
	f.write( bytes( "SS3DMESH", "UTF-8" ) )
	f.write( struct.pack( "L", (1 if is_i32 else 0) * 0x01 + (1 if is_transparent else 0) * 0x10 ) ) # flags
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
	
	write_smallbuf( format )
	f.write( struct.pack( "B", len(parts) ) )
	for part in parts:
		write_part( f, part )
	
	return


def addCached( olist, o ):
	try:
		return olist.index( o )
	except:
		olist.append( o )
		return len( olist ) - 1


def find_in_userdata( obj, key ):
	for prop in obj.items():
		if type( prop[ 1 ] ) in ( int, str, float, bool ):
			if prop[ 0 ] == key:
				return prop[ 1 ]
	return None


def write_geometry( f, ctx, data ):
	f.write( "GEOMETRY \"%s\"\n" % ESC( data.name ) )
	
	# FACE INDICES
	#1: sort by material
	flim = {}
	ficm = {}
	fiim = []
	for face in data.polygons:
	
		if face.material_index not in flim:
			flim[ face.material_index ] = []
		flim[ face.material_index ].append( face )
		
		if face.material_index not in ficm:
			ficm[ face.material_index ] = 0
		ficm[ face.material_index ] += len( face.vertices )
		
		if face.material_index not in fiim:
			fiim.append( face.material_index )
	
	fiim.sort()
	
	#2: write face data - face count, index count, <stream_item_id x numstreams x num_indices>
	Plist = []
	Nlist = []
	Tlists = [ [] for tl in data.uv_layers ]
	Clists = [ [] for cl in data.vertex_colors ]
	
	FACES = ""
	for flist_id in flim:
		flist = flim[ flist_id ]
		FACES += "\tFACES %d %d" % ( len( flist ), ficm[ flist[ 0 ].material_index ] )
		for face in flist:
			m_id = face.material_index
			if flist_id != m_id:
				continue
			
			FACES += " %d" % len( face.vertices )
			for vid in range( len( face.vertices ) ):
				v_id = face.vertices[ vid ]
				l_id = face.loop_start + vid
				
				pos_id = addCached( Plist, data.vertices[ v_id ].co )
				if face.use_smooth != False:
					nrm_id = addCached( Nlist, data.vertices[ v_id ].normal )
				else:
					nrm_id = addCached( Nlist, face.normal )
				
				FACES += " %d %d %d" % ( v_id, pos_id, nrm_id )
				for si in range( len( Tlists ) ):
					txc_id = addCached( Tlists[ si ], data.uv_layers[ si ].data[ l_id ].uv )
					FACES += " %d" % txc_id
				for si in range( len( Clists ) ):
					col_id = addCached( Clists[ si ], data.vertex_colors[ si ].data[ l_id ].color )
					FACES += " %d" % col_id
		FACES += " _\n"
	
	f.write( "\tSTREAM POSITION 0 3 %d" % len( Plist ) )
	for pos in Plist:
		f.write( " %g %g %g" % ( pos.x, pos.y, pos.z ) )
	f.write( " _\n" )
	
	f.write( "\tSTREAM NORMAL 0 3 %d" % len( Nlist ) )
	for nrm in Nlist:
		f.write( " %g %g %g" % ( nrm.x, nrm.y, nrm.z ) )
	f.write( " _\n" )
	
	for tl_id in range( len( Tlists ) ):
		Tlist = Tlists[ tl_id ]
		f.write( "\tSTREAM TEXCOORD %d 2 %d" % ( tl_id, len( Tlist ) ) )
		for txc in Tlist:
			f.write( " %g %g" % ( txc.x, 1 - txc.y ) )
		f.write( " _\n" )
	
	for cl_id in range( len( Clists ) ):
		Clist = Clists[ cl_id ]
		f.write( "\tSTREAM COLOR %d 3 %d" % ( cl_id, len( Clist ) ) )
		for col in Clist:
			f.write( " %g %g %g" % ( col.r, col.g, col.b ) )
		f.write( " _\n" )
	
	f.write( FACES )
	
	# CUSTOM PROPERTIES
	write_userdata( f, data )
	
	f.write( "GEOMETRY_END\n\n" )


def write_node( f, ctx, node, level ):
	tabs = make_tabs( level )
	
	nloc = node.location
	nrot = node.matrix_local.to_quaternion()
	nscl = node.scale
	
	f.write( "%sNODE \"%s\"\n" % ( tabs, ESC( node.name ) ) )
	
	f.write( "%s\tPOSITION %g %g %g _\n" % ( tabs, nloc.x, nloc.y, nloc.z ) )
	f.write( "%s\tROTATION %g %g %g %g _\n" % ( tabs, nrot.x, nrot.y, nrot.z, nrot.w ) )
	f.write( "%s\tSCALE %g %g %g _\n" % ( tabs, nscl.x, nscl.y, nscl.z ) )
	
	if node.type == "CAMERA":
		nty = "CAMERA"
	elif node.type == "MESH":
		nty = "GEOMETRY"
	elif node.type == "LAMP":
		nty = "LIGHT"
	elif node.type == "ARMATURE":
		nty = "ARMATURE"
	else:
		nty = "NULL"
	
	if nty == "GEOMETRY":
		f.write( "%s\t%s \"%s\"\n" % ( tabs, nty, ESC( node.data.name ) ) )
		for mtl in node.data.materials:
			f.write( "%s\t\tMATERIAL \"%s\" _\n" % ( tabs, ESC( mtl.name ) ) )
		for grp in node.vertex_groups:
			f.write( "%s\t\tGROUP \"%s\"" % ( tabs, ESC( grp.name ) ) )
			grl = {}
			for i in range( len( node.data.vertices ) ):
				proceed = False
				for vg in node.data.vertices[ i ].groups:
					if( vg.group == grp.index ):
						proceed = True
						break
				if proceed == False:
					continue
				wt = grp.weight( i )
				if wt > 0.0:
					grl[ i ] = wt
			f.write( "  %d " % len( grl ) )
			for idx, wt in grl.items():
				f.write( " %d %g" % ( idx, wt ) )
			f.write( " _\n" )
		f.write( "%s\tGEOMETRY_END\n" % tabs )
	elif nty != "NULL":
		f.write( "%s\t%s \"%s\" _\n" % ( tabs, nty, ESC( node.data.name ) ) )
	
	write_userdata( f, node, tabs + "\t" )
	
	for ch in node.children:
		write_node( f, ctx, ch, level + 1 )
	
	f.write( "%sNODE_END\n" % tabs )


def write_scene( f, ctx, scene ):
	f.write( "SCENE \"%s\"\n" % ESC( scene.name ) )
	
	for node in scene.objects:
		if node.parent != None:
			continue
		write_node( f, ctx, node, 1 )
	
	f.write( "SCENE_END\n\n" );


def write_ss3dmesh( ctx, filepath ):
	print( "\n\\\\\n>>> SS3DMESH Exporter v0.4!\n//\n\n" )
	print( "Exporting..." )
	
	textures = {}
	materials = {}
	
	print( "Parsing textures... ", end="" )
	for tex in bpy.data.textures:
		texpath = ""
		if hasattr( tex, "image" ) and tex.image != None:
			texpath = tex.image.filepath[ 2: ]
		textures[ tex.name ] = texpath
	print( "OK!" )
	pprint( textures )
	
	print( "Parsing materials... ", end="" )
	for mtl in bpy.data.materials:
		outmtl = { "textures": [], "shader": "default" }
		for tex in  mtl.texture_slots:
			outmtl["textures"].append( textures[ tex.name ] if tex != None else "" )
		while len(outmtl["textures"]) and outmtl["textures"][-1] == "":
			outmtl["textures"].pop()
		shdr = find_in_userdata( mtl, "shader" )
		if type( shdr ) == str:
			outmtl["shader"] = shdr
		materials[ mtl.name ] = outmtl
	print( "OK!" )
	pprint( materials )
	
	print( "Parsing geometries... ", end="" )
	for geom in bpy.data.meshes:
		write_geometry( f, ctx, geom )
	print( "OK!" )
	
	print( "Writing everything... ", end="" )
	f = open( filepath, 'wb' )
	write_mesh( f, MESHDATA )
	f.close()
	print( "OK!" )
	
	print( "\n\\\\\n>>> Done!\n//\n\n" )

	return {'FINISHED'}


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
