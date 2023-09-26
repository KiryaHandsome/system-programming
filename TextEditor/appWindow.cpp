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
	LoadLibrary(TEXT("Msftedit.dll"));
	charFormat.cbSize = sizeof(CHARFORMAT);
	charFormat.yHeight = fontSize * 20;
	charFormat.crTextColor = fontColor;
	charFormat.dwMask = CFM_COLOR | CFM_SIZE | CFM_FACE;
	return CreateWindowEx(
		WS_EX_CLIENTEDGE,
		MSFTEDIT_CLASS, L"",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | WS_TABSTOP,
		0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT,
		parent, NULL, NULL, NULL
	);
}

bool IsTextFieldChanged(WPARAM wParam, LPARAM lParam)
{
	bool isChangeEvent = HIWORD(wParam) == EN_CHANGE;
	bool isTextField = (HWND)lParam == hTextField;
	return isChangeEvent and isTextField;
}

void AppendAsteriskToFilename()
{
	int titleLength = GetWindowTextLength(hMainWindow);
	std::wstring windowTitle(titleLength + 1, '\0');
	GetWindowText(hMainWindow, &windowTitle[0], titleLength + 1);
	int pos = windowTitle.find(WINDOW_TITLE_POSTFIX);
	if (pos != -1) {
		windowTitle.insert(pos, L"*");
		SetWindowText(hMainWindow, windowTitle.c_str());
		contentAlreadyChanged = true;
	}

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
