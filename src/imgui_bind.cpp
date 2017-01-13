
#include "imgui.hpp"

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
};


void sgs_imgui_bind( SGS_CTX )
{
	sgs_RegIntConsts( C, imgui_iconsts, -1 );
};

