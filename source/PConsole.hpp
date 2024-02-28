#include <Windows.h>
#include <stdio.h>

namespace Pixel
{
	// ¿ØÖÆÌ¨
	class Console
	{
	public:
		Console();
		~Console();
		// Ïú»Ù
		void Destory();
	private:
		HWND _hWnd;
	};
}