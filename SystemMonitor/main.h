#pragma once

#include <Windows.h>
#include <string>
#include <Dbt.h>

// constants
const wchar_t APPLICATION_NAME[] = L"SystemMonitor";
const wchar_t MAIN_WINDOW_CLASS_NAME[] = L"MainWindowClassName";
const int MAIN_WINDOW_INITIAL_WIDTH = 400;
const int MAIN_WINDOW_INITIAL_HEIGHT = 300;


HWND editControl;
HBRUSH backgroundBrush;

//functions
LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

HWND InstantiateMainWindow(HINSTANCE hInstance);

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance);

void PrintMessage(std::wstring message);
