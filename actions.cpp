#include "actions.h"
#include <string>

void ProcessWMCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case ID_FILE_NEW:
		//new file logic...
		break;
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
	OpenFileDialog(hWnd);
	SaveDataFromTextFieldToFile(FILE_PATH);
	RemoveAsteriskFromFilename();
	contentAlreadyChanged = false;
	std::wstring filename = std::wstring(PathFindFileName(FILE_PATH)) + WINDOW_TITLE_POSTFIX;
	SetWindowText(hMainWindow, filename.c_str());
}

void LoadFile(HWND hWnd)
{
	OpenFileDialog(hWnd);
	ReadDataFromFile(FILE_PATH);
	std::wstring filename = std::wstring(PathFindFileName(FILE_PATH)) + WINDOW_TITLE_POSTFIX;
	SetWindowText(hMainWindow, filename.c_str());
}
