#include "PNode.hpp"

IDWriteFactory* Pixel::Text::s_pFactory = nullptr;

Pixel::Text::Text() :
	Text(.0f, .0f, "")
{
}

Pixel::Text::Text(float x, float y) :
	Text(x, y, "")
{
}

Pixel::Text::Text(std::string text) :
	Text(.0f, .0f, text)
{
}

Pixel::Text::Text(float x, float y, std::string text, std::string fontName, float fontSize) :
	Node(x, y),
	_text(text),
	_fontName(fontName),
	_fontSize(fontSize),
	_color(0xffffff),
	_weight(DWRITE_FONT_WEIGHT_NORMAL),
	_style(DWRITE_FONT_STYLE_NORMAL),
	_pTextLayout(nullptr)
{
	_Create();
}

Pixel::Text::~Text()
{
	P_SAFERELEASE(_pTextLayout);
}

void Pixel::Text::Render(Renderer* renderer)
{
	if (_pTextLayout) renderer->DrawText(_pTextLayout, _color);
}

void Pixel::Text::Destroy()
{
	P_SAFERELEASE(s_pFactory);
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

Pixel::Color Pixel::Text::GetColor() const
{
	return _color;
}

DWRITE_FONT_WEIGHT Pixel::Text::GetWeight() const
{
	return _weight;
}

DWRITE_FONT_STYLE Pixel::Text::GetStyle() const
{
	return _style;
}

IDWriteTextLayout* Pixel::Text::GetIDWriteTextLayout()
{
	return _pTextLayout;
}

void Pixel::Text::SetText(std::string text)
{
	_text = text;
	_Create();
}

void Pixel::Text::SetFontName(std::string fontName)
{
	_fontName = fontName;
	_Create();
}

void Pixel::Text::SetFontSize(float fontSize)
{
	_fontSize = fontSize;
	_Create();
}

void Pixel::Text::SetColor(Color color)
{
	_color = color;
	_Create();
}

void Pixel::Text::SetWeight(DWRITE_FONT_WEIGHT weight)
{
	_weight = weight;
	_Create();
}

void Pixel::Text::SetStyle(DWRITE_FONT_STYLE style)
{
	_style = style;
	_Create();
}

void Pixel::Text::_ResetSize()
{
	DWRITE_TEXT_METRICS textMetrics;
	_pTextLayout->GetMetrics(&textMetrics);

	Size size(
		textMetrics.width / -2,
		textMetrics.height / -2,
		textMetrics.width,
		textMetrics.height
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[1] = GetTransform().TransformPoint(points[1]);
	points[2] = GetTransform().TransformPoint(points[2]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		GetLeftTop({ points[0], points[1], points[2], points[3] }),		// ¹ÖÂé·³µÄ
		GetRightBottom({ points[0], points[1], points[2], points[3] })
	);

	_SetSize(size);
}

void Pixel::Text::_Create()
{
	HRESULT hr;

	if (!s_pFactory)
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			(IUnknown**)&s_pFactory
		);
		if (FAILED(hr)) return;
	}

	IDWriteTextFormat* pTextFormat;
	hr = s_pFactory->CreateTextFormat(
		ToWideString(_text).c_str(),
		nullptr,
		_weight,
		_style,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontSize,
		L"",
		&pTextFormat
	);
	if (FAILED(hr)) return;

	hr = s_pFactory->CreateTextLayout(
		ToWideString(_text).c_str(),
		ToWideString(_text).length(),
		pTextFormat,
		.0f,
		.0f,
		&_pTextLayout
	);
	if (FAILED(hr))
	{
		P_SAFERELEASE(pTextFormat);
		return;
	}

	DWRITE_TEXT_METRICS textMetrics;
	hr = _pTextLayout->GetMetrics(&textMetrics);
	P_SAFERELEASE(_pTextLayout);
	if (FAILED(hr)) return;

	hr = s_pFactory->CreateTextLayout(
		ToWideString(_text).c_str(),
		ToWideString(_text).length(),
		pTextFormat,
		textMetrics.height,
		textMetrics.width,
		&_pTextLayout
	);
	P_SAFERELEASE(pTextFormat);
	if (FAILED(hr))
	{
		P_SAFERELEASE(_pTextLayout);
		return;
	}

	_SetTransfrom();
	_ResetSize();
}
