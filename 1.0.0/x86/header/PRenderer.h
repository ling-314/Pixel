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
	public:
		ID2D1HwndRenderTarget* GetRenderTarget();
	public:
		void RenderEllipse(Point position, D2D1::Matrix3x2F transform, int radiusX, int radiusY, Color color, bool fill, float strokeWidth);
		void RenderRectangle(Point position, D2D1::Matrix3x2F transform, int width, int height, Color color, bool fill, float strokeWidth);
		void RenderLine(Point vertex1, Point vertex2, D2D1::Matrix3x2F transform, Color color, float strokeWidth);
		void RenderImage(Point position, D2D1::Matrix3x2F transform, ID2D1Bitmap* pBitmap);
		void RenderText(Point position, D2D1::Matrix3x2F transform, Color color, IDWriteTextLayout* pTextLayout);
	protected:
		HWND hWnd;
		ID2D1Factory* pFactory = nullptr;
		ID2D1HwndRenderTarget* pRenderTarget = nullptr;
		ID2D1SolidColorBrush* pSolidColorBrush = nullptr;
	};
}