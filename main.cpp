#include <Windows.h>
#include "main.h"
#include <string>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass = CreateMainWindowClass(hInstance, WindowProc);
	if (!RegisterClassEx(&windowClass)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	hMainWindow = CreateMainWindow(hInstance);
	if (hMainWindow == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

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
		if (!contentAlreadyChanged and IsTextFieldChanged(wParam, lParam)) {
			AppendAsteriskToFilename();
		}
		else {
			ProcessWMCommand(hWindow, wParam, lParam);
		}
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
		return 0;
	}
	case WM_SIZE: {
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);
		MoveWindow(hTextField, 10, 10, newWidth - 20, newHeight - 20, TRUE);
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}
