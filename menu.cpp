#include "menu.h"
#include "resource.h"

int ProcessMenuMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case ID_FILE_NEW:
		//new file logic...
		return 0;
	case ID_FILE_SAVE:
		MessageBox(hWnd, L"Save operation clicked!", L"Save", MB_OK);
		//save logic...
		return 0;
	case ID_FILE_LOAD:
		MessageBox(hWnd, L"Load operation clicked!", L"Load", MB_OK);
		//load logic...
		return 0;
	case ID_ABOUT:
		MessageBox(hWnd, L"Text about application and developer", L"About", MB_OK);
		// 'about' pop up window
		return 0;
	case ID_EXIT:
		PostQuitMessage(0);
		return 0;
	default:
		return 1;
	}
}
