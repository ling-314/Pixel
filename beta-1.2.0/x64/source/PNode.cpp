#include "PNode.h"

Pixel::Node::Node(int x, int y) :
	position(x, y),
	scale(1.0f),
	size(Point(x, y), Point(x, y)),
	collisionBox(Point(x, y), Point(x, y)),
	angle(0)
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

Pixel::Size Pixel::Node::GetSize() const
{
	return size;
}

void Pixel::Node::SetPosition(Point position)
{
	size(Point(position.x, position.y), Point(position.x, position.y));
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

void Pixel::Node::SetCollisionBox(Size size)
{
	collisionBox.leftTop = size.leftTop;
	collisionBox.rightBottom = size.rightBottom;
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
	for (auto node : children)
	{
		node->Scale(scale);
	}
	this->scale = scale;
}

void Pixel::Node::Rotate(float angle)
{
	for (auto node : children)
	{
		node->Rotate(angle);
	}
	this->angle += angle;
}

void Pixel::Node::RotateTo(float angle)
{
	for (auto node : children)
	{
		node->RotateTo(angle);
	}
	this->angle = angle;
}

void Pixel::Node::Render(Renderer* renderer)
{
	for (auto node : children)
	{
		node->Render(renderer);
	}
}
