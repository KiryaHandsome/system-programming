#pragma once

#include "headers.h"

void OpenFileDialog(HWND hWnd);

/*
	Reads data from passed file and set it to text field
*/
void ReadDataFromFile(wchar_t filePath[]);

void SaveDataFromTextFieldToFile(wchar_t filePath[]);
