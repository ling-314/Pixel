#include "PRenderer.h"

Pixel::Renderer::Renderer(HWND hWnd) :
	hWnd(hWnd)
{
}

Pixel::Renderer::~Renderer()
{
	SafeRelease(pFactory);
	SafeRelease(pRenderTarget);
	SafeRelease(pSolidColorBrush);
}

bool Pixel::Renderer::Init()
{
	HRESULT hr;

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pFactory
	);
	if (FAILED(hr)) return false;

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
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		return false;
	}

	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&pSolidColorBrush
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pRenderTarget);
		return false;
	}

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

void Pixel::Renderer::Rotate(float angle, Point point)
{
	pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(
			angle,
			D2D1::Point2F(
				(float)point.x,
				(float)point.y
			)
		)
	);
}

ID2D1HwndRenderTarget* Pixel::Renderer::GetRenderTarget()
{
	return pRenderTarget;
}

void Pixel::Renderer::RenderEllipse(Point position, float scale, float angle, int radiusX, int radiusY, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	Rotate(angle, position);
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
			pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderRectangle(Point position, float scale, float angle, int width, int height, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	Rotate(angle, position);
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
			pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderLine(Point vertex1, Point vertex2, float scale, float angle, Color color, float strokeWidth)
{
	SetColor(color);
	pRenderTarget->DrawLine(
		D2D1::Point2F(
			vertex1.x - abs(vertex2.x - vertex1.x) / 2 * scale,
			vertex1.y - abs(vertex2.y - vertex1.y) / 2 * scale
		),
		D2D1::Point2F(
			vertex2.x + abs(vertex2.x - vertex1.x) / 2 * scale,
			vertex2.y + abs(vertex2.y - vertex1.y) / 2 * scale
		),
		pSolidColorBrush,
		strokeWidth
	);
}

void Pixel::Renderer::RenderImage(Point position, float scale, float angle, ID2D1Bitmap* pBitmap)
{
	Rotate(angle, position);
	pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			(float)position.x - pBitmap->GetSize().width / 2 * scale,
			(float)position.y - pBitmap->GetSize().height / 2 * scale,
			(float)position.x + pBitmap->GetSize().width / 2 * scale,
			(float)position.y + pBitmap->GetSize().height / 2 * scale
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

void Pixel::Renderer::RenderText(Point position, Color color, IDWriteTextLayout* pTextLayout)
{	
	SetColor(color);

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);

	pRenderTarget->DrawTextLayout(
		D2D1::Point2F(
			(float)position.x - metrics.width / 2,
			(float)position.y - metrics.height / 2
		),
		pTextLayout,
		pSolidColorBrush
	);
}
