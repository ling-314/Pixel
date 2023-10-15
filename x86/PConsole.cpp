#include "PConsole.h"

Pixel::Console::Console()
{
	AllocConsole();
	hWnd = GetConsoleWindow();
}

Pixel::Console::~Console()
{
	FreeConsole();
	hWnd = nullptr;
}

void Pixel::Console::Show()
{
	ShowWindow(hWnd, SW_SHOW);
}

void Pixel::Console::Hide()
{
	ShowWindow(hWnd, SW_HIDE);
}
