#include "PNode.hpp"

Pixel::Graphic::Graphic() :
	Graphic(.0f, .0f)
{
}

Pixel::Graphic::Graphic(float x, float y) :
	Node(x, y),
	_attr{ Color::White, false, 1.0f }
{
	_ResetSize();
}

Pixel::GraphicAttribute Pixel::Graphic::GetAttr() const
{
	return _attr;
}

Pixel::Color Pixel::Graphic::GetColor() const
{
	return GetAttr().color;
}

bool Pixel::Graphic::IsFill() const
{
	return GetAttr().fill;
}

float Pixel::Graphic::GetStrokeWidth() const
{
	return GetAttr().strokeWidth;
}

void Pixel::Graphic::SetAttr(GraphicAttribute attr)
{
	_attr = attr;
}

void Pixel::Graphic::SetColor(Color color)
{
	SetAttr({ color, IsFill(), GetStrokeWidth() });
}

void Pixel::Graphic::SetFill(bool fill)
{
	SetAttr({ GetColor(), fill, GetStrokeWidth()});
}

void Pixel::Graphic::SetStrokeWidth(float strokeWidth)
{
	SetAttr({ GetColor(), IsFill(), strokeWidth});
}
