#include "PNode.h"

Pixel::Graphic::Graphic(int x, int y) :
	Node(x, y),
	color(0, 0, 0)
{
}

Pixel::Color Pixel::Graphic::GetColor() const
{
	return color;
}

bool Pixel::Graphic::IsFill() const
{
	return fill;
}

void Pixel::Graphic::SetColor(Color color)
{
	this->color = color;
}

void Pixel::Graphic::SetColor(int r, int g, int b)
{
	color(r, g, b);
}

void Pixel::Graphic::SetColor(int r, int g, int b, int a)
{
	color(r, g, b, a);
}

void Pixel::Graphic::SetFill(bool fill)
{
	this->fill = fill;
}
