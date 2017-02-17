
#include "imgui.hpp"


static int sgsImGui_NewFrame( SGS_CTX )
{
	SGSFN( "ImGui_NewFrame" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::NewFrame();
	return 0;
}

static int sgsImGui_Render( SGS_CTX )
{
	SGSFN( "ImGui_Render" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Render();
	return 0;
}

static int sgsImGui_Shutdown( SGS_CTX )
{
	SGSFN( "ImGui_Shutdown" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Shutdown();
	return 0;
}

static int sgsImGui_ShowUserGuide( SGS_CTX )
{
	SGSFN( "ImGui_ShowUserGuide" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ShowUserGuide();
	return 0;
}

static int sgsImGui_ShowTestWindow( SGS_CTX )
{
	SGSFN( "ImGui_ShowTestWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val0 = sgs_GetVar<bool>()( C, 0 );
	ImGui::ShowTestWindow(
		sgs_ItemType( C, 0 ) != SGS_VT_NULL ? &val0 : NULL
	);
	sgs_PushBool( C, val0 );
	return 1;
}

static int sgsImGui_ShowMetricsWindow( SGS_CTX )
{
	SGSFN( "ImGui_ShowMetricsWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val0 = sgs_GetVar<bool>()( C, 0 );
	ImGui::ShowMetricsWindow(
		sgs_ItemType( C, 0 ) != SGS_VT_NULL ? &val0 : NULL
	);
	sgs_PushBool( C, val0 );
	return 1;
}

static int sgsImGui_Begin( SGS_CTX )
{
	SGSFN( "ImGui_Begin" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Begin(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_ItemType( C, 1 ) != SGS_VT_NULL ? &val1 : NULL,
		3 <= ssz ? sgs_GetVar<ImGuiWindowFlags>()( C, 2 ) : 0
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsImGui_End( SGS_CTX )
{
	SGSFN( "ImGui_End" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::End();
	return 0;
}

static int sgsImGui_BeginChild( SGS_CTX )
{
	SGSFN( "ImGui_BeginChild" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginChild(
		ImGui::GetID( sgs_GetPtr( C, 0 ) ),
		3 <= ssz ? sgs_GetVar<ImVec2>()( C, 1 ) : ImVec2 ( 0 , 0 ),
		4 <= ssz ? sgs_GetVar<bool>()( C, 3 ) : false,
		5 <= ssz ? sgs_GetVar<ImGuiWindowFlags>()( C, 4 ) : 0
	) );
	return 1;
}

static int sgsImGui_EndChild( SGS_CTX )
{
	SGSFN( "ImGui_EndChild" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndChild();
	return 0;
}

static int sgsImGui_GetContentRegionMax( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionMax" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetContentRegionMax() );
	return 2;
}

static int sgsImGui_GetContentRegionAvail( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionAvail" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetContentRegionAvail() );
	return 2;
}

static int sgsImGui_GetContentRegionAvailWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionAvailWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetContentRegionAvailWidth() );
	return 1;
}

static int sgsImGui_GetWindowContentRegionMin( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionMin" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowContentRegionMin() );
	return 2;
}

static int sgsImGui_GetWindowContentRegionMax( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionMax" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowContentRegionMax() );
	return 2;
}

static int sgsImGui_GetWindowContentRegionWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowContentRegionWidth() );
	return 1;
}

static int sgsImGui_GetWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowPos() );
	return 2;
}

static int sgsImGui_GetWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowSize() );
	return 2;
}

static int sgsImGui_GetWindowWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowWidth() );
	return 1;
}

static int sgsImGui_GetWindowHeight( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowHeight" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetWindowHeight() );
	return 1;
}

static int sgsImGui_IsWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowCollapsed" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsWindowCollapsed() );
	return 1;
}

static int sgsImGui_SetWindowFontScale( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowFontScale" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowFontScale(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetNextWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowPos(
		sgs_GetVar<ImVec2>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 2 ) : 0
	);
	return 0;
}

static int sgsImGui_SetNextWindowPosCenter( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowPosCenter" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowPosCenter(
		1 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_SetNextWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowSize(
		sgs_GetVar<ImVec2>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 2 ) : 0
	);
	return 0;
}

static int sgsImGui_SetNextWindowContentSize( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowContentSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowContentSize(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetNextWindowContentWidth( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowContentWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowContentWidth(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetNextWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowCollapsed" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowCollapsed(
		sgs_GetVar<bool>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 1 ) : 0
	);
	return 0;
}

static int sgsImGui_SetNextWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowFocus" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextWindowFocus();
	return 0;
}

static int sgsImGui_SetCurrentWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowPos(
		sgs_GetVar<ImVec2>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 2 ) : 0
	);
	return 0;
}

static int sgsImGui_SetCurrentWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowSize(
		sgs_GetVar<ImVec2>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 2 ) : 0
	);
	return 0;
}

static int sgsImGui_SetCurrentWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowCollapsed" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowCollapsed(
		sgs_GetVar<bool>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 1 ) : 0
	);
	return 0;
}

static int sgsImGui_SetCurrentWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowFocus" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowFocus();
	return 0;
}

static int sgsImGui_SetWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowPos(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		4 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 3 ) : 0
	);
	return 0;
}

static int sgsImGui_SetWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowSize(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		4 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 3 ) : 0
	);
	return 0;
}

static int sgsImGui_SetWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowCollapsed" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowCollapsed(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 ),
		3 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 2 ) : 0
	);
	return 0;
}

static int sgsImGui_SetWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowFocus" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetWindowFocus(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_GetScrollX( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollX" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetScrollX() );
	return 1;
}

static int sgsImGui_GetScrollY( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetScrollY() );
	return 1;
}

static int sgsImGui_GetScrollMaxX( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollMaxX" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetScrollMaxX() );
	return 1;
}

static int sgsImGui_GetScrollMaxY( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollMaxY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetScrollMaxY() );
	return 1;
}

static int sgsImGui_SetScrollX( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollX" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetScrollX(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetScrollY( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetScrollY(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetScrollHere( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollHere" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetScrollHere(
		1 <= ssz ? sgs_GetVar<float>()( C, 0 ) : 0.5
	);
	return 0;
}

static int sgsImGui_SetScrollFromPosY( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollFromPosY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetScrollFromPosY(
		sgs_GetVar<float>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<float>()( C, 1 ) : 0.5
	);
	return 0;
}

