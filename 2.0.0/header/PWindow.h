#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <windowsx.h>
#include "PScene.h"
#include "PEvent.h"
#include "PCamera.h"

namespace Pixel
{
	class Window
	{
	public:
		Window(std::string title = "PixelApp", int width = 640, int height = 480, Window* parent = nullptr);
		Window(const Window& window);
		~Window();
		// 初始化
		virtual bool Init();
		// 运行
		void Update();
		// 切换场景
		void Enter(Scene* target);
		// 显示
		void Show();
		// 隐藏
		void Hide();
	public:
		static Window* Find(HWND hWnd);
	public:
		// 获取窗口句柄
		HWND GetHwnd() const;
		// 获取窗口标题
		std::string GetTitle() const;
		// 获取窗口宽度
		int GetWidth() const;
		// 获取窗口高度
		int GetHeight() const;
		// 获取父窗口
		Window* GetParent() const;
	public:
		// 设置窗口标题
		void SetTitle(std::string title);
		// 设置窗口大小
		void SetSize(int width, int heiht);
		// 设置窗口宽度
		void SetWidth(int width);
		// 设置窗口高度
		void SetHeight(int height);
		// 设置固定大小
		void SetFixedSize(bool fixedSize = false);
	protected:
		WNDCLASS wc;
		DWORD dwStyle;
		std::string title;
		int width;
		int height;
		Window* parent = nullptr;
		HWND hWnd = nullptr;
		Renderer* renderer = nullptr;
		Scene* currentScene = nullptr;
	public:
		Event event;
		Camera camera;
	protected:
		static std::vector<Window*> allWindow;
	protected:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}