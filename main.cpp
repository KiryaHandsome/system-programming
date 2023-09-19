#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MessageBox(NULL, L"Text message", L"Caption", MB_YESNO);
	return 0;
}