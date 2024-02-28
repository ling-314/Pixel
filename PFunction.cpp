#include "PFunction.hpp"

std::wstring Pixel::ToWideString(std::string string)
{
	USES_CONVERSION;
	setlocale(LC_ALL, "");
	return A2W(string.c_str());
}

std::string Pixel::ToByteString(std::wstring string)
{
	USES_CONVERSION;
	setlocale(LC_ALL, "");
	return W2A(string.c_str());
}

Pixel::Point Pixel::GetTop(std::vector<Point> points)
{
	Point top = points[0];
	for (auto point : points) if (point.y < top.y) top = point;
	return top;
}

Pixel::Point Pixel::GetLeft(std::vector<Point> points)
{
	Point left = points[0];
	for (auto point : points) if (point.x < left.x) left = point;
	return left;
}

Pixel::Point Pixel::GetBottom(std::vector<Point> points)
{
	Point bottom = points[0];
	for (auto point : points) if (point.y > bottom.y) bottom = point;
	return bottom;
}

Pixel::Point Pixel::GetRight(std::vector<Point> points)
{
	Point right = points[0];
	for (auto point : points) if (point.x > right.x) right = point;
	return right;
}

Pixel::Point Pixel::GetCenter(std::vector<Point> points)
{
	return Point(
		(GetLeft(points) + GetRight(points)).x / 2,
		(GetTop(points) + GetBottom(points)).y / 2
	);
}

Pixel::Point Pixel::GetLeftTop(std::vector<Point> points)
{
	return Point(GetLeft(points).x, GetTop(points).y);
}

Pixel::Point Pixel::GetRightTop(std::vector<Point> points)
{
	return Point(GetRight(points).x, GetTop(points).y);
}

Pixel::Point Pixel::GetLeftBottom(std::vector<Point> points)
{
	return Point(GetLeft(points).x, GetBottom(points).y);
}

Pixel::Point Pixel::GetRightBottom(std::vector<Point> points)
{
	return Point(GetRight(points).x, GetBottom(points).y);
}
