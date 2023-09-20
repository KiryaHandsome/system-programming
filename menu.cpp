#include "menu.h"

void ProcessMenuMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case ID_FILE_NEW:
		//new file logic...
		break;
	case ID_FILE_SAVE:
		MessageBoxA(hWnd, "Save operation clicked!", "Save", MB_OK);
		//save logic...
		break;
	case ID_FILE_LOAD: {
		OpenFileDialog(hWnd);
		ReadDataFromFile(FILENAME);
		SetWindowTextA(hTextField, BUFFER);
		break;
	}
	case ID_ABOUT:
		MessageBoxA(hWnd, "Text about application and developer", "About", MB_OK);
		break;
	case ID_EXIT:
		PostQuitMessage(0);
		break;
	}
}
