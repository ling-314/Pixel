#include "PNode.h"

Pixel::Rectangle::Rectangle(int x, int y, int width, int height) :
	Graphic(x, y),
	width(width),
	height(height)
{
	size(Point(x - width / 2, y - height / 2), Point(x + width / 2, y + height / 2));
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
	size(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y + height / 2));
	SetCollisionBox(size);
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
	size(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y - height / 2));
	SetCollisionBox(size);
}

void Pixel::Rectangle::SetHeight(int height)
{
	this->height = height;
	size(Point(position.x - width / 2, position.y - height / 2), Point(position.x + width / 2, position.y - height / 2));
	SetCollisionBox(size);
}

void Pixel::Rectangle::Render(Renderer* renderer)
{
	renderer->RenderRectangle(position, scale, width, height, color, fill);
	for (auto node : children)
	{
		node->Render(renderer);
	}
}
