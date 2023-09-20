#pragma once

#include "headers.h"

// current file
static wchar_t* currentFileName = new wchar_t[256] {'\0'};
static char* currentFileBufferData = NULL;

void OpenFileDialog(HWND hWnd);

/*
	Reads data from passed file.
	If something went wrong it returns null, otherwise - data from file.
*/
void ReadDataFromFile(LPCSTR filename);
