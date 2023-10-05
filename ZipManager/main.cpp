#include "main.h"
#include <vector>


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

			// todo: archive picked folder 

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

std::string BrowseFolder(std::string saved_path)
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return "";
	}

	// Create an instance of IFileDialog
	IFileOpenDialog* pfd;
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	if (FAILED(hr)) {
		CoUninitialize();
		return "";
	}

	// Set options for the file dialog to allow picking both files and folders
	DWORD dwOptions;
	pfd->GetOptions(&dwOptions);
	pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);

	// Show the file dialog
	hr = pfd->Show(NULL);
	if (SUCCEEDED(hr)) {
		// Get the selected items
		IShellItemArray* pItems;
		hr = pfd->GetResults(&pItems);
		if (SUCCEEDED(hr)) {
			DWORD itemCount;
			pItems->GetCount(&itemCount);

			std::vector<PWSTR> selectedPaths;
			for (DWORD i = 0; i < itemCount; ++i) {
				IShellItem* pItem;
				pItems->GetItemAt(i, &pItem);

				PWSTR pszPath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
				if (SUCCEEDED(hr)) {
					selectedPaths.push_back(pszPath);
				}

				pItem->Release();
			}

			// Release the item array
			pItems->Release();

			// Output selected paths
			if (!selectedPaths.empty()) {
				OutputDebugStringA("Selected folders:\n");
				for (const auto& path : selectedPaths) {
					OutputDebugString(path);
					OutputDebugStringA("\n");
				}
			}
		}
	}

	// Release COM objects
	pfd->Release();
	CoUninitialize();

	return 0;
	

	//TCHAR path[MAX_PATH];


	//BROWSEINFO bi{ };
	//bi.lpszTitle = TEXT("Browse for folder...");
	//bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	//bi.lpfn = NULL;
	////bi.lParam = (LPARAM)path_param;

	//LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	//if (pidl != NULL)
	//{
	//	//get the name of the folder and put it in path
	//	SHGetPathFromIDList(pidl, path);
	//	OutputDebugString(path);
	//	//free memory used
	//	IMalloc* imalloc = 0;
	//	if (SUCCEEDED(SHGetMalloc(&imalloc)))
	//	{
	//		imalloc->Free(pidl);
	//		imalloc->Release();
	//	}

	//	return "NULL";
	//}

	return "";
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
	if (SUCCEEDED(hr)) {
		IShellItem* result;
		hr = pfd->GetResult(&result);
		if (SUCCEEDED(hr)) {
			PWSTR selectedFolderPath;
			hr = result->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &selectedFolderPath);
			if (SUCCEEDED(hr)) {
				// todo: handle selected folder here
				OutputDebugString(selectedFolderPath);
				selectedFolder = selectedFolderPath;
			}
		}
	}
}
