#include "PNode.h"

Pixel::Node::Node() :
	_position(0, 0),
	_originalSize(Point(0, 0), Point(0, 0)),
	_size(_originalSize),
	_offset(0, 0),
	_show(true),
	_collisionBox(&_originalSize),
	_scale(1.0f),
	_angle(0.0f)
{
}

Pixel::Node::Node(int x, int y) :
	_position(x, y),
	_originalSize(Point(x, y), Point(x, y)),
	_size(_originalSize),
	_offset(0, 0),
	_show(true),
	_collisionBox(&_originalSize),
	_scale(1.0f),
	_angle(0.0f)
{
}

void Pixel::Node::AddChild(Node* node)
{
	_children.push_back(node);
}

void Pixel::Node::RemoveChild(Node* node)
{
	if (_children.empty()) return;
	for (std::vector<Node*>::const_iterator iter = _children.begin(); iter != _children.end(); iter++)
	{
		if (*iter == node)
		{
			_children.erase(iter);
		}
	}
}

void Pixel::Node::ClearChild()
{
	_children.clear();
}

void Pixel::Node::Show()
{
	_show = true;
}

void Pixel::Node::Hide()
{
	_show = false;
}

std::vector<Pixel::Node*> Pixel::Node::GetChildren() const
{
	return _children;
}

Pixel::Point Pixel::Node::GetPosition() const
{
	return Point(_position.x + _offset.x, _position.y + _offset.y);
}

float Pixel::Node::GetPositionX() const
{
	return GetPosition().x;
}

float Pixel::Node::GetPositionY() const
{
	return GetPosition().y;
}

Pixel::CollisionBox Pixel::Node::GetCollisionBox() const
{
	return *_collisionBox;
}

Pixel::Size Pixel::Node::GetOriginalSize() const
{
	return _originalSize;
}

Pixel::Size Pixel::Node::GetSize() const
{
	return _size;
}

Pixel::Vector2 Pixel::Node::GetOffset() const
{
	return _offset;
}

int Pixel::Node::GetOffsetX() const
{
	return GetOffset().x;
}

int Pixel::Node::GetOffsetY() const
{
	return GetOffset().y;
}

bool Pixel::Node::IsShow() const
{
	return _show;
}

void Pixel::Node::SetPosition(Point position)
{
	this->_position = position;
	_originalSize(Point(_originalSize.leftTop.x + position.x, _originalSize.leftTop.y + position.y), Point(_originalSize.rightBottom.x + position.x, _originalSize.rightBottom.y + position.y));
	_SetTransform();
	for (auto child : _children)
	{
		child->SetPosition(Point(
			child->GetPositionX() + position.x - this->_position.x,
			child->GetPositionY() + position.y - this->_position.y
		));
	}
}

void Pixel::Node::SetPosition(float x, float y)
{
	SetPosition(Point(x, y));
}

void Pixel::Node::SetPositionX(float x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Node::SetPositionY(float y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Node::SetOffset(Vector2 offset)
{
	for (auto child : _children) child->SetOffset(offset);
	this->_offset = offset;
}

void Pixel::Node::SetOffset(float x, float y)
{
	SetOffset(Vector2(x, y));
}

void Pixel::Node::SetOffset(float size)
{
	SetOffset(Vector2(
		(GetSize().rightBottom.x - GetSize().leftTop.x) * size,
		(GetSize().rightBottom.y - GetSize().leftTop.y) * size
	));
}

void Pixel::Node::SetOffsetX(float x)
{
	SetOffset(x, GetOffsetY());
}

void Pixel::Node::SetOffsetY(float y)
{
	SetOffset(GetOffsetX(), y);
}

void Pixel::Node::SetCollisionBox(Size* collisionBox)
{
	_collisionBox = collisionBox;
}

float Pixel::Node::GetScale() const
{
	return _scale;
}

float Pixel::Node::GetAngle() const
{
	return _angle;
}

void Pixel::Node::Scale(float scale)
{
	this->_scale = scale;
	_SetTransform();
	for (auto child : _children)
	{
		child->Scale(scale);
	}
}

void Pixel::Node::Rotate(float angle)
{
	this->_angle += angle;
	_SetTransform();
	for (auto child : _children)
	{
		child->Rotate(angle);
	}
}

void Pixel::Node::RotateTo(float angle)
{
	this->_angle = angle;
	_SetTransform();
	for (auto child : _children)
	{
		child->RotateTo(angle);
	}
}

void Pixel::Node::_Render(Renderer* renderer)
{
	if (_show) Render(renderer);
	for (auto child : _children) { if (child) child->Render(renderer); }
}

void Pixel::Node::_SetTransform()
{
	_transform = D2D1::Matrix3x2F::Scale(_scale, _scale, D2D1::Point2F(_position.x, _position.y)) *
		D2D1::Matrix3x2F::Rotation(_angle, D2D1::Point2F(_position.x, _position.y));

	// 获取变换前的包围盒四个点的坐标
	Point leftTop(_originalSize.leftTop.x, _originalSize.leftTop.y);
	Point leftBottom(_originalSize.leftTop.x, _originalSize.rightBottom.y);
	Point rightTop(_originalSize.rightBottom.x, _originalSize.leftTop.y);
	Point rightBottom(_originalSize.rightBottom.x, _originalSize.rightBottom.y);

	// 计算变换后的包围盒四个点变换后的坐标
	leftTop(
		leftTop.x * _transform._11 + leftTop.y * _transform._21 + _transform._31,
		leftTop.x * _transform._12 + leftTop.y * _transform._22 + _transform._32
	);
	leftBottom(
		leftBottom.x * _transform._11 + leftBottom.y * _transform._21 + _transform._31,
		leftBottom.x * _transform._12 + leftBottom.y * _transform._22 + _transform._32
	);
	rightTop(
		rightTop.x * _transform._11 + rightTop.y * _transform._21 + _transform._31,
		rightTop.x * _transform._12 + rightTop.y * _transform._22 + _transform._32
	);
	rightBottom(
		rightBottom.x * _transform._11 + rightBottom.y * _transform._21 + _transform._31,
		rightBottom.x * _transform._12 + rightBottom.y * _transform._22 + _transform._32
	);

	// 计算变换后的包围盒
	leftTop(min(min(leftTop.x, leftBottom.x), min(rightTop.x, rightBottom.x)), min(min(leftTop.y, leftBottom.y), min(rightTop.y, rightBottom.y)));
	rightBottom(max(max(leftTop.x, leftBottom.x), max(rightTop.x, rightBottom.x)), max(max(leftTop.y, leftBottom.y), max(rightTop.y, rightBottom.y)));

	_size(leftTop, rightBottom);
}
