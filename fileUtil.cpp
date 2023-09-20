#include "fileUtil.h"


void OpenFileDialog(HWND hWnd)
{
	OPENFILENAMEA openFileName{};

	char filename[256] = { L'\0' };

	// Initialize OPENFILENAME
	ZeroMemory(&openFileName, sizeof(openFileName));
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = hWnd;
	openFileName.lpstrFile = filename;
	openFileName.lpstrFile[0] = '\0';
	openFileName.nMaxFile = 256;
	openFileName.lpstrFilter = "All files\0*.*\0Cpp files\0*.cpp\0";
	openFileName.nFilterIndex = 1;
	openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	if (GetOpenFileNameA(&openFileName) == TRUE) {
		OutputDebugStringA(filename);
		strcpy_s(FILENAME, 256, filename);
	}
	else {
		MessageBoxA(hWnd, "Error occurred while choose of file", "Error", MB_ICONERROR);
	}
}

void ReadDataFromFile(LPCSTR filename)
{
	HANDLE hFile = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		OutputDebugStringA("Error occured while opening the file");
		return;
	}

	DWORD bytesRead;
	if (!ReadFile(hFile, BUFFER, BUFFER_SIZE, &bytesRead, NULL)) {
		OutputDebugStringA("Error reading from the file.");
		CloseHandle(hFile);
		return;
	}
	CloseHandle(hFile);
}
