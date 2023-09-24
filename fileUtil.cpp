#include "fileUtil.h"


bool OpenFileDialog(HWND hWnd)
{
	OPENFILENAME openFileName{};

	wchar_t filename[FILE_PATH_BUFFER_SIZE] = { '\0' };

	// Initialize OPENFILENAME
	ZeroMemory(&openFileName, sizeof(openFileName));
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = hWnd;
	openFileName.lpstrFile = filename;
	openFileName.lpstrFile[0] = '\0';
	openFileName.nMaxFile = 256;
	openFileName.lpstrFilter = L"All files\0*.*\0";
	openFileName.nFilterIndex = 1;
	openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFileName.lpstrInitialDir = FILE_PATH;

	// Display the Open dialog box. 
	if (GetOpenFileName(&openFileName) == TRUE) {
		wcscpy_s(FILE_PATH, FILE_PATH_BUFFER_SIZE, filename);
		return true;
	}
	else {
		MessageBoxA(hWnd, "Error occurred while choose of file", "Error", MB_ICONERROR);
		return false;
	}
}

void ReadDataFromFile(wchar_t filePath[])
{
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		OutputDebugStringA("Error occured while opening the file");
		return;
	}

	DWORD fileSize = GetFileSize(hFile, NULL);
	char* contentArray = new char[fileSize + 1]; // +1 for null terminator
	DWORD bytesRead = 0;
	if (!ReadFile(hFile, contentArray, fileSize, &bytesRead, NULL)) {
		OutputDebugStringA("Error reading from the file.");
	}
	contentArray[bytesRead] = '\0';
	SetWindowTextA(hTextField, contentArray);
	delete[] contentArray;
	CloseHandle(hFile);
}

void SaveDataFromTextFieldToFile(wchar_t filePath[])
{
	HANDLE FileToSave = CreateFile(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int saveLength = GetWindowTextLength(hTextField) + 1;
	char* data = new char[saveLength];
	saveLength = GetWindowTextA(hTextField, data, saveLength);
	DWORD bytesWritten;
	if (!WriteFile(FileToSave, data, saveLength, &bytesWritten, NULL)) {
		OutputDebugStringA("Error when writing to the file.");
	}
	CloseHandle(FileToSave);
	delete[] data;
}
