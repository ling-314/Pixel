#include "PNode.hpp"

Pixel::Button::Button() :
	Button(nullptr)
{
}

Pixel::Button::Button(Node* normal, Node* stay, Node* press) :
	Node(.0f, .0f),
	_type(Normal)
{
	SetNormal(normal);
	SetStay(stay);
	SetPress(press);
}

void Pixel::Button::RenderSelf(Renderer* renderer)
{
	switch (_type)
	{
	case Normal:
		_normal->Render(renderer);
		break;
	case Stay:
		_stay->Render(renderer);
		break;
	case Press:
		_press->Render(renderer);
		break;
	}
}

Pixel::Node* Pixel::Button::GetNormal()
{
	return _normal;
}

Pixel::Node* Pixel::Button::GetStay()
{
	return _stay;
}

Pixel::Node* Pixel::Button::GetPress()
{
	return _press;
}

void Pixel::Button::SetNormal(Node* normal)
{
	_normal = normal;
	Copy(*normal);
	_ResetSize();
}

void Pixel::Button::SetStay(Node* stay)
{
	_stay = stay;
}

void Pixel::Button::SetPress(Node* press)
{
	_press = press;
}

void Pixel::Button::_ResetSize()
{
	_SetSize(_normal->GetSize());
}

void Pixel::Button::_Handle(const Event& event)
{
	SetPosition(GetPosition());
	auto size = GetSize();
	if (event.mousePosition.In(GetSize()))
		if (event.mouseDown)
			_type = Press;
		else
			_type = Stay;
	else
		_type = Normal;
}
