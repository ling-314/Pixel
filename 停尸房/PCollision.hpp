#pragma once
#include <vector>
#include <initializer_list>
#include <cmath>
#include <d2d1.h>
#include "PType.hpp"

namespace Pixel
{
	class CollisionBox
	{
		friend bool Collide(const CollisionBox& box1, const CollisionBox& box2);
	public:
		struct AABB
		{
			float minX;
			float minY;
			float maxX;
			float maxY;
		};
		struct Line
		{
			Line(Point vertex1, Point vertex2);
			Point vertex1; // 顶点1
			Point vertex2; // 顶点2
			float k; // 斜率
			float b; // 截距
			AABB aabb; // 包围盒
		};
		struct Circle
		{
			Circle(Point center, float radius);
			Point center; // 圆心
			float radius; // 半径
			AABB aabb; // 包围盒
		};
	public:
		CollisionBox();
		// 生成碰撞箱
		// 至少一条边
		void Generate(std::vector<Point> vertices, bool aabb = true);
		// 生成碰撞箱
		void Generate(std::vector<Circle> circles, bool aabb = true);
		// 生成碰撞箱
		// 至少一条边
		void Generate(std::vector<Point> vertices, std::vector<Circle> circles);
	private:
		std::vector<Line> _lines;
		std::vector<Circle> _circles;
		AABB _aabb;
		bool _empty = false; // 是否为空碰撞箱
	};

	// 碰撞检测
	bool Collide(const CollisionBox& box1, const CollisionBox& box2);
}