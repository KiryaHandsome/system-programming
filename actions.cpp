#include "actions.h"

void ProcessWMCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case ID_FONT_TIMESNEWROMAN:
	case ID_FONT_CASCADIA_CODE:
	case ID_FONT_ARIAL:
	case ID_FONT_COURIERNEW:
	case ID_FONT_CALIBRI: {
		font = ProccessFont(LOWORD(wParam));
		UpdateFont();
		break;
	}
	case ID_FONTSIZE_18:
	case ID_FONTSIZE_20:
	case ID_FONTSIZE_22:
	case ID_FONTSIZE_28:
	case ID_FONTSIZE_32: {
		fontSize = ProccessFontSize(LOWORD(wParam));
		UpdateFont();
		break;
	}
	case ID_FILE_SAVE:
		SaveFile(hWnd);
		break;
	case ID_FILE_LOAD:
		LoadFile(hWnd);
		break;
	case ID_ABOUT:
		MessageBoxA(hWnd, "Text about application and developer", "About", MB_OK);
		break;
	case ID_EXIT:
		PostQuitMessage(0);
		break;
	}
}

void SaveFile(HWND hWnd)
{
	if (!OpenFileDialog(hWnd))
		return;
	SaveDataFromTextFieldToFile(FILE_PATH);
	RemoveAsteriskFromFilename();
	contentAlreadyChanged = false;
	std::wstring filename = std::wstring(PathFindFileName(FILE_PATH)) + WINDOW_TITLE_POSTFIX;
	SetWindowText(hMainWindow, filename.c_str());
}

void LoadFile(HWND hWnd)
{
	if (!OpenFileDialog(hWnd))
		return;
	ReadDataFromFile(FILE_PATH);
	std::wstring filename = std::wstring(PathFindFileName(FILE_PATH)) + WINDOW_TITLE_POSTFIX;
	SetWindowText(hMainWindow, filename.c_str());
}

void UpdateFont()
{
	HFONT hFont = CreateFontA(
		fontSize, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		font.c_str());
	SendMessage(hTextField, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
}

std::string ProccessFont(int cellId)
{
	switch (cellId) {
	case ID_FONT_TIMESNEWROMAN: return "Times New Roman";
	case ID_FONT_CASCADIA_CODE: return "Cascadia Code";
	case ID_FONT_ARIAL: return "Arial";
	case ID_FONT_COURIERNEW: return "Courier New";
	case ID_FONT_CALIBRI: return "Calibri";
	default: return "Georgia";
	}
}

int ProccessFontSize(int cellId)
{
	switch (cellId) {
	case ID_FONTSIZE_18: return 18;
	case ID_FONTSIZE_20: return 20;
	case ID_FONTSIZE_22: return 22;
	case ID_FONTSIZE_28: return 28;
	case ID_FONTSIZE_32: return 32;
	default: return 18;
	}
}
