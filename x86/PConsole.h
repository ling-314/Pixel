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
	protected:
		HWND hWnd;
	};
}