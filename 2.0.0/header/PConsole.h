#pragma once
#include <Windows.h>
#include <string>
#include "PType.h"

namespace Pixel
{
	class Console
	{
		Console(const Console&) = delete;
	public:
		Console();
		~Console();
		void Show();
		void Hide();
	public:
		void Print(std::string text);
		void PrintLn(std::string text);
		Console& operator<<(std::string text);
		Console& operator<<(char text);
		Console& operator<<(short text);
		Console& operator<<(int text);
		Console& operator<<(long text);
		Console& operator<<(long long text);
		Console& operator<<(unsigned short text);
		Console& operator<<(unsigned text);
		Console& operator<<(unsigned long text);
		Console& operator<<(unsigned long long text);
		Console& operator<<(float text);
		Console& operator<<(double text);
		Console& operator<<(Point text);
		Console& operator<<(Color text);
		Console& operator<<(Size text);
	protected:
		HWND hWnd;
	};
}