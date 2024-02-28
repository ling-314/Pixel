#include "PRenderer.hpp"

ID2D1Factory* Pixel::Renderer::s_pFactory = nullptr;

Pixel::Renderer::Renderer(HWND hWnd, Camera* camera) :
	_hWnd(hWnd),
	_camera(camera),
	_pRenderTarget(nullptr)
{
}

Pixel::Renderer::~Renderer()
{
	P_SAFERELEASE(_pRenderTarget);
	P_SAFERELEASE(_pSolidColorBrush);
}

bool Pixel::Renderer::Init()
{
	HRESULT hr;

	hr = CoInitialize(nullptr);
	if (FAILED(hr)) return false;

	if (!s_pFactory)
	{
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &s_pFactory);
		if (FAILED(hr)) return false;
	}

	RECT wr;
	GetClientRect(_hWnd, &wr);
	hr = s_pFactory->CreateHwndRenderTarget(
		D2D1_RENDER_TARGET_PROPERTIES(),
		D2D1::HwndRenderTargetProperties(
			_hWnd,
			D2D1::SizeU(
				wr.right - wr.left,
				wr.bottom - wr.top
			)
		),
		&_pRenderTarget
	);
	if (FAILED(hr)) return false;

	hr = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_pSolidColorBrush);
	if (FAILED(hr))
	{
		P_SAFERELEASE(_pRenderTarget);
		return false;
	}

	return true;
}

void Pixel::Renderer::Clear(Color color)
{
	_pRenderTarget->Clear(color);
}

void Pixel::Renderer::Destroy()
{
	P_SAFERELEASE(s_pFactory);
}

ID2D1Factory* Pixel::Renderer::GetFactory()
{
	return s_pFactory;
}

Pixel::Camera* Pixel::Renderer::GetCamera()
{
	return _camera;
}

ID2D1HwndRenderTarget* Pixel::Renderer::GetRenderTarget()
{
	return _pRenderTarget;
}

ID2D1SolidColorBrush* Pixel::Renderer::GetSolidColorBrush()
{
	return _pSolidColorBrush;
}

void Pixel::Renderer::SetHWnd(HWND hWnd)
{
	if (!_pRenderTarget) _hWnd = hWnd;
}

void Pixel::Renderer::DrawEllipse(float radiusX, float radiusY, GraphicAttribute attr)
{
	_pSolidColorBrush->SetColor(attr.color);
	if (attr.fill)
		_pRenderTarget->FillEllipse(
			D2D1::Ellipse(
				Point(),
				radiusX,
				radiusY
			),
			_pSolidColorBrush
		);
	else
		_pRenderTarget->DrawEllipse(
			D2D1::Ellipse(
				Point(),
				radiusX,
				radiusY
			),
			_pSolidColorBrush,
			attr.strokeWidth
		);
}

void Pixel::Renderer::DrawRectangle(float width, float height, float radiusX, float radiusY, GraphicAttribute attr)
{
	_pSolidColorBrush->SetColor(attr.color);
	if (attr.fill)
		_pRenderTarget->FillRoundedRectangle(
			D2D1::RoundedRect(
				Size(width / -2, height / -2, width, height),
				radiusX,
				radiusY
			),
			_pSolidColorBrush
		);
	else
		_pRenderTarget->DrawRoundedRectangle(
			D2D1::RoundedRect(
				Size(width / -2, height / -2, width, height),
				radiusX,
				radiusY
			),
			_pSolidColorBrush,
			attr.strokeWidth
		);
}

void Pixel::Renderer::DrawLine(Point vertex1, Point vertex2, GraphicAttribute attr)
{
	_pSolidColorBrush->SetColor(attr.color);
	_pRenderTarget->DrawLine(
		vertex1,
		vertex2,
		_pSolidColorBrush,
		attr.strokeWidth
	);
}

void Pixel::Renderer::DrawPolygon(ID2D1PathGeometry* pPathGeometry, GraphicAttribute attr)
{
	_pSolidColorBrush->SetColor(attr.color);
	if (attr.fill)
		_pRenderTarget->FillGeometry(
			pPathGeometry,
			_pSolidColorBrush
		);
	else
		_pRenderTarget->DrawGeometry(
			pPathGeometry,
			_pSolidColorBrush,
			attr.strokeWidth
		);
	return;
}

void Pixel::Renderer::DrawText(IDWriteTextLayout* pTextLayout, Color color)
{
	DWRITE_TEXT_METRICS textMetrics;
	pTextLayout->GetMetrics(&textMetrics);

	_pSolidColorBrush->SetColor(color);
	_pRenderTarget->DrawTextLayout(
		Point(textMetrics.width / -2, textMetrics.height / -2),
		pTextLayout,
		_pSolidColorBrush
	);
}

void Pixel::Renderer::DrawImage(ID2D1Bitmap* pBitmap)
{
	Size size = pBitmap->GetSize();
	_pRenderTarget->DrawBitmap(
		pBitmap,
		Size(
			size.width / -2,
			size.height / -2,
			size.width,
			size.height
		),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		size
	);
}
