#include "actions.h"

void ProcessWMCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case ID_FONT_TIMESNEWROMAN:
	case ID_FONT_CASCADIA_CODE:
	case ID_FONT_ARIAL:
	case ID_FONT_COURIERNEW:
	case ID_FONT_CALIBRI: {
		font = PickFont(LOWORD(wParam));
		UpdateFont();
		break;
	}
	case ID_FONTSIZE_18:
	case ID_FONTSIZE_20:
	case ID_FONTSIZE_22:
	case ID_FONTSIZE_28:
	case ID_FONTSIZE_32: {
		fontSize = PickFontSize(LOWORD(wParam));
		UpdateFont();
		break;
	}
	case ID_FORMAT_FONTCOLOR: {
		ChooseFontColor(hWnd);
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
	contentAlreadyChanged = false;
}

void UpdateFont()
{
	charFormat.yHeight = fontSize * 20;
	lstrcpy(charFormat.szFaceName, std::wstring(font.begin(), font.end()).c_str());
	charFormat.crTextColor = fontColor;
	SendMessage(hTextField, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&charFormat);
}

std::string PickFont(int cellId)
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

int PickFontSize(int cellId)
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

void ChooseFontColor(HWND hWnd)
{
	static COLORREF customColors[16];
	CHOOSECOLOR cc{ };
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = customColors; // Set custom color array
	cc.rgbResult = fontColor; // Initial color
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&cc)) {
		charFormat.crTextColor = fontColor = cc.rgbResult;
		SendMessage(hTextField, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&charFormat);
	}
}
