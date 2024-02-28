#pragma once
#include <vector>
#include <initializer_list>
#include <d2d1.h>
#include <dwrite.h>
#include <math.h>
#include <wincodec.h>
#include "PRenderer.hpp"

namespace Pixel
{
	class Scene;
	// 节点
	class Node
	{
		friend Scene;
	public:
		Node();
		Node(float x, float y);
		// 渲染
		// 重载这个函数，自定义渲染方式
		virtual void Render(Renderer* renderer);
		// 重载这个函数，每帧都执行
		virtual void Update();
		// 显示
		void Show();
		// 隐藏
		void Hide();
		// 添加子节点
		void AddChild(Node* target);
		// 添加子节点
		void AddChilds(std::initializer_list<Node*> targets);
		// 移除子节点
		void RemoveChild(Node* child);
		// 移除子节点
		void RemoveChilds(std::initializer_list<Node*> children);
		// 清空子节点
		void ClearChildren();
	public:
		// 获取坐标
		Point GetPosition() const;
		// 获取X坐标
		float GetPositionX() const;
		// 获取Y坐标
		float GetPositionY() const;
		// 获取偏移
		Vector2 GetOffset() const;
		// 获取X偏移
		float GetOffsetX() const;
		// 获取Y偏移
		float GetOffsetY() const;
		// 获取渲染坐标
		Point GetRenderPosition() const;
		// 获取渲染X坐标
		float GetRenderPositionX() const;
		// 获取渲染Y坐标
		float GetRenderPositionY() const;
		// 是否显示
		bool IsVisible() const;
		// 获取缩放大小
		Vector2 GetScale() const;
		// 获取旋转角度
		float GetAngle() const;
		// 获取大小
		Size GetSize() const;
		// 获取父节点
		Node* GetParent();
		// 获取所在场景
		Scene* Where();
		// 获取所有子节点
		std::vector<Node*> GetChildren();
		// 获取二维矩阵
		D2D1::Matrix3x2F GetTransform();
	public:
		// 设置坐标
		void SetPosition(Point position);
		// 设置坐标
		void SetPosition(float x, float y);
		// 设置X坐标
		void SetPositionX(float x);
		// 设置Y坐标
		void SetPositionY(float y);
		// 设置偏移
		void SetOffset(Vector2 offset);
		// 设置偏移
		void SetOffset(float x, float y);
		// 设置X偏移
		void SetOffsetX(float x);
		// 设置Y偏移
		void SetOffsetY(float y);
	public:
		// 缩放
		void Scale(Vector2 scale);
		// 缩放至
		void ScaleTo(Vector2 scale);
		// 缩放X
		void ScaleX(float x);
		// 缩放X至
		void ScaleXTo(float x);
		// 缩放Y
		void ScaleY(float y);
		// 缩放Y至
		void ScaleYTo(float y);
		// X翻转
		void FlipX();
		// Y翻转
		void FlipY();
		// 旋转
		void Rotate(float angle);
		// 转向
		void RotateTo(float angle);
		// 移动（受旋转方向影响）
		void Move(float step);
		// 移动（不受旋转方向影响）
		void Move(Vector2 vector);
		// 向X移动
		void MoveX(float step);
		// 向Y移动
		void MoveY(float step);
	private:
		Point				_position;
		Vector2				_offset;
		bool				_visible;
		Vector2				_scale;
		float				_angle;
		Size				_size;
		Node*				_parent;
		Scene*				_where;
		std::vector<Node*>	_children;
		D2D1::Matrix3x2F	_transform;
	protected:
		void _SetSize(Size size);
		// 重载这个函数，重新计算大小
		virtual void _ResetSize();
		void _SetTransfrom();
	private:
		void _Render(Renderer* renderer);
	};

	using Container = Node;

	class Window;
	// 场景
	class Scene
	{
		friend Window;
	public:
		Scene(const Scene& scene);
		// 添加节点
		void AddNode(Node* target);
		// //添加节点
		void AddNodes(std::initializer_list<Node*> targets);
		// 移除节点
		void RemoveNode(Node* child);
		// 移除节点
		void RemoveNodes(std::initializer_list<Node*> children);
		// 清空节点
		void ClearNodes();
		// 清空并删除节点
		void ClearAndDeleteNodes();
		// 没有节点
		bool NoNodes();
	public:
		// 获取所有节点
		std::vector<Node*> GetNodes();
		// 获取背景颜色
		Color GetBackground() const;
		// 获取进入自己的窗口
		Window* GetEntered();
	public:
		// 设置背景颜色
		void SetBackground(Color color);
	private:
		std::vector<Node*>	_nodes;
		Color				_background;
		Window*				_entered;
	private:
		void _Render(Renderer* renderer);
		void _Update();
	};

	// 图形
	class Graphic :
		public Node
	{
	public:
		Graphic();
		Graphic(float x, float y);
	public:
		// 获取图形属性
		GraphicAttribute GetAttr() const;
	public:
		// 设置图形属性
		void SetAttr(GraphicAttribute attr);
	private:
		GraphicAttribute _attr;
	};

	// 椭圆
	class Ellipse :
		public Graphic
	{
	public:
		Ellipse();
		Ellipse(float x, float y, float radiusX, float radiusY);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取X半径
		float GetRadiusX() const;
		// 获取Y半径
		float GetRadiusY() const;
	public:
		// 设置X半径
		void SetRadiusX(float radiusX);
		// 设置Y半径
		void SetRadiusY(float radiusY);
	protected:
		virtual void _ResetSize() override;
	private:
		float _radiusX;
		float _radiusY;
	};

