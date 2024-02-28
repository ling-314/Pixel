#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <vector>
#include <dwrite.h>
#include <wincodec.h>
#include "PCamera.hpp"
#include "PFunction.hpp"
#include "PType.hpp"

namespace Pixel
{
	// ͼ������
	struct GraphicAttribute
	{
		Color	color;
		bool	fill;
		float	strokeWidth;
	};

	// ��Ⱦ��
	class Renderer
	{
	public:
		Renderer(HWND hWnd, Camera* camera);
		virtual ~Renderer();
		// ��ʼ��
		bool Init();
		// ��ջ���
		void Clear(Color color = 0x000000);
		// ������Դ
		static void Destroy();
	public:
		// ��ȡ�����
		Camera* GetCamera();
		// ��ȡ��ȾĿ��
		ID2D1HwndRenderTarget* GetRenderTarget();
		// ��ȡ��ɫ����
		ID2D1SolidColorBrush* GetSolidColorBrush();
		// ��ȡD2D����
		static ID2D1Factory* GetFactory();
	public:
		// ���� HWND
		void SetHWnd(HWND hWnd);
	public:
		// ����Բ
		void DrawEllipse(float radiusX, float radiusY, GraphicAttribute attr);
		// ������
		void DrawRectangle(float width, float height, float radiusX, float radiusY, GraphicAttribute attr);
		// ���߶�
		void DrawLine(Point vertex1, Point vertex2, GraphicAttribute attr);
		// �������
		void DrawPolygon(ID2D1PathGeometry* pPathGeometry, GraphicAttribute attr);
		// д��
		void DrawText(IDWriteTextLayout* pTextLayout, Color color);
		// ��ͼ
		void DrawImage(ID2D1Bitmap* pBitmap);
	private:
		HWND					_hWnd;
		Camera*					_camera;
		ID2D1HwndRenderTarget*	_pRenderTarget;
		ID2D1SolidColorBrush*	_pSolidColorBrush;
		static ID2D1Factory* s_pFactory;
	};
}