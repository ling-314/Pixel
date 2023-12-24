#include "PEvent.h"

Pixel::Event::Event() :
	close(false),
	mousePosition(0, 0),
	mouseDown(false),
	keyDown(false)
{
	keyStatus =
	{
		{left, false},
		{middle, false},
		{right, false},

		{A, false},
		{B, false},
		{C, false},
		{D, false},
		{E, false},
		{F, false},
		{G, false},
		{H, false},
		{I, false},
		{J, false},
		{K, false},
		{L, false},
		{M, false},
		{N, false},
		{O, false},
		{P, false},
		{Q, false},
		{R, false},
		{S, false},
		{T, false},
		{U, false},
		{V, false},
		{W, false},
		{X, false},
		{Y, false},
		{Z, false},

		{Num0, false},
		{Num1, false},
		{Num2, false},
		{Num3, false},
		{Num4, false},
		{Num5, false},
		{Num6, false},
		{Num7, false},
		{Num8, false},
		{Num9, false},

		{Numpad0, false},
		{Numpad1, false},
		{Numpad2, false},
		{Numpad3, false},
		{Numpad4, false},
		{Numpad5, false},
		{Numpad6, false},
		{Numpad7, false},
		{Numpad8, false},
		{Numpad9, false},

		{Backspace, false},
		{Tab, false},
		{Enter, false},
		{Shift, false},
		{Control, false},
		{Alt, false},
		{LShift, false},
		{RShift, false},
		{LControl, false},
		{RControl, false},
		{LAlt, false},
		{RAlt, false},
		{Esc, false},
		{Space, false},
		{Win, false},

		{Left, false},
		{Up, false},
		{Right, false},
		{Down, false},

		{F1, false},
		{F2, false},
		{F3, false},
		{F4, false},
		{F5, false},
		{F6, false},
		{F7, false},
		{F8, false},
		{F9, false},
		{F10, false},
		{F11, false},
		{F12, false}
	};
}

bool Pixel::Event::Close() const
{
	return close;
}

Pixel::Point Pixel::Event::MousePosition() const
{
	return mousePosition;
}

bool Pixel::Event::MouseDown() const
{
	return mouseDown;
}

bool Pixel::Event::KeyDown() const
{
	return keyDown;
}

bool Pixel::Event::IsDown(KeyCode key) const
{
	return keyStatus.find(key)->second;
}
