#include <Windows.h>
#include "main.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass = CreateMainWindowClass(hInstance, WindowProc);
	if (!RegisterClassEx(&windowClass)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	HWND hMainWindow = CreateMainWindow(hInstance);
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
	case WM_COMMAND:
		ProcessMenuMessage(hWindow, wParam, lParam);
		return 0;
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
		else {
			SetWindowTextA(hTextField, "Hello World!");
		}
		return 0;
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}