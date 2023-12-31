#include "global.h"

HWND hTextField{};
HWND hMainWindow{};

bool contentAlreadyChanged = false;

int fontSize = 18;
std::string font = "Times New Roman";
COLORREF fontColor = RGB(0, 0, 0);
COLORREF backgroundColor = RGB(100, 100, 100);
CHARFORMAT charFormat{ 0 };

const wchar_t DEFAULT_FILENAME[] = L"Untitled.txt";
wchar_t WINDOW_TITLE_POSTFIX[] = L" - HandsomeEditor";
wchar_t FILE_PATH[FILE_PATH_BUFFER_SIZE];

// constants 
const wchar_t MAIN_WINDOW_CLASS_NAME[] = L"MainClassName";
const int MAIN_WINDOW_WIDTH = 500;
const int MAIN_WINDOW_HEIGHT = 300;
const int TEXT_FIELD_WIDTH = 400;
const int TEXT_FIELD_HEIGHT = 250;