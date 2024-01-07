#include "PNode.h"
#include <math.h>

Pixel::Line::Line() :
	_vertex1(0, 0),
	_vertex2(0, 0)
{
}

Pixel::Line::Line(float vertex1x, float vertex1y, float vertex2x, float vertex2y) :
	Graphic((vertex1x + vertex2x) / 2, (vertex1y + vertex2y) / 2),
	_vertex1(vertex1x, vertex1y),
	_vertex2(vertex2x, vertex2y)
{
	_originalSize(_vertex1, _vertex2);
	_SetTransform();
}

Pixel::Line::Line(Point vertex1, Point vertex2) :
	Line(vertex1.x, vertex1.y, vertex2.x, vertex2.y)
{
}

Pixel::Point Pixel::Line::GetVertex1() const
{
	return _vertex1;
}

Pixel::Point Pixel::Line::GetVertex2() const
{
	return _vertex2;
}

float Pixel::Line::GetVertex1X() const
{
	return _vertex1.x;
}

float Pixel::Line::GetVertex1Y() const
{
	return _vertex1.y;
}

float Pixel::Line::GetVertex2X() const
{
	return _vertex2.x;
}

float Pixel::Line::GetVertex2Y() const
{
	return _vertex2.y;
}

void Pixel::Line::SetVertex1(Point point)
{
	_vertex1 = point;
}

void Pixel::Line::SetVertex2(Point point)
{
	_vertex2 = point;
}

void Pixel::Line::SetVertex1X(float x)
{
	_vertex1.x = x;
}

void Pixel::Line::SetVertex1Y(float y)
{
	_vertex1.x = y;
}

void Pixel::Line::SetVertex2X(float x)
{
	_vertex2.x = x;
}

void Pixel::Line::SetVertex2Y(float y)
{
	_vertex2.x = y;
}

void Pixel::Line::SetPosition(Point position)
{
	this->_position = position;
	_vertex1.x += position.x - _vertex1.x;
	_vertex1.y += position.y - _vertex1.y;
	_vertex2.x += position.x - _vertex2.x;
	_vertex2.y += position.y - _vertex2.y;
	_originalSize(_vertex1, _vertex2);
}

void Pixel::Line::SetPosition(float x, float y)
{
	SetPosition(Point(x, y));
}

void Pixel::Line::SetPositionX(float x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Line::SetPositionY(float y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Line::Render(Renderer* renderer)
{
	renderer->RenderLine(_vertex1, _vertex2, _offset, _transform, _color, _strokeWidth);
}
