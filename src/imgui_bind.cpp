
#include "imgui.hpp"


static int sgsimgui_NewFrame( SGS_CTX )
{
	SGSFN( "ImGui_NewFrame" );
	ImGui::NewFrame();
	return 0;
}

static int sgsimgui_Render( SGS_CTX )
{
	SGSFN( "ImGui_Render" );
	ImGui::Render();
	return 0;
}

static int sgsimgui_Shutdown( SGS_CTX )
{
	SGSFN( "ImGui_Shutdown" );
	ImGui::Shutdown();
	return 0;
}

static int sgsimgui_ShowUserGuide( SGS_CTX )
{
	SGSFN( "ImGui_ShowUserGuide" );
	ImGui::ShowUserGuide();
	return 0;
}

static int sgsimgui_ShowTestWindow( SGS_CTX )
{
	SGSFN( "ImGui_ShowTestWindow" );
	bool val0 = sgs_GetVar<bool>()( C, 0 );
	ImGui::ShowTestWindow(
		&val0
	);
	sgs_PushBool( C, val0 );
	return 1;
}

static int sgsimgui_ShowMetricsWindow( SGS_CTX )
{
	SGSFN( "ImGui_ShowMetricsWindow" );
	bool val0 = sgs_GetVar<bool>()( C, 0 );
	ImGui::ShowMetricsWindow(
		&val0
	);
	sgs_PushBool( C, val0 );
	return 1;
}

static int sgsimgui_Begin( SGS_CTX )
{
	SGSFN( "ImGui_Begin" );
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Begin(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<ImGuiWindowFlags>()( C, 2 )
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsimgui_End( SGS_CTX )
{
	SGSFN( "ImGui_End" );
	ImGui::End();
	return 0;
}

static int sgsimgui_EndChild( SGS_CTX )
{
	SGSFN( "ImGui_EndChild" );
	ImGui::EndChild();
	return 0;
}

static int sgsimgui_GetContentRegionMax( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionMax" );
	sgs_PushVar( C, ImGui::GetContentRegionMax() );
	return 2;
}

static int sgsimgui_GetContentRegionAvail( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionAvail" );
	sgs_PushVar( C, ImGui::GetContentRegionAvail() );
	return 2;
}

static int sgsimgui_GetContentRegionAvailWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetContentRegionAvailWidth" );
	sgs_PushVar( C, ImGui::GetContentRegionAvailWidth() );
	return 1;
}

static int sgsimgui_GetWindowContentRegionMin( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionMin" );
	sgs_PushVar( C, ImGui::GetWindowContentRegionMin() );
	return 2;
}

static int sgsimgui_GetWindowContentRegionMax( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionMax" );
	sgs_PushVar( C, ImGui::GetWindowContentRegionMax() );
	return 2;
}

static int sgsimgui_GetWindowContentRegionWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowContentRegionWidth" );
	sgs_PushVar( C, ImGui::GetWindowContentRegionWidth() );
	return 1;
}

static int sgsimgui_GetWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowPos" );
	sgs_PushVar( C, ImGui::GetWindowPos() );
	return 2;
}

static int sgsimgui_GetWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowSize" );
	sgs_PushVar( C, ImGui::GetWindowSize() );
	return 2;
}

static int sgsimgui_GetWindowWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowWidth" );
	sgs_PushVar( C, ImGui::GetWindowWidth() );
	return 1;
}

static int sgsimgui_GetWindowHeight( SGS_CTX )
{
	SGSFN( "ImGui_GetWindowHeight" );
	sgs_PushVar( C, ImGui::GetWindowHeight() );
	return 1;
}

static int sgsimgui_IsWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowCollapsed" );
	sgs_PushVar( C, ImGui::IsWindowCollapsed() );
	return 1;
}