	// 圆角矩形
	class Rectangle :
		public Graphic
	{
	public:
		Rectangle();
		Rectangle(float x, float y, float width, float height);
		Rectangle(float x, float y, float width, float height, float radiusX, float radiusY);
		Rectangle(Size size);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取宽度
		float GetWidth() const;
		// 获取高度
		float GetHeight() const;
		// 获取圆角X半径
		float GetRadiusX() const;
		// 获取圆角Y半径
		float GetRadiusY() const;
	public:
		// 设置宽度
		void SetWidth(float width);
		// 设置高度
		void SetHeight(float height);
		// 设置圆角X半径
		void SetRadiusX(float radiusX);
		// 设置圆角X半径
		void SetRadiusY(float radiusY);
	protected:
		virtual void _ResetSize() override;
	private:
		float _width;
		float _height;
		float _radiusX;
		float _radiusY;
	};

	// 线段
	class Line :
		public Graphic
	{
	public:
		Line();
		Line(float vertex1X, float vertex1Y, float vertex2X, float vertex2Y);
		Line(Point vertex1, Point vertex2);
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取顶点1坐标
		Point GetVertex1() const;
		// 获取顶点1的X坐标
		float GetVertex1X() const;
		// 获取顶点1的Y坐标
		float GetVertex1Y() const;
		// 获取顶点2
		Point GetVertex2() const;
		// 获取顶点2的X坐标
		float GetVertex2X() const;
		// 获取顶点2的Y坐标
		float GetVertex2Y() const;
	public:
		// 设置顶点1坐标
		void SetVertex1(Point position);
		// 设置顶点1坐标
		void SetVertex1(float x, float y);
		// 设置顶点1的X坐标
		void SetVertex1X(float x);
		// 设置顶点1的Y坐标
		void SetVertex1Y(float y);
		// 设置顶点2坐标
		void SetVertex2(Point position);
		// 设置顶点2坐标
		void SetVertex2(float x, float y);
		// 设置顶点2的X坐标
		void SetVertex2X(float x);
		// 设置顶点2的Y坐标
		void SetVertex2Y(float y);
	protected:
		virtual void _ResetSize();
	private:
		Point _vertex1;
		Point _vertex2;
	};

	// 多边形
	class Polygon :
		public Graphic
	{
	public:
		Polygon();
		Polygon(std::vector<Point> vertexes);
		~Polygon();
		virtual void Render(Renderer* renderer) override;
	public:
		// 获取顶点
		std::vector<Point> GetVertexex() const;
	public:
		// 设置顶点
		void SetVertexex(std::vector<Point> vertexes);
	protected:
		virtual void _ResetSize() override;
	private:
		std::vector<Point> _vertexes;
		ID2D1PathGeometry* _pPathGeometry;
	};

	// 文本
	class Text :
		public Node
	{
	public:
		Text();
		Text(float x, float y);
		Text(std::string text);
		Text(float x, float y, std::string text, std::string fontName = "黑体", float fontSize = 16);
		~Text();
		virtual void Render(Renderer* renderer) override;
		// 销毁资源
		static void Destroy();
	public:
		// 获取文本
		std::string GetText() const;
		// 获取字体名
		std::string GetFontName() const;
		// 获取字号
		float GetFontSize() const;
		// 获取文本颜色
		Color GetColor() const;
		// 获取字体粗细
		DWRITE_FONT_WEIGHT GetWeight() const;
		// 获取字体样式
		DWRITE_FONT_STYLE GetStyle() const;
		// 获取IDWriteTextLayout
		IDWriteTextLayout* GetIDWriteTextLayout();
	public:
		// 设置文本
		void SetText(std::string text);
		// 设置字体
		void SetFontName(std::string fontName);
		// 设置字号
		void SetFontSize(float fontSize);
		// 设置颜色
		void SetColor(Color color);
		// 设置字体粗细
		// [1 ~ 999] 之间的整数
		void SetWeight(DWRITE_FONT_WEIGHT weight);
		// 设置字体样式
		void SetStyle(DWRITE_FONT_STYLE style);
	protected:
		virtual void _ResetSize() override;
	private:
		std::string			_text;
		std::string			_fontName;
		float				_fontSize;
		Color				_color;
		DWRITE_FONT_WEIGHT	_weight;
		DWRITE_FONT_STYLE	_style;
		IDWriteTextLayout*	_pTextLayout;
		static IDWriteFactory* s_pFactory;
	private:
		void _Create();
	};

	// 精灵
	class Sprite :
		public Node
	{
	public:
		Sprite();
		Sprite(float x, float y);
		Sprite(std::string path);
		Sprite(float x, float y, std::string path);
		Sprite(int resourceName, std::string resourceType);
		Sprite(float x, float y, int resourceName, std::string resourceType);
		virtual void Render(Renderer* renderer) override;
		// 销毁资源
		static void Destroy();
	public:
		// 获取图像路径
		std::string GetPath() const;
		// 获取图片资源ID
		int GetResourceName() const;
		// 获取图片类型（后缀名）
		std::string GetResourceType() const;
		// 获取IWICFormatConverter
		IWICFormatConverter* GetIWICFormatConverter();
	public:
		// 设置图像路径
		void SetPath(std::string path);
		// 设置图片资源ID
		void SetResourceName(int resourceName);
		// 设置图片类型（后缀名）
		void SetResourceType(std::string resourceType);
	protected:
		virtual void _ResetSize() override;
	private:
		std::string					_path;
		int							_resourceName;
		std::string					_resourceType;
		IWICFormatConverter*		_pConverter;
		static IWICImagingFactory* s_pFactory;
	private:
		void _Create();
	};
}