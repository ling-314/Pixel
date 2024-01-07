#include "PRenderer.h"

Pixel::Renderer::Renderer(HWND hWnd,Camera* camera) :
	_hWnd(hWnd),
	_camera(camera)
{
}

Pixel::Renderer::~Renderer()
{
	SafeRelease(_pFactory);
	SafeRelease(_pRenderTarget);
	SafeRelease(_pSolidColorBrush);
}

bool Pixel::Renderer::Init()
{
	HRESULT hr;

	hr = CoInitialize(nullptr);
	if (FAILED(hr)) return false;

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&_pFactory
	);
	if (FAILED(hr)) return false;

	RECT wr;
	GetClientRect(_hWnd, &wr);

	hr = _pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			_hWnd,
			D2D1::SizeU(
				(UINT32)(wr.right - wr.left),
				(UINT32)(wr.bottom - wr.top)
			)
		),
		&_pRenderTarget
	);
	if (FAILED(hr))
	{
		SafeRelease(_pFactory);
		return false;
	}

	hr = _pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&_pSolidColorBrush
	);
	if (FAILED(hr))
	{
		SafeRelease(_pFactory);
		SafeRelease(_pRenderTarget);
		return false;
	}

	return true;
}

void Pixel::Renderer::SetColor(Color color)
{
	_pSolidColorBrush->SetColor(D2D1::ColorF(
		(float)color.r / 255,
		(float)color.g / 255,
		(float)color.b / 255,
		(float)color.a / 255
	));
}

ID2D1HwndRenderTarget* Pixel::Renderer::GetRenderTarget()
{
	return _pRenderTarget;
}

void Pixel::Renderer::RenderEllipse(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int radiusX, int radiusY, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	_pRenderTarget->SetTransform(transform);
	if (fill)
		_pRenderTarget->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x + offset.x + _camera->GetOffsetX(),
					(float)position.y + offset.y + _camera->GetOffsetY()
				),
				radiusX,
				radiusY
			),
			_pSolidColorBrush
		);
	else
		_pRenderTarget->DrawEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(
					(float)position.x + offset.x + _camera->GetOffsetX(),
					(float)position.y + offset.y + _camera->GetOffsetY()
				),
				radiusX,
				radiusY
			),
			_pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderRectangle(Point position, Vector2 offset, D2D1::Matrix3x2F transform, int width, int height, Color color, bool fill, float strokeWidth)
{
	SetColor(color);
	_pRenderTarget->SetTransform(transform);
	if (fill)
		_pRenderTarget->FillRectangle(
			D2D1::RectF(
				(float)position.x - (float)width / 2 + offset.x + _camera->GetOffsetX(),
				(float)position.y - (float)height / 2 + offset.y + _camera->GetOffsetY(),
				(float)position.x + (float)width / 2 + offset.x + _camera->GetOffsetX(),
				(float)position.y + (float)height / 2 + offset.y + _camera->GetOffsetY()
			),
			_pSolidColorBrush
		);
	else
		_pRenderTarget->DrawRectangle(
			D2D1::RectF(
				(float)position.x - (float)width / 2 + offset.x + _camera->GetOffsetX(),
				(float)position.y - (float)height / 2 + offset.y + _camera->GetOffsetY(),
				(float)position.x + (float)width / 2 + offset.x + _camera->GetOffsetX(),
				(float)position.y + (float)height / 2 + offset.y + _camera->GetOffsetY()
			),
			_pSolidColorBrush,
			strokeWidth
		);
}

void Pixel::Renderer::RenderLine(Point vertex1, Point vertex2, Vector2 offset, D2D1::Matrix3x2F transform, Color color, float strokeWidth)
{
	SetColor(color);
	_pRenderTarget->SetTransform(transform);
	_pRenderTarget->DrawLine(
		D2D1::Point2F(
			vertex1.x + offset.x + _camera->GetOffsetX(),
			vertex1.y + offset.y + _camera->GetOffsetY()
		),
		D2D1::Point2F(
			vertex2.x + offset.x + _camera->GetOffsetX(),
			vertex2.y + offset.y + _camera->GetOffsetY()
		),
		_pSolidColorBrush,
		strokeWidth
	);
}

void Pixel::Renderer::RenderImage(Point position, Vector2 offset, D2D1::Matrix3x2F transform, ID2D1Bitmap* pBitmap)
{
	_pRenderTarget->SetTransform(transform);
	_pRenderTarget->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			(float)position.x - pBitmap->GetSize().width / 2 + offset.x + _camera->GetOffsetX(),
			(float)position.y - pBitmap->GetSize().height / 2 + offset.y + _camera->GetOffsetY(),
			(float)position.x + pBitmap->GetSize().width / 2 + offset.x + _camera->GetOffsetX(),
			(float)position.y + pBitmap->GetSize().height / 2 + offset.y + _camera->GetOffsetY()
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
	_pRenderTarget->SetTransform(transform);

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);

	_pRenderTarget->DrawTextLayout(
		D2D1::Point2F(
			(float)position.x - metrics.width / 2 + offset.x + _camera->GetOffsetX(),
			(float)position.y - metrics.height / 2 + offset.y + _camera->GetOffsetY()
		),
		pTextLayout,
		_pSolidColorBrush
	);
}
