#pragma once

#include <Windows.h>
#include <string>

// constants
const wchar_t APPLICATION_NAME[] = L"Car Park";
const wchar_t MAIN_WINDOW_CLASS_NAME[] = L"MainWindowClassName";
const int MAIN_WINDOW_INITIAL_WIDTH = 600;
const int MAIN_WINDOW_INITIAL_HEIGHT = 500;

const int PARK_PLACES_COUNT = 8;

// buttons params
const int BUTTON_WIDTH = 140;
const int BUTTON_HEIGHT = 50;

// identifiers
#define IDC_PARK_CAR_BUTTON 1

// variables
HWND editControl;
HANDLE semaphore;
HANDLE mutex;
int id = 0;


// functions
DWORD WINAPI ParkCar(LPVOID lpParam);

HWND InstantiateMainWindow(HINSTANCE hInstance);

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance);

void PrintMessage(std::string message);