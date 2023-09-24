#pragma once
#include "headers.h"
#include <string>

void ProcessWMCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);

void SaveFile(HWND hWnd);

void LoadFile(HWND hWnd);

void UpdateFont();

std::string ProccessFont(int cellId);

int ProccessFontSize(int cellId);