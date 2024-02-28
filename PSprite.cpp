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
	_resourceName(0),
	_pConverter(nullptr)
{
	_Create();
}

Pixel::Sprite::Sprite(int resourceName, std::string resourceType) :
	Sprite(.0f, .0f, resourceName, resourceType)
{
}

Pixel::Sprite::Sprite(float x, float y, int resourceName, std::string resourceType) :
	Node(x, y),
	_path(""),
	_resourceName(resourceName),
	_resourceType(resourceType),
	_pConverter(nullptr)
{
	_Create();
}

void Pixel::Sprite::Render(Renderer* renderer)
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

	renderer->DrawImage(pBitmap);
	P_SAFERELEASE(pBitmap);
}

void Pixel::Sprite::Destroy()
{
	P_SAFERELEASE(s_pFactory);
}

std::string Pixel::Sprite::GetPath() const
{
	return _path;
}

int Pixel::Sprite::GetResourceName() const
{
	return _resourceName;
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

void Pixel::Sprite::SetResourceName(int resourceName)
{
	_resourceName = resourceName;
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
	else if (_resourceName != 0)
	{
		HRSRC resource = FindResource(GetModuleHandle(nullptr), MAKEINTRESOURCE(_resourceName), ToWideString(_resourceType).c_str()); // 第三个参数我怎么也没想到是图片后缀名
		DWORD dwLastError = GetLastError();
		if (!resource) return;

		DWORD resourceSize = SizeofResource(GetModuleHandle(nullptr), resource);
		if (!resourceSize) return;

		HGLOBAL global = LoadResource(GetModuleHandle(nullptr), resource);
		if (!global) return;

		LPVOID pResourceData = LockResource(global);
		if (!pResourceData) return;

		IWICStream* pStream;
		hr = s_pFactory->CreateStream(&pStream);
		if (FAILED(hr)) return;

		hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pResourceData), resourceSize);
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
		P_SAFERELEASE(_pConverter);
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
		.0f,
		WICBitmapPaletteTypeCustom
	);
	P_SAFERELEASE(pSource);
	if (FAILED(hr))
	{
		P_SAFERELEASE(_pConverter);
		return;
	}

	_SetTransfrom();
	_ResetSize();
}
