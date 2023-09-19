#include "appWindow.h"


WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance, WNDPROC windowProc) {
    WNDCLASSEX windowClass{};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.lpfnWndProc = windowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = MAIN_WINDOW_CLASS_NAME;
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return windowClass;
}

HWND InstantiateMainWindow(HINSTANCE hInstance)
{
    return CreateWindowEx(
        WS_EX_CLIENTEDGE,
        MAIN_WINDOW_CLASS_NAME,
        MAIN_WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL);
}
