#include "PConsole.h"

Pixel::Console::Console()
{
	AllocConsole();
	_hWnd = GetConsoleWindow();
}

Pixel::Console::~Console()
{
	FreeConsole();
	_hWnd = nullptr;
}

void Pixel::Console::Show()
{
	ShowWindow(_hWnd, SW_SHOW);
}

void Pixel::Console::Hide()
{
	ShowWindow(_hWnd, SW_HIDE);
}
