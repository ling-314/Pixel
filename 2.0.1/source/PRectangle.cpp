#include "PNode.h"

Pixel::Rectangle::Rectangle() :
	Graphic(),
	_width(0),
	_height(0)
{
}

Pixel::Rectangle::Rectangle(float x, float y, float width, float height) :
	Graphic(x, y),
	_width(width),
	_height(height)
{
	_originalSize(Point(x - width / 2, y - height / 2), Point(x + width / 2, y + height / 2));
	_SetTransform();
}

Pixel::Rectangle::Rectangle(float width, float height) :
	Rectangle(0, 0, width, height)
{
}

float Pixel::Rectangle::GetWidth() const
{
	return _width;
}

float Pixel::Rectangle::GetHeight() const
{
	return _height;
}

void Pixel::Rectangle::SetPosition(Point position)
{
	this->_position(position);
	_originalSize(Point(position.x - _width / 2, position.y - _height / 2), Point(position.x + _width / 2, position.y + _height / 2));
}

void Pixel::Rectangle::SetPosition(float x, float y)
{
	SetPosition(Point(x, y));
}

void Pixel::Rectangle::SetPositionX(float x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Rectangle::SetPositionY(float y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Rectangle::SetWidth(float width)
{
	this->_width = width;
	_originalSize(Point(_position.x - width / 2, _position.y - _height / 2), Point(_position.x + width / 2, _position.y - _height / 2));
}

void Pixel::Rectangle::SetHeight(float height)
{
	this->_height = height;
	_originalSize(Point(_position.x - _width / 2, _position.y - height / 2), Point(_position.x + _width / 2, _position.y - height / 2));
}

void Pixel::Rectangle::Render(Renderer* renderer)
{
	renderer->RenderRectangle(_position, _offset, _transform, _width, _height, _color, _fill, _strokeWidth);
}
