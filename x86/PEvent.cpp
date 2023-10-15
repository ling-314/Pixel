#include "PEvent.h"

bool Pixel::Event::Close() const
{
    return close;
}

bool Pixel::Event::MouseDown() const
{
    return mouseDown;
}

bool Pixel::Event::MouseUp() const
{
    return mouseUp;
}

Pixel::MouseCode Pixel::Event::MouseKey() const
{
    return mouseCode;
}

Pixel::Point Pixel::Event::MousePosition() const
{
    return mousePosition;
}

bool Pixel::Event::KeyDown() const
{
    return keyDown;
}

bool Pixel::Event::KeyUp() const
{
    return keyUp;
}

Pixel::KeyCode Pixel::Event::Key() const
{
    return keyCode;
}
