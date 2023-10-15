#pragma once
#include <dwrite.h>

namespace Pixel
{
	typedef const wchar_t* unichar;

	class Point
	{
	public:
		Point(int x, int y);
		void operator()(int x, int y);
		void operator()(Point point);
		void operator=(Point point);
	public:
		int x;
		int y;
	};

	class Color
	{
	public:
		Color(int r, int g, int b);
		Color(int r, int g, int b, int a);
		Color(int hex);
		Color(int hex, int a);
		void operator()(int r, int g, int b);
		void operator()(int r, int g, int b, int a);
		void operator=(Color color);
	public:
		int r;
		int g;
		int b;
		int a = 255;
	public:
		enum : UINT
		{
			Black = 0x000000,
			Blue = 0x0000FF,
			BlueViolet = 0x8A2BE2,
			Brown = 0xA52A2A,
			Chocolate = 0xD2691E,
			DarkBlue = 0x00008B,
			DarkGray = 0xA9A9A9,
			DarkGreen = 0x006400,
			DarkOrange = 0xFF8C00,
			DarkRed = 0x8B0000,
			DarkViolet = 0x9400D3,
			ForestGreen = 0x228B22,
			Gold = 0xFFD700,
			Gray = 0x808080,
			Green = 0x008000,
			GreenYellow = 0xADFF2F,
			LightBlue = 0xADD8E6,
			LightCyan = 0xE0FFFF,
			LightGreen = 0x90EE90,
			LightGray = 0xD3D3D3,
			LightPink = 0xFFB6C1,
			LightSeaGreen = 0x20B2AA,
			LightSkyBlue = 0x87CEFA,
			LightYellow = 0xFFFFE0,
			Orange = 0xFFA500,
			OrangeRed = 0xFF4500,
			Pink = 0xFFC0CB,
			Purple = 0x800080,
			Red = 0xFF0000,
			Silver = 0xC0C0C0,
			SkyBlue = 0x87CEEB,
			Snow = 0xFFFAFA,
			Violet = 0xEE82EE,
			Wheat = 0xF5DEB3,
			White = 0xFFFFFF,
			WhiteSmoke = 0xF5F5F5,
			Wood = 0xDEB887,
			Yellow = 0xFFFF00,
			YellowGreen = 0x9ACD32
		};
	};

	class Size
	{
	public:
		Size(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);
		Size(Point leftTop, Point rightBottom);
		void operator()(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY);
		void operator()(Point leftTop, Point rightBottom);
		void operator=(Size size);
	public:
		Point leftTop;
		Point rightBottom;
	};

	using CollisionBox = Size;
}