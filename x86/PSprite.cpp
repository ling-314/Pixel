#include "PNode.h"

Pixel::Sprite::Sprite(int x, int y, std::wstring path) :
	Node(x, y)
{
	SetPath(path);
}

Pixel::Sprite::~Sprite()
{
	if (pConverter) pConverter->Release();
}

std::wstring Pixel::Sprite::GetPath() const
{
	return path;
}

void Pixel::Sprite::SetPath(std::wstring path)
{
	this->path = path;

	HRESULT hr;

	IWICImagingFactory* pFactory = nullptr;
	CoInitialize(nullptr);
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pFactory
	);
	if (!SUCCEEDED(hr)) return;

	IWICBitmapDecoder* pDecoder = nullptr;
	hr = pFactory->CreateDecoderFromFilename(
		path.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (!SUCCEEDED(hr)) return;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (!SUCCEEDED(hr)) return;

	hr = pFactory->CreateFormatConverter(&pConverter);
	if (!SUCCEEDED(hr)) return;

	hr = pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0,
		WICBitmapPaletteTypeCustom
	);
	if (!SUCCEEDED(hr)) return;

	if (pFactory) pFactory->Release();
	if (pDecoder) pDecoder->Release();
	if (pFrame) pFrame->Release();
	
	UINT width, height;
	pConverter->GetSize(&width, &height);
	size(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y + height / 2));
	SetCollisionBox(size);
}

void Pixel::Sprite::Render(Renderer* renderer)
{
	ID2D1Bitmap* pBitmap;

	HRESULT hr;
	
	hr = renderer->GetRenderTarget()->CreateBitmapFromWicBitmap(
		pConverter,
		nullptr,
		&pBitmap
	);
	if (!SUCCEEDED(hr)) return;

	renderer->RenderImage(position, pBitmap);

	if (pBitmap) pBitmap->Release();

	for (auto node : children)
	{
		node->Render(renderer);
	}
}
