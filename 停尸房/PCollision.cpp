#include "PCollision.hpp"

bool AABBIntersect(const Pixel::CollisionBox::AABB& aabb1, const Pixel::CollisionBox::AABB& aabb2)
{
	// 检查两个包围盒是否相交
	return (aabb1.minX <= aabb2.maxX && aabb1.maxX >= aabb2.minX &&
			aabb1.minY <= aabb2.maxY && aabb1.maxY >= aabb2.minY);
}

bool LineIntersect(const Pixel::CollisionBox::Line& line1, const Pixel::CollisionBox::Line& line2) {
	constexpr float eps = 1e-6f;

	float x1 = line1.vertex1.x, y1 = line1.vertex1.y;
	float x2 = line1.vertex2.x, y2 = line1.vertex2.y;
	float x3 = line2.vertex1.x, y3 = line2.vertex1.y;
	float x4 = line2.vertex2.x, y4 = line2.vertex2.y;

	bool line1Vert = line1.k == std::numeric_limits<float>::infinity();
	bool line2Vert = line2.k == std::numeric_limits<float>::infinity();

	if (line1Vert && line2Vert) {
		// 两条线都垂直：x 必须一致，且 y 区间要重叠
		if (std::abs(x1 - x3) > eps) return false;
		float minY1 = std::min(y1, y2), maxY1 = std::max(y1, y2);
		float minY2 = std::min(y3, y4), maxY2 = std::max(y3, y4);
		return !(maxY1 < minY2 || maxY2 < minY1);
	}

	if (line1Vert) {
		// line1 垂直，x = x1，代入 line2 求 y
		float x = x1;
		float y = line2.k * x + line2.b;
		return x >= std::min(x3, x4) - eps && x <= std::max(x3, x4) + eps &&
			y >= std::min(y1, y2) - eps && y <= std::max(y1, y2) + eps &&
			y >= std::min(y3, y4) - eps && y <= std::max(y3, y4) + eps;
	}

	if (line2Vert) {
		// line2 垂直，x = x3，代入 line1 求 y
		float x = x3;
		float y = line1.k * x + line1.b;
		return x >= std::min(x1, x2) - eps && x <= std::max(x1, x2) + eps &&
			y >= std::min(y1, y2) - eps && y <= std::max(y1, y2) + eps &&
			y >= std::min(y3, y4) - eps && y <= std::max(y3, y4) + eps;
	}

	// 平行线
	if (std::abs(line1.k - line2.k) < eps) return false;

	// 一般情况，求交点
	float x = (line2.b - line1.b) / (line1.k - line2.k);
	float y = line1.k * x + line1.b;

	// 判断交点是否在两个线段内部
	bool inLine1 = x >= std::min(x1, x2) - eps && x <= std::max(x1, x2) + eps &&
		y >= std::min(y1, y2) - eps && y <= std::max(y1, y2) + eps;

	bool inLine2 = x >= std::min(x3, x4) - eps && x <= std::max(x3, x4) + eps &&
		y >= std::min(y3, y4) - eps && y <= std::max(y3, y4) + eps;

	return inLine1 && inLine2;
}

Pixel::CollisionBox::Line::Line(Point vertex1, Point vertex2)
{
	// 初始化端点
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	// 计算斜率
	if (vertex1.y == vertex2.y)
		k = std::numeric_limits<float>::infinity();
	else
		k = (vertex2.y - vertex1.y) / (vertex2.x - vertex1.x);
	// 计算截距
	if (k == std::numeric_limits<float>::infinity())
		b = std::numeric_limits<float>::quiet_NaN();
	else
		b = vertex1.y - k * vertex1.x;
	// 计算包围盒
	aabb.minX = std::min(vertex1.x, vertex2.x);
	aabb.minY = std::min(vertex1.y, vertex2.y);
	aabb.maxX = std::max(vertex1.x, vertex2.x);
	aabb.maxY = std::max(vertex1.y, vertex2.y);
}

Pixel::CollisionBox::Circle::Circle(Point center, float radius)
{
	// 初始化圆心和半径
	this->center = center;
	this->radius = radius;
	// 计算包围盒
	aabb.minX = center.x - radius;
	aabb.minY = center.y - radius;
	aabb.maxX = center.x + radius;
	aabb.maxY = center.y + radius;
}

