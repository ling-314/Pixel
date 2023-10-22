#include "PType.h"

Pixel::Point::Point(int x, int y) :
	x(x),
	y(y)
{
}

void Pixel::Point::operator()(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Pixel::Point::operator()(Point point)
{
	x = point.x;
	y = point.y;
}

void Pixel::Point::operator=(Point point)
{
	x = point.x;
	y = point.y;
}

Pixel::Color::Color(int r, int g, int b) :
	r(r),
	g(g),
	b(b)
{
}

Pixel::Color::Color(int r, int g, int b, int a) :
	r(r),
	g(g),
	b(b),
	a(a)
{
}

Pixel::Color::Color(int hex) :
	Color(hex, 255)
{
}

Pixel::Color::Color(int hex, int a) :
	r((hex & 0xff0000) >> 16),
	g((hex & 0x00ff00) >> 8),
	b((hex & 0x0000ff) >> 0),
	a(a)
{
}

void Pixel::Color::operator()(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Pixel::Color::operator()(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Pixel::Color::operator=(Color color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

Pixel::Size::Size(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY) :
	leftTop(leftTopX, leftTopY),
	rightBottom(rightBottomX, rightBottomY)
{
}

Pixel::Size::Size(Point leftTop, Point rightBottom) :
	leftTop(leftTop),
	rightBottom(rightBottom)
{
}

void Pixel::Size::operator()(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY)
{
	leftTop(leftTopX, leftTopY);
	rightBottom(rightBottomX, rightBottomY);
}

void Pixel::Size::operator()(Point leftTop, Point rightBottom)
{
	this->leftTop(leftTop);
	this->rightBottom(rightBottom);
}

void Pixel::Size::operator=(Size size)
{
	leftTop = size.leftTop;
	rightBottom = size.rightBottom;
}
