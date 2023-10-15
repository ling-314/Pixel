#include "PRenderer.h"

Pixel::Renderer::Renderer(HWND hWnd) :
	hWnd(hWnd)
{
}

Pixel::Renderer::~Renderer()
{
	if (pFactory) pFactory->Release();
	if (pRenderTarget) pRenderTarget->Release();
	if (pSolidColorBrush) pSolidColorBrush->Release();
}

bool Pixel::Renderer::Init()
{
	HRESULT hr;

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pFactory
	);
	if (!SUCCEEDED(hr)) return false;

	RECT wr;
	GetClientRect(hWnd, &wr);

	hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(
				(UINT32)(wr.right - wr.left),
				(UINT32)(wr.bottom - wr.top)
			)
		),
		&pRenderTarget
	);
	if (!SUCCEEDED(hr)) return false;

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&pSolidColorBrush
	);
	if (!SUCCEEDED(hr)) return false;

	return true;
}

void Pixel::Renderer::SetColor(Color color)
{
	pSolidColorBrush->SetColor(D2D1::ColorF(
		(float)color.r / 255,
		(float)color.g / 255,
		(float)color.b / 255,
		(float)color.a / 255
	));
}

ID2D1HwndRenderTarget* Pixel::Renderer::GetRenderTarget()
{
	return pRenderTarget;
}

void Pixel::Renderer::RenderEllipse(Point position, float scale, int radiusX, int radiusY, Color color, bool fill)
{
	SetColor(color);
	if (fill)
		pRenderTarget->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x,
					(float)position.y
				),
				radiusX * scale,
				radiusY * scale
			),
			pSolidColorBrush
		);
	else
		pRenderTarget->DrawEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x,
					(float)position.y
				),
				radiusX * scale,
				radiusY * scale
			),
			pSolidColorBrush
		);
}

void Pixel::Renderer::RenderRectangle(Point position, float scale, int width, int height, Color color, bool fill)
{
	SetColor(color);
	if (fill)
		pRenderTarget->FillRectangle(
			D2D1::RectF(
				((float)position.x - (float)width / 2) * scale,
				((float)position.y - (float)height / 2) * scale,
				((float)position.x + (float)width / 2) * scale,
				((float)position.y + (float)height / 2) * scale
			),
			pSolidColorBrush
		);
	else
		pRenderTarget->DrawRectangle(
			D2D1::RectF(
				((float)position.x - (float)width / 2) * scale,
				((float)position.y - (float)height / 2) * scale,
				((float)position.x + (float)width / 2) * scale,
				((float)position.y + (float)height / 2) * scale
			),
			pSolidColorBrush
		);
}

void Pixel::Renderer::RenderLine(Point vertex1, Point vertex2, Color color)
{
	SetColor(color);
	pRenderTarget->DrawLine(
		D2D1::Point2F(
			(float)vertex1.x,
			(float)vertex1.y
		),
		D2D1::Point2F(
			(float)vertex2.x,
			(float)vertex2.y
		),
		pSolidColorBrush
	);
}

void Pixel::Renderer::RenderImage(Point position, ID2D1Bitmap* pBitmap)
{
	pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			(float)position.x - pBitmap->GetSize().width / 2,
			(float)position.y - pBitmap->GetSize().height / 2,
			(float)position.x + pBitmap->GetSize().width / 2,
			(float)position.y + pBitmap->GetSize().height / 2
		),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(
			0.0f,
			0.0f,
			pBitmap->GetSize().width,
			pBitmap->GetSize().height
		)
	);
}

void Pixel::Renderer::RenderText(Point position, Color color, IDWriteTextLayout* pTextLayout, int width)
{	
	SetColor(color);
	pRenderTarget->DrawTextLayout(
		D2D1::Point2F(
			(float)position.x - width / 2,
			(float)position.y
		),
		pTextLayout,
		pSolidColorBrush
	);
}
