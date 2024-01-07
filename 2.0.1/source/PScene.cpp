#include "PScene.h"

void Pixel::Scene::AddNode(Node* node)
{
	_allNodes.push_back(node);
}

void Pixel::Scene::RemoveNode(Node* node)
{
	if (_allNodes.empty()) return;
	for (std::vector<Node*>::const_iterator iter = _allNodes.begin(); iter != _allNodes.end(); iter++)
	{
		if (*iter == node)
		{
			_allNodes.erase(iter);
		}
	}
}

void Pixel::Scene::ClearNode()
{
	_allNodes.clear();
}

void Pixel::Scene::Update()
{
	for (auto node : _allNodes) node->Update();
}

void Pixel::Scene::SetBackground(Color background)
{
	this->_background = background;
}

Pixel::Color Pixel::Scene::GetBackground() const
{
	return _background;
}

std::vector<Pixel::Node*> Pixel::Scene::GetAllNodes() const
{
	return _allNodes;
}

void Pixel::Scene::_Render(Renderer* renderer)
{
	for (auto node : _allNodes)
		node->_Render(renderer);
}
