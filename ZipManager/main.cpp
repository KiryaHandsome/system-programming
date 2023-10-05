#include "main.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{

	WNDCLASSEX mainWindowClass = CreateMainWindowClass(hInstance);
	if (not RegisterClassEx(&mainWindowClass)) {
		MessageBoxA(NULL, "Main window hasn't registered", "Error", MB_OK);
		return EXIT_FAILURE;
	}

	HWND mainWindow = InstantiateMainWindow(hInstance);


	HWND archiveButton = CreateWindow(
		L"BUTTON", L"Archive",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		10, 10, BUTTON_WIDTH, BUTTON_HEIGHT,
		mainWindow,
		NULL, //(HMENU)IDC_MYBUTTON, // Button identifier
		hInstance,
		NULL
	);

	HWND extractButton = CreateWindow(
		L"BUTTON", L"Extract",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		250, 10, BUTTON_WIDTH, BUTTON_HEIGHT,
		mainWindow,
		NULL, //(HMENU)IDC_MYBUTTON, // Button identifier
		hInstance,
		NULL
	);

	ShowWindow(mainWindow, nCmdShow);
	UpdateWindow(mainWindow);


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
		switch (LOWORD(wParam)) {
			// process
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
		// create buttons here
		return 0;
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = MAIN_WINDOW_CLASS_NAME;
	return wc;
}

HWND InstantiateMainWindow(HINSTANCE hInstance)
{
	return CreateWindowEx(
		WS_EX_CLIENTEDGE,
		MAIN_WINDOW_CLASS_NAME, APPLICATION_NAME, //APPLICATION_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_INITIAL_WIDTH, MAIN_WINDOW_INITIAL_HEIGHT,
		NULL, NULL, hInstance, NULL
	);
}
