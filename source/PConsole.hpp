#include <Windows.h>
#include <stdio.h>

namespace Pixel
{
	// ����̨
	class Console
	{
	public:
		Console();
		~Console();
		// ����
		void Destory();
	private:
		HWND _hWnd;
	};
}