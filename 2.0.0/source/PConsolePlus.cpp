#include "PConsolePlus.h"

Pixel::ConsolePlus::~ConsolePlus()
{
	for (auto node : scene.GetAllNodes())
	{
		if (node) delete node;
	}
}

bool Pixel::ConsolePlus::Init()
{
	bool succeed = Window::Init();
	scene.SetBackground(Color::Black);
	Enter(&scene);
	return succeed;
}

void Pixel::ConsolePlus::Print(std::string text)
{
	UpdateNode();
	auto aText = new Text(text);
	aText->SetFontSize(20);
	aText->SetColor(Color::White);
	aText->SetOffset(
		-(aText->GetSize().rightBottom.x - aText->GetSize().leftTop.x) / 2,
		(aText->GetSize().rightBottom.y - aText->GetSize().leftTop.y) / 2
	);
	aText->SetPosition(0, GetHeight());
	scene.AddNode(aText);
}

void Pixel::ConsolePlus::UpdateNode()
{
	for (auto node : scene.GetAllNodes())
	{
		node->SetPosition(0, node->GetPositionY() - (node->GetSize().rightBottom.y - node->GetSize().leftTop.y));
	}
}

Pixel::ConsolePlus::Output::Output(ConsolePlus* console) :
	console(console)
{
}

Pixel::ConsolePlus::Output& Pixel::ConsolePlus::Output::operator<<(std::string text)
{
	console->Print(text);
	return *this;
}
