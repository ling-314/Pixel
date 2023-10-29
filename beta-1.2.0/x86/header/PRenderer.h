#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#include <string>
#include "PType.h"

template<typename T> void SafeRelease(T* type)
{
	if (type)
	{
		type->Release();
		type = nullptr;
	}
}

namespace Pixel
{
	class Renderer
	{
		Renderer(const Renderer&) = delete;
	public:
		Renderer(HWND hWnd);
		~Renderer();
		bool Init();
	public:
		void SetColor(Color color);
		void Rotate(float angle, Point point);
	public:
		ID2D1HwndRenderTarget* GetRenderTarget();
	public:
		void RenderEllipse(Point position, float scale, float angle, int radiusX, int radiusY, Color color, bool fill, float strokeWidth);
		void RenderRectangle(Point position, float scale, float angle, int width, int height, Color color, bool fill, float strokeWidth);
		void RenderLine(Point vertex1, Point vertex2, float scale, float angle, Color color, float strokeWidth);
		void RenderImage(Point position, float scale, float angle, ID2D1Bitmap* pBitmap);
		void RenderText(Point position, Color color, IDWriteTextLayout* pTextLayout);
	protected:
		HWND hWnd;
		ID2D1Factory* pFactory = nullptr;
		ID2D1HwndRenderTarget* pRenderTarget = nullptr;
		ID2D1SolidColorBrush* pSolidColorBrush = nullptr;
	};
}