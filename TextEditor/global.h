#ifndef GLOBALS_H
#define GLOBALS_H

#include "headers.h"
#include <Windows.h>
#include <string>
#include <richedit.h>


extern HWND hTextField;
extern HWND hMainWindow;
extern bool contentAlreadyChanged;
extern int fontSize;
extern std::string font;
extern COLORREF fontColor;
extern COLORREF backgroundColor;
extern CHARFORMAT charFormat;


#define FILE_PATH_BUFFER_SIZE 256
#define BUFFER_SIZE 64000

// constants 
extern const wchar_t MAIN_WINDOW_CLASS_NAME[];
extern const int MAIN_WINDOW_WIDTH;
extern const int MAIN_WINDOW_HEIGHT;
extern const int TEXT_FIELD_WIDTH;
extern const int TEXT_FIELD_HEIGHT;

extern const wchar_t DEFAULT_FILENAME[];
extern wchar_t WINDOW_TITLE_POSTFIX[];
extern wchar_t FILE_PATH[];

#endif