#include "PCamera.hpp"

Pixel::Camera::Camera() :
	Camera(.0f, .0f)
{
}

Pixel::Camera::Camera(float x, float y) :
	_offset(x, y)
{
}

Pixel::Camera::Camera(Vector2 offset) :
	_offset(offset)
{
}

Pixel::Vector2 Pixel::Camera::GetOffset() const
{
	return _offset;
}

float Pixel::Camera::GetOffsetX() const
{
	return _offset.x;
}

float Pixel::Camera::GetOffsetY() const
{
	return _offset.y;
}

void Pixel::Camera::SetOffset(Vector2 offset)
{
	_offset = offset;
}

void Pixel::Camera::SetOffsetX(float x)
{
	_offset.x = x;
}

void Pixel::Camera::SetOffsetY(float y)
{
	_offset.y = y;
}
