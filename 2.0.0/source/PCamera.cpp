#include "PCamera.h"

Pixel::Camera::Camera() :
	offset(0, 0)
{
}

Pixel::Vector2 Pixel::Camera::GetOffset() const
{
	return offset;
}

int Pixel::Camera::GetOffsetX() const
{
	return GetOffset().x;
}

int Pixel::Camera::GetOffsetY() const
{
	return GetOffset().y;
}

void Pixel::Camera::SetOffset(Vector2 offset)
{
	this->offset = offset;
}

void Pixel::Camera::SetOffset(int x, int y)
{
	SetOffset(Point(x, y));
}

void Pixel::Camera::SetOffsetX(int x)
{
	SetOffset(x, GetOffsetY());
}

void Pixel::Camera::SetOffsetY(int y)
{
	SetOffset(GetOffsetX(), y);
}
