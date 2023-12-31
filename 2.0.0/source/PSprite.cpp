#include "PNode.h"

Pixel::Sprite::Sprite(int x, int y, std::string path) :
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
	SafeRelease(pConverter);
}

std::string Pixel::Sprite::GetPath() const
{
	return path;
}

void Pixel::Sprite::SetPath(std::string path)
{
	this->path = path;

	SafeRelease(pConverter);

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
		pConverter = nullptr;
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
		pConverter = nullptr;
		return;
	}

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pDecoder);
		pConverter = nullptr;
		return;
	}

	hr = pFactory->CreateFormatConverter(&pConverter);
	if (!SUCCEEDED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pDecoder);
		SafeRelease(pFrame);
		pConverter = nullptr;
		return;
	}

	hr = pConverter->Initialize(
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
		pConverter = nullptr;
		return;
	}

	SafeRelease(pFactory);
	SafeRelease(pDecoder);
	SafeRelease(pFrame);
	
	UINT width, height;
	pConverter->GetSize(&width, &height);
	originalSize(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y + height / 2));
	SetTransform();
	SetCollisionBox(size);
}

void Pixel::Sprite::RenderSelf(Renderer* renderer)
{
	ID2D1Bitmap* pBitmap;

	HRESULT hr;
	
	hr = renderer->GetRenderTarget()->CreateBitmapFromWicBitmap(
		pConverter,
		nullptr,
		&pBitmap
	);
	if (!SUCCEEDED(hr)) return;

	renderer->RenderImage(position, offset, transform, pBitmap);

	SafeRelease(pBitmap);
}
