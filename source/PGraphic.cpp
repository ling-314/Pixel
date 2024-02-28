#include "PNode.hpp"

Pixel::Graphic::Graphic() :
	Graphic(.0f, .0f)
{
}

Pixel::Graphic::Graphic(float x, float y) :
	Node(x, y),
	_attr{ Color::White, false, 1.0f }
{
}

Pixel::GraphicAttribute Pixel::Graphic::GetAttr() const
{
	return _attr;
}

void Pixel::Graphic::SetAttr(GraphicAttribute attr)
{
	_attr = attr;
}
