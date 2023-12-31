#include "PNode.h"

Pixel::Text::Text(int x, int y, std::string text) :
	Node(x, y),
	text(text),
	fontName("����"),
	fontSize(16),
	color(0, 0, 0)
{
	Create();
}

Pixel::Text::Text(std::string text) :
	Text(0, 0, text)
{
}

Pixel::Text::~Text()
{
	SafeRelease(pTextLayout);
}

std::string Pixel::Text::GetText() const
{
	return text;
}

std::string Pixel::Text::GetFontName() const
{
	return fontName;
}

int Pixel::Text::GetFontSize() const
{
	return fontSize;
}

Pixel::Color Pixel::Text::GetColor()
{
	return color;
}

void Pixel::Text::SetText(std::string text)
{
	this->text = text;
	Create();
}

void Pixel::Text::SetFontName(std::string fontName)
{
	this->fontName = fontName;
	Create();
}

void Pixel::Text::SetFontSize(int fontSize)
{
	this->fontSize = fontSize;
	Create();
}

void Pixel::Text::SetColor(Color color)
{
	this->color = color;
}

void Pixel::Text::Create()
{
	SafeRelease(pTextLayout);
	HRESULT hr;

	IDWriteFactory* pFactory = nullptr;

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pFactory),
		(IUnknown**)&pFactory
	);
	if (FAILED(hr)) return;

	IDWriteTextFormat* pTextFormat = nullptr;

	hr = pFactory->CreateTextFormat(
		ToWideString(fontName.c_str()).c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		(float)fontSize,
		L"",
		&pTextFormat
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		pTextLayout = nullptr;
		return;
	}

	hr = pFactory->CreateTextLayout(
		ToWideString(text.c_str()).c_str(),
		text.length(),
		pTextFormat,
		0,
		0,
		&pTextLayout
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pTextFormat);
		pTextLayout = nullptr;
		return;
	}

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);
	SafeRelease(pTextLayout);
	hr = pFactory->CreateTextLayout(
		ToWideString(text.c_str()).c_str(),
		text.length(),
		pTextFormat,
		metrics.height / 2,
		metrics.width,
		&pTextLayout
	);
	SafeRelease(pFactory);
	SafeRelease(pTextFormat);
	if (FAILED(hr))
	{
		pTextLayout = nullptr;
		return;
	}

	pTextLayout->GetMetrics(&metrics);
	originalSize(Point(position.x - metrics.width / 2, position.y - metrics.height / 2), Point(position.x + metrics.width / 2, position.y + metrics.height / 2));
	SetTransform();
	SetCollisionBox(size);
}

void Pixel::Text::RenderSelf(Renderer* renderer)
{
	if (!pTextLayout) return;
	renderer->RenderText(position, offset, transform, color, pTextLayout);
}
