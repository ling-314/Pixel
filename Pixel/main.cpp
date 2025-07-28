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
	Renderer::Destroy();
	Sprite::Destroy();
	return 0;
}