#include "PNode.hpp"

Pixel::PolygonBase::PolygonBase() :
	Graphic()
{
}

Pixel::Rectangle::Rectangle() :
	PolygonBase(),
	_width(0.0f),
	_height(0.0f)
{
}

Pixel::Rectangle::Rectangle(float x, float y, float width, float height) :
	PolygonBase(),
	_width(width),
	_height(height)
{
}

void Pixel::Rectangle::RenderSelf(Renderer* renderer)
{
	// TODO
}

float Pixel::Rectangle::GetWidth() const
{
	return _width;
}

float Pixel::Rectangle::GetHeight() const
{
	return _height;
}
