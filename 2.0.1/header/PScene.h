#pragma once
#include <string>
#include <vector>
#include "PNode.h"

namespace Pixel
{
	class Scene
	{
		friend class Window;
	public:
		// 添加节点
		void AddNode(Node* node);
		// 移除节点
		void RemoveNode(Node* node);
		// 清空节点
		void ClearNode();
		// 更新
		void Update();
	public:
		// 设置背景颜色
		void SetBackground(Color background);
	public:
		// 获取背景颜色
		Color GetBackground() const;
		// 获取所有节点
		std::vector<Node*> GetAllNodes() const;
	protected:
		std::vector<Node*>	_allNodes;
		Color				_background = Color::White;
	protected:
		void _Render(Renderer* renderer);
	};
}