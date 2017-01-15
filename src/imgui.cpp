

#include "imgui.hpp"


bool _imgui_TextArrayCallback( void* data, int idx, const char** out_text )
{
	/////////////////////////////
	// ASSUMING IMPLEMENTATION:
	// - out_text is used only before next call to this function
	// > after each call, the previous value is invalid
	imgui_TextArrayCallbackData* tacd = (imgui_TextArrayCallbackData*) data;
	tacd->str = tacd->func.tcall<sgsString>( tacd->func.get_ctx(), idx );
	if( tacd->str.not_null() )
	{
		*out_text = tacd->str.c_str();
		return true;
	}
	return false;
}

float _imgui_FloatArrayCallback( void* data, int idx )
{
	sgsVariable* func = (sgsVariable*) data;
	return func->tcall<float>( func->get_ctx(), idx );
}

imgui_FloatArrayParser::imgui_FloatArrayParser( SGS_CTX, sgs_StkIdx item )
{
	values = NULL;
	sgs_Variable var = sgs_OptStackItem( C, item );
	count = sgs_ArraySize( var );
	if( count > 0 )
	{
		values = new float[ count ];
		for( int i = 0; i < count; ++i )
		{
			sgs_PushNumIndex( C, var, i );
			values[ i ] = sgs_GetReal( C, -1 );
			sgs_Pop( C, 1 );
		}
	}
}


static int sgsimgui_SS_NewFrame( SGS_CTX )
{
	SGSFN( "ImGui_SS_NewFrame" );
	
	float dt;
	if( !sgs_LoadArgs( C, "f", &dt ) )
		return 0;
	
	ImGuiIO& io = ImGui::GetIO();
	
	sgsVariable reg = sgsRegistry( C );
	sgsVariable texvar = reg.getprop( "__imgui_font_texture" );
	if( texvar.not_null() == false )
	{
		unsigned char* bits;
		int w, h;
		io.Fonts->GetTexDataAsRGBA32( &bits, &w, &h );
		ss_CreateImageHelper( C, w, h, bits );
		sgsVariable tex = sgsEnv( C ).getprop( "SS_CreateTexture" ).tcallu<sgsVariable>( C, 1 );
		reg.setprop( "__imgui_font_texture", tex );
		sgs_BreakIf( tex.type_id() != SGS_VT_OBJECT );
		io.Fonts->SetTexID( tex.get_object_struct() );
	}
	
	io.DeltaTime = dt;
	io.KeyShift = io.KeysDown[ SDL_SCANCODE_LSHIFT ] || io.KeysDown[ SDL_SCANCODE_RSHIFT ];
	io.KeyCtrl = io.KeysDown[ SDL_SCANCODE_LCTRL ] || io.KeysDown[ SDL_SCANCODE_RCTRL ];
	io.KeyAlt = io.KeysDown[ SDL_SCANCODE_LALT ] || io.KeysDown[ SDL_SCANCODE_RALT ];
	io.KeySuper = io.KeysDown[ SDL_SCANCODE_LGUI ] || io.KeysDown[ SDL_SCANCODE_RGUI ];
	
	ImGui::NewFrame();
	
	return 0;
}

static void imgui_impl_RenderDrawLists( ImDrawData* draw_data )
{
	if( !GCurRI || !GCurRr )
		return; /* cannot draw without active renderer */
	
	ImGuiIO& io = ImGui::GetIO();
	int fb_width = int( io.DisplaySize.x * io.DisplayFramebufferScale.x );
	int fb_height = int( io.DisplaySize.y * io.DisplayFramebufferScale.y );
	if( fb_width == 0 || fb_height == 0 )
		return;
	draw_data->ScaleClipRects( io.DisplayFramebufferScale );
	
	for( int n = 0; n < draw_data->CmdListsCount; ++n )
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[ n ];
		const ImDrawVert* vtx_buffer = &cmd_list->VtxBuffer.front();
		const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
		
		for( int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); ++cmd_i )
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[ cmd_i ];
			if( pcmd->UserCallback )
			{
				pcmd->UserCallback( cmd_list, pcmd );
			}
			else
			{
				GCurRI->set_render_state( GCurRr, SS_RS_CLIPRECT, pcmd->ClipRect.x, pcmd->ClipRect.y, pcmd->ClipRect.z, pcmd->ClipRect.w );
				GCurRI->set_render_state( GCurRr, SS_RS_CLIPENABLE, 1, 0,0,0 );
				
				GCurRI->apply_texture( GCurRr, (SS_Texture*) ((sgs_VarObj*)pcmd->TextureId)->data );
				
				SS_BasicVertex outverts[ 3 * 1024 ];
				int outidx = 0;
				
				for( unsigned idx = 0; idx < pcmd->ElemCount; ++idx )
				{
					const ImDrawVert& v = vtx_buffer[ idx_buffer[ idx ] ];
					SS_BasicVertex& outv = outverts[ outidx ];
					outv.pos[0] = v.pos.x;
					outv.pos[1] = v.pos.y;
					outv.pos[2] = 0;
					outv.col = v.col;
					outv.tex[0] = v.uv.x;
					outv.tex[1] = v.uv.y;
					outidx++;
					if( outidx == 3 * 1024 )
					{
						GCurRI->draw_basic_vertices( GCurRr, outverts, outidx, SS_PT_TRIANGLES );
						outidx = 0;
					}
				}
				
				if( outidx >= 3 )
					GCurRI->draw_basic_vertices( GCurRr, outverts, outidx, SS_PT_TRIANGLES );
			}
			idx_buffer += pcmd->ElemCount;
		}
	}
	
	GCurRI->set_render_state( GCurRr, SS_RS_CLIPENABLE, 0, 0,0,0 );
}

