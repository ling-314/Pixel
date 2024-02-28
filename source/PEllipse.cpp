#include "PNode.hpp"

Pixel::Ellipse::Ellipse() :
	Ellipse(.0f, .0f, .0f, .0f)
{
}

Pixel::Ellipse::Ellipse(float x, float y, float radiusX, float radiusY) :
	Graphic(x, y),
	_radiusX(radiusX),
	_radiusY(radiusY)
{
}

void Pixel::Ellipse::Render(Renderer* renderer)
{
	renderer->DrawEllipse(_radiusX, _radiusY, GetAttr());
}

float Pixel::Ellipse::GetRadiusX() const
{
	return _radiusX;
}

float Pixel::Ellipse::GetRadiusY() const
{
	return _radiusY;
}

void Pixel::Ellipse::SetRadiusX(float radiusX)
{
	_radiusX = radiusX;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Ellipse::SetRadiusY(float radiusY)
{
	_radiusY = radiusY;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Ellipse::_ResetSize()
{
	// TODO
	Size size(
		-_radiusX + GetRenderPositionX(),
		-_radiusY + GetRenderPositionY(),
		_radiusX * 2 + GetRenderPositionX(),
		_radiusY * 2 + GetRenderPositionY()
	);
	_SetSize(size);
}
