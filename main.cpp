#include <Windows.h>
#include "main.h"
#include "appWindow.h"
#include "resource.h"
#include "menu.h"

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

	HWND hTextField = CreateTextField(hInstance, hMainWindow);
	if (hTextField == NULL) {
		MessageBox(NULL, L"Edit control creation failed!", L"Error", MB_ICONERROR);
		return 1;
	}

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
		return ProcessMenuMessage(hWindow, wParam, lParam);
	case WM_CLOSE:
		DestroyWindow(hWindow);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED: { // make it less blurry
		UINT dpi = HIWORD(wParam);
		RECT* suggestedRect = (RECT*)lParam;
		SetWindowPos(hWindow, NULL, suggestedRect->left, suggestedRect->top, suggestedRect->right - suggestedRect->left, suggestedRect->bottom - suggestedRect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		RedrawWindow(hWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
		return 0;
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}