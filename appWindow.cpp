#include "appWindow.h"
#include <string>


WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance, WNDPROC windowProc) {
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = windowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	windowClass.lpszClassName = MAIN_WINDOW_CLASS_NAME;
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	return windowClass;
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
	std::wstring windowTitle = std::wstring(DEFAULT_FILENAME) + WINDOW_TITLE_POSTFIX;
	return CreateWindowEx(
		WS_EX_CLIENTEDGE,
		MAIN_WINDOW_CLASS_NAME,
		windowTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL);
}

HWND CreateTextField(HWND parent)
{
	return CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"Edit", L"",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_AUTOHSCROLL,
		0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT,
		parent, NULL, NULL, NULL
	);
}

bool IsTextFieldChanged(WPARAM wParam, LPARAM lParam)
{
	return HIWORD(wParam) == EN_CHANGE and (HWND)lParam == hTextField;
}

void AppendAsteriskToFilename()
{
	int titleLength = GetWindowTextLength(hMainWindow);
	std::wstring windowTitle(titleLength + 1, '\0');
	GetWindowText(hMainWindow, &windowTitle[0], titleLength + 1);
	size_t pos = windowTitle.find(WINDOW_TITLE_POSTFIX);
	windowTitle.insert(pos, L"*");
	SetWindowText(hMainWindow, windowTitle.c_str());
	contentAlreadyChanged = true;
}

void RemoveAsteriskFromFilename()
{
	int titleLength = GetWindowTextLength(hMainWindow);
	std::wstring windowTitle(titleLength + 1, L'\0');
	GetWindowText(hMainWindow, &windowTitle[0], titleLength + 1);
	size_t asteriskPos = windowTitle.find('*');
	if (asteriskPos != std::string::npos) {
		windowTitle.erase(asteriskPos, 1);
	}
	SetWindowText(hMainWindow, windowTitle.c_str());
}
