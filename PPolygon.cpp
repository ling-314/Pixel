#include "PNode.hpp"

Pixel::Polygon::Polygon() :
	_pPathGeometry(nullptr)
{
}

Pixel::Polygon::Polygon(std::vector<Point> vertexes) :
	_pPathGeometry(nullptr)
{
	SetVertexex(vertexes);
}

Pixel::Polygon::~Polygon()
{
	P_SAFERELEASE(_pPathGeometry);
}

void Pixel::Polygon::Render(Renderer* renderer)
{
	renderer->DrawPolygon(_pPathGeometry, GetAttr());
}

std::vector<Pixel::Point> Pixel::Polygon::GetVertexex() const
{
	return _vertexes;
}

void Pixel::Polygon::SetVertexex(std::vector<Point> vertexes)
{
	if (vertexes.size() < 3) return;
	
	SetPosition(GetCenter(vertexes));
	_vertexes.resize(vertexes.size());
	for (size_t i = 0; i < vertexes.size(); i++) _vertexes[i] = vertexes[i] - GetPosition();
	
	HRESULT hr;

	if (!_pPathGeometry)
	{
		hr = Renderer::GetFactory()->CreatePathGeometry(&_pPathGeometry);
		if (FAILED(hr)) return;
	}

	ID2D1GeometrySink* pGeometrySink;
	hr = _pPathGeometry->Open(&pGeometrySink);
	if (FAILED(hr)) return;
	pGeometrySink->BeginFigure(_vertexes[0], GetAttr().fill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);
	for (size_t i = 1; i < _vertexes.size(); i++) pGeometrySink->AddLine(_vertexes[i]);
	pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pGeometrySink->Close();

	_SetTransfrom();
	_ResetSize();
}

void Pixel::Polygon::_ResetSize()
{
	Size size(
		GetLeftTop(_vertexes),
		GetRightBottom(_vertexes)
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
