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
	// 图形属性
	struct GraphicAttribute
	{
		Color	color;
		bool	fill;
		float	strokeWidth;
	};

	// 渲染器
	class Renderer
	{
	public:
		Renderer(HWND hWnd, Camera* camera);
		virtual ~Renderer();
		// 初始化
		bool Init();
		// 清空画布
		void Clear(Color color = 0x000000);
		// 销毁资源
		static void Destroy();
	public:
		// 获取摄像机
		Camera* GetCamera();
		// 获取渲染目标
		ID2D1HwndRenderTarget* GetRenderTarget();
		// 获取纯色画笔
		ID2D1SolidColorBrush* GetSolidColorBrush();
		// 获取D2D工厂
		static ID2D1Factory* GetFactory();
	public:
		// 设置 HWND
		void SetHWnd(HWND hWnd);
	public:
		// 画椭圆
		void DrawEllipse(float radiusX, float radiusY, GraphicAttribute attr);
		// 画矩形
		void DrawRectangle(float width, float height, float radiusX, float radiusY, GraphicAttribute attr);
		// 画线段
		void DrawLine(Point vertex1, Point vertex2, GraphicAttribute attr);
		// 画多边形
		void DrawPolygon(ID2D1PathGeometry* pPathGeometry, GraphicAttribute attr);
		// 写字
		void DrawText(IDWriteTextLayout* pTextLayout, Color color);
		// 画图
		void DrawImage(ID2D1Bitmap* pBitmap);
	private:
		HWND					_hWnd;
		Camera*					_camera;
		ID2D1HwndRenderTarget*	_pRenderTarget;
		ID2D1SolidColorBrush*	_pSolidColorBrush;
		static ID2D1Factory* s_pFactory;
	};
}