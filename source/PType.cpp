#include "PType.hpp"

Pixel::Point::Point() :
	Point(0, 0)
{
}

Pixel::Point::Point(float x, float y) :
	x(x),
	y(y)
{
}

Pixel::Point::Point(POINT point) :
	x((float)point.x),
	y((float)point.y)
{
}

Pixel::Point::Point(D2D1_POINT_2F point) :
	x(point.x),
	y(point.y)
{
}

Pixel::Point::Point(D2D1_SIZE_F point)
{
	x = point.width;
	y = point.height;
}

void Pixel::Point::operator=(Point point)
{
	x = point.x;
	y = point.y;
}

Pixel::Point Pixel::Point::operator+(Point point)
{
	return Point(x + point.x, y + point.y);
}

Pixel::Point Pixel::Point::operator+(float x_y)
{
	return Point(x + x_y, y + x_y);
}

Pixel::Point Pixel::Point::operator+(Point point) const
{
	return Point(x + point.x, y + point.y);
}

Pixel::Point Pixel::Point::operator+(float x_y) const
{
	return Point(x + x_y, y + x_y);
}

void Pixel::Point::operator+=(Point point)
{
	x += point.x;
	y += point.y;
}

void Pixel::Point::operator+=(float x_y)
{
	x += x_y;
	y += x_y;
}

Pixel::Point Pixel::Point::operator-(Point point)
{
	return Point(x - point.x, y - point.y);
}

Pixel::Point Pixel::Point::operator-(float x_y)
{
	return Point(x - x_y, y - x_y);
}

Pixel::Point Pixel::Point::operator-(Point point) const
{
	return Point(x - point.x, y - point.y);
}

Pixel::Point Pixel::Point::operator-(float x_y) const
{
	return Point(x - x_y, y - x_y);
}

void Pixel::Point::operator-=(Point point)
{
	x -= point.x;
	y -= point.y;
}

void Pixel::Point::operator-=(float x_y)
{
	x -= x_y;
	y -= x_y;
}

Pixel::Point Pixel::Point::operator*(Point point)
{
	return Point(x * point.x, y * point.y);
}

Pixel::Point Pixel::Point::operator*(float x_y)
{
	return Point(x * x_y, y * x_y);
}

Pixel::Point Pixel::Point::operator*(Point point) const
{
	return Point(x * point.x, y * point.y);
}

Pixel::Point Pixel::Point::operator*(float x_y) const
{
	return Point(x * x_y, y * x_y);
}

void Pixel::Point::operator*=(Point point)
{
	x *= point.x;
	y *= point.y;
}

void Pixel::Point::operator*=(float x_y)
{
	x *= x_y;
	y *= x_y;
}

Pixel::Point Pixel::Point::operator/(Point point)
{
	return Point(x / point.x, y / point.y);
}

Pixel::Point Pixel::Point::operator/(float x_y)
{
	return Point(x / x_y, y / x_y);
}

Pixel::Point Pixel::Point::operator/(Point point) const
{
	return Point(x / point.x, y / point.y);
}

Pixel::Point Pixel::Point::operator/(float x_y) const
{
	return Point(x / x_y, y / x_y);
}

void Pixel::Point::operator/=(Point point)
{
	x /= point.x;
	y /= point.y;
}

void Pixel::Point::operator/=(float x_y)
{
	x /= x_y;
	y /= x_y;
}

Pixel::Point Pixel::Point::operator-()
{
	return Point(-x, -y);
}

Pixel::Point Pixel::Point::operator-() const
{
	return Point(-x, -y);
}

bool Pixel::Point::operator==(Point point)
{
	return x == point.x && y == point.y;
}

bool Pixel::Point::operator==(Point point) const
{
	return x == point.x && y == point.y;
}

bool Pixel::Point::operator!=(Point point)
{
	return x != point.x && y != point.y;
}

bool Pixel::Point::operator!=(Point point) const
{
	return x != point.x && y != point.y;
}

Pixel::Point::operator POINT() const
{
	return POINT{ (LONG)x, (LONG)y };
}

Pixel::Point::operator D2D1_POINT_2F() const
{
	return D2D1_POINT_2F{ x, y };
}

Pixel::Point::operator D2D1_SIZE_F() const
{
	return D2D1_SIZE_F{ x, y };
}

Pixel::Color::Color() :
	r(0),
	g(0),
	b(0),
	a(255)
{
}

Pixel::Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) :
	r(r),
	g(g),
	b(b),
	a(a)
{
}

Pixel::Color::Color(unsigned int rgb, unsigned int a) :
	r((rgb & 0xff0000) >> 16),
	g((rgb & 0xff00) >> 8),
	b(rgb & 0xff),
	a(a)
{
}

Pixel::Color::Color(D2D1_COLOR_F color) :
	r((unsigned int)color.r * 255),
	g((unsigned int)color.g * 255),
	b((unsigned int)color.b * 255),
	a((unsigned int)color.a * 255)
{
}

void Pixel::Color::operator=(Color color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

bool Pixel::Color::operator==(Color color)
{
	return r == color.r && g == color.g && b == color.b && a == color.a;
}

Pixel::Color::operator D2D1_COLOR_F() const
{
	return D2D1::ColorF((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
}

Pixel::Size::Size() :
	left(0),
	top(0),
	width(0),
	height(0)
{
}

Pixel::Size::Size(float left, float top, float width, float height) :
	left(left),
	top(top),
	width(width),
	height(height)
{
}

Pixel::Size::Size(Point leftTop, Point rightBottom) :
	left(leftTop.x),
	top(leftTop.y),
	width(rightBottom.x - leftTop.x),
	height(rightBottom.y - leftTop.y)
{
}

Pixel::Size::Size(RECT size) :
	left((float)size.left),
	top((float)size.top),
	width((float)size.right - (float)size.left),
	height((float)size.bottom - (float)size.top)
{
}

Pixel::Size::Size(SIZE size) :
	left(.0f),
	top(.0f),
	width((float)size.cx),
	height((float)size.cy)
{
}

Pixel::Size::Size(D2D1_SIZE_F size) :
	left(0),
	top(0),
	width(size.width),
	height(size.height)
{
}

Pixel::Size::Size(D2D1_RECT_F size) :
	left(size.left),
	top(size.top),
	width(size.right - size.left),
	height(size.bottom - size.top)
{
}

void Pixel::Size::operator=(Size size)
{
	left = size.left;
	top = size.top;
	width = size.width;
	height = size.height;
}

bool Pixel::Size::operator==(Size size)
{
	return left == size.left && top == size.top && width == size.width && height == size.height;
}

Pixel::Size::operator RECT() const
{
	return RECT{ (LONG)left, (LONG)top, LONG(left + width), LONG(top + height) };
}

Pixel::Size::operator SIZE() const
{
	return SIZE{ (LONG)width, (LONG)height };
}

Pixel::Size::operator D2D1_SIZE_F() const
{
	return D2D1::SizeF(width, height);
}

Pixel::Size::operator D2D1_RECT_F() const
{
	return D2D1::RectF(left, top, left + width, top + height);
}

void Pixel::Size::GetPoints(Point points[4]) const
{
	points[0] = Point(left, top);
	points[1] = Point(left + width, top);
	points[2] = Point(left, top + height);
	points[3] = Point(left + width, top + height);
}
