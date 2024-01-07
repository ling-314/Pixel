#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#include <string>
#include "PType.h"
#include "PCamera.h"
#include "PPublic.h"

namespace Pixel
{
	class Renderer
	{
		Renderer(const Renderer&) = delete;
	public:
		Renderer(HWND hWnd, Camera* camera);
		~Renderer();
		bool Init();
	public:
		void SetColor(Color color);
	public:
		ID2D1HwndRenderTarget* GetRenderTarget();
	public:
		void RenderEllipse(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int radiusX, int radiusY, Color color, bool fill, float strokeWidth);
		void RenderRectangle(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int width, int height, Color color, bool fill, float strokeWidth);
		void RenderLine(Point vertex1, Point vertex2, Vector2 offset, D2D1::Matrix3x2F transform, Color color, float strokeWidth);
		void RenderImage(Point position, Vector2 offset, D2D1::Matrix3x2F transform, ID2D1Bitmap* pBitmap);
		void RenderText(Point position, Vector2 offset, D2D1::Matrix3x2F transform, Color color, IDWriteTextLayout* pTextLayout);
	protected:
		HWND					_hWnd;
		Camera*					_camera;
		ID2D1Factory*			_pFactory = nullptr;
		ID2D1HwndRenderTarget*	_pRenderTarget = nullptr;
		ID2D1SolidColorBrush*	_pSolidColorBrush = nullptr;
	};
}