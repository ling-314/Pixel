#include "PWindow.h"
#include "PConsole.h"
#include "PFunction.h"
#include "PAudio.h"
using namespace Pixel;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window;
	if (window.Init())
	{
		Scene scene;
		scene.SetBackground(0xa8ceff);

		window.Enter(&scene);
		window.Show();

		while (!window.event.Close())
		{
			window.Update();
		}
	}
	return 0;
}