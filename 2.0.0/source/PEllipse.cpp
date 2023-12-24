#include "PNode.h"

Pixel::Ellipse::Ellipse(int x, int y, int radiusX, int radiusY) :
	Graphic(x, y),
	radiusX(radiusX),
	radiusY(radiusY)
{
	originalSize(Point(x - radiusX / 2, y - radiusY / 2), Point(x + radiusX / 2, y + radiusY / 2));
	SetTransform();
	SetCollisionBox(size);
}

Pixel::Ellipse::Ellipse(int radiusX, int radiusY) :
	Ellipse(0, 0, radiusX, radiusY)
{
}

int Pixel::Ellipse::GetRadiusX() const
{
	return radiusX;
}

int Pixel::Ellipse::GetRadiusY() const
{
	return radiusY;
}

void Pixel::Ellipse::SetPosition(Point position)
{
	this->position(position);
	originalSize(Point(position.x - radiusX / 2, position.y - radiusY / 2), Point(position.x + radiusX / 2, position.y + radiusY / 2));
	SetCollisionBox(originalSize);
}

void Pixel::Ellipse::SetPosition(int x, int y)
{
	SetPosition(Point(x, y));
}

void Pixel::Ellipse::SetPositionX(int x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Ellipse::SetPositionY(int y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Ellipse::SetRadiusX(int radiusX)
{
	this->radiusX = radiusX;
	originalSize(Point(position.x - radiusX / 2, position.y - radiusY / 2), Point(position.x + radiusX / 2, position.y + radiusY / 2));
	SetCollisionBox(Point(position.x - radiusX, position.y - radiusY), Point(position.x + radiusX, position.y - radiusY));
}

void Pixel::Ellipse::SetRadiusY(int radiusY)
{
	this->radiusY = radiusY;
	originalSize(Point(position.x - radiusX / 2, position.y - radiusY / 2), Point(position.x + radiusX / 2, position.y + radiusY / 2));
	SetCollisionBox(Point(position.x - radiusX, position.y - radiusY), Point(position.x + radiusX, position.y - radiusY));
}

void Pixel::Ellipse::RenderSelf(Renderer* renderer)
{
	renderer->RenderEllipse(position, offset, transform, radiusX, radiusY, color, fill, strokeWidth);
}
