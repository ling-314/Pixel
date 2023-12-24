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

void Pixel::Scene::Update()
{
	for (auto node : allNodes) node->Update();
}

void Pixel::Scene::SetBackground(Color background)
{
	this->background = background;
}

Pixel::Color Pixel::Scene::GetBackground() const
{
	return background;
}

std::vector<Pixel::Node*> Pixel::Scene::GetAllNodes() const
{
	return allNodes;
}

void Pixel::Scene::Render(Renderer* renderer)
{
	for (auto node : allNodes)
		node->Render(renderer);
}
