#include "PEvent.h"

Pixel::Event::Event() :
	_close(false),
	_mousePosition(0, 0),
	_mouseDown(false),
	_mouseWhell(false),
	_keyDown(false)
{
	_mouseStatus =
	{
		{left, false},
		{middle, false},
		{right, false}
	};
}

bool Pixel::Event::Close() const
{
	return _close;
}

Pixel::Point Pixel::Event::MousePosition() const
{
	return _mousePosition;
}

bool Pixel::Event::MouseDown() const
{
	return _mouseDown;
}

bool Pixel::Event::KeyDown() const
{
	return _keyDown;
}

bool Pixel::Event::IsDown(KeyCode key) const
{
	return GetKeyState(key) & 0x8000;
}

bool Pixel::Event::IsDown(MouseCode key) const
{
	return _mouseStatus.at(key);
}
