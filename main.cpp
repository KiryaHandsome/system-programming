#include <Windows.h>
#include "main.h"
#include <string>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass = CreateMainWindowClass(hInstance, WindowProc);
	if (not RegisterClassEx(&windowClass)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	hMainWindow = CreateMainWindow(hInstance);
	if (hMainWindow == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}
	HICON hSmallIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hMainWindow, WM_SETICON, ICON_SMALL, (LPARAM)hSmallIcon);


	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		if (not contentAlreadyChanged and IsTextFieldChanged(wParam, lParam))
			AppendAsteriskToFilename();
		else
			ProcessWMCommand(hWindow, wParam, lParam);
		return 0;
	}
	case WM_CLOSE:
		DestroyWindow(hWindow);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE: {
		hTextField = CreateTextField(hWindow);
		if (hTextField == NULL) {
			MessageBox(NULL, L"Edit control creation failed!", L"Error", MB_ICONERROR);
			return EXIT_FAILURE;
		}
		SendMessage(hTextField, EM_SETEVENTMASK, 0, ENM_CHANGE);
		UpdateFont();
		return 0;
	}
	case WM_SIZE: {
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);
		MoveWindow(hTextField, 0, 0, newWidth, newHeight, TRUE);
		break;
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}
