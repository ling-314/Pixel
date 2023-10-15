#pragma once
#include <vector>
#include <string>
#include "PType.h"
#include "PRenderer.h"

namespace Pixel
{
	class Node
	{
		friend class Scene;
	public:
		Node(int x, int y);
		// 添加子节点
		void AddChild(Node* node);
		// 移除子节点
		void RemoveChild(Node* node);
		// 移除所有子节点
		void ClearChild();
		virtual void Render(Renderer* renderer);
	public:
		// 获取坐标
		Point GetPosition() const;
		// 获取X坐标
		int GetPositionX() const;
		// 获取Y坐标
		int GetPositionY() const;
		// 获取缩放大小
		float GetScale() const;
		// 获取碰撞箱
		CollisionBox GetCollisionBox() const;
	public:
		// 设置坐标
		virtual void SetPosition(Point position);
		// 设置坐标
		virtual void SetPosition(int x, int y);
		// 设置X坐标
		virtual void SetPositionX(int x);
		// 设置Y坐标
		virtual void SetPositionY(int y);
		// 设置缩放
		void SetScale(float scale);
		// 设置碰撞箱
		void SetCollisionBox(Point leftTop, Point rightBottom);
		// 设置碰撞箱
		void SetCollisionBox(Size size);
	protected:
		Point position;
		float scale;
		std::vector<Node*> children;
		Size size;
		CollisionBox collisionBox;
	};

	using Container = Node;

	class Graphic :
		public Node
	{
	public:
		Graphic(int x, int y);
	public:
		// 获取颜色
		Color GetColor() const;
		// 是否填充
		bool IsFill() const;
	public:
		// 设置颜色
		void SetColor(Color color);
		// 设置颜色
		void SetColor(int r, int g, int b);
		// 设置颜色
		void SetColor(int r, int g, int b, int a);
		// 设置填充
		void SetFill(bool fill);
	protected:
		Color color = { 0, 0, 0, 255 };
		bool fill = false;
	};

	class Ellipse :
		public Graphic
	{
	public:
		Ellipse(int x, int y, int radiusX, int radiusY);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取X半径
		int GetRadiusX() const;
		// 获取Y半径
		int GetRadiusY() const;
	public:
		// 设置坐标
		virtual void SetPosition(Point position) override;
		// 设置坐标
		virtual void SetPosition(int x, int y) override;
		// 设置X坐标
		virtual void SetPositionX(int x) override;
		// 设置Y坐标
		virtual void SetPositionY(int y) override;
		// 设置X半径
		void SetRadiusX(int radiusX);
		// 设置Y半径
		void SetRadiusY(int radiusY);
	protected:
		int radiusY;
		int radiusX;
	};

	class Rectangle :
		public Graphic
	{
	public:
		Rectangle(int x, int y, int width, int height);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取宽度
		int GetWidth() const;
		// 获取高度
		int GetHeight() const;
	public:
		// 设置坐标
		virtual void SetPosition(Point position) override;
		// 设置坐标
		virtual void SetPosition(int x, int y) override;
		// 设置X坐标
		virtual void SetPositionX(int x) override;
		// 设置Y坐标
		virtual void SetPositionY(int y) override;
		// 设置宽度
		void SetWidth(int width);
		// 设置高度
		void SetHeight(int height);
	protected:
		int width;
		int height;
	};

	class Line :
		public Graphic
	{
	public:
		Line(int vertex1x, int vertex1y, int vertex2x, int vertex2y);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取顶点1坐标
		Point GetVertex1() const;
		// 获取顶点2坐标
		Point GetVertex2() const;
		// 获取顶点1X坐标
		int GetVertex1X() const;
		// 获取顶点1Y坐标
		int GetVertex1Y() const;
		// 获取顶点2X坐标
		int GetVertex2X() const;
		// 获取顶点2Y坐标
		int GetVertex2Y() const;
	public:
		// 设置顶点1坐标
		void SetVertex1(Point point);
		// 设置顶点2坐标
		void SetVertex2(Point point);
		// 设置顶点1X坐标
		void SetVertex1X(int x);
		// 设置顶点1Y坐标
		void SetVertex1Y(int y);
		// 设置顶点2X坐标
		void SetVertex2X(int x);
		// 设置顶点2Y坐标
		void SetVertex2Y(int y);
		// 设置坐标
		virtual void SetPosition(Point position) override;
		// 设置坐标
		virtual void SetPosition(int x, int y) override;
		// 设置X坐标
		virtual void SetPositionX(int x) override;
		// 设置Y坐标
		virtual void SetPositionY(int y) override;
	protected:
		Point vertex1;
		Point vertex2;
	};

	class Sprite :
		public Node
	{
	public:
		Sprite(int x, int y, std::wstring path);
		~Sprite();
		virtual void Render(Renderer* renderer) override;
	public:
		std::wstring GetPath() const;
	public:
		void SetPath(std::wstring path);
	protected:
		std::wstring path;
		IWICFormatConverter* pConverter = nullptr;
	};

	class Text :
		public Node
	{
	public:
		Text(int x, int y, std::wstring text);
		~Text();
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取文本内容
		std::wstring GetText() const;
		// 获取字体名
		std::wstring GetFontName() const;
		// 获取字号
		int GetFontSize() const;
		// 获取颜色
		Color GetColor();
	public:
		// 设置文本内容
		void SetText(std::wstring text);
		// 设置字体名
		void SetFontName(std::wstring fontName);
		// 设置字号
		void SetFontSize(int fontSize);
		// 设置颜色
		void SetColor(Color color);
	protected:
		std::wstring text;
		std::wstring fontName;
		int fontSize;
		Color color;
		IDWriteTextLayout* pTextLayout = nullptr;
	protected:
		void Create();
	};
}