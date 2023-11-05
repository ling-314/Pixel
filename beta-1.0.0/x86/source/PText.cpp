#include "PNode.h"

Pixel::Text::Text(int x, int y, std::wstring text) :
	Node(x, y),
	text(text),
	fontName(L"·ÂËÎ"),
	fontSize(16),
	color(0, 0, 0)
{
	Create();
}

Pixel::Text::~Text()
{
	SafeRelease(pTextLayout);
}

std::wstring Pixel::Text::GetText() const
{
	return text;
}

std::wstring Pixel::Text::GetFontName() const
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

void Pixel::Text::SetText(std::wstring text)
{
	this->text = text;
	Create();
}

void Pixel::Text::SetFontName(std::wstring fontName)
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
		fontName.c_str(),
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
		return;
	}

	hr = pFactory->CreateTextLayout(
		text.c_str(),
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
		return;
	}

	DWRITE_TEXT_METRICS metrics;
	pTextLayout->GetMetrics(&metrics);
	SafeRelease(pTextLayout);
	hr = pFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		pTextFormat,
		metrics.height / 2,
		metrics.width,
		&pTextLayout
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pTextFormat);
		return;
	}

	pTextLayout->GetMetrics(&metrics);
	size(Point(position.x - metrics.width / 2, position.y - metrics.height / 2), Point(position.x + metrics.width / 2, position.y + metrics.height / 2));
	SetCollisionBox(size);
}

void Pixel::Text::Render(Renderer* renderer)
{
	renderer->RenderText(position, color, pTextLayout);
	for (auto node : children)
	{
		node->Render(renderer);
	}
}
