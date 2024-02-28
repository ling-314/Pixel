#include "PNode.hpp"

Pixel::Node::Node() :
	Node(.0f, .0f)
{
}

Pixel::Node::Node(float x, float y) :
	_position(x, y),
	_visible(true),
	_scale(1.0f, 1.0f),
	_angle(.0f),
	_parent(nullptr),
	_where(nullptr)
{
	_SetTransfrom();
}

void Pixel::Node::Render(Renderer* renderer)
{
}

void Pixel::Node::Update()
{
}

void Pixel::Node::Show()
{
	_visible = true;
}

void Pixel::Node::Hide()
{
	_visible = false;
}

void Pixel::Node::AddChild(Node* target)
{
	if (!target->GetParent()) _children.push_back(target);
}

void Pixel::Node::AddChilds(std::initializer_list<Node*> targets)
{
	for (auto target : targets) AddChild(target);
}

void Pixel::Node::RemoveChild(Node* child)
{
	if (child->GetParent() == this) _children.erase(std::find(_children.begin(), _children.end(), child));
}

void Pixel::Node::RemoveChilds(std::initializer_list<Node*> children)
{
	for (auto child : children) RemoveChild(child);
}

void Pixel::Node::ClearChildren()
{
	if (!_children.empty())
	{
		for (auto child : _children) child->_parent = nullptr;
		_children.clear();
	}
}

Pixel::Point Pixel::Node::GetPosition() const
{
	return _position;
}

float Pixel::Node::GetPositionX() const
{
	return _position.x;
}

float Pixel::Node::GetPositionY() const
{
	return _position.y;
}

Pixel::Vector2 Pixel::Node::GetOffset() const
{
	return _offset;
}

float Pixel::Node::GetOffsetX() const
{
	return _offset.x;
}

float Pixel::Node::GetOffsetY() const
{
	return _offset.y;
}

Pixel::Point Pixel::Node::GetRenderPosition() const
{
	return _position + _offset;
}

float Pixel::Node::GetRenderPositionX() const
{
	return (_position + _offset).x;
}

float Pixel::Node::GetRenderPositionY() const
{
	return (_position + _offset).y;
}

bool Pixel::Node::IsVisible() const
{
	return _visible;
}

Pixel::Vector2 Pixel::Node::GetScale() const
{
	return _scale;
}

float Pixel::Node::GetAngle() const
{
	return _angle;
}

Pixel::Size Pixel::Node::GetSize() const
{
	return _size;
}

Pixel::Node* Pixel::Node::GetParent()
{
	return _parent;
}

Pixel::Scene* Pixel::Node::Where()
{
	return _where;
}

std::vector<Pixel::Node*> Pixel::Node::GetChildren()
{
	return _children;
}

D2D1::Matrix3x2F Pixel::Node::GetTransform()
{
	return _transform;
}

void Pixel::Node::SetPosition(Point position)
{
	Point old = _position;
	_position = position;
	_SetTransfrom();
	_ResetSize();
	for (auto child : _children) child->SetPosition(child->GetPosition() + position - old);
}

void Pixel::Node::SetPosition(float x, float y)
{
	SetPosition(Point(x, y));
}

void Pixel::Node::SetPositionX(float x)
{
	SetPosition(Point(x, GetPositionY()));
}

void Pixel::Node::SetPositionY(float y)
{
	SetPosition(Point(GetPositionX(), y));
}

void Pixel::Node::SetOffset(Vector2 offset)
{
	_offset = offset;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Node::SetOffset(float x, float y)
{
	SetOffset(Vector2(x, y));
}

void Pixel::Node::SetOffsetX(float x)
{
	SetOffset(x, GetOffsetY());
}

void Pixel::Node::SetOffsetY(float y)
{
	SetOffset(GetOffsetX(), y);
}

void Pixel::Node::Scale(Vector2 scale)
{
	_scale += scale;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->Scale(scale);
}

void Pixel::Node::ScaleTo(Vector2 scale)
{
	Vector2 old = _scale;
	_scale = scale;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->ScaleTo(scale - old);
}

void Pixel::Node::ScaleX(float x)
{
	_scale.x += x;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->ScaleX(x);
}

void Pixel::Node::ScaleXTo(float x)
{
	Vector2 old = _scale;
	_scale.x = x;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->ScaleXTo(x - old.x);
}

void Pixel::Node::ScaleY(float y)
{
	_scale.y += y;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->ScaleX(y);
}

void Pixel::Node::ScaleYTo(float y)
{
	Vector2 old = _scale;
	_scale.y = y;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->ScaleXTo(y - old.y);
}

void Pixel::Node::FlipX()
{
	_scale.x *= -1;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Node::FlipY()
{
	_scale.y *= -1;
	_SetTransfrom();
	_ResetSize();
}

void Pixel::Node::Rotate(float angle)
{
	_angle += angle;
	if (_angle != 0) _angle = fmodf(360.0f, _angle);
	else _angle = 0;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->Rotate(angle);
}

void Pixel::Node::RotateTo(float angle)
{
	float old = _angle;
	if (angle != 0) _angle = fmodf(360.0f, angle);
	else _angle = 0;
	_SetTransfrom();
	_ResetSize();

	for (auto child : _children) child->RotateTo(angle - old);
}

void Pixel::Node::Move(float step)
{
	float x = 90 / _angle, y = 1 - x;

	if (0 <= _angle <= 90)
	{
		x *= step;
		y *= step;
	}
	else if (90 <= _angle <= 180)
	{
		x *= -step;
		y *= step;
	}
	else if (180 <= _angle <= 270)
	{
		x *= -step;
		y *= -step;
	}
	else if (270 <= _angle <= 360)
	{
		x *= step;
		y *= -step;
	}
	else
	{
	}

	SetPosition(GetPosition() + Vector2(x, y));
}

void Pixel::Node::Move(Vector2 vector)
{
	SetPosition(GetPosition() + vector);
}

void Pixel::Node::MoveX(float step)
{
	SetPositionX(GetPositionX() + step);
}

void Pixel::Node::MoveY(float step)
{
	SetPositionY(GetPositionY() + step);
}

void Pixel::Node::_SetSize(Size size)
{
	_size = size;
}

void Pixel::Node::_ResetSize()
{
	_SetSize(Size(GetRenderPosition(), GetRenderPosition()));
}

void Pixel::Node::_SetTransfrom()
{
	_transform = D2D1::Matrix3x2F::Scale(_scale.x, _scale.y, Point()) *
		D2D1::Matrix3x2F::Rotation(_angle, Point()) *
		D2D1::Matrix3x2F::Translation(GetRenderPositionX(), GetRenderPositionY());
}

void Pixel::Node::_Render(Renderer* renderer)
{
	if (_visible)
	{
		renderer->GetRenderTarget()->SetTransform(_transform * D2D1::Matrix3x2F::Translation(-renderer->GetCamera()->GetOffset()));
		Render(renderer);
	}
	for (auto child : _children)
	{
		if (child->IsVisible()) child->_Render(renderer);
	}
}
