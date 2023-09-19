#pragma once

#include <Windows.h>

// constants 
static const wchar_t* MAIN_WINDOW_CLASS_NAME = L"MainClassName";
static const wchar_t* MAIN_WINDOW_TITLE = L"Handsome Text Editor";
static const int MAIN_WINDOW_WIDTH = 500;
static const int MAIN_WINDOW_HEIGHT = 300;


//functions
WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance, WNDPROC windowProc);

HWND InstantiateMainWindow(HINSTANCE hInstance);