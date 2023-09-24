#pragma once
#include "headers.h"

//functions
WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance, WNDPROC windowProc);
HWND CreateMainWindow(HINSTANCE hInstance);
HWND CreateTextField(HWND parent);
bool IsTextFieldChanged(WPARAM wParam, LPARAM lParam);
void AppendAsteriskToFilename();
void RemoveAsteriskFromFilename();