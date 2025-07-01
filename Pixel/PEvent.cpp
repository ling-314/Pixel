#include "PEvent.hpp"

bool Pixel::Event::Pressed(KeyCode keycode)
{
    for (auto aKeycode : keyCode)
        if (aKeycode == keycode)
            return true;
    return false;
}
