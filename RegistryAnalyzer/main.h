#pragma once


#include <windows.h>
#include <iostream>
#include <vector>

void EnumerateRegistryKeys(HKEY hKey, const std::wstring& path, HWND hEdit);