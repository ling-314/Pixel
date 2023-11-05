#include "PNode.h"
#include <math.h>

Pixel::Line::Line(int vertex1x, int vertex1y, int vertex2x, int vertex2y) :
	Graphic((vertex1x + vertex2x) / 2, (vertex1y + vertex2y) / 2),
	vertex1(vertex1x, vertex1y),
	vertex2(vertex2x, vertex2y)
{
	size(vertex1, vertex2);
	SetCollisionBox(size);
}

Pixel::Point Pixel::Line::GetVertex1() const
{
	return vertex1;
}

Pixel::Point Pixel::Line::GetVertex2() const
{
	return vertex2;
}

int Pixel::Line::GetVertex1X() const
{
	return vertex1.x;
}

int Pixel::Line::GetVertex1Y() const
{
	return vertex1.y;
}

int Pixel::Line::GetVertex2X() const
{
	return vertex2.x;
}

int Pixel::Line::GetVertex2Y() const
{
	return vertex2.y;
}

void Pixel::Line::SetVertex1(Point point)
{
	vertex1 = point;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetVertex2(Point point)
{
	vertex2 = point;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetVertex1X(int x)
{
	vertex1.x = x;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetVertex1Y(int y)
{
	vertex1.x = y;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetVertex2X(int x)
{
	vertex2.x = x;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetVertex2Y(int y)
{
	vertex2.x = y;
	SetCollisionBox(vertex1, vertex2);
}

void Pixel::Line::SetPosition(Point position)
{
	this->position = position;
	vertex1.x += position.x - vertex1.x;
	vertex1.y += position.y - vertex1.y;
	vertex2.x += position.x - vertex2.x;
	vertex2.y += position.y - vertex2.y;
	size(vertex1, vertex2);
	SetCollisionBox(size);
}

void Pixel::Line::SetPosition(int x, int y)
{
	SetPosition(Point(x, y));
}

void Pixel::Line::SetPositionX(int x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Line::SetPositionY(int y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Line::Render(Renderer* renderer)
{
	renderer->RenderLine(vertex1, vertex2, scale, angle, color, strokeWidth);
	for (auto node : children)
	{
		node->Render(renderer);
	}
}
