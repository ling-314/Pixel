#pragma once
#include "PType.h"

namespace Pixel
{
	enum MouseCode
	{
		left,
		middle,
		right
	};

	enum KeyCode
	{
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
	};

	// ´°¿ÚÊÂ¼þ
	class Event
	{
		friend class Window;
	public:
		bool Close() const;
		bool MouseDown() const;
		bool MouseUp() const;
		MouseCode MouseKey() const;
		Point MousePosition() const;
		bool KeyDown() const;
		bool KeyUp() const;
		KeyCode Key() const;
	protected:
		bool close = false;
		bool mouseDown = false;
		bool mouseUp = true;
		MouseCode mouseCode;
		Point mousePosition = Point(0, 0);
		bool keyDown = false;
		bool keyUp = true;
		KeyCode keyCode;
	};
}