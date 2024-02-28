#include "PEvent.hpp"

Pixel::Event::Event() :
	_close(false),
	_mouseDown(false),
	_keyDown(false),
	_mouseMove(false)
{
}

bool Pixel::Event::Close() const
{
	return _close;
}

bool Pixel::Event::IsDown(KeyCode code) const
{
	return std::find(_pressed.begin(), _pressed.end(), code) != _pressed.end();
}

bool Pixel::Event::IsMouseDown() const
{
	return _mouseDown;
}

bool Pixel::Event::IsMouseMove() const
{
	return _mouseMove;
}

bool Pixel::Event::IsKeyDown() const
{
	return _keyDown;
}
