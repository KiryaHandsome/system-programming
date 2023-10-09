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
		L"BUTTON", L"Park Car",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		10, 10, BUTTON_WIDTH, BUTTON_HEIGHT,
		mainWindow,
		(HMENU)IDC_PARK_CAR_BUTTON,
		hInstance,
		NULL
	);

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

	semaphore = CreateSemaphore(NULL, PARK_PLACES_COUNT, PARK_PLACES_COUNT, NULL);
	mutex = CreateMutexA(NULL, FALSE, "Mutex");
	if (semaphore == NULL || mutex == NULL) {
		return EXIT_FAILURE;
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
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_PARK_CAR_BUTTON: {
			int* currentId = new int;
			*currentId = ++id;
			HANDLE newCar = CreateThread(NULL, 0, ParkCar, currentId, 0, NULL);
			if (newCar == NULL) {
				MessageBoxA(hWindow, "Thread not created", "Error", MB_OK);
			}
			break;
		}
		}
		return 0;
	}
	case WM_CLOSE:
		DestroyWindow(hWindow);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE: {
		RECT clientRect;
		GetClientRect(hWindow, &clientRect);
		MoveWindow(editControl, 20, 80, clientRect.right - 20, clientRect.bottom - 100, TRUE);
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
		MAIN_WINDOW_CLASS_NAME, APPLICATION_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_INITIAL_WIDTH, MAIN_WINDOW_INITIAL_HEIGHT,
		NULL, NULL, hInstance, NULL
	);
}

void PrintMessage(std::string message)
{
	std::wstring wMessage(message.begin(), message.end());
	WaitForSingleObject(mutex, INFINITE);
	OutputDebugStringA(message.c_str());
	SendMessage(editControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(editControl, EM_REPLACESEL, 0, (LPARAM)wMessage.c_str());
	ReleaseMutex(mutex);
}

DWORD WINAPI ParkCar(LPVOID lpParam) {
	int* carIdPtr = reinterpret_cast<int*>(lpParam);
	std::string carId = std::to_string((*carIdPtr));
	while (true) {
		PrintMessage(carId + " car is trying to park...\n");
		if (WaitForSingleObject(semaphore, 0) == WAIT_OBJECT_0) {
			PrintMessage(carId + " car is parked\n");
			Sleep(5000); // car on the park
			PrintMessage(carId + " car left park\n");
			ReleaseSemaphore(semaphore, 1, NULL);
			break;
		}
		else { // there are no park places 
			Sleep(500);
			PrintMessage(carId + " there is no free places :( Please wait a bit...\n");
		}
	}
	ExitThread(0);
	return 0;
}
