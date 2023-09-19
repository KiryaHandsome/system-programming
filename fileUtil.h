#pragma once

#include "headers.h"

// current file
namespace cf {
	static const int BUFFER_SIZE = 256;
	static char FILENAME[BUFFER_SIZE];
	static char BUFFER[BUFFER_SIZE];
}


static wchar_t* currentFileName = new wchar_t[256] {'\0'};
static char* currentFileBufferData = NULL;

void OpenFileDialog(HWND hWnd);

/*
	Reads data from passed file.
	If something went wrong it returns null, otherwise - data from file.
*/
void ReadDataFromFile(LPCSTR filename);
