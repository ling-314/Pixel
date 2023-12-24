#pragma once
#include <map>
#include "PType.h"

namespace Pixel
{
	enum KeyCode
	{
		left,
		middle,
		right,

		A = 0x41,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		Num0 = 0x30,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,

		Numpad0 = 0x60,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,

		Backspace = 0x08,
		Tab,
		Enter = 0x0B,
		Shift = 0x10,
		Control,
		Alt,
		LShift = 0xA0,
		RShift,
		LControl,
		RControl,
		LAlt,
		RAlt,
		Esc = 0x1B,
		Space = 0x20,
		Win = 0x5B,

		Left = 0x25,
		Up,
		Right,
		Down,

		F1 = 0x70,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
	};

	// ´°¿ÚÊÂ¼þ
	class Event
	{
		friend class Window;
	public:
		Event();
		bool Close() const;
		Point MousePosition() const;
		bool MouseDown() const;
		bool KeyDown() const;
		bool IsDown(KeyCode key) const;
	protected:
		bool close;
		Point mousePosition;
		bool mouseDown;
		bool keyDown;
		std::map<KeyCode, bool> keyStatus;
	};
}