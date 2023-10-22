#include "PScene.h"

void Pixel::Scene::AddNode(Node* node)
{
	allNodes.push_back(node);
}

void Pixel::Scene::RemoveNode(Node* node)
{
	if (allNodes.empty()) return;
	for (std::vector<Node*>::const_iterator iter = allNodes.begin(); iter != allNodes.end(); iter++)
	{
		if (*iter == node)
		{
			allNodes.erase(iter);
		}
	}
}

void Pixel::Scene::ClearNode()
{
	allNodes.clear();
}

void Pixel::Scene::SetBackground(Color background)
{
	this->background = background;
}

void Pixel::Scene::SetBackground(int r, int g, int b)
{
	background(r, g, b);
}

void Pixel::Scene::SetBackground(int r, int g, int b, int a)
{
	background(r, g, b, a);
}

Pixel::Color Pixel::Scene::GetBackground() const
{
	return background;
}

void Pixel::Scene::Render(Renderer* renderer)
{
	for (auto node : allNodes)
		node->Render(renderer);
}
