#include "PNode.h"

Pixel::Node::Node(int x, int y) :
	position(x, y),
	originalSize(Point(x, y), Point(x, y)),
	size(originalSize),
	collisionBox(originalSize),
	scale(1.0f),
	angle(0.0f)
{
}

void Pixel::Node::AddChild(Node* node)
{
	children.push_back(node);
}

void Pixel::Node::RemoveChild(Node* node)
{
	if (children.empty()) return;
	for (std::vector<Node*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
	{
		if (*iter == node)
		{
			children.erase(iter);
		}
	}
}

void Pixel::Node::ClearChild()
{
	children.clear();
}

std::vector<Pixel::Node*> Pixel::Node::GetChildren() const
{
	return children;
}

Pixel::Point Pixel::Node::GetPosition() const
{
	return position;
}

int Pixel::Node::GetPositionX() const
{
	return GetPosition().x;
}

int Pixel::Node::GetPositionY() const
{
	return GetPosition().y;
}

Pixel:: CollisionBox Pixel::Node::GetCollisionBox() const
{
	return collisionBox;
}

Pixel::Size Pixel::Node::GetOriginalSize() const
{
	return originalSize;
}

Pixel::Size Pixel::Node::GetSize() const
{
	return originalSize;
}

void Pixel::Node::SetPosition(Point position)
{
	originalSize(Point(position.x, position.y), Point(position.x, position.y));
	SetCollisionBox(
		Point(
			GetCollisionBox().leftTop.x + position.x - this->position.x,
			GetCollisionBox().leftTop.y + position.y - this->position.y
		),
		Point(
			GetCollisionBox().rightBottom.x + position.x - this->position.x,
			GetCollisionBox().rightBottom.y + position.y - this->position.y
		)
	);
	for (auto node : children)
	{
		node->SetPosition(Point(
			node->GetPositionX() + position.x - this->position.x,
			node->GetPositionY() + position.y - this->position.y
		));
	}
	this->position = position;
}

void Pixel::Node::SetPosition(int x, int y)
{
	SetPosition(Point(x, y));
}

void Pixel::Node::SetPositionX(int x)
{
	SetPosition(x, GetPositionY());
}

void Pixel::Node::SetPositionY(int y)
{
	SetPosition(GetPositionX(), y);
}

void Pixel::Node::SetCollisionBox(Point leftTop, Point rightBottom)
{
	collisionBox.leftTop = leftTop;
	collisionBox.rightBottom = rightBottom;
}

void Pixel::Node::SetCollisionBox(Size originalSize)
{
	collisionBox.leftTop = originalSize.leftTop;
	collisionBox.rightBottom = originalSize.rightBottom;
}

float Pixel::Node::GetScale() const
{
	return scale;
}

float Pixel::Node::GetAngle() const
{
	return angle;
}

void Pixel::Node::Scale(float scale)
{
	this->scale = scale;
	SetTransform();
	for (auto node : children)
	{
		node->Scale(scale);
	}
}

void Pixel::Node::Rotate(float angle)
{
	this->angle += angle;
	SetTransform();
	for (auto node : children)
	{
		node->Rotate(angle);
	}
}

void Pixel::Node::RotateTo(float angle)
{
	this->angle = angle;
	SetTransform();
	for (auto node : children)
	{
		node->RotateTo(angle);
	}
}

void Pixel::Node::SetTransform()
{
	transform = D2D1::Matrix3x2F::Scale(scale, scale, D2D1::Point2F((float)position.x, (float)position.y)) *
		D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F((float)position.x, (float)position.y));

	// 获取变换前的包围盒四个点的坐标
	Point leftTop(originalSize.leftTop.x, originalSize.leftTop.y);
	Point leftBottom(originalSize.leftTop.x, originalSize.rightBottom.y);
	Point rightTop(originalSize.rightBottom.x, originalSize.leftTop.y);
	Point rightBottom(originalSize.rightBottom.x, originalSize.rightBottom.y);

	// 计算变换后的包围盒四个点变换后的坐标
	leftTop(leftTop.x * transform._11 + leftTop.y * transform._21 + transform._31, 
		leftTop.x * transform._12 + leftTop.y * transform._22 + transform._32
	);
	leftBottom(leftBottom.x * transform._11 + leftBottom.y * transform._21 + transform._31,
		leftBottom.x * transform._12 + leftBottom.y * transform._22 + transform._32
	);
	rightTop(rightTop.x * transform._11 + rightTop.y * transform._21 + transform._31,
		rightTop.x * transform._12 + rightTop.y * transform._22 + transform._32
	);
	rightBottom(rightBottom.x * transform._11 + rightBottom.y * transform._21 + transform._31,
		rightBottom.x * transform._12 + rightBottom.y * transform._22 + transform._32
	);

	// 计算变换后的包围盒
	leftTop(min(min(leftTop.x, leftBottom.x), min(rightTop.x, rightBottom.x)), min(min(leftTop.y, leftBottom.y), min(rightTop.y, rightBottom.y)));
	rightBottom(max(max(leftTop.x, leftBottom.x), max(rightTop.x, rightBottom.x)), max(max(leftTop.y, leftBottom.y), max(rightTop.y, rightBottom.y)));

	size(leftTop, rightBottom);
}

void Pixel::Node::Render(Renderer* renderer)
{
	for (auto node : children)
	{
		node->Render(renderer);
	}
}