static const char* imgui_impl_GetClipboardText( void* user_data )
{
	SGS_CTX = (sgs_Context*) user_data;
	char* text = SDL_GetClipboardText();
	if( text )
	{
		sgsVariable reg = sgsRegistry( C );
		sgsString str( C, text );
		reg.setprop( "__imgui_clipboard", str.get_variable() );
		SDL_free( text );
		return str.c_str();
	}
	return "";
}

static void imgui_impl_SetClipboardText( void* user_data, const char* text )
{
	SDL_SetClipboardText( text );
}

static int sgsimgui_SS_Init( SGS_CTX )
{
	int w = 9999, h = 9999;
	SGSFN( "ImGui_SS_Init" );
	if( !sgs_LoadArgs( C, "|II", &w, &h ) )
		return 0;
	
	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ ImGuiKey_Tab ] = SDLK_TAB;
	io.KeyMap[ ImGuiKey_LeftArrow ] = SDL_SCANCODE_LEFT;
	io.KeyMap[ ImGuiKey_RightArrow ] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ ImGuiKey_UpArrow ] = SDL_SCANCODE_UP;
	io.KeyMap[ ImGuiKey_DownArrow ] = SDL_SCANCODE_DOWN;
	io.KeyMap[ ImGuiKey_PageUp ] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ ImGuiKey_PageDown ] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ ImGuiKey_Home ] = SDL_SCANCODE_HOME;
	io.KeyMap[ ImGuiKey_End ] = SDL_SCANCODE_END;
	io.KeyMap[ ImGuiKey_Delete ] = SDLK_DELETE;
	io.KeyMap[ ImGuiKey_Backspace ] = SDLK_BACKSPACE;
	io.KeyMap[ ImGuiKey_Enter ] = SDLK_RETURN;
	io.KeyMap[ ImGuiKey_Escape ] = SDLK_ESCAPE;
	io.KeyMap[ ImGuiKey_A ] = SDLK_a;
	io.KeyMap[ ImGuiKey_C ] = SDLK_c;
	io.KeyMap[ ImGuiKey_V ] = SDLK_v;
	io.KeyMap[ ImGuiKey_X ] = SDLK_x;
	io.KeyMap[ ImGuiKey_Y ] = SDLK_y;
	io.KeyMap[ ImGuiKey_Z ] = SDLK_z;
	
	io.DisplaySize = ImVec2( w, h );
	io.SetClipboardTextFn = imgui_impl_SetClipboardText;
	io.GetClipboardTextFn = imgui_impl_GetClipboardText;
	io.ClipboardUserData = C;
	io.RenderDrawListsFn = imgui_impl_RenderDrawLists;
	
	return 0;
}

static int sgsimgui_SS_Event( SGS_CTX )
{
	sgs_Variable evtvar;
	SGSFN( "ImGui_SS_Event" );
	if( !sgs_LoadArgs( C, "v", &evtvar ) )
		return 0;
	
	sgsVariable ev( C, &evtvar );
	
	ImGuiIO& io = ImGui::GetIO();
	if( ev.is_object( ssi_WindowEvent ) )
	{
		SDL_WindowEvent* p = ev.get_object_data<SDL_WindowEvent>();
		if( p->event == SDL_WINDOWEVENT_RESIZED )
		{
			io.DisplaySize = ImVec2( p->data1, p->data2 );
		}
	}
	else if( ev.is_object( ssi_KeyboardEvent ) )
	{
		SDL_KeyboardEvent* p = ev.get_object_data<SDL_KeyboardEvent>();
		int key = p->keysym.sym & ~SDLK_SCANCODE_MASK;
		io.KeysDown[ key ] = p->type == SDL_KEYDOWN;
	}
	else if( ev.is_object( ssi_TextInputEvent ) )
	{
		SDL_TextInputEvent* p = ev.get_object_data<SDL_TextInputEvent>();
		io.AddInputCharactersUTF8( p->text );
	}
	else if( ev.is_object( ssi_MouseButtonEvent ) )
	{
		SS_MouseButtonEvent* p = ev.get_object_data<SS_MouseButtonEvent>();
		bool down = p->orig.type == SDL_MOUSEBUTTONDOWN;
		if( p->orig.button == SDL_BUTTON_LEFT )
			io.MouseDown[0] = down;
		if( p->orig.button == SDL_BUTTON_RIGHT )
			io.MouseDown[1] = down;
		if( p->orig.button == SDL_BUTTON_MIDDLE )
			io.MouseDown[2] = down;
	}
	else if( ev.is_object( ssi_MouseMotionEvent ) )
	{
		SS_MouseMotionEvent* p = ev.get_object_data<SS_MouseMotionEvent>();
		io.MousePos = ImVec2( p->x, p->y );
	}
	else if( ev.is_object( ssi_MouseWheelEvent ) )
	{
		SDL_MouseWheelEvent* p = ev.get_object_data<SDL_MouseWheelEvent>();
		io.MouseWheel += p->y;
	}
	return 0;
}

static sgs_RegFuncConst imgui_fconsts[] =
{
	{ "ImGui_SS_NewFrame", sgsimgui_SS_NewFrame },
	{ "ImGui_SS_Init", sgsimgui_SS_Init },
	{ "ImGui_SS_Event", sgsimgui_SS_Event },
	{ NULL, NULL },
};

extern void sgs_imgui_bind( SGS_CTX );

extern "C" SGS_DLL_EXPORT int sgscript_main( SGS_CTX )
{
	sgs_imgui_bind( C );
	sgs_RegFuncConsts( C, imgui_fconsts, -1 );
	return SGS_SUCCESS;
}

