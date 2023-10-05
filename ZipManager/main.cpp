#include "main.h"
#include <thread>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{

	WNDCLASSEX mainWindowClass = CreateMainWindowClass(hInstance);
	if (not RegisterClassEx(&mainWindowClass)) {
		MessageBoxA(NULL, "Main window hasn't registered", "Error", MB_OK);
		return EXIT_FAILURE;
	}

	HWND mainWindow = InstantiateMainWindow(hInstance);


	HWND archiveButton = CreateWindow(
		L"BUTTON", L"Archive",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		10, 10, BUTTON_WIDTH, BUTTON_HEIGHT,
		mainWindow,
		(HMENU)IDC_ARCHIVE_BUTTON,
		hInstance,
		NULL
	);

	HWND extractButton = CreateWindow(
		L"BUTTON", L"Extract",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		250, 10, BUTTON_WIDTH, BUTTON_HEIGHT,
		mainWindow,
		(HMENU)IDC_EXTRACT_BUTTON,
		hInstance,
		NULL
	);

	ShowWindow(mainWindow, nCmdShow);
	UpdateWindow(mainWindow);


	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;


}

LRESULT CALLBACK WindowProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_ARCHIVE_BUTTON: {
			bool isPicked = PickFolder();
			if (isPicked) {
				std::wstring folderPath(selectedFolder);
				std::wstring zipFilePath = std::wstring(selectedFolder).append(L".zip");
				AddFolderToZip(folderPath.c_str(), zipFilePath.c_str());
			}
			break;
		}
		case IDC_EXTRACT_BUTTON:
			MessageBox(hWindow, TEXT("Extract button clicked!"), TEXT("Button Click"), MB_OK | MB_ICONINFORMATION);
			break;
		}
		return 0;
	}
	case WM_CLOSE:
		DestroyWindow(hWindow);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE: {
		// create buttons here
		return 0;
	}
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
}

WNDCLASSEX CreateMainWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszClassName = MAIN_WINDOW_CLASS_NAME;
	return wc;
}

HWND InstantiateMainWindow(HINSTANCE hInstance)
{
	return CreateWindowEx(
		WS_EX_CLIENTEDGE,
		MAIN_WINDOW_CLASS_NAME, APPLICATION_NAME, //APPLICATION_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_INITIAL_WIDTH, MAIN_WINDOW_INITIAL_HEIGHT,
		NULL, NULL, hInstance, NULL
	);
}

bool PickFolder()
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return false;
	}

	IFileOpenDialog* pfd;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	if (FAILED(hr)) {
		CoUninitialize();
		return false;
	}
	SetFileDialogOptions(pfd);
	BrowseFolder(pfd);

	pfd->Release();
	CoUninitialize();
	return true;
}

void SetFileDialogOptions(IFileOpenDialog* pfd)
{
	DWORD dwOptions;
	pfd->GetOptions(&dwOptions);
	pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
}

void BrowseFolder(IFileOpenDialog* pfd)
{
	HRESULT hr = pfd->Show(NULL);
	if (FAILED(hr))
		return;

	IShellItem* result;
	hr = pfd->GetResult(&result);
	if (FAILED(hr))
		return;
	PWSTR selectedFolderPath;
	hr = result->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &selectedFolderPath);
	if (FAILED(hr))
		return;
	OutputDebugString(selectedFolderPath);
	selectedFolder = selectedFolderPath;

}

void AddFileToZip(const wchar_t* zipFileName, const wchar_t* sourceFileName)
{
	struct zip* archive;
	struct zip_source* source;

	archive = zip_open(WcharToString(zipFileName).c_str(), ZIP_CREATE, NULL);
	if (archive == NULL) {
		perror("Failed to open zip archive");
		return;
	}

	source = zip_source_file(archive, WcharToString(sourceFileName).c_str(), 0, 0);
	if (source == NULL) {
		perror("Failed to create zip source from file");
		zip_close(archive);
		return;
	}


	std::wstring filePath = sourceFileName;
	size_t found = filePath.find(selectedFolder + L"\\");
	if (found != std::wstring::npos) {
		filePath.erase(found, selectedFolder.length() + 1);
	}

	if (zip_file_add(archive, WcharToString(filePath.c_str()).c_str(), source, 0) < 0) {
		perror("Failed to add file to zip archive");
		zip_source_free(source);
		zip_close(archive);
		return;
	}
	zip_close(archive);
}

void AddFolderToZip(const wchar_t* folderPath, const wchar_t* zipFileName) {
	WIN32_FIND_DATA findFileData;
	wchar_t searchPattern[MAX_PATH];

	swprintf(searchPattern, sizeof(searchPattern) / sizeof(searchPattern[0]), L"%s\\*", folderPath);

	HANDLE hFind = FindFirstFile(searchPattern, &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				wchar_t filePath[MAX_PATH];
				swprintf(filePath, sizeof(filePath) / sizeof(filePath[0]), L"%s\\%s", folderPath, findFileData.cFileName);
				AddFileToZip(zipFileName, filePath);
			} else if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
				wchar_t subFolderPath[MAX_PATH];
					swprintf(subFolderPath, sizeof(subFolderPath) / sizeof(subFolderPath[0]), L"%s\\%s", folderPath, findFileData.cFileName);
				AddFolderToZip(subFolderPath, zipFileName);
			}
		} while (FindNextFile(hFind, &findFileData) != 0);

		FindClose(hFind);
	}
}

std::string WcharToString(const wchar_t* data)
{
	std::wstring wideString(data);
	return std::string(wideString.begin(), wideString.end());
}

