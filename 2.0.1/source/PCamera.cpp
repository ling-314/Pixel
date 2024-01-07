#include "PCamera.h"

Pixel::Camera::Camera() :
	_offset(0, 0)
{
}

Pixel::Vector2 Pixel::Camera::GetOffset() const
{
	return _offset;
}

float Pixel::Camera::GetOffsetX() const
{
	return GetOffset().x;
}

float Pixel::Camera::GetOffsetY() const
{
	return GetOffset().y;
}

void Pixel::Camera::SetOffset(Vector2 offset)
{
	this->_offset = offset;
}

void Pixel::Camera::SetOffset(float x, float y)
{
	SetOffset(Point(x, y));
}

void Pixel::Camera::SetOffsetX(float x)
{
	SetOffset(x, GetOffsetY());
}

void Pixel::Camera::SetOffsetY(float y)
{
	SetOffset(GetOffsetX(), y);
}
