#include "PNode.hpp"

IWICImagingFactory* Pixel::Sprite::s_pFactory = nullptr;

Pixel::Sprite::Sprite() :
	Sprite(.0f, .0f, "")
{
}

Pixel::Sprite::Sprite(float x, float y) :
	Sprite(x, y, "")
{
}

Pixel::Sprite::Sprite(std::string path) :
	Sprite(.0f, .0f, path)
{
}

Pixel::Sprite::Sprite(float x, float y, std::string path) :
	Node(x, y),
	_path(path),
	_resource(0, "", nullptr),
	_pConverter(nullptr)
{
	_Create();
}

Pixel::Sprite::Sprite(int resourceID, std::string resourceType, HMODULE resourceModule) :
	Sprite(.0f, .0f, resourceID, resourceType, resourceModule)
{
}

Pixel::Sprite::Sprite(float x, float y, int resourceID, std::string resourceType, HMODULE resourceModule) :
	Node(x, y),
	_path(""),
	_resource(resourceID, resourceType, resourceModule),
	_pConverter(nullptr)
{
	_Create();
}

void Pixel::Sprite::RenderSelf(Renderer* renderer)
{
	if (!_pConverter) return;

	ID2D1Bitmap* pBitmap;

	HRESULT hr;

	if (!_pConverter) return;
	hr = renderer->GetRenderTarget()->CreateBitmapFromWicBitmap(
		_pConverter,
		nullptr,
		&pBitmap
	);

	renderer->DrawImage(pBitmap, _cropping);
	P_SAFERELEASE(pBitmap);
}

void Pixel::Sprite::Crop(Size size)
{
	_cropping = size;
}

void Pixel::Sprite::Destroy()
{
	P_SAFERELEASE(s_pFactory);
}

std::string Pixel::Sprite::GetPath() const
{
	return _path;
}

int Pixel::Sprite::GetResourceID() const
{
	return _resource.id;
}

std::string Pixel::Sprite::GetResourceType() const
{
	return _resourceType;
}

IWICFormatConverter* Pixel::Sprite::GetIWICFormatConverter()
{
	return _pConverter;
}

void Pixel::Sprite::SetPath(std::string path)
{
	_path = path;
	_Create();
}

void Pixel::Sprite::SetResourceID(int resourceID)
{
	_resource.id = resourceID;
}

void Pixel::Sprite::SetResourceType(std::string resourceType)
{
	_resourceType = resourceType;
}

void Pixel::Sprite::_ResetSize() // 有误差，接受不了的话自己搞吧
{
	if (!_pConverter)
	{
		_SetSize(Size());
		return;
	}

	UINT width, height;
	_pConverter->GetSize(&width, &height);

	Size size(
		-(float)width / 2,
		-(float)height / 2,
		(float)width,
		(float)height
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[1] = GetTransform().TransformPoint(points[1]);
	points[2] = GetTransform().TransformPoint(points[2]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		GetLeftTop({ points[0], points[1], points[2], points[3] }),		// 怪麻烦的
		GetRightBottom({ points[0], points[1], points[2], points[3] })
	);

	_SetSize(size);
}

void Pixel::Sprite::_Create()
{
	P_SAFERELEASE(_pConverter);

	HRESULT hr;

	if (!s_pFactory)
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&s_pFactory
		);
		if (FAILED(hr)) return;
	}

	IWICBitmapDecoder* pDecoder;
	
	if (_path != "")
	{
		hr = s_pFactory->CreateDecoderFromFilename(
			ToWideString(_path).c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		if (FAILED(hr)) return;
	}
	else if (_resource.id != 0 && _resource.type != "")
	{
		if (!_resource.Load()) return;

		IWICStream* pStream;
		hr = s_pFactory->CreateStream(&pStream);
		if (FAILED(hr)) return;

		hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(_resource.GetBuffer()), _resource.GetSize());
		if (FAILED(hr))
		{
			P_SAFERELEASE(pStream);
			return;
		}

		hr = s_pFactory->CreateDecoderFromStream(
			pStream,
			nullptr,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		P_SAFERELEASE(pStream);
		if (FAILED(hr)) return;
	}
	else
	{
		return;
	}

	IWICBitmapFrameDecode* pSource;
	hr = pDecoder->GetFrame(0, &pSource);
	P_SAFERELEASE(pDecoder);
	if (FAILED(hr)) return;

	hr = s_pFactory->CreateFormatConverter(&_pConverter);
	if (FAILED(hr))
	{
		P_SAFERELEASE(pSource);
		return;
	}

	hr = _pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		.0,
		WICBitmapPaletteTypeCustom
	);
	P_SAFERELEASE(pSource);
	if (FAILED(hr))
	{
		P_SAFERELEASE(_pConverter);
		return;
	}

	UINT width, height;
	_pConverter->GetSize(&width, &height);
	Crop(Size(Point(.0f, .0f), Point((int)width, (int)height)));

	_SetTransfrom();
	_ResetSize();
}
