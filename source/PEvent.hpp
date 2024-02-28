#pragma once
#include <Windows.h>
#include <vector>
#include "PType.hpp"

namespace Pixel
{
	// 鼠标、键盘编码
	enum KeyCode
	{
		LeftBtn = VK_LBUTTON,
		RightBtn,
		MiddleBtn = VK_MBUTTON,

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

		Numpad0 = VK_NUMPAD0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,

		F1 = VK_F1,
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

		Backspace = VK_BACK,
		Tab,
		Enter,

		Shift = VK_SHIFT,
		Control,
		Alt,

		Space =VK_SPACE,

		LeftArrow = VK_LEFT,
		UpArrow,
		RightArrow,
		DownArrow,

		LeftShift = VK_LSHIFT,
		RightShift,
		LeftControl,
		RightControl,
		LeftAlt,
		RightAlt
	};

	// 窗口事件
	class Event
	{
		friend class Window;
	public:
		Event();
		// 窗口关闭
		bool Close() const;
		// 鼠标按下
		bool IsMouseDown() const;
		// 键盘按下
		bool IsKeyDown() const;
		// 按键按下
		bool IsDown(KeyCode code) const;
		// 鼠标移动
		bool IsMouseMove() const;
	private:
		bool					_close;
		bool					_mouseDown;
		bool					_keyDown;
		std::vector<KeyCode>	_pressed;
		bool					_mouseMove;
		Point					_mousePosition;
	};
}