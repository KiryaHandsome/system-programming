#include "main.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX mainWindowClass = CreateMainWindowClass(hInstance);
	if (not RegisterClassEx(&mainWindowClass)) {
		MessageBoxA(NULL, "Main window hasn't registered", "Error", MB_OK);
		return EXIT_FAILURE;
	}

	HWND mainWindow = InstantiateMainWindow(hInstance);
	editControl = CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOVSCROLL | WS_DISABLED | ES_MULTILINE | WS_VSCROLL,
		20,
		80,
		500,
		300,
		mainWindow,
		NULL,
		(HINSTANCE)GetWindowLongPtr(mainWindow, GWLP_HINSTANCE),
		NULL
	);

	ShowWindow(mainWindow, nCmdShow);
	UpdateWindow(mainWindow);

	if (AddClipboardFormatListener(mainWindow))
	{
		OutputDebugStringA("clipboard listener connected");
	}

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CLOSE:
		DestroyWindow(hWindow);
		RemoveClipboardFormatListener(hWindow);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE: {
		RECT clientRect;
		GetClientRect(hWindow, &clientRect);
		MoveWindow(editControl, 20, 20, clientRect.right - 40, clientRect.bottom - 40, TRUE);
		return 0;
	}
	case WM_DISPLAYCHANGE:
	{
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);
		PrintMessage(L"Display size was changed to " + std::to_wstring(newWidth) + L"x" + std::to_wstring(newHeight) + L"\r\n");
		MoveWindow(hWindow, 20, 80, newWidth - 40, newHeight - 100, TRUE);
		RECT clientRect;
		GetClientRect(hWindow, &clientRect);
		MoveWindow(editControl, 20, 20, clientRect.right - 40, clientRect.bottom - 40, TRUE);
		break;
	}
	case WM_DEVICECHANGE:
	{
		switch (wParam)
		{
		case DBT_DEVICEARRIVAL: {
			PrintMessage(L"Device connected to computer\r\n");
			break;
		}
		case DBT_DEVICEREMOVECOMPLETE:
		{
			PrintMessage(L"Device removed from computer\r\n");
			break;
		}
		}
	}
	case WM_POWERBROADCAST:
	{
		switch (wParam)
		{
		case PBT_APMPOWERSTATUSCHANGE:
		{
			SYSTEM_POWER_STATUS powerStatus;
			if (GetSystemPowerStatus(&powerStatus))
			{
				if (powerStatus.ACLineStatus == AC_LINE_ONLINE)
					PrintMessage(L"Power adapter connected\r\n");
				else
					PrintMessage(L"Power adapter removed\r\n");
			}
			return 0;
		}
		break;
		}
	}
	case WM_CLIPBOARDUPDATE:
	{
		if (OpenClipboard(hWindow))
		{
			HANDLE hClipboardData = GetClipboardData(CF_TEXT);
			if (hClipboardData)
			{
				char* pszData = static_cast<char*>(GlobalLock(hClipboardData));
				if (pszData)
				{
					std::string data = pszData;
					PrintMessage(L"Clipboard updated: " + std::wstring(data.begin(), data.end()) + L"\r\n");
					GlobalUnlock(hClipboardData);
				}
			}
			CloseClipboard();
		}
		break;
	}
	case WM_KEYUP:
	{
		int virtualKeyCode = (int)wParam;
		std::string keyChar = std::string(1, MapVirtualKey(virtualKeyCode, MAPVK_VK_TO_CHAR));
		if (isprint(keyChar[0]))
			PrintMessage(L"Key up: " + std::wstring(keyChar.begin(), keyChar.end()) + L"\r\n");
		else
			PrintMessage(L"Key up!\r\n");
		break;
	}
	case WM_KEYDOWN:
	{
		int virtualKeyCode = (int)wParam;
		std::string keyChar = std::string(1, MapVirtualKey(virtualKeyCode, MAPVK_VK_TO_CHAR));
		if (isprint(keyChar[0]))
			PrintMessage(L"Key down: " + std::wstring(keyChar.begin(), keyChar.end()) + L"\r\n");
		else
			PrintMessage(L"Key down!\r\n");
		break;
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
		MAIN_WINDOW_CLASS_NAME, APPLICATION_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_INITIAL_WIDTH, MAIN_WINDOW_INITIAL_HEIGHT,
		NULL, NULL, hInstance, NULL
	);
}


void PrintMessage(std::wstring message)
{
	SendMessage(editControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(editControl, EM_REPLACESEL, 0, (LPARAM)message.c_str());
}