#include "PNode.hpp"

Pixel::Line::Line() :
	Line(.0f, .0f, .0f, .0f)
{
}

Pixel::Line::Line(float vertex1X, float vertex1Y, float vertex2X, float vertex2Y) :
	Line(Point(vertex1X, vertex1Y), Point(vertex2X, vertex2Y))
{
}

Pixel::Line::Line(Point vertex1, Point vertex2) :
	Graphic(GetCenter({vertex1, vertex2}).x, GetCenter({ vertex1, vertex2 }).y),
	_vertex1(vertex1 - GetPosition()),
	_vertex2(vertex2 - GetPosition())
{
}

void Pixel::Line::Render(Renderer* renderer)
{
	renderer->DrawLine(_vertex1, _vertex2, GetAttr());
}

Pixel::Point Pixel::Line::GetVertex1() const
{
	return _vertex1;
}

float Pixel::Line::GetVertex1X() const
{
	return GetVertex1().x;
}

float Pixel::Line::GetVertex1Y() const
{
	return GetVertex1().y;
}

Pixel::Point Pixel::Line::GetVertex2() const
{
	return _vertex2;
}

float Pixel::Line::GetVertex2X() const
{
	return GetVertex2().x;
}

float Pixel::Line::GetVertex2Y() const
{
	return GetVertex2().y;
}

void Pixel::Line::SetVertex1(Point position)
{
	_vertex1 = position;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Line::SetVertex1(float x, float y)
{
	SetVertex1(Point(x, y));
}

void Pixel::Line::SetVertex1X(float x)
{
	SetVertex1(x, GetVertex1Y());
}

void Pixel::Line::SetVertex1Y(float y)
{
	SetVertex1(GetVertex1X(), y);
}

void Pixel::Line::SetVertex2(Point position)
{
	_vertex2 = position;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Line::SetVertex2(float x, float y)
{
	SetVertex2(Point(x, y));
}

void Pixel::Line::SetVertex2X(float x)
{
	SetVertex2(x, GetVertex2Y());
}

void Pixel::Line::SetVertex2Y(float y)
{
	SetVertex2(GetVertex2X(), y);
}

void Pixel::Line::_ResetSize()
{
	Size size(
		_vertex1,
		_vertex2
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[1] = GetTransform().TransformPoint(points[1]);
	points[2] = GetTransform().TransformPoint(points[2]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		points[0],
		points[3]
	);

	_SetSize(size);
}