static int sgsImGui_SetKeyboardFocusHere( SGS_CTX )
{
	SGSFN( "ImGui_SetKeyboardFocusHere" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetKeyboardFocusHere(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_PushFont( SGS_CTX )
{
	SGSFN( "ImGui_PushFont" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushFont(
		sgs_GetVar<ImFont *>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PopFont( SGS_CTX )
{
	SGSFN( "ImGui_PopFont" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopFont();
	return 0;
}

static int sgsImGui_PushStyleColor( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleColor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushStyleColor(
		sgs_GetVar<ImGuiCol>()( C, 0 ),
		sgs_GetVar<ImVec4>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_PopStyleColor( SGS_CTX )
{
	SGSFN( "ImGui_PopStyleColor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopStyleColor(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 1
	);
	return 0;
}

static int sgsImGui_PushStyleVarF( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleVarF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushStyleVar(
		sgs_GetVar<ImGuiStyleVar>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_PushStyleVarV2( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleVarV2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushStyleVar(
		sgs_GetVar<ImGuiStyleVar>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_PopStyleVar( SGS_CTX )
{
	SGSFN( "ImGui_PopStyleVar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopStyleVar(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 1
	);
	return 0;
}

static int sgsImGui_GetFont( SGS_CTX )
{
	SGSFN( "ImGui_GetFont" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetFont() );
	return 1;
}

static int sgsImGui_GetFontSize( SGS_CTX )
{
	SGSFN( "ImGui_GetFontSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetFontSize() );
	return 1;
}

static int sgsImGui_GetFontTexUvWhitePixel( SGS_CTX )
{
	SGSFN( "ImGui_GetFontTexUvWhitePixel" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetFontTexUvWhitePixel() );
	return 2;
}

static int sgsImGui_GetStyleColorU32( SGS_CTX )
{
	SGSFN( "ImGui_GetStyleColorU32" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColorU32(
		sgs_GetVar<ImGuiCol>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<float>()( C, 1 ) : 1
	) );
	return 1;
}

static int sgsImGui_GetColorU32( SGS_CTX )
{
	SGSFN( "ImGui_GetColorU32" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColorU32(
		sgs_GetVar<ImVec4>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_PushItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_PushItemWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushItemWidth(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PopItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_PopItemWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopItemWidth();
	return 0;
}

static int sgsImGui_CalcItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_CalcItemWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::CalcItemWidth() );
	return 1;
}

static int sgsImGui_PushTextWrapPos( SGS_CTX )
{
	SGSFN( "ImGui_PushTextWrapPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushTextWrapPos(
		1 <= ssz ? sgs_GetVar<float>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_PopTextWrapPos( SGS_CTX )
{
	SGSFN( "ImGui_PopTextWrapPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopTextWrapPos();
	return 0;
}

static int sgsImGui_PushAllowKeyboardFocus( SGS_CTX )
{
	SGSFN( "ImGui_PushAllowKeyboardFocus" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushAllowKeyboardFocus(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PopAllowKeyboardFocus( SGS_CTX )
{
	SGSFN( "ImGui_PopAllowKeyboardFocus" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopAllowKeyboardFocus();
	return 0;
}

static int sgsImGui_PushButtonRepeat( SGS_CTX )
{
	SGSFN( "ImGui_PushButtonRepeat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushButtonRepeat(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PopButtonRepeat( SGS_CTX )
{
	SGSFN( "ImGui_PopButtonRepeat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopButtonRepeat();
	return 0;
}

static int sgsImGui_Separator( SGS_CTX )
{
	SGSFN( "ImGui_Separator" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Separator();
	return 0;
}

static int sgsImGui_SameLine( SGS_CTX )
{
	SGSFN( "ImGui_SameLine" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SameLine(
		1 <= ssz ? sgs_GetVar<float>()( C, 0 ) : 0,
		2 <= ssz ? sgs_GetVar<float>()( C, 1 ) : - 1
	);
	return 0;
}

static int sgsImGui_NewLine( SGS_CTX )
{
	SGSFN( "ImGui_NewLine" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::NewLine();
	return 0;
}

static int sgsImGui_Spacing( SGS_CTX )
{
	SGSFN( "ImGui_Spacing" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Spacing();
	return 0;
}

static int sgsImGui_Dummy( SGS_CTX )
{
	SGSFN( "ImGui_Dummy" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Dummy(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_Indent( SGS_CTX )
{
	SGSFN( "ImGui_Indent" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Indent(
		1 <= ssz ? sgs_GetVar<float>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_Unindent( SGS_CTX )
{
	SGSFN( "ImGui_Unindent" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Unindent(
		1 <= ssz ? sgs_GetVar<float>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_BeginGroup( SGS_CTX )
{
	SGSFN( "ImGui_BeginGroup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::BeginGroup();
	return 0;
}

static int sgsImGui_EndGroup( SGS_CTX )
{
	SGSFN( "ImGui_EndGroup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndGroup();
	return 0;
}

static int sgsImGui_GetCursorPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetCursorPos() );
	return 2;
}

static int sgsImGui_GetCursorPosX( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPosX" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetCursorPosX() );
	return 1;
}

static int sgsImGui_GetCursorPosY( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPosY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetCursorPosY() );
	return 1;
}

static int sgsImGui_SetCursorPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetCursorPos(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetCursorPosX( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPosX" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetCursorPosX(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_SetCursorPosY( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPosY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetCursorPosY(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_GetCursorStartPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorStartPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetCursorStartPos() );
	return 2;
}

static int sgsImGui_GetCursorScreenPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorScreenPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetCursorScreenPos() );
	return 2;
}

static int sgsImGui_SetCursorScreenPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorScreenPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetCursorScreenPos(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_AlignFirstTextHeightToWidgets( SGS_CTX )
{
	SGSFN( "ImGui_AlignFirstTextHeightToWidgets" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::AlignFirstTextHeightToWidgets();
	return 0;
}

static int sgsImGui_GetTextLineHeight( SGS_CTX )
{
	SGSFN( "ImGui_GetTextLineHeight" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetTextLineHeight() );
	return 1;
}

static int sgsImGui_GetTextLineHeightWithSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetTextLineHeightWithSpacing" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetTextLineHeightWithSpacing() );
	return 1;
}

static int sgsImGui_GetItemsLineHeightWithSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetItemsLineHeightWithSpacing" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetItemsLineHeightWithSpacing() );
	return 1;
}

static int sgsImGui_Columns( SGS_CTX )
{
	SGSFN( "ImGui_Columns" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Columns(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 1,
		2 <= ssz ? sgs_GetVar<const char *>()( C, 1 ) : NULL,
		3 <= ssz ? sgs_GetVar<bool>()( C, 2 ) : true
	);
	return 0;
}

static int sgsImGui_NextColumn( SGS_CTX )
{
	SGSFN( "ImGui_NextColumn" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::NextColumn();
	return 0;
}

static int sgsImGui_GetColumnIndex( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnIndex" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColumnIndex() );
	return 1;
}

static int sgsImGui_GetColumnOffset( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnOffset" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColumnOffset(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : - 1
	) );
	return 1;
}

static int sgsImGui_SetColumnOffset( SGS_CTX )
{
	SGSFN( "ImGui_SetColumnOffset" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetColumnOffset(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_GetColumnWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnWidth" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColumnWidth(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : - 1
	) );
	return 1;
}

static int sgsImGui_GetColumnsCount( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnsCount" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetColumnsCount() );
	return 1;
}

static int sgsimgui_PushID( SGS_CTX )
{
	SGSFN( "ImGui_PushID" );
	ImGui::PushID( sgs_GetPtr( C, 0 ) );
	return 0;
}

static int sgsImGui_PopID( SGS_CTX )
{
	SGSFN( "ImGui_PopID" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopID();
	return 0;
}

static int sgsimgui_GetID( SGS_CTX )
{
	SGSFN( "ImGui_GetID" );
	sgs_PushInt( C, ImGui::GetID( sgs_GetPtr( C, 0 ) ) );
	return 1;
}

static int sgsImGui_Text( SGS_CTX )
{
	SGSFN( "ImGui_Text" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Text(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_TextColored( SGS_CTX )
{
	SGSFN( "ImGui_TextColored" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TextColored(
		sgs_GetVar<ImVec4>()( C, 0 ),
		"%s",
		sgs_GetVar<const char*>()( C, 4 )
	);
	return 0;
}

static int sgsImGui_TextDisabled( SGS_CTX )
{
	SGSFN( "ImGui_TextDisabled" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TextDisabled(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_TextWrapped( SGS_CTX )
{
	SGSFN( "ImGui_TextWrapped" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TextWrapped(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_TextUnformatted( SGS_CTX )
{
	SGSFN( "ImGui_TextUnformatted" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TextUnformatted(
		sgs_GetVar<const char *>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<const char *>()( C, 1 ) : NULL
	);
	return 0;
}

static int sgsImGui_LabelText( SGS_CTX )
{
	SGSFN( "ImGui_LabelText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LabelText(
		sgs_GetVar<const char *>()( C, 0 ),
		"%s",
		sgs_GetVar<const char*>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_Bullet( SGS_CTX )
{
	SGSFN( "ImGui_Bullet" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Bullet();
	return 0;
}

static int sgsImGui_BulletText( SGS_CTX )
{
	SGSFN( "ImGui_BulletText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::BulletText(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_Button( SGS_CTX )
{
	SGSFN( "ImGui_Button" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::Button(
		sgs_GetVar<const char *>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImVec2>()( C, 1 ) : ImVec2 ( 0 , 0 )
	) );
	return 1;
}

static int sgsImGui_SmallButton( SGS_CTX )
{
	SGSFN( "ImGui_SmallButton" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::SmallButton(
		sgs_GetVar<const char *>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_InvisibleButton( SGS_CTX )
{
	SGSFN( "ImGui_InvisibleButton" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::InvisibleButton(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	) );
	return 1;
}

static int sgsImGui_Image( SGS_CTX )
{
	SGSFN( "ImGui_Image" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Image(
		sgs_GetVar<ImTextureID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		5 <= ssz ? sgs_GetVar<ImVec2>()( C, 3 ) : ImVec2 ( 0 , 0 ),
		7 <= ssz ? sgs_GetVar<ImVec2>()( C, 5 ) : ImVec2 ( 1 , 1 ),
		11 <= ssz ? sgs_GetVar<ImVec4>()( C, 7 ) : ImVec4 ( 1 , 1 , 1 , 1 ),
		15 <= ssz ? sgs_GetVar<ImVec4>()( C, 11 ) : ImVec4 ( 0 , 0 , 0 , 0 )
	);
	return 0;
}

static int sgsImGui_ImageButton( SGS_CTX )
{
	SGSFN( "ImGui_ImageButton" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ImageButton(
		sgs_GetVar<ImTextureID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		5 <= ssz ? sgs_GetVar<ImVec2>()( C, 3 ) : ImVec2 ( 0 , 0 ),
		7 <= ssz ? sgs_GetVar<ImVec2>()( C, 5 ) : ImVec2 ( 1 , 1 ),
		8 <= ssz ? sgs_GetVar<int>()( C, 7 ) : - 1,
		12 <= ssz ? sgs_GetVar<ImVec4>()( C, 8 ) : ImVec4 ( 0 , 0 , 0 , 0 ),
		16 <= ssz ? sgs_GetVar<ImVec4>()( C, 12 ) : ImVec4 ( 1 , 1 , 1 , 1 )
	) );
	return 1;
}

static int sgsImGui_Checkbox( SGS_CTX )
{
	SGSFN( "ImGui_Checkbox" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Checkbox(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsImGui_CheckboxFlags( SGS_CTX )
{
	SGSFN( "ImGui_CheckboxFlags" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	unsigned val1 = sgs_GetVar<unsigned>()( C, 1 );
	sgs_PushVar( C, ImGui::CheckboxFlags(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<unsigned int>()( C, 2 )
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsimgui_RadioButton( SGS_CTX )
{
	SGSFN( "ImGui_RadioButton" );
	sgs_SizeVal ssz = sgs_StackSize( C );
	if( ssz == 2 ){ sgs_PushBool( C, ImGui::RadioButton( sgs_GetVar<const char*>()( C, 0 ), sgs_GetInt( C, 1 ) ) ); return 1; }
	else if( ssz == 3 )
	{
		int val = sgs_GetInt( C, 1 );
		sgs_PushBool( C, ImGui::RadioButton( sgs_GetVar<const char*>()( C, 0 ), &val, sgs_GetInt( C, 2 ) ) );
		sgs_PushInt( C, val );
		return 2;
	}
	else return sgs_Msg( C, SGS_WARNING, "expected 2 or 3 arguments, got %d", ssz );
}

static int sgsImGui_Combo( SGS_CTX )
{
	SGSFN( "ImGui_Combo" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::Combo(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<const char *>()( C, 2 ),
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : - 1
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsImGui_ComboCb( SGS_CTX )
{
	SGSFN( "ImGui_ComboCb" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	imgui_TextArrayCallbackData val2;
	val2.func = sgsVariable( C, 2 );
	sgs_PushVar( C, ImGui::Combo(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		_imgui_TextArrayCallback,
		&val2,
		sgs_GetVar<int>()( C, 3 ),
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : - 1
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsImGui_ColorButton( SGS_CTX )
{
	SGSFN( "ImGui_ColorButton" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ColorButton(
		sgs_GetVar<ImVec4>()( C, 0 ),
		5 <= ssz ? sgs_GetVar<bool>()( C, 4 ) : false,
		6 <= ssz ? sgs_GetVar<bool>()( C, 5 ) : true
	) );
	return 1;
}

static int sgsImGui_ColorEdit3( SGS_CTX )
{
	SGSFN( "ImGui_ColorEdit3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::ColorEdit3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsImGui_ColorEdit4( SGS_CTX )
{
	SGSFN( "ImGui_ColorEdit4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::ColorEdit4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		6 <= ssz ? sgs_GetVar<bool>()( C, 5 ) : true
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsImGui_ColorEditMode( SGS_CTX )
{
	SGSFN( "ImGui_ColorEditMode" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ColorEditMode(
		sgs_GetVar<ImGuiColorEditMode>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PlotLines( SGS_CTX )
{
	SGSFN( "ImGui_PlotLines" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	imgui_FloatArrayParser val1( C, 1 );
	ImGui::PlotLines(
		sgs_GetVar<const char *>()( C, 0 ),
		val1.values,
		val1.count,
		3 <= ssz ? sgs_GetVar<int>()( C, 2 ) : 0,
		4 <= ssz ? sgs_GetVar<const char *>()( C, 3 ) : NULL,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : FLT_MAX,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : FLT_MAX,
		8 <= ssz ? sgs_GetVar<ImVec2>()( C, 6 ) : ImVec2 ( 0 , 0 ),
		9 <= ssz ? sgs_GetVar<int>()( C, 8 ) : sizeof ( float )
	);
	return 0;
}

static int sgsImGui_PlotLinesCb( SGS_CTX )
{
	SGSFN( "ImGui_PlotLinesCb" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgsVariable val1( C, 1 );
	ImGui::PlotLines(
		sgs_GetVar<const char *>()( C, 0 ),
		_imgui_FloatArrayCallback,
		&val1,
		sgs_GetVar<int>()( C, 2 ),
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : 0,
		5 <= ssz ? sgs_GetVar<const char *>()( C, 4 ) : NULL,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : FLT_MAX,
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : FLT_MAX,
		9 <= ssz ? sgs_GetVar<ImVec2>()( C, 7 ) : ImVec2 ( 0 , 0 )
	);
	return 0;
}

static int sgsImGui_PlotHistogram( SGS_CTX )
{
	SGSFN( "ImGui_PlotHistogram" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	imgui_FloatArrayParser val1( C, 1 );
	ImGui::PlotHistogram(
		sgs_GetVar<const char *>()( C, 0 ),
		val1.values,
		val1.count,
		3 <= ssz ? sgs_GetVar<int>()( C, 2 ) : 0,
		4 <= ssz ? sgs_GetVar<const char *>()( C, 3 ) : NULL,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : FLT_MAX,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : FLT_MAX,
		8 <= ssz ? sgs_GetVar<ImVec2>()( C, 6 ) : ImVec2 ( 0 , 0 ),
		9 <= ssz ? sgs_GetVar<int>()( C, 8 ) : sizeof ( float )
	);
	return 0;
}

static int sgsImGui_PlotHistogramCb( SGS_CTX )
{
	SGSFN( "ImGui_PlotHistogramCb" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgsVariable val1( C, 1 );
	ImGui::PlotHistogram(
		sgs_GetVar<const char *>()( C, 0 ),
		_imgui_FloatArrayCallback,
		&val1,
		sgs_GetVar<int>()( C, 2 ),
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : 0,
		5 <= ssz ? sgs_GetVar<const char *>()( C, 4 ) : NULL,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : FLT_MAX,
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : FLT_MAX,
		9 <= ssz ? sgs_GetVar<ImVec2>()( C, 7 ) : ImVec2 ( 0 , 0 )
	);
	return 0;
}

static int sgsImGui_ProgressBar( SGS_CTX )
{
	SGSFN( "ImGui_ProgressBar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ProgressBar(
		sgs_GetVar<float>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImVec2>()( C, 1 ) : ImVec2 ( - 1 , 0 ),
		4 <= ssz ? sgs_GetVar<const char *>()( C, 3 ) : NULL
	);
	return 0;
}

static int sgsImGui_DragFloat( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::DragFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<float>()( C, 2 ) : 1,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 0,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<const char *>()( C, 5 ) : "%.3f",
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : 1
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsImGui_DragFloat2( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::DragFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 1,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.3f",
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsImGui_DragFloat3( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::DragFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 1,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : 0,
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : "%.3f",
		9 <= ssz ? sgs_GetVar<float>()( C, 8 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsImGui_DragFloat4( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::DragFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 1,
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : 0,
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 0,
		9 <= ssz ? sgs_GetVar<const char *>()( C, 8 ) : "%.3f",
		10 <= ssz ? sgs_GetVar<float>()( C, 9 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsImGui_DragFloatRange2( SGS_CTX )
{
	SGSFN( "ImGui_DragFloatRange2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1 = sgs_GetVar<float>()( C, 1 );
	float val2 = sgs_GetVar<float>()( C, 2 );
	sgs_PushVar( C, ImGui::DragFloatRange2(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		&val2,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 1,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.3f",
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : NULL,
		9 <= ssz ? sgs_GetVar<float>()( C, 8 ) : 1
	) );
	sgs_PushReal( C, val1 );
	sgs_PushReal( C, val2 );
	return 3;
}

static int sgsImGui_DragInt( SGS_CTX )
{
	SGSFN( "ImGui_DragInt" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::DragInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<float>()( C, 2 ) : 1,
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : 0,
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<const char *>()( C, 5 ) : "%.0f"
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsImGui_DragInt2( SGS_CTX )
{
	SGSFN( "ImGui_DragInt2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::DragInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 1,
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsImGui_DragInt3( SGS_CTX )
{
	SGSFN( "ImGui_DragInt3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::DragInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 1,
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<int>()( C, 6 ) : 0,
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsImGui_DragInt4( SGS_CTX )
{
	SGSFN( "ImGui_DragInt4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::DragInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 1,
		7 <= ssz ? sgs_GetVar<int>()( C, 6 ) : 0,
		8 <= ssz ? sgs_GetVar<int>()( C, 7 ) : 0,
		9 <= ssz ? sgs_GetVar<const char *>()( C, 8 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsImGui_DragIntRange2( SGS_CTX )
{
	SGSFN( "ImGui_DragIntRange2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	int val2 = sgs_GetVar<int>()( C, 2 );
	sgs_PushVar( C, ImGui::DragIntRange2(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		&val2,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 1,
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.0f",
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : NULL
	) );
	sgs_PushInt( C, val1 );
	sgs_PushInt( C, val2 );
	return 3;
}

static int sgsImGui_InputText( SGS_CTX )
{
	SGSFN( "ImGui_InputText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	size_t val1_size = sgs_GetInt( C, 2 );
	char* val1 = new char[ val1_size + 1 ];
	sgsString val1_src( C, 1 );
	size_t val1_cpsz = val1_size < val1_src.size() ? val1_size : val1_src.size();
	memcpy( val1, val1_src.c_str(), val1_cpsz );
	val1[ val1_cpsz ] = 0;
	sgs_PushVar( C, ImGui::InputText(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		val1_size,
		4 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 3 ) : 0,
		4 <= ssz ? NULL : NULL,
		5 <= ssz ? sgs_GetVar<void *>()( C, 4 ) : NULL
	) );
	val1[ val1_size ] = 0;
	sgs_PushString( C, val1 );
	return 2;
}

static int sgsImGui_InputTextMultiline( SGS_CTX )
{
	SGSFN( "ImGui_InputTextMultiline" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	size_t val1_size = sgs_GetInt( C, 2 );
	char* val1 = new char[ val1_size + 1 ];
	sgsString val1_src( C, 1 );
	size_t val1_cpsz = val1_size < val1_src.size() ? val1_size : val1_src.size();
	memcpy( val1, val1_src.c_str(), val1_cpsz );
	val1[ val1_cpsz ] = 0;
	sgs_PushVar( C, ImGui::InputTextMultiline(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		val1_size,
		5 <= ssz ? sgs_GetVar<ImVec2>()( C, 3 ) : ImVec2 ( 0 , 0 ),
		6 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 5 ) : 0,
		6 <= ssz ? NULL : NULL,
		7 <= ssz ? sgs_GetVar<void *>()( C, 6 ) : NULL
	) );
	val1[ val1_size ] = 0;
	sgs_PushString( C, val1 );
	return 2;
}

static int sgsImGui_InputFloat( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::InputFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<float>()( C, 2 ) : 0,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : 0,
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : - 1,
		6 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 5 ) : 0
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsImGui_InputFloat2( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::InputFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : - 1,
		5 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 4 ) : 0
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsImGui_InputFloat3( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::InputFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : - 1,
		6 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 5 ) : 0
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsImGui_InputFloat4( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::InputFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : - 1,
		7 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 6 ) : 0
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsImGui_InputInt( SGS_CTX )
{
	SGSFN( "ImGui_InputInt" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::InputInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<int>()( C, 2 ) : 1,
		4 <= ssz ? sgs_GetVar<int>()( C, 3 ) : 100,
		5 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 4 ) : 0
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsImGui_InputInt2( SGS_CTX )
{
	SGSFN( "ImGui_InputInt2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::InputInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		4 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 3 ) : 0
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsImGui_InputInt3( SGS_CTX )
{
	SGSFN( "ImGui_InputInt3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::InputInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		5 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 4 ) : 0
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsImGui_InputInt4( SGS_CTX )
{
	SGSFN( "ImGui_InputInt4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::InputInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		6 <= ssz ? sgs_GetVar<ImGuiInputTextFlags>()( C, 5 ) : 0
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsImGui_SliderFloat( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 ),
		5 <= ssz ? sgs_GetVar<const char *>()( C, 4 ) : "%.3f",
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 1
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsImGui_SliderFloat2( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::SliderFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<const char *>()( C, 5 ) : "%.3f",
		7 <= ssz ? sgs_GetVar<float>()( C, 6 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsImGui_SliderFloat3( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::SliderFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.3f",
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsImGui_SliderFloat4( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::SliderFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 ),
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : "%.3f",
		9 <= ssz ? sgs_GetVar<float>()( C, 8 ) : 1
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsImGui_SliderAngle( SGS_CTX )
{
	SGSFN( "ImGui_SliderAngle" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderAngle(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<float>()( C, 2 ) : - 360,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : + 360
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsImGui_SliderInt( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<int>()( C, 2 ),
		sgs_GetVar<int>()( C, 3 ),
		5 <= ssz ? sgs_GetVar<const char *>()( C, 4 ) : "%.0f"
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsImGui_SliderInt2( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::SliderInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<const char *>()( C, 5 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsImGui_SliderInt3( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt3" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::SliderInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsImGui_SliderInt4( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::SliderInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<int>()( C, 6 ),
		8 <= ssz ? sgs_GetVar<const char *>()( C, 7 ) : "%.0f"
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsImGui_VSliderFloat( SGS_CTX )
{
	SGSFN( "ImGui_VSliderFloat" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val3 = sgs_GetVar<float>()( C, 3 );
	sgs_PushVar( C, ImGui::VSliderFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		&val3,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.3f",
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 1
	) );
	sgs_PushReal( C, val3 );
	return 2;
}

static int sgsImGui_VSliderInt( SGS_CTX )
{
	SGSFN( "ImGui_VSliderInt" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val3 = sgs_GetVar<int>()( C, 3 );
	sgs_PushVar( C, ImGui::VSliderInt(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		&val3,
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		7 <= ssz ? sgs_GetVar<const char *>()( C, 6 ) : "%.0f"
	) );
	sgs_PushInt( C, val3 );
	return 2;
}

static int sgsimgui_TreeNode( SGS_CTX )
{
	SGSFN( "ImGui_TreeNode" );
	sgs_SizeVal ssz = sgs_StackSize( C );
	if( ssz == 1 ){ sgs_PushBool( C, ImGui::TreeNode( sgs_GetVar<const char*>()( C, 0 ) ) ); return 1; }
	else if( ssz == 2 ){ sgs_PushBool( C, ImGui::TreeNode( sgs_GetVar<void*>()( C, 0 ), "%s", sgs_GetVar<const char*>()( C, 1 ) ) ); return 1; }
	else return sgs_Msg( C, SGS_WARNING, "expected 1 or 2 arguments, got %d", ssz );
}

static int sgsimgui_TreeNodeEx( SGS_CTX )
{
	SGSFN( "ImGui_TreeNodeEx" );
	sgs_SizeVal ssz = sgs_StackSize( C );
	if( ssz == 2 ){ sgs_PushBool( C, ImGui::TreeNodeEx( sgs_GetVar<const char*>()( C, 0 ), sgs_GetInt( C, 1 ) ) ); return 1; }
	else if( ssz == 3 ){ sgs_PushBool( C, ImGui::TreeNodeEx( sgs_GetVar<void*>()( C, 0 ), sgs_GetInt( C, 1 ), "%s", sgs_GetVar<const char*>()( C, 2 ) ) ); return 1; }
	else return sgs_Msg( C, SGS_WARNING, "expected 1 or 2 arguments, got %d", ssz );
}

static int sgsImGui_TreePush( SGS_CTX )
{
	SGSFN( "ImGui_TreePush" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TreePush(
		1 <= ssz ? sgs_GetVar<const void *>()( C, 0 ) : NULL
	);
	return 0;
}

static int sgsImGui_TreePop( SGS_CTX )
{
	SGSFN( "ImGui_TreePop" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TreePop();
	return 0;
}

static int sgsImGui_TreeAdvanceToLabelPos( SGS_CTX )
{
	SGSFN( "ImGui_TreeAdvanceToLabelPos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::TreeAdvanceToLabelPos();
	return 0;
}

static int sgsImGui_GetTreeNodeToLabelSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetTreeNodeToLabelSpacing" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetTreeNodeToLabelSpacing() );
	return 1;
}

static int sgsImGui_SetNextTreeNodeOpen( SGS_CTX )
{
	SGSFN( "ImGui_SetNextTreeNodeOpen" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetNextTreeNodeOpen(
		sgs_GetVar<bool>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<ImGuiSetCond>()( C, 1 ) : 0
	);
	return 0;
}

static int sgsImGui_CollapsingHeader( SGS_CTX )
{
	SGSFN( "ImGui_CollapsingHeader" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::CollapsingHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<ImGuiTreeNodeFlags>()( C, 1 ) : 0
	) );
	return 1;
}

static int sgsImGui_CollapsingHeaderCloseable( SGS_CTX )
{
	SGSFN( "ImGui_CollapsingHeaderCloseable" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::CollapsingHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<ImGuiTreeNodeFlags>()( C, 2 ) : 0
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsImGui_Selectable( SGS_CTX )
{
	SGSFN( "ImGui_Selectable" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Selectable(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		3 <= ssz ? sgs_GetVar<ImGuiSelectableFlags>()( C, 2 ) : 0,
		5 <= ssz ? sgs_GetVar<ImVec2>()( C, 3 ) : ImVec2 ( 0 , 0 )
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsImGui_ListBoxHeader( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxHeader" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ListBoxHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<ImVec2>()( C, 1 ) : ImVec2 ( 0 , 0 )
	) );
	return 1;
}

static int sgsImGui_ListBoxHeader2( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxHeader2" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ListBoxHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 ),
		3 <= ssz ? sgs_GetVar<int>()( C, 2 ) : - 1
	) );
	return 1;
}

static int sgsImGui_ListBoxFooter( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxFooter" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ListBoxFooter();
	return 0;
}

static int sgsImGui_ValueB( SGS_CTX )
{
	SGSFN( "ImGui_ValueB" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_ValueI( SGS_CTX )
{
	SGSFN( "ImGui_ValueI" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_ValueU( SGS_CTX )
{
	SGSFN( "ImGui_ValueU" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<unsigned int>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_ValueF( SGS_CTX )
{
	SGSFN( "ImGui_ValueF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		3 <= ssz ? sgs_GetVar<const char *>()( C, 2 ) : NULL
	);
	return 0;
}

static int sgsImGui_ValueColorF( SGS_CTX )
{
	SGSFN( "ImGui_ValueColorF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ValueColor(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec4>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_ValueColor( SGS_CTX )
{
	SGSFN( "ImGui_ValueColor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ValueColor(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImU32>()( C, 1 )
	);
	return 0;
}

static int sgsImGui_SetTooltip( SGS_CTX )
{
	SGSFN( "ImGui_SetTooltip" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetTooltip(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_BeginTooltip( SGS_CTX )
{
	SGSFN( "ImGui_BeginTooltip" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::BeginTooltip();
	return 0;
}

static int sgsImGui_EndTooltip( SGS_CTX )
{
	SGSFN( "ImGui_EndTooltip" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndTooltip();
	return 0;
}

static int sgsImGui_BeginMainMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_BeginMainMenuBar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginMainMenuBar() );
	return 1;
}

static int sgsImGui_EndMainMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_EndMainMenuBar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndMainMenuBar();
	return 0;
}

static int sgsImGui_BeginMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_BeginMenuBar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginMenuBar() );
	return 1;
}

static int sgsImGui_EndMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_EndMenuBar" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndMenuBar();
	return 0;
}

static int sgsImGui_BeginMenu( SGS_CTX )
{
	SGSFN( "ImGui_BeginMenu" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginMenu(
		sgs_GetVar<const char *>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<bool>()( C, 1 ) : true
	) );
	return 1;
}

static int sgsImGui_EndMenu( SGS_CTX )
{
	SGSFN( "ImGui_EndMenu" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndMenu();
	return 0;
}

static int sgsImGui_MenuItem( SGS_CTX )
{
	SGSFN( "ImGui_MenuItem" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val2 = sgs_GetVar<bool>()( C, 2 );
	sgs_PushVar( C, ImGui::MenuItem(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 ),
		&val2,
		4 <= ssz ? sgs_GetVar<bool>()( C, 3 ) : true
	) );
	sgs_PushBool( C, val2 );
	return 2;
}

static int sgsImGui_OpenPopup( SGS_CTX )
{
	SGSFN( "ImGui_OpenPopup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::OpenPopup(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_BeginPopup( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginPopup(
		sgs_GetVar<const char *>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_BeginPopupModal( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupModal" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::BeginPopupModal(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_ItemType( C, 1 ) != SGS_VT_NULL ? &val1 : NULL,
		3 <= ssz ? sgs_GetVar<ImGuiWindowFlags>()( C, 2 ) : 0
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsImGui_BeginPopupContextItem( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextItem" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginPopupContextItem(
		sgs_GetVar<const char *>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<int>()( C, 1 ) : 1
	) );
	return 1;
}

static int sgsImGui_BeginPopupContextWindow( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginPopupContextWindow(
		1 <= ssz ? sgs_GetVar<bool>()( C, 0 ) : true,
		2 <= ssz ? sgs_GetVar<const char *>()( C, 1 ) : NULL,
		3 <= ssz ? sgs_GetVar<int>()( C, 2 ) : 1
	) );
	return 1;
}

static int sgsImGui_BeginPopupContextVoid( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextVoid" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginPopupContextVoid(
		1 <= ssz ? sgs_GetVar<const char *>()( C, 0 ) : NULL,
		2 <= ssz ? sgs_GetVar<int>()( C, 1 ) : 1
	) );
	return 1;
}

static int sgsImGui_EndPopup( SGS_CTX )
{
	SGSFN( "ImGui_EndPopup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndPopup();
	return 0;
}

static int sgsImGui_CloseCurrentPopup( SGS_CTX )
{
	SGSFN( "ImGui_CloseCurrentPopup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::CloseCurrentPopup();
	return 0;
}

static int sgsImGui_LogToTTY( SGS_CTX )
{
	SGSFN( "ImGui_LogToTTY" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogToTTY(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : - 1
	);
	return 0;
}

static int sgsImGui_LogToFile( SGS_CTX )
{
	SGSFN( "ImGui_LogToFile" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogToFile(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : - 1,
		2 <= ssz ? sgs_GetVar<const char *>()( C, 1 ) : NULL
	);
	return 0;
}

static int sgsImGui_LogToClipboard( SGS_CTX )
{
	SGSFN( "ImGui_LogToClipboard" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogToClipboard(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : - 1
	);
	return 0;
}

static int sgsImGui_LogFinish( SGS_CTX )
{
	SGSFN( "ImGui_LogFinish" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogFinish();
	return 0;
}

static int sgsImGui_LogButtons( SGS_CTX )
{
	SGSFN( "ImGui_LogButtons" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogButtons();
	return 0;
}

static int sgsImGui_LogText( SGS_CTX )
{
	SGSFN( "ImGui_LogText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::LogText(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_PushClipRect( SGS_CTX )
{
	SGSFN( "ImGui_PushClipRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PushClipRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<bool>()( C, 4 )
	);
	return 0;
}

static int sgsImGui_PopClipRect( SGS_CTX )
{
	SGSFN( "ImGui_PopClipRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::PopClipRect();
	return 0;
}

static int sgsImGui_IsItemHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsItemHovered" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsItemHovered() );
	return 1;
}

static int sgsImGui_IsItemHoveredRect( SGS_CTX )
{
	SGSFN( "ImGui_IsItemHoveredRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsItemHoveredRect() );
	return 1;
}

static int sgsImGui_IsItemActive( SGS_CTX )
{
	SGSFN( "ImGui_IsItemActive" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsItemActive() );
	return 1;
}

static int sgsImGui_IsItemClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsItemClicked" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsItemClicked(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 0
	) );
	return 1;
}

static int sgsImGui_IsItemVisible( SGS_CTX )
{
	SGSFN( "ImGui_IsItemVisible" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsItemVisible() );
	return 1;
}

static int sgsImGui_IsAnyItemHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsAnyItemHovered" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsAnyItemHovered() );
	return 1;
}

static int sgsImGui_IsAnyItemActive( SGS_CTX )
{
	SGSFN( "ImGui_IsAnyItemActive" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsAnyItemActive() );
	return 1;
}

static int sgsImGui_GetItemRectMin( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectMin" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetItemRectMin() );
	return 2;
}

static int sgsImGui_GetItemRectMax( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectMax" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetItemRectMax() );
	return 2;
}

static int sgsImGui_GetItemRectSize( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetItemRectSize() );
	return 2;
}

static int sgsImGui_SetItemAllowOverlap( SGS_CTX )
{
	SGSFN( "ImGui_SetItemAllowOverlap" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetItemAllowOverlap();
	return 0;
}

static int sgsImGui_IsWindowHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowHovered" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsWindowHovered() );
	return 1;
}

static int sgsImGui_IsWindowFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowFocused" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsWindowFocused() );
	return 1;
}

static int sgsImGui_IsRootWindowFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowFocused" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsRootWindowFocused() );
	return 1;
}

static int sgsImGui_IsRootWindowOrAnyChildFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowOrAnyChildFocused" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsRootWindowOrAnyChildFocused() );
	return 1;
}

static int sgsImGui_IsRootWindowOrAnyChildHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowOrAnyChildHovered" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsRootWindowOrAnyChildHovered() );
	return 1;
}

static int sgsImGui_IsRectVisible( SGS_CTX )
{
	SGSFN( "ImGui_IsRectVisible" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsRectVisible(
		sgs_GetVar<ImVec2>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsRectVisibleScreen( SGS_CTX )
{
	SGSFN( "ImGui_IsRectVisibleScreen" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsRectVisible(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 )
	) );
	return 1;
}

static int sgsImGui_IsPosHoveringAnyWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsPosHoveringAnyWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsPosHoveringAnyWindow(
		sgs_GetVar<ImVec2>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_GetTime( SGS_CTX )
{
	SGSFN( "ImGui_GetTime" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetTime() );
	return 1;
}

static int sgsImGui_GetFrameCount( SGS_CTX )
{
	SGSFN( "ImGui_GetFrameCount" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetFrameCount() );
	return 1;
}

static int sgsImGui_GetStyleColName( SGS_CTX )
{
	SGSFN( "ImGui_GetStyleColName" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetStyleColName(
		sgs_GetVar<ImGuiCol>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_CalcItemRectClosestPoint( SGS_CTX )
{
	SGSFN( "ImGui_CalcItemRectClosestPoint" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::CalcItemRectClosestPoint(
		sgs_GetVar<ImVec2>()( C, 0 ),
		3 <= ssz ? sgs_GetVar<bool>()( C, 2 ) : false,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : + 0
	) );
	return 2;
}

static int sgsImGui_CalcTextSize( SGS_CTX )
{
	SGSFN( "ImGui_CalcTextSize" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::CalcTextSize(
		sgs_GetVar<const char *>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<const char *>()( C, 1 ) : NULL,
		3 <= ssz ? sgs_GetVar<bool>()( C, 2 ) : false,
		4 <= ssz ? sgs_GetVar<float>()( C, 3 ) : - 1
	) );
	return 2;
}

static int sgsImGui_CalcListClipping( SGS_CTX )
{
	SGSFN( "ImGui_CalcListClipping" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	int val2 = sgs_GetVar<int>()( C, 2 );
	int val3 = sgs_GetVar<int>()( C, 3 );
	ImGui::CalcListClipping(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		&val2,
		&val3
	);
	sgs_PushInt( C, val2 );
	sgs_PushInt( C, val3 );
	return 2;
}

static int sgsImGui_BeginChildFrame( SGS_CTX )
{
	SGSFN( "ImGui_BeginChildFrame" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::BeginChildFrame(
		ImGui::GetID( sgs_GetPtr( C, 0 ) ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		4 <= ssz ? sgs_GetVar<ImGuiWindowFlags>()( C, 3 ) : 0
	) );
	return 1;
}

static int sgsImGui_EndChildFrame( SGS_CTX )
{
	SGSFN( "ImGui_EndChildFrame" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::EndChildFrame();
	return 0;
}

static int sgsImGui_ColorConvertU32ToFloat4( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertU32ToFloat4" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ColorConvertU32ToFloat4(
		sgs_GetVar<ImU32>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_ColorConvertFloat4ToU32( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertFloat4ToU32" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::ColorConvertFloat4ToU32(
		sgs_GetVar<ImVec4>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_ColorConvertRGBtoHSV( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertRGBtoHSV" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val3 = sgs_GetVar<float>()( C, 3 );
	float val4 = sgs_GetVar<float>()( C, 4 );
	float val5 = sgs_GetVar<float>()( C, 5 );
	ImGui::ColorConvertRGBtoHSV(
		sgs_GetVar<float>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		sgs_GetVar<float>()( C, 2 ),
		val3,
		val4,
		val5
	);
	sgs_PushReal( C, val3 );
	sgs_PushReal( C, val4 );
	sgs_PushReal( C, val5 );
	return 3;
}

static int sgsImGui_ColorConvertHSVtoRGB( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertHSVtoRGB" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	float val3 = sgs_GetVar<float>()( C, 3 );
	float val4 = sgs_GetVar<float>()( C, 4 );
	float val5 = sgs_GetVar<float>()( C, 5 );
	ImGui::ColorConvertHSVtoRGB(
		sgs_GetVar<float>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		sgs_GetVar<float>()( C, 2 ),
		val3,
		val4,
		val5
	);
	sgs_PushReal( C, val3 );
	sgs_PushReal( C, val4 );
	sgs_PushReal( C, val5 );
	return 3;
}

static int sgsImGui_GetKeyIndex( SGS_CTX )
{
	SGSFN( "ImGui_GetKeyIndex" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetKeyIndex(
		sgs_GetVar<ImGuiKey>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsKeyDown( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyDown" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsKeyDown(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsKeyPressed( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyPressed" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsKeyPressed(
		sgs_GetVar<int>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<bool>()( C, 1 ) : true
	) );
	return 1;
}

static int sgsImGui_IsKeyReleased( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyReleased" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsKeyReleased(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsMouseDown( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDown" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseDown(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsMouseClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseClicked" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseClicked(
		sgs_GetVar<int>()( C, 0 ),
		2 <= ssz ? sgs_GetVar<bool>()( C, 1 ) : false
	) );
	return 1;
}

static int sgsImGui_IsMouseDoubleClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDoubleClicked" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseDoubleClicked(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsMouseReleased( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseReleased" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseReleased(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_IsMouseHoveringWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseHoveringWindow() );
	return 1;
}

static int sgsImGui_IsMouseHoveringAnyWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringAnyWindow" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseHoveringAnyWindow() );
	return 1;
}

static int sgsImGui_IsMouseHoveringRect( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseHoveringRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		5 <= ssz ? sgs_GetVar<bool>()( C, 4 ) : true
	) );
	return 1;
}

static int sgsImGui_IsMouseDragging( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDragging" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::IsMouseDragging(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 0,
		2 <= ssz ? sgs_GetVar<float>()( C, 1 ) : - 1
	) );
	return 1;
}

static int sgsImGui_GetMousePos( SGS_CTX )
{
	SGSFN( "ImGui_GetMousePos" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetMousePos() );
	return 2;
}

static int sgsImGui_GetMousePosOnOpeningCurrentPopup( SGS_CTX )
{
	SGSFN( "ImGui_GetMousePosOnOpeningCurrentPopup" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetMousePosOnOpeningCurrentPopup() );
	return 2;
}

static int sgsImGui_GetMouseDragDelta( SGS_CTX )
{
	SGSFN( "ImGui_GetMouseDragDelta" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetMouseDragDelta(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 0,
		2 <= ssz ? sgs_GetVar<float>()( C, 1 ) : - 1
	) );
	return 2;
}

static int sgsImGui_ResetMouseDragDelta( SGS_CTX )
{
	SGSFN( "ImGui_ResetMouseDragDelta" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::ResetMouseDragDelta(
		1 <= ssz ? sgs_GetVar<int>()( C, 0 ) : 0
	);
	return 0;
}

static int sgsImGui_GetMouseCursor( SGS_CTX )
{
	SGSFN( "ImGui_GetMouseCursor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetMouseCursor() );
	return 1;
}

static int sgsImGui_SetMouseCursor( SGS_CTX )
{
	SGSFN( "ImGui_SetMouseCursor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetMouseCursor(
		sgs_GetVar<ImGuiMouseCursor>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_CaptureKeyboardFromApp( SGS_CTX )
{
	SGSFN( "ImGui_CaptureKeyboardFromApp" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::CaptureKeyboardFromApp(
		1 <= ssz ? sgs_GetVar<bool>()( C, 0 ) : true
	);
	return 0;
}

static int sgsImGui_CaptureMouseFromApp( SGS_CTX )
{
	SGSFN( "ImGui_CaptureMouseFromApp" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::CaptureMouseFromApp(
		1 <= ssz ? sgs_GetVar<bool>()( C, 0 ) : true
	);
	return 0;
}

static int sgsImGui_MemAlloc( SGS_CTX )
{
	SGSFN( "ImGui_MemAlloc" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::MemAlloc(
		sgs_GetVar<size_t>()( C, 0 )
	) );
	return 1;
}

static int sgsImGui_MemFree( SGS_CTX )
{
	SGSFN( "ImGui_MemFree" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::MemFree(
		sgs_GetVar<void *>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_GetClipboardText( SGS_CTX )
{
	SGSFN( "ImGui_GetClipboardText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetClipboardText() );
	return 1;
}

static int sgsImGui_SetClipboardText( SGS_CTX )
{
	SGSFN( "ImGui_SetClipboardText" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::SetClipboardText(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsImGui_GetVersion( SGS_CTX )
{
	SGSFN( "ImGui_GetVersion" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetVersion() );
	return 1;
}

static int sgsImDrawList_PushClipRect( SGS_CTX )
{
	SGSFN( "ImDrawList_PushClipRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PushClipRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		5 <= ssz ? sgs_GetVar<bool>()( C, 4 ) : false
	);
	return 0;
}

static int sgsImDrawList_PushClipRectFullScreen( SGS_CTX )
{
	SGSFN( "ImDrawList_PushClipRectFullScreen" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PushClipRectFullScreen();
	return 0;
}

static int sgsImDrawList_PopClipRect( SGS_CTX )
{
	SGSFN( "ImDrawList_PopClipRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PopClipRect();
	return 0;
}

static int sgsImDrawList_PopTextureID( SGS_CTX )
{
	SGSFN( "ImDrawList_PopTextureID" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PopTextureID();
	return 0;
}

static int sgsImDrawList_AddLine( SGS_CTX )
{
	SGSFN( "ImDrawList_AddLine" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddLine(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 1
	);
	return 0;
}

static int sgsImDrawList_AddRect( SGS_CTX )
{
	SGSFN( "ImDrawList_AddRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<int>()( C, 6 ) : ~ 0,
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 1
	);
	return 0;
}

static int sgsImDrawList_AddRectFilled( SGS_CTX )
{
	SGSFN( "ImDrawList_AddRectFilled" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddRectFilled(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 0,
		7 <= ssz ? sgs_GetVar<int>()( C, 6 ) : ~ 0
	);
	return 0;
}

static int sgsImDrawList_AddRectFilledMultiColor( SGS_CTX )
{
	SGSFN( "ImDrawList_AddRectFilledMultiColor" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddRectFilledMultiColor(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 ),
		sgs_GetVar<ImU32>()( C, 5 ),
		sgs_GetVar<ImU32>()( C, 6 ),
		sgs_GetVar<ImU32>()( C, 7 )
	);
	return 0;
}

static int sgsImDrawList_AddQuad( SGS_CTX )
{
	SGSFN( "ImDrawList_AddQuad" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddQuad(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImVec2>()( C, 6 ),
		sgs_GetVar<ImU32>()( C, 8 ),
		10 <= ssz ? sgs_GetVar<float>()( C, 9 ) : 1
	);
	return 0;
}

static int sgsImDrawList_AddQuadFilled( SGS_CTX )
{
	SGSFN( "ImDrawList_AddQuadFilled" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddQuadFilled(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImVec2>()( C, 6 ),
		sgs_GetVar<ImU32>()( C, 8 )
	);
	return 0;
}

static int sgsImDrawList_AddTriangle( SGS_CTX )
{
	SGSFN( "ImDrawList_AddTriangle" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddTriangle(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImU32>()( C, 6 ),
		8 <= ssz ? sgs_GetVar<float>()( C, 7 ) : 1
	);
	return 0;
}

static int sgsImDrawList_AddTriangleFilled( SGS_CTX )
{
	SGSFN( "ImDrawList_AddTriangleFilled" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddTriangleFilled(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImU32>()( C, 6 )
	);
	return 0;
}

static int sgsImDrawList_AddCircle( SGS_CTX )
{
	SGSFN( "ImDrawList_AddCircle" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddCircle(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 3 ),
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : 12,
		6 <= ssz ? sgs_GetVar<float>()( C, 5 ) : 1
	);
	return 0;
}

static int sgsImDrawList_AddCircleFilled( SGS_CTX )
{
	SGSFN( "ImDrawList_AddCircleFilled" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddCircleFilled(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 3 ),
		5 <= ssz ? sgs_GetVar<int>()( C, 4 ) : 12
	);
	return 0;
}

static int sgsImDrawList_AddImage( SGS_CTX )
{
	SGSFN( "ImDrawList_AddImage" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddImage(
		sgs_GetVar<ImTextureID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImVec2>()( C, 3 ),
		7 <= ssz ? sgs_GetVar<ImVec2>()( C, 5 ) : ImVec2 ( 0 , 0 ),
		9 <= ssz ? sgs_GetVar<ImVec2>()( C, 7 ) : ImVec2 ( 1 , 1 ),
		10 <= ssz ? sgs_GetVar<ImU32>()( C, 9 ) : 4294967295U
	);
	return 0;
}

static int sgsImDrawList_AddBezierCurve( SGS_CTX )
{
	SGSFN( "ImDrawList_AddBezierCurve" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddBezierCurve(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImVec2>()( C, 6 ),
		sgs_GetVar<ImU32>()( C, 8 ),
		sgs_GetVar<float>()( C, 9 ),
		11 <= ssz ? sgs_GetVar<int>()( C, 10 ) : 0
	);
	return 0;
}

static int sgsImDrawList_PathClear( SGS_CTX )
{
	SGSFN( "ImDrawList_PathClear" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathClear();
	return 0;
}

static int sgsImDrawList_PathLineTo( SGS_CTX )
{
	SGSFN( "ImDrawList_PathLineTo" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathLineTo(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_PathLineToMergeDuplicate( SGS_CTX )
{
	SGSFN( "ImDrawList_PathLineToMergeDuplicate" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathLineToMergeDuplicate(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_PathFill( SGS_CTX )
{
	SGSFN( "ImDrawList_PathFill" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathFill(
		sgs_GetVar<ImU32>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_PathStroke( SGS_CTX )
{
	SGSFN( "ImDrawList_PathStroke" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathStroke(
		sgs_GetVar<ImU32>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 ),
		3 <= ssz ? sgs_GetVar<float>()( C, 2 ) : 1
	);
	return 0;
}

static int sgsImDrawList_PathArcTo( SGS_CTX )
{
	SGSFN( "ImDrawList_PathArcTo" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathArcTo(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : 10
	);
	return 0;
}

static int sgsImDrawList_PathArcToFast( SGS_CTX )
{
	SGSFN( "ImDrawList_PathArcToFast" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathArcToFast(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 )
	);
	return 0;
}

static int sgsImDrawList_PathBezierCurveTo( SGS_CTX )
{
	SGSFN( "ImDrawList_PathBezierCurveTo" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathBezierCurveTo(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		7 <= ssz ? sgs_GetVar<int>()( C, 6 ) : 0
	);
	return 0;
}

static int sgsImDrawList_PathRect( SGS_CTX )
{
	SGSFN( "ImDrawList_PathRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PathRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		5 <= ssz ? sgs_GetVar<float>()( C, 4 ) : 0,
		6 <= ssz ? sgs_GetVar<int>()( C, 5 ) : ~ 0
	);
	return 0;
}

static int sgsImDrawList_ChannelsSplit( SGS_CTX )
{
	SGSFN( "ImDrawList_ChannelsSplit" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->ChannelsSplit(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_ChannelsMerge( SGS_CTX )
{
	SGSFN( "ImDrawList_ChannelsMerge" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->ChannelsMerge();
	return 0;
}

static int sgsImDrawList_ChannelsSetCurrent( SGS_CTX )
{
	SGSFN( "ImDrawList_ChannelsSetCurrent" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->ChannelsSetCurrent(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_AddCallback( SGS_CTX )
{
	SGSFN( "ImDrawList_AddCallback" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgsVariable val0( C, 0 );
	ImGui::GetWindowDrawList()->AddCallback(
		imgui_DrawCallback,
		new sgsVariable( val0 )
	);
	return 0;
}

static int sgsImDrawList_AddDrawCmd( SGS_CTX )
{
	SGSFN( "ImDrawList_AddDrawCmd" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->AddDrawCmd();
	return 0;
}

static int sgsImDrawList_Clear( SGS_CTX )
{
	SGSFN( "ImDrawList_Clear" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->Clear();
	return 0;
}

static int sgsImDrawList_ClearFreeMemory( SGS_CTX )
{
	SGSFN( "ImDrawList_ClearFreeMemory" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->ClearFreeMemory();
	return 0;
}

static int sgsImDrawList_PrimReserve( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimReserve" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimReserve(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 )
	);
	return 0;
}

static int sgsImDrawList_PrimRect( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 )
	);
	return 0;
}

static int sgsImDrawList_PrimRectUV( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimRectUV" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimRectUV(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImVec2>()( C, 6 ),
		sgs_GetVar<ImU32>()( C, 8 )
	);
	return 0;
}

static int sgsImDrawList_PrimQuadUV( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimQuadUV" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimQuadUV(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 4 ),
		sgs_GetVar<ImVec2>()( C, 6 ),
		sgs_GetVar<ImVec2>()( C, 8 ),
		sgs_GetVar<ImVec2>()( C, 10 ),
		sgs_GetVar<ImVec2>()( C, 12 ),
		sgs_GetVar<ImVec2>()( C, 14 ),
		sgs_GetVar<ImU32>()( C, 16 )
	);
	return 0;
}

static int sgsImDrawList_PrimWriteVtx( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimWriteVtx" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimWriteVtx(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 )
	);
	return 0;
}

static int sgsImDrawList_PrimWriteIdx( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimWriteIdx" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimWriteIdx(
		sgs_GetVar<ImDrawIdx>()( C, 0 )
	);
	return 0;
}

static int sgsImDrawList_PrimVtx( SGS_CTX )
{
	SGSFN( "ImDrawList_PrimVtx" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->PrimVtx(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<ImU32>()( C, 4 )
	);
	return 0;
}

static int sgsImDrawList_UpdateClipRect( SGS_CTX )
{
	SGSFN( "ImDrawList_UpdateClipRect" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->UpdateClipRect();
	return 0;
}

static int sgsImDrawList_UpdateTextureID( SGS_CTX )
{
	SGSFN( "ImDrawList_UpdateTextureID" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetWindowDrawList()->UpdateTextureID();
	return 0;
}

static int sgsImFontAtlas_AddFont( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFont" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFont(
		NULL) );
	return 1;
}

static int sgsImFontAtlas_AddFontDefault( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFontDefault" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFontDefault(
		0 <= ssz ? NULL : NULL) );
	return 1;
}

static int sgsImFontAtlas_AddFontFromFileTTF( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFontFromFileTTF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFontFromFileTTF(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		2 <= ssz ? NULL : NULL,
		2 <= ssz ? NULL : NULL
	) );
	return 1;
}

static int sgsImFontAtlas_AddFontFromMemoryTTF( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFontFromMemoryTTF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
		sgs_GetVar<void *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 ),
		sgs_GetVar<float>()( C, 2 ),
		3 <= ssz ? NULL : NULL,
		3 <= ssz ? NULL : NULL
	) );
	return 1;
}

static int sgsImFontAtlas_AddFontFromMemoryCompressedTTF( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFontFromMemoryCompressedTTF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		sgs_GetVar<const void *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 ),
		sgs_GetVar<float>()( C, 2 ),
		3 <= ssz ? NULL : NULL,
		3 <= ssz ? NULL : NULL
	) );
	return 1;
}

static int sgsImFontAtlas_AddFontFromMemoryCompressedBase85TTF( SGS_CTX )
{
	SGSFN( "ImFontAtlas_AddFontFromMemoryCompressedBase85TTF" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		2 <= ssz ? NULL : NULL,
		2 <= ssz ? NULL : NULL
	) );
	return 1;
}

static int sgsImFontAtlas_ClearTexData( SGS_CTX )
{
	SGSFN( "ImFontAtlas_ClearTexData" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->ClearTexData();
	return 0;
}

static int sgsImFontAtlas_ClearInputData( SGS_CTX )
{
	SGSFN( "ImFontAtlas_ClearInputData" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->ClearInputData();
	return 0;
}

static int sgsImFontAtlas_ClearFonts( SGS_CTX )
{
	SGSFN( "ImFontAtlas_ClearFonts" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->ClearFonts();
	return 0;
}

static int sgsImFontAtlas_Clear( SGS_CTX )
{
	SGSFN( "ImFontAtlas_Clear" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->Clear();
	return 0;
}

static int sgsImFontAtlas_SetTexID( SGS_CTX )
{
	SGSFN( "ImFontAtlas_SetTexID" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->SetTexID(
		sgs_GetVar<void *>()( C, 0 )
	);
	return 0;
}

static int sgsImFontAtlas_Build( SGS_CTX )
{
	SGSFN( "ImFontAtlas_Build" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	sgs_PushVar( C, ImGui::GetIO().Fonts->Build() );
	return 1;
}

static int sgsImFontAtlas_RenderCustomTexData( SGS_CTX )
{
	SGSFN( "ImFontAtlas_RenderCustomTexData" );
	sgs_StkIdx ssz = sgs_StackSize( C ); (void) ssz;
	ImGui::GetIO().Fonts->RenderCustomTexData(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<void *>()( C, 1 )
	);
	return 0;
}


static sgs_RegFuncConst imgui_fconsts[] =
{
	{ "ImGui_NewFrame", sgsImGui_NewFrame },
	{ "ImGui_Render", sgsImGui_Render },
	{ "ImGui_Shutdown", sgsImGui_Shutdown },
	{ "ImGui_ShowUserGuide", sgsImGui_ShowUserGuide },
	{ "ImGui_ShowTestWindow", sgsImGui_ShowTestWindow },
	{ "ImGui_ShowMetricsWindow", sgsImGui_ShowMetricsWindow },
	{ "ImGui_Begin", sgsImGui_Begin },
	{ "ImGui_End", sgsImGui_End },
	{ "ImGui_BeginChild", sgsImGui_BeginChild },
	{ "ImGui_EndChild", sgsImGui_EndChild },
	{ "ImGui_GetContentRegionMax", sgsImGui_GetContentRegionMax },
	{ "ImGui_GetContentRegionAvail", sgsImGui_GetContentRegionAvail },
	{ "ImGui_GetContentRegionAvailWidth", sgsImGui_GetContentRegionAvailWidth },
	{ "ImGui_GetWindowContentRegionMin", sgsImGui_GetWindowContentRegionMin },
	{ "ImGui_GetWindowContentRegionMax", sgsImGui_GetWindowContentRegionMax },
	{ "ImGui_GetWindowContentRegionWidth", sgsImGui_GetWindowContentRegionWidth },
	{ "ImGui_GetWindowPos", sgsImGui_GetWindowPos },
	{ "ImGui_GetWindowSize", sgsImGui_GetWindowSize },
	{ "ImGui_GetWindowWidth", sgsImGui_GetWindowWidth },
	{ "ImGui_GetWindowHeight", sgsImGui_GetWindowHeight },
	{ "ImGui_IsWindowCollapsed", sgsImGui_IsWindowCollapsed },
	{ "ImGui_SetWindowFontScale", sgsImGui_SetWindowFontScale },
	{ "ImGui_SetNextWindowPos", sgsImGui_SetNextWindowPos },
	{ "ImGui_SetNextWindowPosCenter", sgsImGui_SetNextWindowPosCenter },
	{ "ImGui_SetNextWindowSize", sgsImGui_SetNextWindowSize },
	{ "ImGui_SetNextWindowContentSize", sgsImGui_SetNextWindowContentSize },
	{ "ImGui_SetNextWindowContentWidth", sgsImGui_SetNextWindowContentWidth },
	{ "ImGui_SetNextWindowCollapsed", sgsImGui_SetNextWindowCollapsed },
	{ "ImGui_SetNextWindowFocus", sgsImGui_SetNextWindowFocus },
	{ "ImGui_SetCurrentWindowPos", sgsImGui_SetCurrentWindowPos },
	{ "ImGui_SetCurrentWindowSize", sgsImGui_SetCurrentWindowSize },
	{ "ImGui_SetCurrentWindowCollapsed", sgsImGui_SetCurrentWindowCollapsed },
	{ "ImGui_SetCurrentWindowFocus", sgsImGui_SetCurrentWindowFocus },
	{ "ImGui_SetWindowPos", sgsImGui_SetWindowPos },
	{ "ImGui_SetWindowSize", sgsImGui_SetWindowSize },
	{ "ImGui_SetWindowCollapsed", sgsImGui_SetWindowCollapsed },
	{ "ImGui_SetWindowFocus", sgsImGui_SetWindowFocus },
	{ "ImGui_GetScrollX", sgsImGui_GetScrollX },
	{ "ImGui_GetScrollY", sgsImGui_GetScrollY },
	{ "ImGui_GetScrollMaxX", sgsImGui_GetScrollMaxX },
	{ "ImGui_GetScrollMaxY", sgsImGui_GetScrollMaxY },
	{ "ImGui_SetScrollX", sgsImGui_SetScrollX },
	{ "ImGui_SetScrollY", sgsImGui_SetScrollY },
	{ "ImGui_SetScrollHere", sgsImGui_SetScrollHere },
	{ "ImGui_SetScrollFromPosY", sgsImGui_SetScrollFromPosY },
	{ "ImGui_SetKeyboardFocusHere", sgsImGui_SetKeyboardFocusHere },
	{ "ImGui_PushFont", sgsImGui_PushFont },
	{ "ImGui_PopFont", sgsImGui_PopFont },
	{ "ImGui_PushStyleColor", sgsImGui_PushStyleColor },
	{ "ImGui_PopStyleColor", sgsImGui_PopStyleColor },
	{ "ImGui_PushStyleVarF", sgsImGui_PushStyleVarF },
	{ "ImGui_PushStyleVarV2", sgsImGui_PushStyleVarV2 },
	{ "ImGui_PopStyleVar", sgsImGui_PopStyleVar },
	{ "ImGui_GetFont", sgsImGui_GetFont },
	{ "ImGui_GetFontSize", sgsImGui_GetFontSize },
	{ "ImGui_GetFontTexUvWhitePixel", sgsImGui_GetFontTexUvWhitePixel },
	{ "ImGui_GetStyleColorU32", sgsImGui_GetStyleColorU32 },
	{ "ImGui_GetColorU32", sgsImGui_GetColorU32 },
	{ "ImGui_PushItemWidth", sgsImGui_PushItemWidth },
	{ "ImGui_PopItemWidth", sgsImGui_PopItemWidth },
	{ "ImGui_CalcItemWidth", sgsImGui_CalcItemWidth },
	{ "ImGui_PushTextWrapPos", sgsImGui_PushTextWrapPos },
	{ "ImGui_PopTextWrapPos", sgsImGui_PopTextWrapPos },
	{ "ImGui_PushAllowKeyboardFocus", sgsImGui_PushAllowKeyboardFocus },
	{ "ImGui_PopAllowKeyboardFocus", sgsImGui_PopAllowKeyboardFocus },
	{ "ImGui_PushButtonRepeat", sgsImGui_PushButtonRepeat },
	{ "ImGui_PopButtonRepeat", sgsImGui_PopButtonRepeat },
	{ "ImGui_Separator", sgsImGui_Separator },
	{ "ImGui_SameLine", sgsImGui_SameLine },
	{ "ImGui_NewLine", sgsImGui_NewLine },
	{ "ImGui_Spacing", sgsImGui_Spacing },
	{ "ImGui_Dummy", sgsImGui_Dummy },
	{ "ImGui_Indent", sgsImGui_Indent },
	{ "ImGui_Unindent", sgsImGui_Unindent },
	{ "ImGui_BeginGroup", sgsImGui_BeginGroup },
	{ "ImGui_EndGroup", sgsImGui_EndGroup },
	{ "ImGui_GetCursorPos", sgsImGui_GetCursorPos },
	{ "ImGui_GetCursorPosX", sgsImGui_GetCursorPosX },
	{ "ImGui_GetCursorPosY", sgsImGui_GetCursorPosY },
	{ "ImGui_SetCursorPos", sgsImGui_SetCursorPos },
	{ "ImGui_SetCursorPosX", sgsImGui_SetCursorPosX },
	{ "ImGui_SetCursorPosY", sgsImGui_SetCursorPosY },
	{ "ImGui_GetCursorStartPos", sgsImGui_GetCursorStartPos },
	{ "ImGui_GetCursorScreenPos", sgsImGui_GetCursorScreenPos },
	{ "ImGui_SetCursorScreenPos", sgsImGui_SetCursorScreenPos },
	{ "ImGui_AlignFirstTextHeightToWidgets", sgsImGui_AlignFirstTextHeightToWidgets },
	{ "ImGui_GetTextLineHeight", sgsImGui_GetTextLineHeight },
	{ "ImGui_GetTextLineHeightWithSpacing", sgsImGui_GetTextLineHeightWithSpacing },
	{ "ImGui_GetItemsLineHeightWithSpacing", sgsImGui_GetItemsLineHeightWithSpacing },
	{ "ImGui_Columns", sgsImGui_Columns },
	{ "ImGui_NextColumn", sgsImGui_NextColumn },
	{ "ImGui_GetColumnIndex", sgsImGui_GetColumnIndex },
	{ "ImGui_GetColumnOffset", sgsImGui_GetColumnOffset },
	{ "ImGui_SetColumnOffset", sgsImGui_SetColumnOffset },
	{ "ImGui_GetColumnWidth", sgsImGui_GetColumnWidth },
	{ "ImGui_GetColumnsCount", sgsImGui_GetColumnsCount },
	{ "ImGui_PushID", sgsimgui_PushID },
	{ "ImGui_PopID", sgsImGui_PopID },
	{ "ImGui_GetID", sgsimgui_GetID },
	{ "ImGui_Text", sgsImGui_Text },
	{ "ImGui_TextColored", sgsImGui_TextColored },
	{ "ImGui_TextDisabled", sgsImGui_TextDisabled },
	{ "ImGui_TextWrapped", sgsImGui_TextWrapped },
	{ "ImGui_TextUnformatted", sgsImGui_TextUnformatted },
	{ "ImGui_LabelText", sgsImGui_LabelText },
	{ "ImGui_Bullet", sgsImGui_Bullet },
	{ "ImGui_BulletText", sgsImGui_BulletText },
	{ "ImGui_Button", sgsImGui_Button },
	{ "ImGui_SmallButton", sgsImGui_SmallButton },
	{ "ImGui_InvisibleButton", sgsImGui_InvisibleButton },
	{ "ImGui_Image", sgsImGui_Image },
	{ "ImGui_ImageButton", sgsImGui_ImageButton },
	{ "ImGui_Checkbox", sgsImGui_Checkbox },
	{ "ImGui_CheckboxFlags", sgsImGui_CheckboxFlags },
	{ "ImGui_RadioButton", sgsimgui_RadioButton },
	{ "ImGui_Combo", sgsImGui_Combo },
	{ "ImGui_ComboCb", sgsImGui_ComboCb },
	{ "ImGui_ColorButton", sgsImGui_ColorButton },
	{ "ImGui_ColorEdit3", sgsImGui_ColorEdit3 },
	{ "ImGui_ColorEdit4", sgsImGui_ColorEdit4 },
	{ "ImGui_ColorEditMode", sgsImGui_ColorEditMode },
	{ "ImGui_PlotLines", sgsImGui_PlotLines },
	{ "ImGui_PlotLinesCb", sgsImGui_PlotLinesCb },
	{ "ImGui_PlotHistogram", sgsImGui_PlotHistogram },
	{ "ImGui_PlotHistogramCb", sgsImGui_PlotHistogramCb },
	{ "ImGui_ProgressBar", sgsImGui_ProgressBar },
	{ "ImGui_DragFloat", sgsImGui_DragFloat },
	{ "ImGui_DragFloat2", sgsImGui_DragFloat2 },
	{ "ImGui_DragFloat3", sgsImGui_DragFloat3 },
	{ "ImGui_DragFloat4", sgsImGui_DragFloat4 },
	{ "ImGui_DragFloatRange2", sgsImGui_DragFloatRange2 },
	{ "ImGui_DragInt", sgsImGui_DragInt },
	{ "ImGui_DragInt2", sgsImGui_DragInt2 },
	{ "ImGui_DragInt3", sgsImGui_DragInt3 },
	{ "ImGui_DragInt4", sgsImGui_DragInt4 },
	{ "ImGui_DragIntRange2", sgsImGui_DragIntRange2 },
	{ "ImGui_InputText", sgsImGui_InputText },
	{ "ImGui_InputTextMultiline", sgsImGui_InputTextMultiline },
	{ "ImGui_InputFloat", sgsImGui_InputFloat },
	{ "ImGui_InputFloat2", sgsImGui_InputFloat2 },
	{ "ImGui_InputFloat3", sgsImGui_InputFloat3 },
	{ "ImGui_InputFloat4", sgsImGui_InputFloat4 },
	{ "ImGui_InputInt", sgsImGui_InputInt },
	{ "ImGui_InputInt2", sgsImGui_InputInt2 },
	{ "ImGui_InputInt3", sgsImGui_InputInt3 },
	{ "ImGui_InputInt4", sgsImGui_InputInt4 },
	{ "ImGui_SliderFloat", sgsImGui_SliderFloat },
	{ "ImGui_SliderFloat2", sgsImGui_SliderFloat2 },
	{ "ImGui_SliderFloat3", sgsImGui_SliderFloat3 },
	{ "ImGui_SliderFloat4", sgsImGui_SliderFloat4 },
	{ "ImGui_SliderAngle", sgsImGui_SliderAngle },
	{ "ImGui_SliderInt", sgsImGui_SliderInt },
	{ "ImGui_SliderInt2", sgsImGui_SliderInt2 },
	{ "ImGui_SliderInt3", sgsImGui_SliderInt3 },
	{ "ImGui_SliderInt4", sgsImGui_SliderInt4 },
	{ "ImGui_VSliderFloat", sgsImGui_VSliderFloat },
	{ "ImGui_VSliderInt", sgsImGui_VSliderInt },
	{ "ImGui_TreeNode", sgsimgui_TreeNode },
	{ "ImGui_TreeNodeEx", sgsimgui_TreeNodeEx },
	{ "ImGui_TreePush", sgsImGui_TreePush },
	{ "ImGui_TreePop", sgsImGui_TreePop },
	{ "ImGui_TreeAdvanceToLabelPos", sgsImGui_TreeAdvanceToLabelPos },
	{ "ImGui_GetTreeNodeToLabelSpacing", sgsImGui_GetTreeNodeToLabelSpacing },
	{ "ImGui_SetNextTreeNodeOpen", sgsImGui_SetNextTreeNodeOpen },
	{ "ImGui_CollapsingHeader", sgsImGui_CollapsingHeader },
	{ "ImGui_CollapsingHeaderCloseable", sgsImGui_CollapsingHeaderCloseable },
	{ "ImGui_Selectable", sgsImGui_Selectable },
	{ "ImGui_ListBoxHeader", sgsImGui_ListBoxHeader },
	{ "ImGui_ListBoxHeader2", sgsImGui_ListBoxHeader2 },
	{ "ImGui_ListBoxFooter", sgsImGui_ListBoxFooter },
	{ "ImGui_ValueB", sgsImGui_ValueB },
	{ "ImGui_ValueI", sgsImGui_ValueI },
	{ "ImGui_ValueU", sgsImGui_ValueU },
	{ "ImGui_ValueF", sgsImGui_ValueF },
	{ "ImGui_ValueColorF", sgsImGui_ValueColorF },
	{ "ImGui_ValueColor", sgsImGui_ValueColor },
	{ "ImGui_SetTooltip", sgsImGui_SetTooltip },
	{ "ImGui_BeginTooltip", sgsImGui_BeginTooltip },
	{ "ImGui_EndTooltip", sgsImGui_EndTooltip },
	{ "ImGui_BeginMainMenuBar", sgsImGui_BeginMainMenuBar },
	{ "ImGui_EndMainMenuBar", sgsImGui_EndMainMenuBar },
	{ "ImGui_BeginMenuBar", sgsImGui_BeginMenuBar },
	{ "ImGui_EndMenuBar", sgsImGui_EndMenuBar },
	{ "ImGui_BeginMenu", sgsImGui_BeginMenu },
	{ "ImGui_EndMenu", sgsImGui_EndMenu },
	{ "ImGui_MenuItem", sgsImGui_MenuItem },
	{ "ImGui_OpenPopup", sgsImGui_OpenPopup },
	{ "ImGui_BeginPopup", sgsImGui_BeginPopup },
	{ "ImGui_BeginPopupModal", sgsImGui_BeginPopupModal },
	{ "ImGui_BeginPopupContextItem", sgsImGui_BeginPopupContextItem },
	{ "ImGui_BeginPopupContextWindow", sgsImGui_BeginPopupContextWindow },
	{ "ImGui_BeginPopupContextVoid", sgsImGui_BeginPopupContextVoid },
	{ "ImGui_EndPopup", sgsImGui_EndPopup },
	{ "ImGui_CloseCurrentPopup", sgsImGui_CloseCurrentPopup },
	{ "ImGui_LogToTTY", sgsImGui_LogToTTY },
	{ "ImGui_LogToFile", sgsImGui_LogToFile },
	{ "ImGui_LogToClipboard", sgsImGui_LogToClipboard },
	{ "ImGui_LogFinish", sgsImGui_LogFinish },
	{ "ImGui_LogButtons", sgsImGui_LogButtons },
	{ "ImGui_LogText", sgsImGui_LogText },
	{ "ImGui_PushClipRect", sgsImGui_PushClipRect },
	{ "ImGui_PopClipRect", sgsImGui_PopClipRect },
	{ "ImGui_IsItemHovered", sgsImGui_IsItemHovered },
	{ "ImGui_IsItemHoveredRect", sgsImGui_IsItemHoveredRect },
	{ "ImGui_IsItemActive", sgsImGui_IsItemActive },
	{ "ImGui_IsItemClicked", sgsImGui_IsItemClicked },
	{ "ImGui_IsItemVisible", sgsImGui_IsItemVisible },
	{ "ImGui_IsAnyItemHovered", sgsImGui_IsAnyItemHovered },
	{ "ImGui_IsAnyItemActive", sgsImGui_IsAnyItemActive },
	{ "ImGui_GetItemRectMin", sgsImGui_GetItemRectMin },
	{ "ImGui_GetItemRectMax", sgsImGui_GetItemRectMax },
	{ "ImGui_GetItemRectSize", sgsImGui_GetItemRectSize },
	{ "ImGui_SetItemAllowOverlap", sgsImGui_SetItemAllowOverlap },
	{ "ImGui_IsWindowHovered", sgsImGui_IsWindowHovered },
	{ "ImGui_IsWindowFocused", sgsImGui_IsWindowFocused },
	{ "ImGui_IsRootWindowFocused", sgsImGui_IsRootWindowFocused },
	{ "ImGui_IsRootWindowOrAnyChildFocused", sgsImGui_IsRootWindowOrAnyChildFocused },
	{ "ImGui_IsRootWindowOrAnyChildHovered", sgsImGui_IsRootWindowOrAnyChildHovered },
	{ "ImGui_IsRectVisible", sgsImGui_IsRectVisible },
	{ "ImGui_IsRectVisibleScreen", sgsImGui_IsRectVisibleScreen },
	{ "ImGui_IsPosHoveringAnyWindow", sgsImGui_IsPosHoveringAnyWindow },
	{ "ImGui_GetTime", sgsImGui_GetTime },
	{ "ImGui_GetFrameCount", sgsImGui_GetFrameCount },
	{ "ImGui_GetStyleColName", sgsImGui_GetStyleColName },
	{ "ImGui_CalcItemRectClosestPoint", sgsImGui_CalcItemRectClosestPoint },
	{ "ImGui_CalcTextSize", sgsImGui_CalcTextSize },
	{ "ImGui_CalcListClipping", sgsImGui_CalcListClipping },
	{ "ImGui_BeginChildFrame", sgsImGui_BeginChildFrame },
	{ "ImGui_EndChildFrame", sgsImGui_EndChildFrame },
	{ "ImGui_ColorConvertU32ToFloat4", sgsImGui_ColorConvertU32ToFloat4 },
	{ "ImGui_ColorConvertFloat4ToU32", sgsImGui_ColorConvertFloat4ToU32 },
	{ "ImGui_ColorConvertRGBtoHSV", sgsImGui_ColorConvertRGBtoHSV },
	{ "ImGui_ColorConvertHSVtoRGB", sgsImGui_ColorConvertHSVtoRGB },
	{ "ImGui_GetKeyIndex", sgsImGui_GetKeyIndex },
	{ "ImGui_IsKeyDown", sgsImGui_IsKeyDown },
	{ "ImGui_IsKeyPressed", sgsImGui_IsKeyPressed },
	{ "ImGui_IsKeyReleased", sgsImGui_IsKeyReleased },
	{ "ImGui_IsMouseDown", sgsImGui_IsMouseDown },
	{ "ImGui_IsMouseClicked", sgsImGui_IsMouseClicked },
	{ "ImGui_IsMouseDoubleClicked", sgsImGui_IsMouseDoubleClicked },
	{ "ImGui_IsMouseReleased", sgsImGui_IsMouseReleased },
	{ "ImGui_IsMouseHoveringWindow", sgsImGui_IsMouseHoveringWindow },
	{ "ImGui_IsMouseHoveringAnyWindow", sgsImGui_IsMouseHoveringAnyWindow },
	{ "ImGui_IsMouseHoveringRect", sgsImGui_IsMouseHoveringRect },
	{ "ImGui_IsMouseDragging", sgsImGui_IsMouseDragging },
	{ "ImGui_GetMousePos", sgsImGui_GetMousePos },
	{ "ImGui_GetMousePosOnOpeningCurrentPopup", sgsImGui_GetMousePosOnOpeningCurrentPopup },
	{ "ImGui_GetMouseDragDelta", sgsImGui_GetMouseDragDelta },
	{ "ImGui_ResetMouseDragDelta", sgsImGui_ResetMouseDragDelta },
	{ "ImGui_GetMouseCursor", sgsImGui_GetMouseCursor },
	{ "ImGui_SetMouseCursor", sgsImGui_SetMouseCursor },
	{ "ImGui_CaptureKeyboardFromApp", sgsImGui_CaptureKeyboardFromApp },
	{ "ImGui_CaptureMouseFromApp", sgsImGui_CaptureMouseFromApp },
	{ "ImGui_MemAlloc", sgsImGui_MemAlloc },
	{ "ImGui_MemFree", sgsImGui_MemFree },
	{ "ImGui_GetClipboardText", sgsImGui_GetClipboardText },
	{ "ImGui_SetClipboardText", sgsImGui_SetClipboardText },
	{ "ImGui_GetVersion", sgsImGui_GetVersion },
	{ "ImDrawList_PushClipRect", sgsImDrawList_PushClipRect },
	{ "ImDrawList_PushClipRectFullScreen", sgsImDrawList_PushClipRectFullScreen },
	{ "ImDrawList_PopClipRect", sgsImDrawList_PopClipRect },
	{ "ImDrawList_PopTextureID", sgsImDrawList_PopTextureID },
	{ "ImDrawList_AddLine", sgsImDrawList_AddLine },
	{ "ImDrawList_AddRect", sgsImDrawList_AddRect },
	{ "ImDrawList_AddRectFilled", sgsImDrawList_AddRectFilled },
	{ "ImDrawList_AddRectFilledMultiColor", sgsImDrawList_AddRectFilledMultiColor },
	{ "ImDrawList_AddQuad", sgsImDrawList_AddQuad },
	{ "ImDrawList_AddQuadFilled", sgsImDrawList_AddQuadFilled },
	{ "ImDrawList_AddTriangle", sgsImDrawList_AddTriangle },
	{ "ImDrawList_AddTriangleFilled", sgsImDrawList_AddTriangleFilled },
	{ "ImDrawList_AddCircle", sgsImDrawList_AddCircle },
	{ "ImDrawList_AddCircleFilled", sgsImDrawList_AddCircleFilled },
	{ "ImDrawList_AddImage", sgsImDrawList_AddImage },
	{ "ImDrawList_AddBezierCurve", sgsImDrawList_AddBezierCurve },
	{ "ImDrawList_PathClear", sgsImDrawList_PathClear },
	{ "ImDrawList_PathLineTo", sgsImDrawList_PathLineTo },
	{ "ImDrawList_PathLineToMergeDuplicate", sgsImDrawList_PathLineToMergeDuplicate },
	{ "ImDrawList_PathFill", sgsImDrawList_PathFill },
	{ "ImDrawList_PathStroke", sgsImDrawList_PathStroke },
	{ "ImDrawList_PathArcTo", sgsImDrawList_PathArcTo },
	{ "ImDrawList_PathArcToFast", sgsImDrawList_PathArcToFast },
	{ "ImDrawList_PathBezierCurveTo", sgsImDrawList_PathBezierCurveTo },
	{ "ImDrawList_PathRect", sgsImDrawList_PathRect },
	{ "ImDrawList_ChannelsSplit", sgsImDrawList_ChannelsSplit },
	{ "ImDrawList_ChannelsMerge", sgsImDrawList_ChannelsMerge },
	{ "ImDrawList_ChannelsSetCurrent", sgsImDrawList_ChannelsSetCurrent },
	{ "ImDrawList_AddCallback", sgsImDrawList_AddCallback },
	{ "ImDrawList_AddDrawCmd", sgsImDrawList_AddDrawCmd },
	{ "ImDrawList_Clear", sgsImDrawList_Clear },
	{ "ImDrawList_ClearFreeMemory", sgsImDrawList_ClearFreeMemory },
	{ "ImDrawList_PrimReserve", sgsImDrawList_PrimReserve },
	{ "ImDrawList_PrimRect", sgsImDrawList_PrimRect },
	{ "ImDrawList_PrimRectUV", sgsImDrawList_PrimRectUV },
	{ "ImDrawList_PrimQuadUV", sgsImDrawList_PrimQuadUV },
	{ "ImDrawList_PrimWriteVtx", sgsImDrawList_PrimWriteVtx },
	{ "ImDrawList_PrimWriteIdx", sgsImDrawList_PrimWriteIdx },
	{ "ImDrawList_PrimVtx", sgsImDrawList_PrimVtx },
	{ "ImDrawList_UpdateClipRect", sgsImDrawList_UpdateClipRect },
	{ "ImDrawList_UpdateTextureID", sgsImDrawList_UpdateTextureID },
	{ "ImFontAtlas_AddFont", sgsImFontAtlas_AddFont },
	{ "ImFontAtlas_AddFontDefault", sgsImFontAtlas_AddFontDefault },
	{ "ImFontAtlas_AddFontFromFileTTF", sgsImFontAtlas_AddFontFromFileTTF },
	{ "ImFontAtlas_AddFontFromMemoryTTF", sgsImFontAtlas_AddFontFromMemoryTTF },
	{ "ImFontAtlas_AddFontFromMemoryCompressedTTF", sgsImFontAtlas_AddFontFromMemoryCompressedTTF },
	{ "ImFontAtlas_AddFontFromMemoryCompressedBase85TTF", sgsImFontAtlas_AddFontFromMemoryCompressedBase85TTF },
	{ "ImFontAtlas_ClearTexData", sgsImFontAtlas_ClearTexData },
	{ "ImFontAtlas_ClearInputData", sgsImFontAtlas_ClearInputData },
	{ "ImFontAtlas_ClearFonts", sgsImFontAtlas_ClearFonts },
	{ "ImFontAtlas_Clear", sgsImFontAtlas_Clear },
	{ "ImFontAtlas_SetTexID", sgsImFontAtlas_SetTexID },
	{ "ImFontAtlas_Build", sgsImFontAtlas_Build },
	{ "ImFontAtlas_RenderCustomTexData", sgsImFontAtlas_RenderCustomTexData },
	{ NULL, NULL }
};


static sgs_RegIntConst imgui_iconsts[] =
{
	{ "ImGuiWindowFlags_NoTitleBar", 1 },
	{ "ImGuiWindowFlags_NoResize", 2 },
	{ "ImGuiWindowFlags_NoMove", 4 },
	{ "ImGuiWindowFlags_NoScrollbar", 8 },
	{ "ImGuiWindowFlags_NoScrollWithMouse", 16 },
	{ "ImGuiWindowFlags_NoCollapse", 32 },
	{ "ImGuiWindowFlags_AlwaysAutoResize", 64 },
	{ "ImGuiWindowFlags_ShowBorders", 128 },
	{ "ImGuiWindowFlags_NoSavedSettings", 256 },
	{ "ImGuiWindowFlags_NoInputs", 512 },
	{ "ImGuiWindowFlags_MenuBar", 1024 },
	{ "ImGuiWindowFlags_HorizontalScrollbar", 2048 },
	{ "ImGuiWindowFlags_NoFocusOnAppearing", 4096 },
	{ "ImGuiWindowFlags_NoBringToFrontOnFocus", 8192 },
	{ "ImGuiWindowFlags_AlwaysVerticalScrollbar", 16384 },
	{ "ImGuiWindowFlags_AlwaysHorizontalScrollbar", 32768 },
	{ "ImGuiWindowFlags_AlwaysUseWindowPadding", 65536 },
	{ "ImGuiWindowFlags_ChildWindow", 1048576 },
	{ "ImGuiWindowFlags_ChildWindowAutoFitX", 2097152 },
	{ "ImGuiWindowFlags_ChildWindowAutoFitY", 4194304 },
	{ "ImGuiWindowFlags_ComboBox", 8388608 },
	{ "ImGuiWindowFlags_Tooltip", 16777216 },
	{ "ImGuiWindowFlags_Popup", 33554432 },
	{ "ImGuiWindowFlags_Modal", 67108864 },
	{ "ImGuiWindowFlags_ChildMenu", 134217728 },
	{ "ImGuiInputTextFlags_CharsDecimal", 1 },
	{ "ImGuiInputTextFlags_CharsHexadecimal", 2 },
	{ "ImGuiInputTextFlags_CharsUppercase", 4 },
	{ "ImGuiInputTextFlags_CharsNoBlank", 8 },
	{ "ImGuiInputTextFlags_AutoSelectAll", 16 },
	{ "ImGuiInputTextFlags_EnterReturnsTrue", 32 },
	{ "ImGuiInputTextFlags_CallbackCompletion", 64 },
	{ "ImGuiInputTextFlags_CallbackHistory", 128 },
	{ "ImGuiInputTextFlags_CallbackAlways", 256 },
	{ "ImGuiInputTextFlags_CallbackCharFilter", 512 },
	{ "ImGuiInputTextFlags_AllowTabInput", 1024 },
	{ "ImGuiInputTextFlags_CtrlEnterForNewLine", 2048 },
	{ "ImGuiInputTextFlags_NoHorizontalScroll", 4096 },
	{ "ImGuiInputTextFlags_AlwaysInsertMode", 8192 },
	{ "ImGuiInputTextFlags_ReadOnly", 16384 },
	{ "ImGuiInputTextFlags_Password", 32768 },
	{ "ImGuiInputTextFlags_Multiline", 1048576 },
	{ "ImGuiTreeNodeFlags_Selected", 1 },
	{ "ImGuiTreeNodeFlags_Framed", 2 },
	{ "ImGuiTreeNodeFlags_AllowOverlapMode", 4 },
	{ "ImGuiTreeNodeFlags_NoTreePushOnOpen", 8 },
	{ "ImGuiTreeNodeFlags_NoAutoOpenOnLog", 16 },
	{ "ImGuiTreeNodeFlags_DefaultOpen", 32 },
	{ "ImGuiTreeNodeFlags_OpenOnDoubleClick", 64 },
	{ "ImGuiTreeNodeFlags_OpenOnArrow", 128 },
	{ "ImGuiTreeNodeFlags_Leaf", 256 },
	{ "ImGuiTreeNodeFlags_Bullet", 512 },
	{ "ImGuiTreeNodeFlags_CollapsingHeader", 18 },
	{ "ImGuiSelectableFlags_DontClosePopups", 1 },
	{ "ImGuiSelectableFlags_SpanAllColumns", 2 },
	{ "ImGuiSelectableFlags_AllowDoubleClick", 4 },
	{ "ImGuiKey_Tab", 0 },
	{ "ImGuiKey_LeftArrow", 1 },
	{ "ImGuiKey_RightArrow", 2 },
	{ "ImGuiKey_UpArrow", 3 },
	{ "ImGuiKey_DownArrow", 4 },
	{ "ImGuiKey_PageUp", 5 },
	{ "ImGuiKey_PageDown", 6 },
	{ "ImGuiKey_Home", 7 },
	{ "ImGuiKey_End", 8 },
	{ "ImGuiKey_Delete", 9 },
	{ "ImGuiKey_Backspace", 10 },
	{ "ImGuiKey_Enter", 11 },
	{ "ImGuiKey_Escape", 12 },
	{ "ImGuiKey_A", 13 },
	{ "ImGuiKey_C", 14 },
	{ "ImGuiKey_V", 15 },
	{ "ImGuiKey_X", 16 },
	{ "ImGuiKey_Y", 17 },
	{ "ImGuiKey_Z", 18 },
	{ "ImGuiKey_COUNT", 19 },
	{ "ImGuiCol_Text", 0 },
	{ "ImGuiCol_TextDisabled", 1 },
	{ "ImGuiCol_WindowBg", 2 },
	{ "ImGuiCol_ChildWindowBg", 3 },
	{ "ImGuiCol_PopupBg", 4 },
	{ "ImGuiCol_Border", 5 },
	{ "ImGuiCol_BorderShadow", 6 },
	{ "ImGuiCol_FrameBg", 7 },
	{ "ImGuiCol_FrameBgHovered", 8 },
	{ "ImGuiCol_FrameBgActive", 9 },
	{ "ImGuiCol_TitleBg", 10 },
	{ "ImGuiCol_TitleBgCollapsed", 11 },
	{ "ImGuiCol_TitleBgActive", 12 },
	{ "ImGuiCol_MenuBarBg", 13 },
	{ "ImGuiCol_ScrollbarBg", 14 },
	{ "ImGuiCol_ScrollbarGrab", 15 },
	{ "ImGuiCol_ScrollbarGrabHovered", 16 },
	{ "ImGuiCol_ScrollbarGrabActive", 17 },
	{ "ImGuiCol_ComboBg", 18 },
	{ "ImGuiCol_CheckMark", 19 },
	{ "ImGuiCol_SliderGrab", 20 },
	{ "ImGuiCol_SliderGrabActive", 21 },
	{ "ImGuiCol_Button", 22 },
	{ "ImGuiCol_ButtonHovered", 23 },
	{ "ImGuiCol_ButtonActive", 24 },
	{ "ImGuiCol_Header", 25 },
	{ "ImGuiCol_HeaderHovered", 26 },
	{ "ImGuiCol_HeaderActive", 27 },
	{ "ImGuiCol_Column", 28 },
	{ "ImGuiCol_ColumnHovered", 29 },
	{ "ImGuiCol_ColumnActive", 30 },
	{ "ImGuiCol_ResizeGrip", 31 },
	{ "ImGuiCol_ResizeGripHovered", 32 },
	{ "ImGuiCol_ResizeGripActive", 33 },
	{ "ImGuiCol_CloseButton", 34 },
	{ "ImGuiCol_CloseButtonHovered", 35 },
	{ "ImGuiCol_CloseButtonActive", 36 },
	{ "ImGuiCol_PlotLines", 37 },
	{ "ImGuiCol_PlotLinesHovered", 38 },
	{ "ImGuiCol_PlotHistogram", 39 },
	{ "ImGuiCol_PlotHistogramHovered", 40 },
	{ "ImGuiCol_TextSelectedBg", 41 },
	{ "ImGuiCol_ModalWindowDarkening", 42 },
	{ "ImGuiCol_COUNT", 43 },
	{ "ImGuiStyleVar_Alpha", 0 },
	{ "ImGuiStyleVar_WindowPadding", 1 },
	{ "ImGuiStyleVar_WindowRounding", 2 },
	{ "ImGuiStyleVar_WindowMinSize", 3 },
	{ "ImGuiStyleVar_ChildWindowRounding", 4 },
	{ "ImGuiStyleVar_FramePadding", 5 },
	{ "ImGuiStyleVar_FrameRounding", 6 },
	{ "ImGuiStyleVar_ItemSpacing", 7 },
	{ "ImGuiStyleVar_ItemInnerSpacing", 8 },
	{ "ImGuiStyleVar_IndentSpacing", 9 },
	{ "ImGuiStyleVar_GrabMinSize", 10 },
	{ "ImGuiStyleVar_ButtonTextAlign", 11 },
	{ "ImGuiStyleVar_Count_", 12 },
	{ "ImGuiColorEditMode_UserSelect", -2 },
	{ "ImGuiColorEditMode_UserSelectShowButton", -1 },
	{ "ImGuiColorEditMode_RGB", 0 },
	{ "ImGuiColorEditMode_HSV", 1 },
	{ "ImGuiColorEditMode_HEX", 2 },
	{ "ImGuiMouseCursor_None", -1 },
	{ "ImGuiMouseCursor_Arrow", 0 },
	{ "ImGuiMouseCursor_TextInput", 1 },
	{ "ImGuiMouseCursor_Move", 2 },
	{ "ImGuiMouseCursor_ResizeNS", 3 },
	{ "ImGuiMouseCursor_ResizeEW", 4 },
	{ "ImGuiMouseCursor_ResizeNESW", 5 },
	{ "ImGuiMouseCursor_ResizeNWSE", 6 },
	{ "ImGuiMouseCursor_Count_", 7 },
	{ "ImGuiSetCond_Always", 1 },
	{ "ImGuiSetCond_Once", 2 },
	{ "ImGuiSetCond_FirstUseEver", 4 },
	{ "ImGuiSetCond_Appearing", 8 },
	{ NULL, 0 }
};


void sgs_imgui_bind( SGS_CTX )
{
	sgs_RegFuncConsts( C, imgui_fconsts, -1 );
	sgs_RegIntConsts( C, imgui_iconsts, -1 );
};

