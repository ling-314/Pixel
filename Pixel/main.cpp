#include "PWindow.hpp"
using namespace Pixel;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window main;
	if (main.Init())
	{
	}
	else
	{
		Renderer::Destroy();
		Sprite::Destroy();
		return 1;
	}
	return 0;
}