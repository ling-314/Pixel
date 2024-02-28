#include "PNode.hpp"

Pixel::Scene::Scene(const Scene& scene) :
	_background(scene._background)
{
}

void Pixel::Scene::AddNode(Node* target)
{
	if (!target->Where())
	{
		_nodes.push_back(target);
		target->_where = this;
	}
}

void Pixel::Scene::AddNodes(std::initializer_list<Node*> targets)
{
	for (auto target : targets) AddNode(target);
}

void Pixel::Scene::RemoveNode(Node* child)
{
	if (child->Where() == this)
	{
		_nodes.erase(std::find(_nodes.begin(), _nodes.end(), child));
		child->_where = nullptr;
	}
}

void Pixel::Scene::RemoveNodes(std::initializer_list<Node*> children)
{
	for (auto child : children) RemoveNode(child);
}

void Pixel::Scene::ClearNodes()
{
	for (auto node : _nodes) node->_where = nullptr;
	_nodes.clear();
}

void Pixel::Scene::ClearAndDeleteNodes()
{
	for (auto node : _nodes) delete node;
	ClearNodes();
}

bool Pixel::Scene::NoNodes()
{
	return _nodes.empty();
}

std::vector<Pixel::Node*> Pixel::Scene::GetNodes()
{
	return _nodes;
}

Pixel::Color Pixel::Scene::GetBackground() const
{
	return _background;
}

Pixel::Window* Pixel::Scene::GetEntered()
{
	return _entered;
}

void Pixel::Scene::SetBackground(Color color)
{
	_background = color;
}

void Pixel::Scene::_Render(Renderer* renderer)
{
	for (auto node : _nodes) node->_Render(renderer);
}

void Pixel::Scene::_Update()
{
	for (auto node : _nodes) node->Update();
}
