#pragma once
#include <vector>
#include <initializer_list>
#include <d2d1.h>
#include <dwrite.h>
#include <math.h>
#include <wincodec.h>
#include <algorithm>
#include "PRenderer.hpp"
#include "PEvent.hpp"

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
		Node(Point position);
		// 渲染（自己）
		// 重载这个函数，自定义渲染方式
		virtual void RenderSelf(Renderer* renderer);
		// 重载这个函数，每帧都执行
		virtual void Update();
		// 渲染
		void Render(Renderer* renderer);
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
		// 拷贝属性
		void Copy(const Node& node);
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
		// 获取图层顺序
		int GetLayer() const;
		// 获取父节点
		Node* GetParent();
		// 获取所在场景
		Scene* Where();
		// 获取所有子节点
		std::vector<Node*> GetChildren();
		// 获取二维矩阵
		D2D1::Matrix3x2F GetTransform() const;
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
		// 非等比缩放会影响碰撞检测
		void ScaleX(float x);
		// 缩放X至
		// 非等比缩放会影响碰撞检测
		void ScaleXTo(float x);
		// 缩放Y
		// 非等比缩放会影响碰撞检测
		void ScaleY(float y);
		// 缩放Y至
		// 非等比缩放会影响碰撞检测
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
		// 倾斜X
		void Skew(float x, float y);
		// 倾斜X
		void SkewX(float x);
		// 倾斜Y
		void SkewY(float y);
		// 设置图层顺序
		void SetLayer(int layer);
		// 上移一个图层
		void MoveUpALayer();
		// 下移一个图层
		void MoveDownALayer();
	private:
		Point				_position;
		Vector2				_offset;
		bool				_visible;
		Vector2				_scale;
		float				_angle;
		Vector2				_skew;
		Size				_size;
		int					_layer;
		Node*				_parent;
		Scene*				_where;
		std::vector<Node*>	_children;
		D2D1::Matrix3x2F	_transform;
	protected:
		void _SetSize(Size size);
		// 重载这个函数，重新计算大小，应在每个构造函数中调用一次
		virtual void _ResetSize();
		void _SetTransfrom();
		// 重载这个函数，处理消息
		virtual void _Handle(const Event& event);
	};

	class Container :
		public Node
	{
	public:
		virtual void RenderSelf(Renderer* renderer) override;
	};

	class Window;
	// 场景
	class Scene
	{
		friend Window;
	public:
		Scene();
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
		// 排序节点
		void SortNodes();
		// 没有节点
		bool IsEmpty() const;
	protected:
		// 重载这个函数，当进入场景时执行
		virtual void OnEnter();
		// 重载这个函数，当退出场景时执行
		virtual void OnExit();
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
		// 分发消息
		void _Dispatch(const Event& event);
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
		// 获取颜色
		Color GetColor() const;
		// 获取填充
		bool IsFill() const;
		// 获取描边粗细
		float GetStrokeWidth() const;
	public:
		// 设置图形属性
		void SetAttr(GraphicAttribute attr);
		// 设置颜色
		void SetColor(Color color);
		// 设置填充
		void SetFill(bool fill);
		// 设置描边粗细
		void SetStrokeWidth(float strokeWidth);
	private:
		GraphicAttribute _attr;
	};

	class EllipseBase :
		public Graphic
	{
	public:
		EllipseBase();
		EllipseBase(float x, float y);
		EllipseBase(float radius);
		EllipseBase(float x, float y, float radius);
	public:
		// 获取 X 半径
		float GetRadiusX() const;
		// 获取 Y 半径
		float GetRadiusY() const;
	public:
		// 设置半径
		void SetRadius(float radius);
	protected:
		virtual void _ResetSize() override;
	protected:
		float _radiusX;
		float _radiusY;
	};

	class Ellipse :
		public EllipseBase
	{
	public:
		Ellipse();
		Ellipse(float radiusX, float radiusY);
		Ellipse(float x, float y, float radiusX, float radiusY);
		virtual void RenderSelf(Renderer* renderer) override;
	public:
		// 设置 X 半径
		void SetRadiusX(float radiusX);
		// 设置 Y 半径
		void SetRadiusY(float radiusY);
	};

	class Circle :
		public EllipseBase
	{
	public:
		Circle();
		Circle(float radius);
		Circle(float x, float y, float radius);
		virtual void RenderSelf(Renderer* renderer) override;
	public:
		// 获取半径
		float GetRadius() const;
	};

	class PolygonBase :
		public Graphic
	{
	public:
		PolygonBase();
	public:
		// 获取顶点
		virtual std::vector<Point> GetVertices() const = 0;
		// 获取顶点数量
		size_t GetVertexCount() const { return GetVertices().size(); }
	};

	class Rectangle :
		public PolygonBase
	{
	public:
		Rectangle();
		Rectangle(float x, float y, float width, float height);
		virtual void RenderSelf(Renderer* renderer) override;
	public:
		// 获取宽度
		float GetWidth() const;
		// 获取高度
		float GetHeight() const;
		// 获取顶点
		std::vector<Point> GetVertices() const override;
	public:
		// 设置宽度
		void SetWidth(float width);
		// 设置高度
		void SetHeight(float height);
	protected:
		virtual void _ResetSize() override;
	private:
		float _width;
		float _height;
	};

	class Polygon :
		public PolygonBase
	{
	public:
		Polygon();
		Polygon(std::vector<Point> vertices);
		Polygon(std::initializer_list<Point> vertices);
		virtual void RenderSelf(Renderer* renderer) override;
	public:
		// 获取顶点
		std::vector<Point> GetVertices() const override;
	public:
		// 设置顶点
		void SetVertices(std::vector<Point> vertices);
		// 设置顶点
		void SetVertices(std::initializer_list<Point> vertices);
		// 添加顶点
		void AddVertex(Point vertex);
		// 添加顶点
		void AddVertices(std::initializer_list<Point> vertices);
		// 移除顶点
		void RemoveVertex(Point vertex);
		// 移除顶点
		void RemoveVertices(std::initializer_list<Point> vertices);
		// 清空顶点
		void ClearVertices();
	protected:
		virtual void _ResetSize() override;
	private:
		std::vector<Point> _vertices;
		ID2D1PathGeometry* _pPathGeometry;
	private:
		void _Create();
	};

	// 线段
	class Line :
		public Graphic
	{
	public:
		Line();
		Line(float vertex1X, float vertex1Y, float vertex2X, float vertex2Y);
		Line(Point vertex1, Point vertex2);
		virtual void RenderSelf(Renderer* renderer) override;
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
		virtual void _ResetSize() override;
	private:
		Point _vertex1;
		Point _vertex2;
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
		virtual void RenderSelf(Renderer* renderer) override;
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
		Sprite(int resourceID, std::string resourceType, HMODULE resourceModule);
		Sprite(float x, float y, int resourceID, std::string resourceType, HMODULE resourceModule);
		virtual void RenderSelf(Renderer* renderer) override;
		// 裁剪
		void Crop(Size size);
		// 销毁资源
		static void Destroy();
	public:
		// 获取图像路径
		std::string GetPath() const;
		// 获取图片资源ID
		int GetResourceID() const;
		// 获取图片类型（后缀名）
		std::string GetResourceType() const;
		// 获取IWICFormatConverter
		IWICFormatConverter* GetIWICFormatConverter();
	public:
		// 设置图像路径
		void SetPath(std::string path);
		// 设置图片资源ID
		void SetResourceID(int resourceID);
		// 设置图片类型（后缀名）
		void SetResourceType(std::string resourceType);
	protected:
		virtual void _ResetSize() override;
	private:
		std::string					_path;
		Resource					_resource;
		std::string					_resourceType;
		IWICFormatConverter*		_pConverter;
		Size						_cropping;
		static IWICImagingFactory* s_pFactory;
	private:
		void _Create();
	};

	// 按钮
	class Button :
		public Node
	{
	public:
		Button();
		Button(Node* normal, Node* stay = nullptr, Node* press = nullptr);
		virtual void RenderSelf(Renderer* renderer) override;
		// 按钮状态
		enum ButtonType
		{
			Normal,
			Stay,
			Press
		};
	public:
		// 获取默认样式
		Node* GetNormal();
		// 获取鼠标停留样式
		Node* GetStay();
		// 获取按下样式
		Node* GetPress();
	public:
		// 设置默认样式
		void SetNormal(Node* normal);
		// 设置鼠标停留样式
		void SetStay(Node* stay);
		// 设置按下样式
		void SetPress(Node* press);
	protected:
		virtual void _ResetSize();
	private:
		Node*		_normal;
		Node*		_stay;
		Node*		_press;
		ButtonType	_type;
	protected:
		virtual void _Handle(const Event& event) override;
	};
}