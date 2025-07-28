#include "PNode.hpp"

Pixel::EllipseBase::EllipseBase() :
	Graphic(),
	_radiusX(0.0f),
	_radiusY(0.0f)
{
}

Pixel::EllipseBase::EllipseBase(float x, float y) :
	Graphic(x, y),
	_radiusX(0.0f),
	_radiusY(0.0f)
{
}

Pixel::EllipseBase::EllipseBase(float radius) :
	Graphic(),
	_radiusX(radius),
	_radiusY(radius)
{
}

Pixel::EllipseBase::EllipseBase(float x, float y, float radius) :
	EllipseBase(radius)
{
	SetPosition(x, y);
}

float Pixel::EllipseBase::GetRadiusX() const
{
	return _radiusX;
}

float Pixel::EllipseBase::GetRadiusY() const
{
	return _radiusY;
}

void Pixel::EllipseBase::SetRadius(float radius)
{
	_radiusX = radius;
	_radiusY = radius;
	_ResetSize();
}

void Pixel::EllipseBase::_ResetSize()
{
	Size size(
		_radiusX / -2,
		_radiusY / -2,
		_radiusX,
		_radiusY
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		points[0],
		points[3]
	);

	_SetSize(size);
}

Pixel::Ellipse::Ellipse() :
	EllipseBase()
{
}

Pixel::Ellipse::Ellipse(float radiusX, float radiusY) :
	EllipseBase()
{
	_radiusX = radiusX;
	_radiusY = radiusY;
	_ResetSize();
}

Pixel::Ellipse::Ellipse(float x, float y, float radiusX, float radiusY) :
	EllipseBase(x, y)
{
	_radiusX = radiusX;
	_radiusY = radiusY;
	_ResetSize();
}

void Pixel::Ellipse::RenderSelf(Renderer* renderer)
{
	renderer->DrawEllipse(
		_radiusX,
		_radiusY,
		GetAttr()
	);
}

void Pixel::Ellipse::SetRadiusX(float radiusX)
{
	_radiusX = radiusX;
	_ResetSize();
}

void Pixel::Ellipse::SetRadiusY(float radiusY)
{
	_radiusY = radiusY;
	_ResetSize();
}

Pixel::Circle::Circle() :
	EllipseBase()
{
}

Pixel::Circle::Circle(float radius) :
	EllipseBase(radius)
{
}

Pixel::Circle::Circle(float x, float y, float radius) :
	EllipseBase(x, y, radius)
{
}

void Pixel::Circle::RenderSelf(Renderer* renderer)
{
	renderer->DrawEllipse(
		_radiusX,
		_radiusY,
		GetAttr()
	);
}

float Pixel::Circle::GetRadius() const
{
	return _radiusX;
}
