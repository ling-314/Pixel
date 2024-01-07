#include "PNode.h"

Pixel::Ellipse::Ellipse() :
	Graphic(),
	_radiusX(0),
	_radiusY(0)
{
}

Pixel::Ellipse::Ellipse(float x, float y, float radiusX, float radiusY) :
	Graphic(x, y),
	_radiusX(radiusX),
	_radiusY(radiusY)
{
	_originalSize(Point(x - radiusX / 2, y - radiusY / 2), Point(x + radiusX / 2, y + radiusY / 2));
	_SetTransform();
}

Pixel::Ellipse::Ellipse(float radiusX, float radiusY) :
	Ellipse(0, 0, radiusX, radiusY)
{
}

float Pixel::Ellipse::GetRadiusX() const
{
	return _radiusX;
}

float Pixel::Ellipse::GetRadiusY() const
{
	return _radiusY;
}

void Pixel::Ellipse::SetPosition(Point position)
{
	this->_position(position);
	_originalSize(Point(position.x - _radiusX / 2, position.y - _radiusY / 2), Point(position.x + _radiusX / 2, position.y + _radiusY / 2));
}

void Pixel::Ellipse::SetPosition(float x, float y)
{
	SetPosition(Point(x, y));
}

void Pixel::Ellipse::SetPositionX(float x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Ellipse::SetPositionY(float y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Ellipse::SetRadiusX(float radiusX)
{
	this->_radiusX = radiusX;
	_originalSize(Point(_position.x - radiusX / 2, _position.y - _radiusY / 2), Point(_position.x + radiusX / 2, _position.y + _radiusY / 2));
}

void Pixel::Ellipse::SetRadiusY(float radiusY)
{
	this->_radiusY = radiusY;
	_originalSize(Point(_position.x - _radiusX / 2, _position.y - radiusY / 2), Point(_position.x + _radiusX / 2, _position.y + radiusY / 2));
}

void Pixel::Ellipse::Render(Renderer* renderer)
{
	renderer->RenderEllipse(_position, _offset, _transform, _radiusX, _radiusY, _color, _fill, _strokeWidth);
}