static int sgsimgui_SetWindowFontScale( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowFontScale" );
	ImGui::SetWindowFontScale(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowPos" );
	ImGui::SetNextWindowPos(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowPosCenter( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowPosCenter" );
	ImGui::SetNextWindowPosCenter(
		sgs_GetVar<ImGuiSetCond>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowSize" );
	ImGui::SetNextWindowSize(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowContentSize( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowContentSize" );
	ImGui::SetNextWindowContentSize(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowContentWidth( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowContentWidth" );
	ImGui::SetNextWindowContentWidth(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowCollapsed" );
	ImGui::SetNextWindowCollapsed(
		sgs_GetVar<bool>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_SetNextWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetNextWindowFocus" );
	ImGui::SetNextWindowFocus();
	return 0;
}

static int sgsimgui_SetCurrentWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowPos" );
	ImGui::SetWindowPos(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_SetCurrentWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowSize" );
	ImGui::SetWindowSize(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_SetCurrentWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowCollapsed" );
	ImGui::SetWindowCollapsed(
		sgs_GetVar<bool>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_SetCurrentWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetCurrentWindowFocus" );
	ImGui::SetWindowFocus();
	return 0;
}

static int sgsimgui_SetWindowPos( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowPos" );
	ImGui::SetWindowPos(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImGuiSetCond>()( C, 3 )
	);
	return 0;
}

static int sgsimgui_SetWindowSize( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowSize" );
	ImGui::SetWindowSize(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImGuiSetCond>()( C, 3 )
	);
	return 0;
}

static int sgsimgui_SetWindowCollapsed( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowCollapsed" );
	ImGui::SetWindowCollapsed(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 ),
		sgs_GetVar<ImGuiSetCond>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_SetWindowFocus( SGS_CTX )
{
	SGSFN( "ImGui_SetWindowFocus" );
	ImGui::SetWindowFocus(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetScrollX( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollX" );
	sgs_PushVar( C, ImGui::GetScrollX() );
	return 1;
}

static int sgsimgui_GetScrollY( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollY" );
	sgs_PushVar( C, ImGui::GetScrollY() );
	return 1;
}

static int sgsimgui_GetScrollMaxX( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollMaxX" );
	sgs_PushVar( C, ImGui::GetScrollMaxX() );
	return 1;
}

static int sgsimgui_GetScrollMaxY( SGS_CTX )
{
	SGSFN( "ImGui_GetScrollMaxY" );
	sgs_PushVar( C, ImGui::GetScrollMaxY() );
	return 1;
}

static int sgsimgui_SetScrollX( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollX" );
	ImGui::SetScrollX(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetScrollY( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollY" );
	ImGui::SetScrollY(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetScrollHere( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollHere" );
	ImGui::SetScrollHere(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetScrollFromPosY( SGS_CTX )
{
	SGSFN( "ImGui_SetScrollFromPosY" );
	ImGui::SetScrollFromPosY(
		sgs_GetVar<float>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_SetKeyboardFocusHere( SGS_CTX )
{
	SGSFN( "ImGui_SetKeyboardFocusHere" );
	ImGui::SetKeyboardFocusHere(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PopFont( SGS_CTX )
{
	SGSFN( "ImGui_PopFont" );
	ImGui::PopFont();
	return 0;
}

static int sgsimgui_PushStyleColor( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleColor" );
	ImGui::PushStyleColor(
		sgs_GetVar<ImGuiCol>()( C, 0 ),
		sgs_GetVar<ImVec4>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_PopStyleColor( SGS_CTX )
{
	SGSFN( "ImGui_PopStyleColor" );
	ImGui::PopStyleColor(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PushStyleVarF( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleVarF" );
	ImGui::PushStyleVar(
		sgs_GetVar<ImGuiStyleVar>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_PushStyleVarV2( SGS_CTX )
{
	SGSFN( "ImGui_PushStyleVarV2" );
	ImGui::PushStyleVar(
		sgs_GetVar<ImGuiStyleVar>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_PopStyleVar( SGS_CTX )
{
	SGSFN( "ImGui_PopStyleVar" );
	ImGui::PopStyleVar(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetFontSize( SGS_CTX )
{
	SGSFN( "ImGui_GetFontSize" );
	sgs_PushVar( C, ImGui::GetFontSize() );
	return 1;
}

static int sgsimgui_GetFontTexUvWhitePixel( SGS_CTX )
{
	SGSFN( "ImGui_GetFontTexUvWhitePixel" );
	sgs_PushVar( C, ImGui::GetFontTexUvWhitePixel() );
	return 2;
}

static int sgsimgui_PushItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_PushItemWidth" );
	ImGui::PushItemWidth(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PopItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_PopItemWidth" );
	ImGui::PopItemWidth();
	return 0;
}

static int sgsimgui_CalcItemWidth( SGS_CTX )
{
	SGSFN( "ImGui_CalcItemWidth" );
	sgs_PushVar( C, ImGui::CalcItemWidth() );
	return 1;
}

static int sgsimgui_PushTextWrapPos( SGS_CTX )
{
	SGSFN( "ImGui_PushTextWrapPos" );
	ImGui::PushTextWrapPos(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PopTextWrapPos( SGS_CTX )
{
	SGSFN( "ImGui_PopTextWrapPos" );
	ImGui::PopTextWrapPos();
	return 0;
}

static int sgsimgui_PushAllowKeyboardFocus( SGS_CTX )
{
	SGSFN( "ImGui_PushAllowKeyboardFocus" );
	ImGui::PushAllowKeyboardFocus(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PopAllowKeyboardFocus( SGS_CTX )
{
	SGSFN( "ImGui_PopAllowKeyboardFocus" );
	ImGui::PopAllowKeyboardFocus();
	return 0;
}

static int sgsimgui_PushButtonRepeat( SGS_CTX )
{
	SGSFN( "ImGui_PushButtonRepeat" );
	ImGui::PushButtonRepeat(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PopButtonRepeat( SGS_CTX )
{
	SGSFN( "ImGui_PopButtonRepeat" );
	ImGui::PopButtonRepeat();
	return 0;
}

static int sgsimgui_Separator( SGS_CTX )
{
	SGSFN( "ImGui_Separator" );
	ImGui::Separator();
	return 0;
}

static int sgsimgui_SameLine( SGS_CTX )
{
	SGSFN( "ImGui_SameLine" );
	ImGui::SameLine(
		sgs_GetVar<float>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_NewLine( SGS_CTX )
{
	SGSFN( "ImGui_NewLine" );
	ImGui::NewLine();
	return 0;
}

static int sgsimgui_Spacing( SGS_CTX )
{
	SGSFN( "ImGui_Spacing" );
	ImGui::Spacing();
	return 0;
}

static int sgsimgui_Dummy( SGS_CTX )
{
	SGSFN( "ImGui_Dummy" );
	ImGui::Dummy(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_Indent( SGS_CTX )
{
	SGSFN( "ImGui_Indent" );
	ImGui::Indent(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_Unindent( SGS_CTX )
{
	SGSFN( "ImGui_Unindent" );
	ImGui::Unindent(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_BeginGroup( SGS_CTX )
{
	SGSFN( "ImGui_BeginGroup" );
	ImGui::BeginGroup();
	return 0;
}

static int sgsimgui_EndGroup( SGS_CTX )
{
	SGSFN( "ImGui_EndGroup" );
	ImGui::EndGroup();
	return 0;
}

static int sgsimgui_GetCursorPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPos" );
	sgs_PushVar( C, ImGui::GetCursorPos() );
	return 2;
}

static int sgsimgui_GetCursorPosX( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPosX" );
	sgs_PushVar( C, ImGui::GetCursorPosX() );
	return 1;
}

static int sgsimgui_GetCursorPosY( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorPosY" );
	sgs_PushVar( C, ImGui::GetCursorPosY() );
	return 1;
}

static int sgsimgui_SetCursorPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPos" );
	ImGui::SetCursorPos(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetCursorPosX( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPosX" );
	ImGui::SetCursorPosX(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_SetCursorPosY( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorPosY" );
	ImGui::SetCursorPosY(
		sgs_GetVar<float>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetCursorStartPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorStartPos" );
	sgs_PushVar( C, ImGui::GetCursorStartPos() );
	return 2;
}

static int sgsimgui_GetCursorScreenPos( SGS_CTX )
{
	SGSFN( "ImGui_GetCursorScreenPos" );
	sgs_PushVar( C, ImGui::GetCursorScreenPos() );
	return 2;
}

static int sgsimgui_SetCursorScreenPos( SGS_CTX )
{
	SGSFN( "ImGui_SetCursorScreenPos" );
	ImGui::SetCursorScreenPos(
		sgs_GetVar<ImVec2>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_AlignFirstTextHeightToWidgets( SGS_CTX )
{
	SGSFN( "ImGui_AlignFirstTextHeightToWidgets" );
	ImGui::AlignFirstTextHeightToWidgets();
	return 0;
}

static int sgsimgui_GetTextLineHeight( SGS_CTX )
{
	SGSFN( "ImGui_GetTextLineHeight" );
	sgs_PushVar( C, ImGui::GetTextLineHeight() );
	return 1;
}

static int sgsimgui_GetTextLineHeightWithSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetTextLineHeightWithSpacing" );
	sgs_PushVar( C, ImGui::GetTextLineHeightWithSpacing() );
	return 1;
}

static int sgsimgui_GetItemsLineHeightWithSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetItemsLineHeightWithSpacing" );
	sgs_PushVar( C, ImGui::GetItemsLineHeightWithSpacing() );
	return 1;
}

static int sgsimgui_Columns( SGS_CTX )
{
	SGSFN( "ImGui_Columns" );
	ImGui::Columns(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 ),
		sgs_GetVar<bool>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_NextColumn( SGS_CTX )
{
	SGSFN( "ImGui_NextColumn" );
	ImGui::NextColumn();
	return 0;
}

static int sgsimgui_GetColumnIndex( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnIndex" );
	sgs_PushVar( C, ImGui::GetColumnIndex() );
	return 1;
}

static int sgsimgui_GetColumnOffset( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnOffset" );
	sgs_PushVar( C, ImGui::GetColumnOffset(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_SetColumnOffset( SGS_CTX )
{
	SGSFN( "ImGui_SetColumnOffset" );
	ImGui::SetColumnOffset(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_GetColumnWidth( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnWidth" );
	sgs_PushVar( C, ImGui::GetColumnWidth(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_GetColumnsCount( SGS_CTX )
{
	SGSFN( "ImGui_GetColumnsCount" );
	sgs_PushVar( C, ImGui::GetColumnsCount() );
	return 1;
}

static int sgsimgui_PushID( SGS_CTX )
{
	SGSFN( "ImGui_PushID" );
	ImGui::PushID( sgs_GetPtr( C, 0 ) );
	return 0;
}

static int sgsimgui_PopID( SGS_CTX )
{
	SGSFN( "ImGui_PopID" );
	ImGui::PopID();
	return 0;
}

static int sgsimgui_GetID( SGS_CTX )
{
	SGSFN( "ImGui_GetID" );
	sgs_PushInt( C, ImGui::GetID( sgs_GetPtr( C, 0 ) ) );
	return 1;
}

static int sgsimgui_Text( SGS_CTX )
{
	SGSFN( "ImGui_Text" );
	ImGui::Text(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_TextColored( SGS_CTX )
{
	SGSFN( "ImGui_TextColored" );
	ImGui::TextColored(
		sgs_GetVar<ImVec4>()( C, 0 ),
		"%s",
		sgs_GetVar<const char*>()( C, 4 )
	);
	return 0;
}

static int sgsimgui_TextDisabled( SGS_CTX )
{
	SGSFN( "ImGui_TextDisabled" );
	ImGui::TextDisabled(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_TextWrapped( SGS_CTX )
{
	SGSFN( "ImGui_TextWrapped" );
	ImGui::TextWrapped(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_TextUnformatted( SGS_CTX )
{
	SGSFN( "ImGui_TextUnformatted" );
	ImGui::TextUnformatted(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_LabelText( SGS_CTX )
{
	SGSFN( "ImGui_LabelText" );
	ImGui::LabelText(
		sgs_GetVar<const char *>()( C, 0 ),
		"%s",
		sgs_GetVar<const char*>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_Bullet( SGS_CTX )
{
	SGSFN( "ImGui_Bullet" );
	ImGui::Bullet();
	return 0;
}

static int sgsimgui_BulletText( SGS_CTX )
{
	SGSFN( "ImGui_BulletText" );
	ImGui::BulletText(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_Button( SGS_CTX )
{
	SGSFN( "ImGui_Button" );
	sgs_PushVar( C, ImGui::Button(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_SmallButton( SGS_CTX )
{
	SGSFN( "ImGui_SmallButton" );
	sgs_PushVar( C, ImGui::SmallButton(
		sgs_GetVar<const char *>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_InvisibleButton( SGS_CTX )
{
	SGSFN( "ImGui_InvisibleButton" );
	sgs_PushVar( C, ImGui::InvisibleButton(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_Image( SGS_CTX )
{
	SGSFN( "ImGui_Image" );
	ImGui::Image(
		sgs_GetVar<ImTextureID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImVec2>()( C, 3 ),
		sgs_GetVar<ImVec2>()( C, 5 ),
		sgs_GetVar<ImVec4>()( C, 7 ),
		sgs_GetVar<ImVec4>()( C, 11 )
	);
	return 0;
}

static int sgsimgui_ImageButton( SGS_CTX )
{
	SGSFN( "ImGui_ImageButton" );
	sgs_PushVar( C, ImGui::ImageButton(
		sgs_GetVar<ImTextureID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImVec2>()( C, 3 ),
		sgs_GetVar<ImVec2>()( C, 5 ),
		sgs_GetVar<int>()( C, 7 ),
		sgs_GetVar<ImVec4>()( C, 8 ),
		sgs_GetVar<ImVec4>()( C, 12 )
	) );
	return 1;
}

static int sgsimgui_Checkbox( SGS_CTX )
{
	SGSFN( "ImGui_Checkbox" );
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Checkbox(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsimgui_CheckboxFlags( SGS_CTX )
{
	SGSFN( "ImGui_CheckboxFlags" );
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

static int sgsimgui_ColorButton( SGS_CTX )
{
	SGSFN( "ImGui_ColorButton" );
	sgs_PushVar( C, ImGui::ColorButton(
		sgs_GetVar<ImVec4>()( C, 0 ),
		sgs_GetVar<bool>()( C, 4 ),
		sgs_GetVar<bool>()( C, 5 )
	) );
	return 1;
}

static int sgsimgui_ColorEdit3( SGS_CTX )
{
	SGSFN( "ImGui_ColorEdit3" );
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

static int sgsimgui_ColorEdit4( SGS_CTX )
{
	SGSFN( "ImGui_ColorEdit4" );
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::ColorEdit4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<bool>()( C, 5 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsimgui_ColorEditMode( SGS_CTX )
{
	SGSFN( "ImGui_ColorEditMode" );
	ImGui::ColorEditMode(
		sgs_GetVar<ImGuiColorEditMode>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_ProgressBar( SGS_CTX )
{
	SGSFN( "ImGui_ProgressBar" );
	ImGui::ProgressBar(
		sgs_GetVar<float>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<const char *>()( C, 3 )
	);
	return 0;
}

static int sgsimgui_DragFloat( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat" );
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::DragFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<const char *>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 )
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsimgui_DragFloat2( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat2" );
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::DragFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 ),
		sgs_GetVar<float>()( C, 7 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsimgui_DragFloat3( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat3" );
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::DragFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 ),
		sgs_GetVar<float>()( C, 8 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsimgui_DragFloat4( SGS_CTX )
{
	SGSFN( "ImGui_DragFloat4" );
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::DragFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 ),
		sgs_GetVar<float>()( C, 7 ),
		sgs_GetVar<const char *>()( C, 8 ),
		sgs_GetVar<float>()( C, 9 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsimgui_DragFloatRange2( SGS_CTX )
{
	SGSFN( "ImGui_DragFloatRange2" );
	float val1 = sgs_GetVar<float>()( C, 1 );
	float val2 = sgs_GetVar<float>()( C, 2 );
	sgs_PushVar( C, ImGui::DragFloatRange2(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		&val2,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 ),
		sgs_GetVar<float>()( C, 8 )
	) );
	sgs_PushReal( C, val1 );
	sgs_PushReal( C, val2 );
	return 3;
}

static int sgsimgui_DragInt( SGS_CTX )
{
	SGSFN( "ImGui_DragInt" );
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::DragInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<const char *>()( C, 5 )
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsimgui_DragInt2( SGS_CTX )
{
	SGSFN( "ImGui_DragInt2" );
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::DragInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsimgui_DragInt3( SGS_CTX )
{
	SGSFN( "ImGui_DragInt3" );
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::DragInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<int>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsimgui_DragInt4( SGS_CTX )
{
	SGSFN( "ImGui_DragInt4" );
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::DragInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<int>()( C, 6 ),
		sgs_GetVar<int>()( C, 7 ),
		sgs_GetVar<const char *>()( C, 8 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsimgui_DragIntRange2( SGS_CTX )
{
	SGSFN( "ImGui_DragIntRange2" );
	int val1 = sgs_GetVar<int>()( C, 1 );
	int val2 = sgs_GetVar<int>()( C, 2 );
	sgs_PushVar( C, ImGui::DragIntRange2(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		&val2,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 )
	) );
	sgs_PushInt( C, val1 );
	sgs_PushInt( C, val2 );
	return 3;
}

static int sgsimgui_InputFloat( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat" );
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::InputFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<ImGuiInputTextFlags>()( C, 5 )
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsimgui_InputFloat2( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat2" );
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::InputFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<ImGuiInputTextFlags>()( C, 4 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsimgui_InputFloat3( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat3" );
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::InputFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<ImGuiInputTextFlags>()( C, 5 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsimgui_InputFloat4( SGS_CTX )
{
	SGSFN( "ImGui_InputFloat4" );
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::InputFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<ImGuiInputTextFlags>()( C, 6 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsimgui_InputInt( SGS_CTX )
{
	SGSFN( "ImGui_InputInt" );
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::InputInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<int>()( C, 2 ),
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<ImGuiInputTextFlags>()( C, 4 )
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsimgui_InputInt2( SGS_CTX )
{
	SGSFN( "ImGui_InputInt2" );
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::InputInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<ImGuiInputTextFlags>()( C, 3 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsimgui_InputInt3( SGS_CTX )
{
	SGSFN( "ImGui_InputInt3" );
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::InputInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<ImGuiInputTextFlags>()( C, 4 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsimgui_InputInt4( SGS_CTX )
{
	SGSFN( "ImGui_InputInt4" );
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::InputInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<ImGuiInputTextFlags>()( C, 5 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsimgui_SliderFloat( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat" );
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<const char *>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 )
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsimgui_SliderFloat2( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat2" );
	float val1[2] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ) };
	sgs_PushVar( C, ImGui::SliderFloat2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 3 ),
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<const char *>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	return 3;
}

static int sgsimgui_SliderFloat3( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat3" );
	float val1[3] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ) };
	sgs_PushVar( C, ImGui::SliderFloat3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 ),
		sgs_GetVar<float>()( C, 7 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	return 4;
}

static int sgsimgui_SliderFloat4( SGS_CTX )
{
	SGSFN( "ImGui_SliderFloat4" );
	float val1[4] = { sgs_GetVar<float>()( C, 1 ), sgs_GetVar<float>()( C, 2 ), sgs_GetVar<float>()( C, 3 ), sgs_GetVar<float>()( C, 4 ) };
	sgs_PushVar( C, ImGui::SliderFloat4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<float>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 ),
		sgs_GetVar<float>()( C, 8 )
	) );
	sgs_PushReal( C, val1[0] );
	sgs_PushReal( C, val1[1] );
	sgs_PushReal( C, val1[2] );
	sgs_PushReal( C, val1[3] );
	return 5;
}

static int sgsimgui_SliderAngle( SGS_CTX )
{
	SGSFN( "ImGui_SliderAngle" );
	float val1 = sgs_GetVar<float>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderAngle(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<float>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 )
	) );
	sgs_PushReal( C, val1 );
	return 2;
}

static int sgsimgui_SliderInt( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt" );
	int val1 = sgs_GetVar<int>()( C, 1 );
	sgs_PushVar( C, ImGui::SliderInt(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<int>()( C, 2 ),
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<const char *>()( C, 4 )
	) );
	sgs_PushInt( C, val1 );
	return 2;
}

static int sgsimgui_SliderInt2( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt2" );
	int val1[2] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ) };
	sgs_PushVar( C, ImGui::SliderInt2(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 3 ),
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<const char *>()( C, 5 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	return 3;
}

static int sgsimgui_SliderInt3( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt3" );
	int val1[3] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ) };
	sgs_PushVar( C, ImGui::SliderInt3(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	return 4;
}

static int sgsimgui_SliderInt4( SGS_CTX )
{
	SGSFN( "ImGui_SliderInt4" );
	int val1[4] = { sgs_GetVar<int>()( C, 1 ), sgs_GetVar<int>()( C, 2 ), sgs_GetVar<int>()( C, 3 ), sgs_GetVar<int>()( C, 4 ) };
	sgs_PushVar( C, ImGui::SliderInt4(
		sgs_GetVar<const char *>()( C, 0 ),
		val1,
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<int>()( C, 6 ),
		sgs_GetVar<const char *>()( C, 7 )
	) );
	sgs_PushInt( C, val1[0] );
	sgs_PushInt( C, val1[1] );
	sgs_PushInt( C, val1[2] );
	sgs_PushInt( C, val1[3] );
	return 5;
}

static int sgsimgui_VSliderFloat( SGS_CTX )
{
	SGSFN( "ImGui_VSliderFloat" );
	float val3 = sgs_GetVar<float>()( C, 3 );
	sgs_PushVar( C, ImGui::VSliderFloat(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		&val3,
		sgs_GetVar<float>()( C, 4 ),
		sgs_GetVar<float>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 ),
		sgs_GetVar<float>()( C, 7 )
	) );
	sgs_PushReal( C, val3 );
	return 2;
}

static int sgsimgui_VSliderInt( SGS_CTX )
{
	SGSFN( "ImGui_VSliderInt" );
	int val3 = sgs_GetVar<int>()( C, 3 );
	sgs_PushVar( C, ImGui::VSliderInt(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		&val3,
		sgs_GetVar<int>()( C, 4 ),
		sgs_GetVar<int>()( C, 5 ),
		sgs_GetVar<const char *>()( C, 6 )
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

static int sgsimgui_TreePush( SGS_CTX )
{
	SGSFN( "ImGui_TreePush" );
	ImGui::TreePush(
		sgs_GetVar<const void *>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_TreePop( SGS_CTX )
{
	SGSFN( "ImGui_TreePop" );
	ImGui::TreePop();
	return 0;
}

static int sgsimgui_TreeAdvanceToLabelPos( SGS_CTX )
{
	SGSFN( "ImGui_TreeAdvanceToLabelPos" );
	ImGui::TreeAdvanceToLabelPos();
	return 0;
}

static int sgsimgui_GetTreeNodeToLabelSpacing( SGS_CTX )
{
	SGSFN( "ImGui_GetTreeNodeToLabelSpacing" );
	sgs_PushVar( C, ImGui::GetTreeNodeToLabelSpacing() );
	return 1;
}

static int sgsimgui_SetNextTreeNodeOpen( SGS_CTX )
{
	SGSFN( "ImGui_SetNextTreeNodeOpen" );
	ImGui::SetNextTreeNodeOpen(
		sgs_GetVar<bool>()( C, 0 ),
		sgs_GetVar<ImGuiSetCond>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_CollapsingHeader( SGS_CTX )
{
	SGSFN( "ImGui_CollapsingHeader" );
	sgs_PushVar( C, ImGui::CollapsingHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImGuiTreeNodeFlags>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_CollapsingHeaderCloseable( SGS_CTX )
{
	SGSFN( "ImGui_CollapsingHeaderCloseable" );
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::CollapsingHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<ImGuiTreeNodeFlags>()( C, 2 )
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsimgui_Selectable( SGS_CTX )
{
	SGSFN( "ImGui_Selectable" );
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::Selectable(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<ImGuiSelectableFlags>()( C, 2 ),
		sgs_GetVar<ImVec2>()( C, 3 )
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsimgui_ListBoxHeader( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxHeader" );
	sgs_PushVar( C, ImGui::ListBoxHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_ListBoxHeader2( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxHeader2" );
	sgs_PushVar( C, ImGui::ListBoxHeader(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 ),
		sgs_GetVar<int>()( C, 2 )
	) );
	return 1;
}

static int sgsimgui_ListBoxFooter( SGS_CTX )
{
	SGSFN( "ImGui_ListBoxFooter" );
	ImGui::ListBoxFooter();
	return 0;
}

static int sgsimgui_ValueB( SGS_CTX )
{
	SGSFN( "ImGui_ValueB" );
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_ValueI( SGS_CTX )
{
	SGSFN( "ImGui_ValueI" );
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_ValueU( SGS_CTX )
{
	SGSFN( "ImGui_ValueU" );
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<unsigned int>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_ValueF( SGS_CTX )
{
	SGSFN( "ImGui_ValueF" );
	ImGui::Value(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 ),
		sgs_GetVar<const char *>()( C, 2 )
	);
	return 0;
}

static int sgsimgui_ValueColorF( SGS_CTX )
{
	SGSFN( "ImGui_ValueColorF" );
	ImGui::ValueColor(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImVec4>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_ValueColor( SGS_CTX )
{
	SGSFN( "ImGui_ValueColor" );
	ImGui::ValueColor(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<ImU32>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_SetTooltip( SGS_CTX )
{
	SGSFN( "ImGui_SetTooltip" );
	ImGui::SetTooltip(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_BeginTooltip( SGS_CTX )
{
	SGSFN( "ImGui_BeginTooltip" );
	ImGui::BeginTooltip();
	return 0;
}

static int sgsimgui_EndTooltip( SGS_CTX )
{
	SGSFN( "ImGui_EndTooltip" );
	ImGui::EndTooltip();
	return 0;
}

static int sgsimgui_BeginMainMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_BeginMainMenuBar" );
	sgs_PushVar( C, ImGui::BeginMainMenuBar() );
	return 1;
}

static int sgsimgui_EndMainMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_EndMainMenuBar" );
	ImGui::EndMainMenuBar();
	return 0;
}

static int sgsimgui_BeginMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_BeginMenuBar" );
	sgs_PushVar( C, ImGui::BeginMenuBar() );
	return 1;
}

static int sgsimgui_EndMenuBar( SGS_CTX )
{
	SGSFN( "ImGui_EndMenuBar" );
	ImGui::EndMenuBar();
	return 0;
}

static int sgsimgui_BeginMenu( SGS_CTX )
{
	SGSFN( "ImGui_BeginMenu" );
	sgs_PushVar( C, ImGui::BeginMenu(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_EndMenu( SGS_CTX )
{
	SGSFN( "ImGui_EndMenu" );
	ImGui::EndMenu();
	return 0;
}

static int sgsimgui_MenuItem( SGS_CTX )
{
	SGSFN( "ImGui_MenuItem" );
	bool val2 = sgs_GetVar<bool>()( C, 2 );
	sgs_PushVar( C, ImGui::MenuItem(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 ),
		&val2,
		sgs_GetVar<bool>()( C, 3 )
	) );
	sgs_PushBool( C, val2 );
	return 2;
}

static int sgsimgui_OpenPopup( SGS_CTX )
{
	SGSFN( "ImGui_OpenPopup" );
	ImGui::OpenPopup(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_BeginPopup( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopup" );
	sgs_PushVar( C, ImGui::BeginPopup(
		sgs_GetVar<const char *>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_BeginPopupModal( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupModal" );
	bool val1 = sgs_GetVar<bool>()( C, 1 );
	sgs_PushVar( C, ImGui::BeginPopupModal(
		sgs_GetVar<const char *>()( C, 0 ),
		&val1,
		sgs_GetVar<ImGuiWindowFlags>()( C, 2 )
	) );
	sgs_PushBool( C, val1 );
	return 2;
}

static int sgsimgui_BeginPopupContextItem( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextItem" );
	sgs_PushVar( C, ImGui::BeginPopupContextItem(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_BeginPopupContextWindow( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextWindow" );
	sgs_PushVar( C, ImGui::BeginPopupContextWindow(
		sgs_GetVar<bool>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 ),
		sgs_GetVar<int>()( C, 2 )
	) );
	return 1;
}

static int sgsimgui_BeginPopupContextVoid( SGS_CTX )
{
	SGSFN( "ImGui_BeginPopupContextVoid" );
	sgs_PushVar( C, ImGui::BeginPopupContextVoid(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<int>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_EndPopup( SGS_CTX )
{
	SGSFN( "ImGui_EndPopup" );
	ImGui::EndPopup();
	return 0;
}

static int sgsimgui_CloseCurrentPopup( SGS_CTX )
{
	SGSFN( "ImGui_CloseCurrentPopup" );
	ImGui::CloseCurrentPopup();
	return 0;
}

static int sgsimgui_LogToTTY( SGS_CTX )
{
	SGSFN( "ImGui_LogToTTY" );
	ImGui::LogToTTY(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_LogToFile( SGS_CTX )
{
	SGSFN( "ImGui_LogToFile" );
	ImGui::LogToFile(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 )
	);
	return 0;
}

static int sgsimgui_LogToClipboard( SGS_CTX )
{
	SGSFN( "ImGui_LogToClipboard" );
	ImGui::LogToClipboard(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_LogFinish( SGS_CTX )
{
	SGSFN( "ImGui_LogFinish" );
	ImGui::LogFinish();
	return 0;
}

static int sgsimgui_LogButtons( SGS_CTX )
{
	SGSFN( "ImGui_LogButtons" );
	ImGui::LogButtons();
	return 0;
}

static int sgsimgui_LogText( SGS_CTX )
{
	SGSFN( "ImGui_LogText" );
	ImGui::LogText(
		"%s",
		sgs_GetVar<const char*>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_PushClipRect( SGS_CTX )
{
	SGSFN( "ImGui_PushClipRect" );
	ImGui::PushClipRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<bool>()( C, 4 )
	);
	return 0;
}

static int sgsimgui_PopClipRect( SGS_CTX )
{
	SGSFN( "ImGui_PopClipRect" );
	ImGui::PopClipRect();
	return 0;
}

static int sgsimgui_IsItemHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsItemHovered" );
	sgs_PushVar( C, ImGui::IsItemHovered() );
	return 1;
}

static int sgsimgui_IsItemHoveredRect( SGS_CTX )
{
	SGSFN( "ImGui_IsItemHoveredRect" );
	sgs_PushVar( C, ImGui::IsItemHoveredRect() );
	return 1;
}

static int sgsimgui_IsItemActive( SGS_CTX )
{
	SGSFN( "ImGui_IsItemActive" );
	sgs_PushVar( C, ImGui::IsItemActive() );
	return 1;
}

static int sgsimgui_IsItemClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsItemClicked" );
	sgs_PushVar( C, ImGui::IsItemClicked(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsItemVisible( SGS_CTX )
{
	SGSFN( "ImGui_IsItemVisible" );
	sgs_PushVar( C, ImGui::IsItemVisible() );
	return 1;
}

static int sgsimgui_IsAnyItemHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsAnyItemHovered" );
	sgs_PushVar( C, ImGui::IsAnyItemHovered() );
	return 1;
}

static int sgsimgui_IsAnyItemActive( SGS_CTX )
{
	SGSFN( "ImGui_IsAnyItemActive" );
	sgs_PushVar( C, ImGui::IsAnyItemActive() );
	return 1;
}

static int sgsimgui_GetItemRectMin( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectMin" );
	sgs_PushVar( C, ImGui::GetItemRectMin() );
	return 2;
}

static int sgsimgui_GetItemRectMax( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectMax" );
	sgs_PushVar( C, ImGui::GetItemRectMax() );
	return 2;
}

static int sgsimgui_GetItemRectSize( SGS_CTX )
{
	SGSFN( "ImGui_GetItemRectSize" );
	sgs_PushVar( C, ImGui::GetItemRectSize() );
	return 2;
}

static int sgsimgui_SetItemAllowOverlap( SGS_CTX )
{
	SGSFN( "ImGui_SetItemAllowOverlap" );
	ImGui::SetItemAllowOverlap();
	return 0;
}

static int sgsimgui_IsWindowHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowHovered" );
	sgs_PushVar( C, ImGui::IsWindowHovered() );
	return 1;
}

static int sgsimgui_IsWindowFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsWindowFocused" );
	sgs_PushVar( C, ImGui::IsWindowFocused() );
	return 1;
}

static int sgsimgui_IsRootWindowFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowFocused" );
	sgs_PushVar( C, ImGui::IsRootWindowFocused() );
	return 1;
}

static int sgsimgui_IsRootWindowOrAnyChildFocused( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowOrAnyChildFocused" );
	sgs_PushVar( C, ImGui::IsRootWindowOrAnyChildFocused() );
	return 1;
}

static int sgsimgui_IsRootWindowOrAnyChildHovered( SGS_CTX )
{
	SGSFN( "ImGui_IsRootWindowOrAnyChildHovered" );
	sgs_PushVar( C, ImGui::IsRootWindowOrAnyChildHovered() );
	return 1;
}

static int sgsimgui_IsRectVisible( SGS_CTX )
{
	SGSFN( "ImGui_IsRectVisible" );
	sgs_PushVar( C, ImGui::IsRectVisible(
		sgs_GetVar<ImVec2>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsRectVisibleScreen( SGS_CTX )
{
	SGSFN( "ImGui_IsRectVisibleScreen" );
	sgs_PushVar( C, ImGui::IsRectVisible(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 )
	) );
	return 1;
}

static int sgsimgui_IsPosHoveringAnyWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsPosHoveringAnyWindow" );
	sgs_PushVar( C, ImGui::IsPosHoveringAnyWindow(
		sgs_GetVar<ImVec2>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_GetTime( SGS_CTX )
{
	SGSFN( "ImGui_GetTime" );
	sgs_PushVar( C, ImGui::GetTime() );
	return 1;
}

static int sgsimgui_GetFrameCount( SGS_CTX )
{
	SGSFN( "ImGui_GetFrameCount" );
	sgs_PushVar( C, ImGui::GetFrameCount() );
	return 1;
}

static int sgsimgui_GetStyleColName( SGS_CTX )
{
	SGSFN( "ImGui_GetStyleColName" );
	sgs_PushVar( C, ImGui::GetStyleColName(
		sgs_GetVar<ImGuiCol>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_CalcItemRectClosestPoint( SGS_CTX )
{
	SGSFN( "ImGui_CalcItemRectClosestPoint" );
	sgs_PushVar( C, ImGui::CalcItemRectClosestPoint(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<bool>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 )
	) );
	return 2;
}

static int sgsimgui_CalcTextSize( SGS_CTX )
{
	SGSFN( "ImGui_CalcTextSize" );
	sgs_PushVar( C, ImGui::CalcTextSize(
		sgs_GetVar<const char *>()( C, 0 ),
		sgs_GetVar<const char *>()( C, 1 ),
		sgs_GetVar<bool>()( C, 2 ),
		sgs_GetVar<float>()( C, 3 )
	) );
	return 2;
}

static int sgsimgui_CalcListClipping( SGS_CTX )
{
	SGSFN( "ImGui_CalcListClipping" );
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

static int sgsimgui_BeginChildFrame( SGS_CTX )
{
	SGSFN( "ImGui_BeginChildFrame" );
	sgs_PushVar( C, ImGui::BeginChildFrame(
		sgs_GetVar<ImGuiID>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 1 ),
		sgs_GetVar<ImGuiWindowFlags>()( C, 3 )
	) );
	return 1;
}

static int sgsimgui_EndChildFrame( SGS_CTX )
{
	SGSFN( "ImGui_EndChildFrame" );
	ImGui::EndChildFrame();
	return 0;
}

static int sgsimgui_ColorConvertU32ToFloat4( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertU32ToFloat4" );
	sgs_PushVar( C, ImGui::ColorConvertU32ToFloat4(
		sgs_GetVar<ImU32>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_ColorConvertFloat4ToU32( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertFloat4ToU32" );
	sgs_PushVar( C, ImGui::ColorConvertFloat4ToU32(
		sgs_GetVar<ImVec4>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_ColorConvertRGBtoHSV( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertRGBtoHSV" );
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

static int sgsimgui_ColorConvertHSVtoRGB( SGS_CTX )
{
	SGSFN( "ImGui_ColorConvertHSVtoRGB" );
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

static int sgsimgui_GetKeyIndex( SGS_CTX )
{
	SGSFN( "ImGui_GetKeyIndex" );
	sgs_PushVar( C, ImGui::GetKeyIndex(
		sgs_GetVar<ImGuiKey>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsKeyDown( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyDown" );
	sgs_PushVar( C, ImGui::IsKeyDown(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsKeyPressed( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyPressed" );
	sgs_PushVar( C, ImGui::IsKeyPressed(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_IsKeyReleased( SGS_CTX )
{
	SGSFN( "ImGui_IsKeyReleased" );
	sgs_PushVar( C, ImGui::IsKeyReleased(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsMouseDown( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDown" );
	sgs_PushVar( C, ImGui::IsMouseDown(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsMouseClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseClicked" );
	sgs_PushVar( C, ImGui::IsMouseClicked(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<bool>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_IsMouseDoubleClicked( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDoubleClicked" );
	sgs_PushVar( C, ImGui::IsMouseDoubleClicked(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsMouseReleased( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseReleased" );
	sgs_PushVar( C, ImGui::IsMouseReleased(
		sgs_GetVar<int>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_IsMouseHoveringWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringWindow" );
	sgs_PushVar( C, ImGui::IsMouseHoveringWindow() );
	return 1;
}

static int sgsimgui_IsMouseHoveringAnyWindow( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringAnyWindow" );
	sgs_PushVar( C, ImGui::IsMouseHoveringAnyWindow() );
	return 1;
}

static int sgsimgui_IsMouseHoveringRect( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseHoveringRect" );
	sgs_PushVar( C, ImGui::IsMouseHoveringRect(
		sgs_GetVar<ImVec2>()( C, 0 ),
		sgs_GetVar<ImVec2>()( C, 2 ),
		sgs_GetVar<bool>()( C, 4 )
	) );
	return 1;
}

static int sgsimgui_IsMouseDragging( SGS_CTX )
{
	SGSFN( "ImGui_IsMouseDragging" );
	sgs_PushVar( C, ImGui::IsMouseDragging(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	) );
	return 1;
}

static int sgsimgui_GetMousePos( SGS_CTX )
{
	SGSFN( "ImGui_GetMousePos" );
	sgs_PushVar( C, ImGui::GetMousePos() );
	return 2;
}

static int sgsimgui_GetMousePosOnOpeningCurrentPopup( SGS_CTX )
{
	SGSFN( "ImGui_GetMousePosOnOpeningCurrentPopup" );
	sgs_PushVar( C, ImGui::GetMousePosOnOpeningCurrentPopup() );
	return 2;
}

static int sgsimgui_GetMouseDragDelta( SGS_CTX )
{
	SGSFN( "ImGui_GetMouseDragDelta" );
	sgs_PushVar( C, ImGui::GetMouseDragDelta(
		sgs_GetVar<int>()( C, 0 ),
		sgs_GetVar<float>()( C, 1 )
	) );
	return 2;
}

static int sgsimgui_ResetMouseDragDelta( SGS_CTX )
{
	SGSFN( "ImGui_ResetMouseDragDelta" );
	ImGui::ResetMouseDragDelta(
		sgs_GetVar<int>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetMouseCursor( SGS_CTX )
{
	SGSFN( "ImGui_GetMouseCursor" );
	sgs_PushVar( C, ImGui::GetMouseCursor() );
	return 1;
}

static int sgsimgui_SetMouseCursor( SGS_CTX )
{
	SGSFN( "ImGui_SetMouseCursor" );
	ImGui::SetMouseCursor(
		sgs_GetVar<ImGuiMouseCursor>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_CaptureKeyboardFromApp( SGS_CTX )
{
	SGSFN( "ImGui_CaptureKeyboardFromApp" );
	ImGui::CaptureKeyboardFromApp(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_CaptureMouseFromApp( SGS_CTX )
{
	SGSFN( "ImGui_CaptureMouseFromApp" );
	ImGui::CaptureMouseFromApp(
		sgs_GetVar<bool>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_MemAlloc( SGS_CTX )
{
	SGSFN( "ImGui_MemAlloc" );
	sgs_PushVar( C, ImGui::MemAlloc(
		sgs_GetVar<size_t>()( C, 0 )
	) );
	return 1;
}

static int sgsimgui_MemFree( SGS_CTX )
{
	SGSFN( "ImGui_MemFree" );
	ImGui::MemFree(
		sgs_GetVar<void *>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetClipboardText( SGS_CTX )
{
	SGSFN( "ImGui_GetClipboardText" );
	sgs_PushVar( C, ImGui::GetClipboardText() );
	return 1;
}

static int sgsimgui_SetClipboardText( SGS_CTX )
{
	SGSFN( "ImGui_SetClipboardText" );
	ImGui::SetClipboardText(
		sgs_GetVar<const char *>()( C, 0 )
	);
	return 0;
}

static int sgsimgui_GetVersion( SGS_CTX )
{
	SGSFN( "ImGui_GetVersion" );
	sgs_PushVar( C, ImGui::GetVersion() );
	return 1;
}


static sgs_RegFuncConst imgui_fconsts[] =
{
	{ "ImGui_NewFrame", sgsimgui_NewFrame },
	{ "ImGui_Render", sgsimgui_Render },
	{ "ImGui_Shutdown", sgsimgui_Shutdown },
	{ "ImGui_ShowUserGuide", sgsimgui_ShowUserGuide },
	{ "ImGui_ShowTestWindow", sgsimgui_ShowTestWindow },
	{ "ImGui_ShowMetricsWindow", sgsimgui_ShowMetricsWindow },
	{ "ImGui_Begin", sgsimgui_Begin },
	{ "ImGui_End", sgsimgui_End },
	{ "ImGui_EndChild", sgsimgui_EndChild },
	{ "ImGui_GetContentRegionMax", sgsimgui_GetContentRegionMax },
	{ "ImGui_GetContentRegionAvail", sgsimgui_GetContentRegionAvail },
	{ "ImGui_GetContentRegionAvailWidth", sgsimgui_GetContentRegionAvailWidth },
	{ "ImGui_GetWindowContentRegionMin", sgsimgui_GetWindowContentRegionMin },
	{ "ImGui_GetWindowContentRegionMax", sgsimgui_GetWindowContentRegionMax },
	{ "ImGui_GetWindowContentRegionWidth", sgsimgui_GetWindowContentRegionWidth },
	{ "ImGui_GetWindowPos", sgsimgui_GetWindowPos },
	{ "ImGui_GetWindowSize", sgsimgui_GetWindowSize },
	{ "ImGui_GetWindowWidth", sgsimgui_GetWindowWidth },
	{ "ImGui_GetWindowHeight", sgsimgui_GetWindowHeight },
	{ "ImGui_IsWindowCollapsed", sgsimgui_IsWindowCollapsed },
	{ "ImGui_SetWindowFontScale", sgsimgui_SetWindowFontScale },
	{ "ImGui_SetNextWindowPos", sgsimgui_SetNextWindowPos },
	{ "ImGui_SetNextWindowPosCenter", sgsimgui_SetNextWindowPosCenter },
	{ "ImGui_SetNextWindowSize", sgsimgui_SetNextWindowSize },
	{ "ImGui_SetNextWindowContentSize", sgsimgui_SetNextWindowContentSize },
	{ "ImGui_SetNextWindowContentWidth", sgsimgui_SetNextWindowContentWidth },
	{ "ImGui_SetNextWindowCollapsed", sgsimgui_SetNextWindowCollapsed },
	{ "ImGui_SetNextWindowFocus", sgsimgui_SetNextWindowFocus },
	{ "ImGui_SetCurrentWindowPos", sgsimgui_SetCurrentWindowPos },
	{ "ImGui_SetCurrentWindowSize", sgsimgui_SetCurrentWindowSize },
	{ "ImGui_SetCurrentWindowCollapsed", sgsimgui_SetCurrentWindowCollapsed },
	{ "ImGui_SetCurrentWindowFocus", sgsimgui_SetCurrentWindowFocus },
	{ "ImGui_SetWindowPos", sgsimgui_SetWindowPos },
	{ "ImGui_SetWindowSize", sgsimgui_SetWindowSize },
	{ "ImGui_SetWindowCollapsed", sgsimgui_SetWindowCollapsed },
	{ "ImGui_SetWindowFocus", sgsimgui_SetWindowFocus },
	{ "ImGui_GetScrollX", sgsimgui_GetScrollX },
	{ "ImGui_GetScrollY", sgsimgui_GetScrollY },
	{ "ImGui_GetScrollMaxX", sgsimgui_GetScrollMaxX },
	{ "ImGui_GetScrollMaxY", sgsimgui_GetScrollMaxY },
	{ "ImGui_SetScrollX", sgsimgui_SetScrollX },
	{ "ImGui_SetScrollY", sgsimgui_SetScrollY },
	{ "ImGui_SetScrollHere", sgsimgui_SetScrollHere },
	{ "ImGui_SetScrollFromPosY", sgsimgui_SetScrollFromPosY },
	{ "ImGui_SetKeyboardFocusHere", sgsimgui_SetKeyboardFocusHere },
	{ "ImGui_PopFont", sgsimgui_PopFont },
	{ "ImGui_PushStyleColor", sgsimgui_PushStyleColor },
	{ "ImGui_PopStyleColor", sgsimgui_PopStyleColor },
	{ "ImGui_PushStyleVarF", sgsimgui_PushStyleVarF },
	{ "ImGui_PushStyleVarV2", sgsimgui_PushStyleVarV2 },
	{ "ImGui_PopStyleVar", sgsimgui_PopStyleVar },
	{ "ImGui_GetFontSize", sgsimgui_GetFontSize },
	{ "ImGui_GetFontTexUvWhitePixel", sgsimgui_GetFontTexUvWhitePixel },
	{ "ImGui_PushItemWidth", sgsimgui_PushItemWidth },
	{ "ImGui_PopItemWidth", sgsimgui_PopItemWidth },
	{ "ImGui_CalcItemWidth", sgsimgui_CalcItemWidth },
	{ "ImGui_PushTextWrapPos", sgsimgui_PushTextWrapPos },
	{ "ImGui_PopTextWrapPos", sgsimgui_PopTextWrapPos },
	{ "ImGui_PushAllowKeyboardFocus", sgsimgui_PushAllowKeyboardFocus },
	{ "ImGui_PopAllowKeyboardFocus", sgsimgui_PopAllowKeyboardFocus },
	{ "ImGui_PushButtonRepeat", sgsimgui_PushButtonRepeat },
	{ "ImGui_PopButtonRepeat", sgsimgui_PopButtonRepeat },
	{ "ImGui_Separator", sgsimgui_Separator },
	{ "ImGui_SameLine", sgsimgui_SameLine },
	{ "ImGui_NewLine", sgsimgui_NewLine },
	{ "ImGui_Spacing", sgsimgui_Spacing },
	{ "ImGui_Dummy", sgsimgui_Dummy },
	{ "ImGui_Indent", sgsimgui_Indent },
	{ "ImGui_Unindent", sgsimgui_Unindent },
	{ "ImGui_BeginGroup", sgsimgui_BeginGroup },
	{ "ImGui_EndGroup", sgsimgui_EndGroup },
	{ "ImGui_GetCursorPos", sgsimgui_GetCursorPos },
	{ "ImGui_GetCursorPosX", sgsimgui_GetCursorPosX },
	{ "ImGui_GetCursorPosY", sgsimgui_GetCursorPosY },
	{ "ImGui_SetCursorPos", sgsimgui_SetCursorPos },
	{ "ImGui_SetCursorPosX", sgsimgui_SetCursorPosX },
	{ "ImGui_SetCursorPosY", sgsimgui_SetCursorPosY },
	{ "ImGui_GetCursorStartPos", sgsimgui_GetCursorStartPos },
	{ "ImGui_GetCursorScreenPos", sgsimgui_GetCursorScreenPos },
	{ "ImGui_SetCursorScreenPos", sgsimgui_SetCursorScreenPos },
	{ "ImGui_AlignFirstTextHeightToWidgets", sgsimgui_AlignFirstTextHeightToWidgets },
	{ "ImGui_GetTextLineHeight", sgsimgui_GetTextLineHeight },
	{ "ImGui_GetTextLineHeightWithSpacing", sgsimgui_GetTextLineHeightWithSpacing },
	{ "ImGui_GetItemsLineHeightWithSpacing", sgsimgui_GetItemsLineHeightWithSpacing },
	{ "ImGui_Columns", sgsimgui_Columns },
	{ "ImGui_NextColumn", sgsimgui_NextColumn },
	{ "ImGui_GetColumnIndex", sgsimgui_GetColumnIndex },
	{ "ImGui_GetColumnOffset", sgsimgui_GetColumnOffset },
	{ "ImGui_SetColumnOffset", sgsimgui_SetColumnOffset },
	{ "ImGui_GetColumnWidth", sgsimgui_GetColumnWidth },
	{ "ImGui_GetColumnsCount", sgsimgui_GetColumnsCount },
	{ "ImGui_PushID", sgsimgui_PushID },
	{ "ImGui_PopID", sgsimgui_PopID },
	{ "ImGui_GetID", sgsimgui_GetID },
	{ "ImGui_Text", sgsimgui_Text },
	{ "ImGui_TextColored", sgsimgui_TextColored },
	{ "ImGui_TextDisabled", sgsimgui_TextDisabled },
	{ "ImGui_TextWrapped", sgsimgui_TextWrapped },
	{ "ImGui_TextUnformatted", sgsimgui_TextUnformatted },
	{ "ImGui_LabelText", sgsimgui_LabelText },
	{ "ImGui_Bullet", sgsimgui_Bullet },
	{ "ImGui_BulletText", sgsimgui_BulletText },
	{ "ImGui_Button", sgsimgui_Button },
	{ "ImGui_SmallButton", sgsimgui_SmallButton },
	{ "ImGui_InvisibleButton", sgsimgui_InvisibleButton },
	{ "ImGui_Image", sgsimgui_Image },
	{ "ImGui_ImageButton", sgsimgui_ImageButton },
	{ "ImGui_Checkbox", sgsimgui_Checkbox },
	{ "ImGui_CheckboxFlags", sgsimgui_CheckboxFlags },
	{ "ImGui_RadioButton", sgsimgui_RadioButton },
	{ "ImGui_ColorButton", sgsimgui_ColorButton },
	{ "ImGui_ColorEdit3", sgsimgui_ColorEdit3 },
	{ "ImGui_ColorEdit4", sgsimgui_ColorEdit4 },
	{ "ImGui_ColorEditMode", sgsimgui_ColorEditMode },
	{ "ImGui_ProgressBar", sgsimgui_ProgressBar },
	{ "ImGui_DragFloat", sgsimgui_DragFloat },
	{ "ImGui_DragFloat2", sgsimgui_DragFloat2 },
	{ "ImGui_DragFloat3", sgsimgui_DragFloat3 },
	{ "ImGui_DragFloat4", sgsimgui_DragFloat4 },
	{ "ImGui_DragFloatRange2", sgsimgui_DragFloatRange2 },
	{ "ImGui_DragInt", sgsimgui_DragInt },
	{ "ImGui_DragInt2", sgsimgui_DragInt2 },
	{ "ImGui_DragInt3", sgsimgui_DragInt3 },
	{ "ImGui_DragInt4", sgsimgui_DragInt4 },
	{ "ImGui_DragIntRange2", sgsimgui_DragIntRange2 },
	{ "ImGui_InputFloat", sgsimgui_InputFloat },
	{ "ImGui_InputFloat2", sgsimgui_InputFloat2 },
	{ "ImGui_InputFloat3", sgsimgui_InputFloat3 },
	{ "ImGui_InputFloat4", sgsimgui_InputFloat4 },
	{ "ImGui_InputInt", sgsimgui_InputInt },
	{ "ImGui_InputInt2", sgsimgui_InputInt2 },
	{ "ImGui_InputInt3", sgsimgui_InputInt3 },
	{ "ImGui_InputInt4", sgsimgui_InputInt4 },
	{ "ImGui_SliderFloat", sgsimgui_SliderFloat },
	{ "ImGui_SliderFloat2", sgsimgui_SliderFloat2 },
	{ "ImGui_SliderFloat3", sgsimgui_SliderFloat3 },
	{ "ImGui_SliderFloat4", sgsimgui_SliderFloat4 },
	{ "ImGui_SliderAngle", sgsimgui_SliderAngle },
	{ "ImGui_SliderInt", sgsimgui_SliderInt },
	{ "ImGui_SliderInt2", sgsimgui_SliderInt2 },
	{ "ImGui_SliderInt3", sgsimgui_SliderInt3 },
	{ "ImGui_SliderInt4", sgsimgui_SliderInt4 },
	{ "ImGui_VSliderFloat", sgsimgui_VSliderFloat },
	{ "ImGui_VSliderInt", sgsimgui_VSliderInt },
	{ "ImGui_TreeNode", sgsimgui_TreeNode },
	{ "ImGui_TreeNodeEx", sgsimgui_TreeNodeEx },
	{ "ImGui_TreePush", sgsimgui_TreePush },
	{ "ImGui_TreePop", sgsimgui_TreePop },
	{ "ImGui_TreeAdvanceToLabelPos", sgsimgui_TreeAdvanceToLabelPos },
	{ "ImGui_GetTreeNodeToLabelSpacing", sgsimgui_GetTreeNodeToLabelSpacing },
	{ "ImGui_SetNextTreeNodeOpen", sgsimgui_SetNextTreeNodeOpen },
	{ "ImGui_CollapsingHeader", sgsimgui_CollapsingHeader },
	{ "ImGui_CollapsingHeaderCloseable", sgsimgui_CollapsingHeaderCloseable },
	{ "ImGui_Selectable", sgsimgui_Selectable },
	{ "ImGui_ListBoxHeader", sgsimgui_ListBoxHeader },
	{ "ImGui_ListBoxHeader2", sgsimgui_ListBoxHeader2 },
	{ "ImGui_ListBoxFooter", sgsimgui_ListBoxFooter },
	{ "ImGui_ValueB", sgsimgui_ValueB },
	{ "ImGui_ValueI", sgsimgui_ValueI },
	{ "ImGui_ValueU", sgsimgui_ValueU },
	{ "ImGui_ValueF", sgsimgui_ValueF },
	{ "ImGui_ValueColorF", sgsimgui_ValueColorF },
	{ "ImGui_ValueColor", sgsimgui_ValueColor },
	{ "ImGui_SetTooltip", sgsimgui_SetTooltip },
	{ "ImGui_BeginTooltip", sgsimgui_BeginTooltip },
	{ "ImGui_EndTooltip", sgsimgui_EndTooltip },
	{ "ImGui_BeginMainMenuBar", sgsimgui_BeginMainMenuBar },
	{ "ImGui_EndMainMenuBar", sgsimgui_EndMainMenuBar },
	{ "ImGui_BeginMenuBar", sgsimgui_BeginMenuBar },
	{ "ImGui_EndMenuBar", sgsimgui_EndMenuBar },
	{ "ImGui_BeginMenu", sgsimgui_BeginMenu },
	{ "ImGui_EndMenu", sgsimgui_EndMenu },
	{ "ImGui_MenuItem", sgsimgui_MenuItem },
	{ "ImGui_OpenPopup", sgsimgui_OpenPopup },
	{ "ImGui_BeginPopup", sgsimgui_BeginPopup },
	{ "ImGui_BeginPopupModal", sgsimgui_BeginPopupModal },
	{ "ImGui_BeginPopupContextItem", sgsimgui_BeginPopupContextItem },
	{ "ImGui_BeginPopupContextWindow", sgsimgui_BeginPopupContextWindow },
	{ "ImGui_BeginPopupContextVoid", sgsimgui_BeginPopupContextVoid },
	{ "ImGui_EndPopup", sgsimgui_EndPopup },
	{ "ImGui_CloseCurrentPopup", sgsimgui_CloseCurrentPopup },
	{ "ImGui_LogToTTY", sgsimgui_LogToTTY },
	{ "ImGui_LogToFile", sgsimgui_LogToFile },
	{ "ImGui_LogToClipboard", sgsimgui_LogToClipboard },
	{ "ImGui_LogFinish", sgsimgui_LogFinish },
	{ "ImGui_LogButtons", sgsimgui_LogButtons },
	{ "ImGui_LogText", sgsimgui_LogText },
	{ "ImGui_PushClipRect", sgsimgui_PushClipRect },
	{ "ImGui_PopClipRect", sgsimgui_PopClipRect },
	{ "ImGui_IsItemHovered", sgsimgui_IsItemHovered },
	{ "ImGui_IsItemHoveredRect", sgsimgui_IsItemHoveredRect },
	{ "ImGui_IsItemActive", sgsimgui_IsItemActive },
	{ "ImGui_IsItemClicked", sgsimgui_IsItemClicked },
	{ "ImGui_IsItemVisible", sgsimgui_IsItemVisible },
	{ "ImGui_IsAnyItemHovered", sgsimgui_IsAnyItemHovered },
	{ "ImGui_IsAnyItemActive", sgsimgui_IsAnyItemActive },
	{ "ImGui_GetItemRectMin", sgsimgui_GetItemRectMin },
	{ "ImGui_GetItemRectMax", sgsimgui_GetItemRectMax },
	{ "ImGui_GetItemRectSize", sgsimgui_GetItemRectSize },
	{ "ImGui_SetItemAllowOverlap", sgsimgui_SetItemAllowOverlap },
	{ "ImGui_IsWindowHovered", sgsimgui_IsWindowHovered },
	{ "ImGui_IsWindowFocused", sgsimgui_IsWindowFocused },
	{ "ImGui_IsRootWindowFocused", sgsimgui_IsRootWindowFocused },
	{ "ImGui_IsRootWindowOrAnyChildFocused", sgsimgui_IsRootWindowOrAnyChildFocused },
	{ "ImGui_IsRootWindowOrAnyChildHovered", sgsimgui_IsRootWindowOrAnyChildHovered },
	{ "ImGui_IsRectVisible", sgsimgui_IsRectVisible },
	{ "ImGui_IsRectVisibleScreen", sgsimgui_IsRectVisibleScreen },
	{ "ImGui_IsPosHoveringAnyWindow", sgsimgui_IsPosHoveringAnyWindow },
	{ "ImGui_GetTime", sgsimgui_GetTime },
	{ "ImGui_GetFrameCount", sgsimgui_GetFrameCount },
	{ "ImGui_GetStyleColName", sgsimgui_GetStyleColName },
	{ "ImGui_CalcItemRectClosestPoint", sgsimgui_CalcItemRectClosestPoint },
	{ "ImGui_CalcTextSize", sgsimgui_CalcTextSize },
	{ "ImGui_CalcListClipping", sgsimgui_CalcListClipping },
	{ "ImGui_BeginChildFrame", sgsimgui_BeginChildFrame },
	{ "ImGui_EndChildFrame", sgsimgui_EndChildFrame },
	{ "ImGui_ColorConvertU32ToFloat4", sgsimgui_ColorConvertU32ToFloat4 },
	{ "ImGui_ColorConvertFloat4ToU32", sgsimgui_ColorConvertFloat4ToU32 },
	{ "ImGui_ColorConvertRGBtoHSV", sgsimgui_ColorConvertRGBtoHSV },
	{ "ImGui_ColorConvertHSVtoRGB", sgsimgui_ColorConvertHSVtoRGB },
	{ "ImGui_GetKeyIndex", sgsimgui_GetKeyIndex },
	{ "ImGui_IsKeyDown", sgsimgui_IsKeyDown },
	{ "ImGui_IsKeyPressed", sgsimgui_IsKeyPressed },
	{ "ImGui_IsKeyReleased", sgsimgui_IsKeyReleased },
	{ "ImGui_IsMouseDown", sgsimgui_IsMouseDown },
	{ "ImGui_IsMouseClicked", sgsimgui_IsMouseClicked },
	{ "ImGui_IsMouseDoubleClicked", sgsimgui_IsMouseDoubleClicked },
	{ "ImGui_IsMouseReleased", sgsimgui_IsMouseReleased },
	{ "ImGui_IsMouseHoveringWindow", sgsimgui_IsMouseHoveringWindow },
	{ "ImGui_IsMouseHoveringAnyWindow", sgsimgui_IsMouseHoveringAnyWindow },
	{ "ImGui_IsMouseHoveringRect", sgsimgui_IsMouseHoveringRect },
	{ "ImGui_IsMouseDragging", sgsimgui_IsMouseDragging },
	{ "ImGui_GetMousePos", sgsimgui_GetMousePos },
	{ "ImGui_GetMousePosOnOpeningCurrentPopup", sgsimgui_GetMousePosOnOpeningCurrentPopup },
	{ "ImGui_GetMouseDragDelta", sgsimgui_GetMouseDragDelta },
	{ "ImGui_ResetMouseDragDelta", sgsimgui_ResetMouseDragDelta },
	{ "ImGui_GetMouseCursor", sgsimgui_GetMouseCursor },
	{ "ImGui_SetMouseCursor", sgsimgui_SetMouseCursor },
	{ "ImGui_CaptureKeyboardFromApp", sgsimgui_CaptureKeyboardFromApp },
	{ "ImGui_CaptureMouseFromApp", sgsimgui_CaptureMouseFromApp },
	{ "ImGui_MemAlloc", sgsimgui_MemAlloc },
	{ "ImGui_MemFree", sgsimgui_MemFree },
	{ "ImGui_GetClipboardText", sgsimgui_GetClipboardText },
	{ "ImGui_SetClipboardText", sgsimgui_SetClipboardText },
	{ "ImGui_GetVersion", sgsimgui_GetVersion },
	{ NULL, NULL }
};


static sgs_RegIntConst imgui_iconsts[] =
{
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

