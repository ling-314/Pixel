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
	// �ڵ�
	class Node
	{
		friend Scene;
	public:
		Node();
		Node(float x, float y);
		// ��Ⱦ
		// ��������������Զ�����Ⱦ��ʽ
		virtual void Render(Renderer* renderer);
		// �������������ÿ֡��ִ��
		virtual void Update();
		// ��ʾ
		void Show();
		// ����
		void Hide();
		// ����ӽڵ�
		void AddChild(Node* target);
		// ����ӽڵ�
		void AddChilds(std::initializer_list<Node*> targets);
		// �Ƴ��ӽڵ�
		void RemoveChild(Node* child);
		// �Ƴ��ӽڵ�
		void RemoveChilds(std::initializer_list<Node*> children);
		// ����ӽڵ�
		void ClearChildren();
	public:
		// ��ȡ����
		Point GetPosition() const;
		// ��ȡX����
		float GetPositionX() const;
		// ��ȡY����
		float GetPositionY() const;
		// ��ȡƫ��
		Vector2 GetOffset() const;
		// ��ȡXƫ��
		float GetOffsetX() const;
		// ��ȡYƫ��
		float GetOffsetY() const;
		// ��ȡ��Ⱦ����
		Point GetRenderPosition() const;
		// ��ȡ��ȾX����
		float GetRenderPositionX() const;
		// ��ȡ��ȾY����
		float GetRenderPositionY() const;
		// �Ƿ���ʾ
		bool IsVisible() const;
		// ��ȡ���Ŵ�С
		Vector2 GetScale() const;
		// ��ȡ��ת�Ƕ�
		float GetAngle() const;
		// ��ȡ��С
		Size GetSize() const;
		// ��ȡ���ڵ�
		Node* GetParent();
		// ��ȡ���ڳ���
		Scene* Where();
		// ��ȡ�����ӽڵ�
		std::vector<Node*> GetChildren();
		// ��ȡ��ά����
		D2D1::Matrix3x2F GetTransform();
	public:
		// ��������
		void SetPosition(Point position);
		// ��������
		void SetPosition(float x, float y);
		// ����X����
		void SetPositionX(float x);
		// ����Y����
		void SetPositionY(float y);
		// ����ƫ��
		void SetOffset(Vector2 offset);
		// ����ƫ��
		void SetOffset(float x, float y);
		// ����Xƫ��
		void SetOffsetX(float x);
		// ����Yƫ��
		void SetOffsetY(float y);
	public:
		// ����
		void Scale(Vector2 scale);
		// ������
		void ScaleTo(Vector2 scale);
		// ����X
		void ScaleX(float x);
		// ����X��
		void ScaleXTo(float x);
		// ����Y
		void ScaleY(float y);
		// ����Y��
		void ScaleYTo(float y);
		// X��ת
		void FlipX();
		// Y��ת
		void FlipY();
		// ��ת
		void Rotate(float angle);
		// ת��
		void RotateTo(float angle);
		// �ƶ�������ת����Ӱ�죩
		void Move(float step);
		// �ƶ���������ת����Ӱ�죩
		void Move(Vector2 vector);
		// ��X�ƶ�
		void MoveX(float step);
		// ��Y�ƶ�
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
		// ����������������¼����С
		virtual void _ResetSize();
		void _SetTransfrom();
	private:
		void _Render(Renderer* renderer);
	};

	using Container = Node;

	class Window;
	// ����
	class Scene
	{
		friend Window;
	public:
		Scene(const Scene& scene);
		// ��ӽڵ�
		void AddNode(Node* target);
		// //��ӽڵ�
		void AddNodes(std::initializer_list<Node*> targets);
		// �Ƴ��ڵ�
		void RemoveNode(Node* child);
		// �Ƴ��ڵ�
		void RemoveNodes(std::initializer_list<Node*> children);
		// ��սڵ�
		void ClearNodes();
		// ��ղ�ɾ���ڵ�
		void ClearAndDeleteNodes();
		// û�нڵ�
		bool NoNodes();
	public:
		// ��ȡ���нڵ�
		std::vector<Node*> GetNodes();
		// ��ȡ������ɫ
		Color GetBackground() const;
		// ��ȡ�����Լ��Ĵ���
		Window* GetEntered();
	public:
		// ���ñ�����ɫ
		void SetBackground(Color color);
	private:
		std::vector<Node*>	_nodes;
		Color				_background;
		Window*				_entered;
	private:
		void _Render(Renderer* renderer);
		void _Update();
	};

	// ͼ��
	class Graphic :
		public Node
	{
	public:
		Graphic();
		Graphic(float x, float y);
	public:
		// ��ȡͼ������
		GraphicAttribute GetAttr() const;
	public:
		// ����ͼ������
		void SetAttr(GraphicAttribute attr);
	private:
		GraphicAttribute _attr;
	};

	// ��Բ
	class Ellipse :
		public Graphic
	{
	public:
		Ellipse();
		Ellipse(float x, float y, float radiusX, float radiusY);
		virtual void Render(Renderer* renderer) override;
	public:
		// ��ȡX�뾶
		float GetRadiusX() const;
		// ��ȡY�뾶
		float GetRadiusY() const;
	public:
		// ����X�뾶
		void SetRadiusX(float radiusX);
		// ����Y�뾶
		void SetRadiusY(float radiusY);
	protected:
		virtual void _ResetSize() override;
	private:
		float _radiusX;
		float _radiusY;
	};

	// Բ�Ǿ���
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
		// ��ȡ���
		float GetWidth() const;
		// ��ȡ�߶�
		float GetHeight() const;
		// ��ȡԲ��X�뾶
		float GetRadiusX() const;
		// ��ȡԲ��Y�뾶
		float GetRadiusY() const;
	public:
		// ���ÿ��
		void SetWidth(float width);
		// ���ø߶�
		void SetHeight(float height);
		// ����Բ��X�뾶
		void SetRadiusX(float radiusX);
		// ����Բ��X�뾶
		void SetRadiusY(float radiusY);
	protected:
		virtual void _ResetSize() override;
	private:
		float _width;
		float _height;
		float _radiusX;
		float _radiusY;
	};

	// �߶�
	class Line :
		public Graphic
	{
	public:
		Line();
		Line(float vertex1X, float vertex1Y, float vertex2X, float vertex2Y);
		Line(Point vertex1, Point vertex2);
		virtual void Render(Renderer* renderer) override;
	public:
		// ��ȡ����1����
		Point GetVertex1() const;
		// ��ȡ����1��X����
		float GetVertex1X() const;
		// ��ȡ����1��Y����
		float GetVertex1Y() const;
		// ��ȡ����2
		Point GetVertex2() const;
		// ��ȡ����2��X����
		float GetVertex2X() const;
		// ��ȡ����2��Y����
		float GetVertex2Y() const;
	public:
		// ���ö���1����
		void SetVertex1(Point position);
		// ���ö���1����
		void SetVertex1(float x, float y);
		// ���ö���1��X����
		void SetVertex1X(float x);
		// ���ö���1��Y����
		void SetVertex1Y(float y);
		// ���ö���2����
		void SetVertex2(Point position);
		// ���ö���2����
		void SetVertex2(float x, float y);
		// ���ö���2��X����
		void SetVertex2X(float x);
		// ���ö���2��Y����
		void SetVertex2Y(float y);
	protected:
		virtual void _ResetSize();
	private:
		Point _vertex1;
		Point _vertex2;
	};

	// �����
	class Polygon :
		public Graphic
	{
	public:
		Polygon();
		Polygon(std::vector<Point> vertexes);
		~Polygon();
		virtual void Render(Renderer* renderer) override;
	public:
		// ��ȡ����
		std::vector<Point> GetVertexex() const;
	public:
		// ���ö���
		void SetVertexex(std::vector<Point> vertexes);
	protected:
		virtual void _ResetSize() override;
	private:
		std::vector<Point> _vertexes;
		ID2D1PathGeometry* _pPathGeometry;
	};

	// �ı�
	class Text :
		public Node
	{
	public:
		Text();
		Text(float x, float y);
		Text(std::string text);
		Text(float x, float y, std::string text, std::string fontName = "����", float fontSize = 16);
		~Text();
		virtual void Render(Renderer* renderer) override;
		// ������Դ
		static void Destroy();
	public:
		// ��ȡ�ı�
		std::string GetText() const;
		// ��ȡ������
		std::string GetFontName() const;
		// ��ȡ�ֺ�
		float GetFontSize() const;
		// ��ȡ�ı���ɫ
		Color GetColor() const;
		// ��ȡ�����ϸ
		DWRITE_FONT_WEIGHT GetWeight() const;
		// ��ȡ������ʽ
		DWRITE_FONT_STYLE GetStyle() const;
		// ��ȡIDWriteTextLayout
		IDWriteTextLayout* GetIDWriteTextLayout();
	public:
		// �����ı�
		void SetText(std::string text);
		// ��������
		void SetFontName(std::string fontName);
		// �����ֺ�
		void SetFontSize(float fontSize);
		// ������ɫ
		void SetColor(Color color);
		// ���������ϸ
		// [1 ~ 999] ֮�������
		void SetWeight(DWRITE_FONT_WEIGHT weight);
		// ����������ʽ
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

	// ����
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
		// ������Դ
		static void Destroy();
	public:
		// ��ȡͼ��·��
		std::string GetPath() const;
		// ��ȡͼƬ��ԴID
		int GetResourceName() const;
		// ��ȡͼƬ���ͣ���׺����
		std::string GetResourceType() const;
		// ��ȡIWICFormatConverter
		IWICFormatConverter* GetIWICFormatConverter();
	public:
		// ����ͼ��·��
		void SetPath(std::string path);
		// ����ͼƬ��ԴID
		void SetResourceName(int resourceName);
		// ����ͼƬ���ͣ���׺����
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