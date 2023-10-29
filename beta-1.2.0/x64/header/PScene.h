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
	public:
		// 设置背景颜色
		void SetBackground(Color background);
		// 设置背景颜色
		void SetBackground(int r, int g, int b);
		// 设置背景颜色
		void SetBackground(int r, int g, int b, int a);
	public:
		Color GetBackground() const;
	protected:
		std::vector<Node*> allNodes;
		Color background = Color::White;
	protected:
		void Render(Renderer* renderer);
	};
}