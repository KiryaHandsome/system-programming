#pragma once

#include <Windows.h>
#include <string>
#include "shlobj_core.h"
#include "shobjidl_core.h"
#include <vector>
#include <zip.h>

// constants
const wchar_t APPLICATION_NAME[] = L"ZipManager";
const wchar_t MAIN_WINDOW_CLASS_NAME[] = L"MainWindowClassName";
const int MAIN_WINDOW_INITIAL_WIDTH = 400;
const int MAIN_WINDOW_INITIAL_HEIGHT = 300;

// buttons params
const int BUTTON_WIDTH = 140;
const int BUTTON_HEIGHT = 50;

// identifiers
#define IDC_ARCHIVE_BUTTON 1
#define IDC_EXTRACT_BUTTON 2

// variables
std::wstring selectedFolder;
std::wstring selectedZip;

// functions
LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance);

HWND InstantiateMainWindow(HINSTANCE hInstance);

bool PickFolder();

void SetFileDialogOptions(IFileOpenDialog* pfd);

void BrowseFolder(IFileOpenDialog* pfd);

void AddFileToZip(const wchar_t* zipFileName, const wchar_t* sourceFileName);

void AddFolderToZip(const wchar_t* folderPath, const wchar_t* zipFileName);

std::string WcharToString(const wchar_t* data);

void ExtractZip(const char* zipFileName, const char* outputFolder);

bool PickZipToExtract();
