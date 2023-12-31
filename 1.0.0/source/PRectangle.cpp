#include "PNode.h"

Pixel::Rectangle::Rectangle(int x, int y, int width, int height) :
	Graphic(x, y),
	width(width),
	height(height)
{
	originalSize(Point(x - width / 2, y - height / 2), Point(x + width / 2, y + height / 2));
	SetTransform();
	SetCollisionBox(size);
}

int Pixel::Rectangle::GetWidth() const
{
	return width;
}

int Pixel::Rectangle::GetHeight() const
{
	return height;
}

void Pixel::Rectangle::SetPosition(Point position)
{
	this->position(position);
	//this->position.x -= offset.x;
	//this->position.y -= offset.y;
	originalSize(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y + height / 2));
	SetCollisionBox(originalSize);
}

void Pixel::Rectangle::SetPosition(int x, int y)
{
	SetPosition(Point(x, y));
}

void Pixel::Rectangle::SetPositionX(int x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Rectangle::SetPositionY(int y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Rectangle::SetWidth(int width)
{
	this->width = width;
	originalSize(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y - height / 2));
	SetCollisionBox(originalSize);
}

void Pixel::Rectangle::SetHeight(int height)
{
	this->height = height;
	originalSize(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y - height / 2));
	SetCollisionBox(originalSize);
}

void Pixel::Rectangle::RenderSelf(Renderer* renderer)
{
	renderer->RenderRectangle(position, offset, transform, width, height, color, fill, strokeWidth);
}
