#pragma once
#include "headers.h"
#include <string>

void ProcessWMCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);

void UpdateFont();

std::string PickFont(int cellId);

int PickFontSize(int cellId);

void ChooseFontColor(HWND hWnd);

void ChooseBackgroundColor(HWND hWnd);

/*
	Returns configured CHOOSECOLOR struct
*/
CHOOSECOLOR ConfigureChooseColor(HWND hWnd, COLORREF initialColor);