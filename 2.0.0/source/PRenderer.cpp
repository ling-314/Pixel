#include "PRenderer.h"

Pixel::Renderer::Renderer(HWND hWnd,Camera* camera) :
	hWnd(hWnd),
	camera(camera)
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

	hr = CoInitialize(nullptr);
	if (FAILED(hr)) return false;

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

ID2D1HwndRenderTarget* Pixel::Renderer::GetRenderTarget()
{
	return pRenderTarget;
}

void Pixel::Renderer::RenderEllipse(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int radiusX, int radiusY, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	pRenderTarget->SetTransform(transform);
	if (fill)
		pRenderTarget->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x - offset.x + camera->GetOffsetX(),
					(float)position.y - offset.y + camera->GetOffsetY()
				),
				radiusX,
				radiusY
			),
			pSolidColorBrush
		);
	else
		pRenderTarget->DrawEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x - offset.x + camera->GetOffsetX(),
					(float)position.y - offset.y + camera->GetOffsetY()
				),
				radiusX,
				radiusY
			),
			pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderRectangle(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int width, int height, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	pRenderTarget->SetTransform(transform);
	if (fill)
		pRenderTarget->FillRectangle(
			D2D1::RectF(
				(float)position.x - (float)width / 2 - offset.x + camera->GetOffsetX(),
				(float)position.y - (float)height / 2 - offset.y + camera->GetOffsetY(),
				(float)position.x + (float)width / 2 - offset.x + camera->GetOffsetX(),
				(float)position.y + (float)height / 2 - offset.y + camera->GetOffsetY()
			),
			pSolidColorBrush
		);
	else
		pRenderTarget->DrawRectangle(
			D2D1::RectF(
				(float)position.x - (float)width / 2 - offset.x + camera->GetOffsetX(),
				(float)position.y - (float)height / 2 - offset.y + camera->GetOffsetY(),
				(float)position.x + (float)width / 2 - offset.x + camera->GetOffsetX(),
				(float)position.y + (float)height / 2 - offset.y + camera->GetOffsetY()
			),
			pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderLine(Point vertex1, Point vertex2, Vector2 offset, D2D1::Matrix3x2F transform, Color color, float strokeWidth)
{
	SetColor(color);
	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawLine(
		D2D1::Point2F(
			vertex1.x - offset.x + camera->GetOffsetX(),
			vertex1.y - offset.y + camera->GetOffsetY()
		),
		D2D1::Point2F(
			vertex2.x - offset.x + camera->GetOffsetX(),
			vertex2.y - offset.y + camera->GetOffsetY()
		),
		pSolidColorBrush,
		strokeWidth
	);
}

void Pixel::Renderer::RenderImage(Point position, Vector2 offset, D2D1::Matrix3x2F transform, ID2D1Bitmap* pBitmap)
{
	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			(float)position.x - pBitmap->GetSize().width / 2 - offset.x + camera->GetOffsetX(),
			(float)position.y - pBitmap->GetSize().height / 2 - offset.y + camera->GetOffsetY(),
			(float)position.x + pBitmap->GetSize().width / 2 - offset.x + camera->GetOffsetX(),
			(float)position.y + pBitmap->GetSize().height / 2 - offset.y + camera->GetOffsetY()
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

void Pixel::Renderer::RenderText(Point position, Vector2 offset, D2D1::Matrix3x2F transform, Color color, IDWriteTextLayout* pTextLayout)
{	
	SetColor(color);
	pRenderTarget->SetTransform(transform);

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);

	pRenderTarget->DrawTextLayout(
		D2D1::Point2F(
			(float)position.x - metrics.width / 2 - offset.x + camera->GetOffsetX(),
			(float)position.y - metrics.height / 2 - offset.y + camera->GetOffsetY()
		),
		pTextLayout,
		pSolidColorBrush
	);
}
