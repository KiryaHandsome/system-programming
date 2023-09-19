#include <Windows.h>
#include "main.h"
#include "appWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
    WNDCLASSEX windowClass = CreateMainWindowClass(hInstance, WindowProc);
    if (!RegisterClassEx(&windowClass)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    HWND hMainWindow = InstantiateMainWindow(hInstance);
    if (hMainWindow == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

    // Create an edit control
    HWND hTextField = CreateTextField(hInstance, hMainWindow);
    if (hTextField == NULL) {
        MessageBox(NULL, L"Edit control creation failed!", L"Error", MB_ICONERROR);
        return 1;
    }

    MSG message;
    while (GetMessage(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND:
        
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}