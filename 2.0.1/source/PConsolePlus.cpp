#include "PConsolePlus.h"

Pixel::ConsolePlus::~ConsolePlus()
{
	for (auto node : _scene.GetAllNodes())
	{
		if (node) delete node;
	}
}

bool Pixel::ConsolePlus::Init()
{
	bool succeed = Window::Init();
	_scene.SetBackground(Color::Black);
	Enter(&_scene);
	return succeed;
}

void Pixel::ConsolePlus::Print(std::string text)
{
	_UpdateNode();
	auto aText = new Text(text);
	aText->SetFontSize(20);
	aText->SetColor(Color::White);
	aText->SetOffset(
		-(aText->GetSize().rightBottom.x - aText->GetSize().leftTop.x) / 2,
		(aText->GetSize().rightBottom.y - aText->GetSize().leftTop.y) / 2
	);
	aText->SetPosition(0, GetHeight());
	_scene.AddNode(aText);
}

void Pixel::ConsolePlus::_UpdateNode()
{
	for (auto node : _scene.GetAllNodes())
	{
		node->SetPosition(0, node->GetPositionY() - (node->GetSize().rightBottom.y - node->GetSize().leftTop.y));
	}
}

Pixel::ConsolePlus::Output::Output(ConsolePlus* console) :
	_console(console)
{
}

Pixel::ConsolePlus::Output& Pixel::ConsolePlus::Output::operator<<(std::string text)
{
	_console->Print(text);
	return *this;
}
