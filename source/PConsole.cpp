#include "PConsole.hpp"

Pixel::Console::Console()
{
	AllocConsole();
	_hWnd = GetConsoleWindow();
	FILE* stream;
	freopen_s(&stream, "CON", "r", stdin);
	freopen_s(&stream, "CON", "w", stdout);
}

Pixel::Console::~Console()
{
	FreeConsole();
}

void Pixel::Console::Destory()
{
	FreeConsole();
	_hWnd = nullptr;
}
