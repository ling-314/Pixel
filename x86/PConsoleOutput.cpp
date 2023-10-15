#include "PConsole.h"

void Pixel::Console::Print(std::string text)
{
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), text.c_str(), text.length(), 0, 0);
}

void Pixel::Console::PrintLn(std::string text)
{
	Print(text);
	Print("\n");
}
