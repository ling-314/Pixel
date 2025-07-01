#include "PType.hpp"

Pixel::Vector2::Vector2() :
	Vector2(0, 0)
{
}

Pixel::Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{
}

Pixel::Vector2::Vector2(int x, int y) :
	x((float)x),
	y((float)y)
{
}

Pixel::Vector2::Vector2(POINT point) :
	x((float)point.x),
	y((float)point.y)
{
}

Pixel::Vector2::Vector2(D2D1_POINT_2F point) :
	x(point.x),
	y(point.y)
{
}

Pixel::Vector2::Vector2(D2D1_SIZE_F point)
{
	x = point.width;
	y = point.height;
}

Pixel::Vector2 Pixel::Vector2::Infinity()
{
	return Vector2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}

bool Pixel::Vector2::In(const Size& size) const
{
	return x >= size.left && x <= size.left + size.width && y >= size.top && y <= size.top + size.height;
}

void Pixel::Vector2::operator=(Vector2 vector2)
{
	x = vector2.x;
	y = vector2.y;
}

Pixel::Vector2 Pixel::Vector2::operator+(Vector2 vector2)
{
	return Vector2(x + vector2.x, y + vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator+(float x_y)
{
	return Vector2(x + x_y, y + x_y);
}

Pixel::Vector2 Pixel::Vector2::operator+(Vector2 vector2) const
{
	return Vector2(x + vector2.x, y + vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator+(float x_y) const
{
	return Vector2(x + x_y, y + x_y);
}

void Pixel::Vector2::operator+=(Vector2 vector2)
{
	x += vector2.x;
	y += vector2.y;
}

void Pixel::Vector2::operator+=(float x_y)
{
	x += x_y;
	y += x_y;
}

Pixel::Vector2 Pixel::Vector2::operator-(Vector2 vector2)
{
	return Vector2(x - vector2.x, y - vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator-(float x_y)
{
	return Vector2(x - x_y, y - x_y);
}

Pixel::Vector2 Pixel::Vector2::operator-(Vector2 vector2) const
{
	return Vector2(x - vector2.x, y - vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator-(float x_y) const
{
	return Vector2(x - x_y, y - x_y);
}

void Pixel::Vector2::operator-=(Vector2 vector2)
{
	x -= vector2.x;
	y -= vector2.y;
}

void Pixel::Vector2::operator-=(float x_y)
{
	x -= x_y;
	y -= x_y;
}

Pixel::Vector2 Pixel::Vector2::operator*(Vector2 vector2)
{
	return Vector2(x * vector2.x, y * vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator*(float x_y)
{
	return Vector2(x * x_y, y * x_y);
}

Pixel::Vector2 Pixel::Vector2::operator*(Vector2 vector2) const
{
	return Vector2(x * vector2.x, y * vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator*(float x_y) const
{
	return Vector2(x * x_y, y * x_y);
}

void Pixel::Vector2::operator*=(Vector2 vector2)
{
	x *= vector2.x;
	y *= vector2.y;
}

void Pixel::Vector2::operator*=(float x_y)
{
	x *= x_y;
	y *= x_y;
}

Pixel::Vector2 Pixel::Vector2::operator/(Vector2 vector2)
{
	return Vector2(x / vector2.x, y / vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator/(float x_y)
{
	return Vector2(x / x_y, y / x_y);
}

Pixel::Vector2 Pixel::Vector2::operator/(Vector2 vector2) const
{
	return Vector2(x / vector2.x, y / vector2.y);
}

Pixel::Vector2 Pixel::Vector2::operator/(float x_y) const
{
	return Vector2(x / x_y, y / x_y);
}

void Pixel::Vector2::operator/=(Vector2 vector2)
{
	x /= vector2.x;
	y /= vector2.y;
}

void Pixel::Vector2::operator/=(float x_y)
{
	x /= x_y;
	y /= x_y;
}

Pixel::Vector2 Pixel::Vector2::operator-()
{
	return Vector2(-x, -y);
}

Pixel::Vector2 Pixel::Vector2::operator-() const
{
	return Vector2(-x, -y);
}

bool Pixel::Vector2::operator==(Vector2 vector2)
{
	return x == vector2.x && y == vector2.y;
}

bool Pixel::Vector2::operator==(Vector2 vector2) const
{
	return x == vector2.x && y == vector2.y;
}

bool Pixel::Vector2::operator!=(Vector2 vector2)
{
	return x != vector2.x && y != vector2.y;
}

bool Pixel::Vector2::operator!=(Vector2 vector2) const
{
	return x != vector2.x && y != vector2.y;
}

Pixel::Vector2::operator POINT() const
{
	return POINT{ (LONG)x, (LONG)y };
}

Pixel::Vector2::operator D2D1_POINT_2F() const
{
	return D2D1_POINT_2F{ x, y };
}

Pixel::Vector2::operator D2D1_SIZE_F() const
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

Pixel::Resource::Resource() :
	id(0),
	type(""),
	_buffer(nullptr),
	_size(0),
	module(nullptr)
{
}

Pixel::Resource::Resource(int id, std::string type, HMODULE module) :
	id(id),
	type(type),
	_buffer(nullptr),
	_size(0),
	module(module)
{
	Load();
}

bool Pixel::Resource::Load()
{
	HRSRC resource = FindResource(module, MAKEINTRESOURCE(id), ToWideString(type).c_str());
	if (!resource) return false;

	DWORD resourceSize = SizeofResource(module, resource);
	if (!resourceSize) return false;

	HGLOBAL global = LoadResource(module, resource);
	if (!global) return false;

	LPVOID pResourceData = LockResource(global);
	if (!pResourceData) return false;

	_buffer = pResourceData;
	_size = resourceSize;

	return true;
}

void* Pixel::Resource::GetBuffer()
{
	return _buffer;
}

unsigned int Pixel::Resource::GetSize() const
{
	return _size;
}

Pixel::CollisionBox::CollisionBox()
{
}

Pixel::CollisionBox::CollisionBox(std::vector<Point> vertexes, Size size)
{
	_vertexes = vertexes;
	_Create(size);
}

void Pixel::CollisionBox::_Create(const Size size)
{
	if (_vertexes.size() < 3)
		return;
	auto PointOnTheEdge = [](Point point, Size size) -> bool
		{
			return (point.x == size.left || point.x == size.left + size.width || point.y == size.top || point.y == size.top + size.height);
		};
	auto GetPrev = [](const std::vector<Point>& vertexes, const std::vector<Point>::const_iterator& point) -> Point
		{
			if (point == vertexes.begin())
				return vertexes[vertexes.size() - 1];
			else
				return *(std::prev(point, 1));
		};
	auto GetNext = [](const std::vector<Point>& vertexes, const std::vector<Point>::const_iterator& point) -> Point
		{
			if (point == vertexes.end() - 1)
				return *(vertexes.begin());
			else
				return *(std::next(point, 1));
		};
	std::vector<Point> vertexes = _vertexes; // 避免影响到原来的顶点
	for (std::vector<Point>::const_iterator point = vertexes.begin(); point != vertexes.end(); point++)
	{
		if (vertexes.size() == 3)
		{
			_triangles.push_back({ GetPrev(vertexes, point), *point, GetNext(vertexes, point) });
			return;
		}
		if (PointOnTheEdge(*point, size)) // true表示point是凸点
		{
			_triangles.push_back({ GetPrev(vertexes, point), *point, GetNext(vertexes, point) });
			vertexes.erase(point); // 移除凸点，方便下次切三角
			point = vertexes.begin();
		}
	}
}
