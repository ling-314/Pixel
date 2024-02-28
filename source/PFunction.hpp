#pragma once
#include <string>
#include <locale>
#include <atlconv.h>
#include <vector>
#include "PType.hpp"
#define P_SAFERELEASE(target) \
if (target) \
{ \
	target->Release(); \
	target = nullptr; \
}

namespace Pixel
{
	// string 转 wstring 
	std::wstring ToWideString(std::string string);
	// wstring 转 string
	std::string ToByteString(std::wstring string);
	// 获取最上边的点
	Point GetTop(std::vector<Point> points);
	// 获取最左边的点
	Point GetLeft(std::vector<Point> points);
	// 获取最下边的点
	Point GetBottom(std::vector<Point> points);
	// 获取最右边的点
	Point GetRight(std::vector<Point> points);
	// 获取最中间的点
	Point GetCenter(std::vector<Point> points);
	// 获取左上角的点
	Point GetLeftTop(std::vector<Point> points);
	// 获取右上角的点
	Point GetRightTop(std::vector<Point> points);
	// 获取左下角的点
	Point GetLeftBottom(std::vector<Point> points);
	// 获取右下角的点
	Point GetRightBottom(std::vector<Point> points);
}