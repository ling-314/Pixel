#include "PNode.h"

Pixel::Sprite::Sprite(float x, float y, std::string path) :
	Node(x, y)
{
	SetPath(path);
}

Pixel::Sprite::Sprite(std::string path) :
	Sprite(0, 0, path)
{
}

Pixel::Sprite::~Sprite()
{
	SafeRelease(_pConverter);
}

std::string Pixel::Sprite::GetPath() const
{
	return _path;
}

void Pixel::Sprite::SetPath(std::string path)
{
	this->_path = path;

	SafeRelease(_pConverter);

	HRESULT hr;

	IWICImagingFactory* pFactory = nullptr;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pFactory
	);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(_pConverter);
		return;
	}

	IWICBitmapDecoder* pDecoder = nullptr;
	hr = pFactory->CreateDecoderFromFilename(
		ToWideString(path.c_str()).c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(_pConverter);
		return;
	}

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pDecoder);
		SafeRelease(_pConverter);
		return;
	}

	hr = pFactory->CreateFormatConverter(&_pConverter);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pDecoder);
		SafeRelease(pFrame);
		SafeRelease(_pConverter);
		return;
	}

	hr = _pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0,
		WICBitmapPaletteTypeCustom
	);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pDecoder);
		SafeRelease(pFrame);
		SafeRelease(_pConverter);
		return;
	}

	SafeRelease(pFactory);
	SafeRelease(pDecoder);
	SafeRelease(pFrame);
	
	UINT width, height;
	_pConverter->GetSize(&width, &height);
	_originalSize(Point(_position.x - width / 2, _position.y - height / 2), Point(_position.x + width / 2, _position.y + height / 2));
	_SetTransform();
}

void Pixel::Sprite::Render(Renderer* renderer)
{
	ID2D1Bitmap* pBitmap;

	HRESULT hr;
	
	hr = renderer->GetRenderTarget()->CreateBitmapFromWicBitmap(
		_pConverter,
		nullptr,
		&pBitmap
	);
	if (!SUCCEEDED(hr)) return;

	renderer->RenderImage(_position, _offset, _transform, pBitmap);

	SafeRelease(pBitmap);
}
