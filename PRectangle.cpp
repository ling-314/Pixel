#include "PNode.hpp"

Pixel::Rectangle::Rectangle() :
	Rectangle(.0f, .0f, .0f, .0f, .0f, .0f)
{
}

Pixel::Rectangle::Rectangle(float x, float y, float width, float height) :
	Rectangle(x, y, width, height, .0f, .0f)
{
}

Pixel::Rectangle::Rectangle(float x, float y, float width, float height, float radiusX, float radiusY) :
	Graphic(x, y),
	_width(width),
	_height(height),
	_radiusX(radiusX),
	_radiusY(radiusY)
{
}

Pixel::Rectangle::Rectangle(Size size) :
	Rectangle((size.left + size.left + size.width) / 2, (size.top + size.top + size.height) / 2, size.width, size.height)
{
}

void Pixel::Rectangle::Render(Renderer* renderer)
{
	renderer->DrawRectangle(_width, _height, _radiusX, _radiusY, GetAttr());
}

float Pixel::Rectangle::GetWidth() const
{
	return _width;
}

float Pixel::Rectangle::GetHeight() const
{
	return _height;
}

float Pixel::Rectangle::GetRadiusX() const
{
	return _radiusX;
}

float Pixel::Rectangle::GetRadiusY() const
{
	return _radiusY;
}

void Pixel::Rectangle::SetWidth(float width)
{
	_width = width;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Rectangle::SetHeight(float height)
{
	_height = height;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Rectangle::SetRadiusX(float radiusX)
{
	_radiusX = radiusX;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Rectangle::SetRadiusY(float radiusY)
{
	_radiusY = radiusY;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Rectangle::_ResetSize()
{
	Size size(
		-_width / 2,
		-_height / 2,
		_width,
		_height
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[1] = GetTransform().TransformPoint(points[1]);
	points[2] = GetTransform().TransformPoint(points[2]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		GetLeftTop({ points[0], points[1], points[2], points[3] }),		// ¹ÖÂé·³µÄ
		GetRightBottom({ points[0], points[1], points[2], points[3] })
	);

	_SetSize(size);
}
