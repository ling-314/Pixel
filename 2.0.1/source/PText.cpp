#include "PNode.h"

Pixel::Text::Text() :
	Node(),
	_text(""),
	_fontName("·ÂËÎ"),
	_fontSize(16),
	_color(0, 0, 0)
{
}

Pixel::Text::Text(float x, float y, std::string text) :
	Node(x, y),
	_text(text),
	_fontName("·ÂËÎ"),
	_fontSize(16),
	_color(0, 0, 0)
{
	_Create();
}

Pixel::Text::Text(std::string text) :
	Text(0, 0, text)
{
}

Pixel::Text::~Text()
{
	SafeRelease(_pTextLayout);
}

std::string Pixel::Text::GetText() const
{
	return _text;
}

std::string Pixel::Text::GetFontName() const
{
	return _fontName;
}

float Pixel::Text::GetFontSize() const
{
	return _fontSize;
}

Pixel::Color Pixel::Text::GetColor()
{
	return _color;
}

void Pixel::Text::SetText(std::string text)
{
	this->_text = text;
	_Create();
}

void Pixel::Text::SetFontName(std::string fontName)
{
	this->_fontName = fontName;
	_Create();
}

void Pixel::Text::SetFontSize(float fontSize)
{
	this->_fontSize = fontSize;
	_Create();
}

void Pixel::Text::SetColor(Color color)
{
	this->_color = color;
}

void Pixel::Text::_Create()
{
	SafeRelease(_pTextLayout);
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
		ToWideString(_fontName.c_str()).c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		(float)_fontSize,
		L"",
		&pTextFormat
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		_pTextLayout = nullptr;
		return;
	}

	hr = pFactory->CreateTextLayout(
		ToWideString(_text.c_str()).c_str(),
		_text.length(),
		pTextFormat,
		0,
		0,
		&_pTextLayout
	);
	if (FAILED(hr))
	{
		SafeRelease(pFactory);
		SafeRelease(pTextFormat);
		_pTextLayout = nullptr;
		return;
	}

	DWRITE_TEXT_METRICS metrics;
	_pTextLayout->GetMetrics(&metrics);
	SafeRelease(_pTextLayout);
	hr = pFactory->CreateTextLayout(
		ToWideString(_text.c_str()).c_str(),
		_text.length(),
		pTextFormat,
		metrics.height / 2,
		metrics.width,
		&_pTextLayout
	);
	SafeRelease(pFactory);
	SafeRelease(pTextFormat);
	if (FAILED(hr))
	{
		_pTextLayout = nullptr;
		return;
	}

	_pTextLayout->GetMetrics(&metrics);
	_originalSize(Point(_position.x - metrics.width / 2, _position.y - metrics.height / 2), Point(_position.x + metrics.width / 2, _position.y + metrics.height / 2));
	_SetTransform();
}

void Pixel::Text::Render(Renderer* renderer)
{
	if (!_pTextLayout) return;
	renderer->RenderText(_position, _offset, _transform, _color, _pTextLayout);
}
