#include "PNode.hpp"

Pixel::PolygonBase::PolygonBase() :
	Graphic()
{
}

Pixel::Rectangle::Rectangle() :
	PolygonBase(),
	_width(0.0f),
	_height(0.0f)
{
}

Pixel::Rectangle::Rectangle(float x, float y, float width, float height) :
	PolygonBase(),
	_width(width),
	_height(height)
{
	_ResetSize();
}

void Pixel::Rectangle::RenderSelf(Renderer* renderer)
{
	renderer->DrawRectangle(_width, _height, GetAttr());
}

float Pixel::Rectangle::GetWidth() const
{
	return _width;
}

float Pixel::Rectangle::GetHeight() const
{
	return _height;
}

std::vector<Pixel::Point> Pixel::Rectangle::GetVertices() const
{
	return {
		Point(-_width / 2, -_height / 2),
		Point(_width / 2, -_height / 2),
		Point(_width / 2, _height / 2),
		Point(-_width / 2, _height / 2)
	};
}

void Pixel::Rectangle::SetWidth(float width)
{
	_width = width;
	_ResetSize();
}

void Pixel::Rectangle::SetHeight(float height)
{
	_height = height;
	_ResetSize();
}

void Pixel::Rectangle::_ResetSize()
{
	Size size(
		_width / -2,
		_height / -2,
		_width,
		_height
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		points[0],
		points[3]
	);

	_SetSize(size);
}

Pixel::Polygon::Polygon() :
	PolygonBase(),
	_vertices(),
	_pPathGeometry(nullptr)
{
	_Create();
}

Pixel::Polygon::Polygon(std::vector<Point> vertices) :
	PolygonBase(),
	_vertices(std::move(vertices)),
	_pPathGeometry(nullptr)
{
	_Create();
}

Pixel::Polygon::Polygon(std::initializer_list<Point> vertices) :
	PolygonBase(),
	_vertices(vertices),
	_pPathGeometry(nullptr)
{
	_Create();
}

void Pixel::Polygon::RenderSelf(Renderer* renderer)
{
	renderer->DrawPolygon(_pPathGeometry, GetAttr());
}

std::vector<Pixel::Point> Pixel::Polygon::GetVertices() const
{
	return _vertices;
}

void Pixel::Polygon::SetVertices(std::vector<Point> vertices)
{
	_vertices = std::move(vertices);
	_Create();
}

void Pixel::Polygon::SetVertices(std::initializer_list<Point> vertices)
{
	_vertices.assign(vertices);
	_Create();
}

void Pixel::Polygon::AddVertex(Point vertex)
{
	_vertices.push_back(vertex);
	_Create();
}

void Pixel::Polygon::AddVertices(std::initializer_list<Point> vertices)
{
	_vertices.insert(_vertices.end(), vertices);
	_Create();
}

void Pixel::Polygon::RemoveVertex(Point vertex)
{
	auto it = std::find(_vertices.begin(), _vertices.end(), vertex);
	if (it != _vertices.end())
	{
		_vertices.erase(it);
		_Create();
	}
}

void Pixel::Polygon::RemoveVertices(std::initializer_list<Point> vertices)
{
	for (const auto& vertex : vertices)
	{
		auto it = std::find(_vertices.begin(), _vertices.end(), vertex);
		if (it != _vertices.end())
		{
			_vertices.erase(it);
		}
	}
	_Create();
}

void Pixel::Polygon::ClearVertices()
{
	_vertices.clear();
	_Create();
}

void Pixel::Polygon::_ResetSize()
{
	if (_vertices.empty())
	{
		_SetSize(Size(0, 0, 0, 0));
		return;
	}
	float minX = 0.0f, maxX = 0.0f, minY = 0.0f, maxY = 0.0f;
	for (const auto& v : _vertices)
	{
		if (v.x < minX) minX = v.x;
		if (v.x > maxX) maxX = v.x;
		if (v.y < minY) minY = v.y;
		if (v.y > maxY) maxY = v.y;
	}

	float width = maxX - minX;
	float height = maxY - minY;

	Size size(
		width / -2,
		height / -2,
		width,
		height
	);

	Point points[4];
	size.GetPoints(points);

	points[0] = GetTransform().TransformPoint(points[0]);
	points[3] = GetTransform().TransformPoint(points[3]);

	size = Size(
		points[0],
		points[3]
	);

	_SetSize(size);
}

void Pixel::Polygon::_Create()
{
	if (_pPathGeometry)
	{
		_pPathGeometry->Release();
		_pPathGeometry = nullptr;
	}
	if (_vertices.empty())
	{
		return;
	}

	// 计算中心点
	float sumX = 0.0f, sumY = 0.0f;
	for (const auto& v : _vertices) {
		sumX += v.x;
		sumY += v.y;
	}
	float centerX = sumX / _vertices.size();
	float centerY = sumY / _vertices.size();

	ID2D1Factory* factory = Renderer::GetFactory();
	factory->CreatePathGeometry(&_pPathGeometry);
	ID2D1GeometrySink* sink;
	_pPathGeometry->Open(&sink);

	// 以中心点为原点平移所有顶点
	sink->BeginFigure(
		D2D1::Point2F(_vertices[0].x - centerX, _vertices[0].y - centerY),
		D2D1_FIGURE_BEGIN_FILLED
	);
	for (size_t i = 1; i < _vertices.size(); ++i)
	{
		sink->AddLine(D2D1::Point2F(_vertices[i].x - centerX, _vertices[i].y - centerY));
	}
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	P_SAFERELEASE(sink);

	_ResetSize();
}
