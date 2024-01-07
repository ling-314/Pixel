#include "PNode.h"

Pixel::Graphic::Graphic() :
	Node(),
	_color(0, 0, 0)
{
}

Pixel::Graphic::Graphic(int x, int y) :
	Node(x, y),
	_color(0, 0, 0)
{
}

Pixel::Color Pixel::Graphic::GetColor() const
{
	return _color;
}

bool Pixel::Graphic::IsFill() const
{
	return _fill;
}

float Pixel::Graphic::GetStrokeWidth() const
{
	return _strokeWidth;
}

void Pixel::Graphic::SetColor(Color color)
{
	this->_color = color;
}

void Pixel::Graphic::SetColor(int r, int g, int b)
{
	_color(r, g, b);
}

void Pixel::Graphic::SetColor(int r, int g, int b, int a)
{
	_color(r, g, b, a);
}

void Pixel::Graphic::SetFill(bool fill)
{
	this->_fill = fill;
}

void Pixel::Graphic::SetStrokeWidth(float strokeWidth)
{
	this->_strokeWidth = strokeWidth;
}
