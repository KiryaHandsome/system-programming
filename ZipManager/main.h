#pragma once

#include <Windows.h>
#include <string>

// constants
const wchar_t APPLICATION_NAME[] = L"ZipManager";
const wchar_t MAIN_WINDOW_CLASS_NAME[] = L"MainWindowClassName";
const int MAIN_WINDOW_INITIAL_WIDTH = 400;
const int MAIN_WINDOW_INITIAL_HEIGHT = 300;

const int BUTTON_WIDTH = 140;
const int BUTTON_HEIGHT = 50;



// functions
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow);

LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance);

HWND InstantiateMainWindow(HINSTANCE hInstance);