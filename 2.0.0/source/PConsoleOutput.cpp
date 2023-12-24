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

Pixel::Console& Pixel::Console::operator<<(std::string text)
{
	Print(text);
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(char text)
{
	char str[2] = { text, '\0' };
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str, 1, 0, 0);
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(short text)
{
	Print(std::to_string(text));
	return *this;
}
Pixel::Console& Pixel::Console::operator<<(int text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(long text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(long long text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(unsigned short text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(unsigned text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(unsigned long text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(unsigned long long text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(float text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(double text)
{
	Print(std::to_string(text));
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(Point text)
{
	*this << "Point{ x = " << text.x << ", y = " << text.y << " }";
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(Color text)
{
	*this << "Color{ r = " << text.r << ", g = " << text.g << ", b = " << text.b << ", a = " << text.a << " }";
	return *this;
}

Pixel::Console& Pixel::Console::operator<<(Size text)
{
	*this << "Size{ Point{ x = " << text.leftTop.x << ", y = " << text.leftTop.y << " }, Point{ x = " << text.rightBottom.x << ", y = " << text.rightBottom.y << " } }";
	return *this;
}