Pixel::CollisionBox::CollisionBox() :
	_aabb{ 0, 0, 0, 0 },
	_empty(true)
{
}

void Pixel::CollisionBox::Generate(std::vector<Point> vertices, bool aabb)
{
	// 清空之前的线
	_lines.clear();
	// 初始化线
	for (auto it = vertices.begin(); it != vertices.end(); it++)
	{
		if (it + 1 != vertices.end())
		{
			_lines.push_back(Line(*it, *(it + 1)));
		}
		else
		{
			_lines.push_back(Line(*it, vertices.front()));
		}
	}
	// 计算包围盒
	if (aabb)
	{
		_circles.clear();
		if (_lines.empty())
		{
			_aabb.minX = _aabb.minY = std::numeric_limits<float>::infinity();
			_aabb.maxX = _aabb.maxY = -std::numeric_limits<float>::infinity();
		}
		else
		{
			_aabb.minX = _lines[0].aabb.minX;
			_aabb.minY = _lines[0].aabb.minY;
			_aabb.maxX = _lines[0].aabb.maxX;
			_aabb.maxY = _lines[0].aabb.maxY;
			for (const auto& line : _lines)
			{
				if (line.aabb.minX < _aabb.minX) _aabb.minX = line.aabb.minX;
				if (line.aabb.minY < _aabb.minY) _aabb.minY = line.aabb.minY;
				if (line.aabb.maxX > _aabb.maxX) _aabb.maxX = line.aabb.maxX;
				if (line.aabb.maxY > _aabb.maxY) _aabb.maxY = line.aabb.maxY;
			}
		}
	}
}

void Pixel::CollisionBox::Generate(std::vector<Circle> circles, bool aabb)
{
	// 清空之前的圆
	_circles.clear();
	// 初始化圆
	_circles = circles;
	// 计算包围盒
	if (aabb)
	{
		_lines.clear();
		if (_circles.empty())
		{
			_aabb.minX = _aabb.minY = std::numeric_limits<float>::infinity();
			_aabb.maxX = _aabb.maxY = -std::numeric_limits<float>::infinity();
		}
		else
		{
			_aabb.minX = _circles[0].aabb.minX;
			_aabb.minY = _circles[0].aabb.minY;
			_aabb.maxX = _circles[0].aabb.maxX;
			_aabb.maxY = _circles[0].aabb.maxY;
			for (const auto& circle : _circles)
			{
				if (circle.aabb.minX < _aabb.minX) _aabb.minX = circle.aabb.minX;
				if (circle.aabb.minY < _aabb.minY) _aabb.minY = circle.aabb.minY;
				if (circle.aabb.maxX > _aabb.maxX) _aabb.maxX = circle.aabb.maxX;
				if (circle.aabb.maxY > _aabb.maxY) _aabb.maxY = circle.aabb.maxY;
			}
		}
	}
}

void Pixel::CollisionBox::Generate(std::vector<Point> vertices, std::vector<Circle> circles)
{
	Generate(vertices, false);
	Generate(circles, false);
}

bool Pixel::Collide(const CollisionBox& box1, const CollisionBox& box2)
{
	// 如果任意一个碰撞箱为空，则不发生碰撞
	if (box1._empty || box2._empty)
		return false;
	// 首先检查包围盒是否相交
	if (!AABBIntersect(box1._aabb, box2._aabb))
		return false;
	// 检查线段碰撞
	for (const auto& line1 : box1._lines)
	{
		for (const auto& line2 : box2._lines)
		{
			if (AABBIntersect(line1.aabb, line2.aabb) && LineIntersect(line1, line2))
			{
				return true; // 发生碰撞
			}
		}
	}
	// 检查圆形碰撞
	for (const auto& circle1 : box1._circles)
	{
		for (const auto& circle2 : box2._circles)
		{
			if (AABBIntersect(circle1.aabb, circle2.aabb))
			{
				float dx = circle1.center.x - circle2.center.x;
				float dy = circle1.center.y - circle2.center.y;
				float distanceSquared = dx * dx + dy * dy;
				float radiusSum = circle1.radius + circle2.radius;
				if (distanceSquared <= radiusSum * radiusSum)
				{
					return true; // 发生碰撞
				}
			}
		}
	}
	return false; // 没有碰撞
}
