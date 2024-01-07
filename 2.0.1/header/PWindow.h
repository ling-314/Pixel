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
		Window(std::string title = "PixelApp", int width = 640, int height = 480);
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
		// 获取窗口消息
		Event GetEvent() const;
		// 获取摄像机
		Camera* GetCamera();
	public:
		// 设置窗口标题
		void SetTitle(std::string title);
		// 设置窗口大小
		void SetSize(int width, int height);
		// 设置窗口宽度
		void SetWidth(int width);
		// 设置窗口高度
		void SetHeight(int height);
		// 设置固定大小
		void SetFixedSize(bool fixedSize = false);
	protected:
		WNDCLASS		_wc;
		DWORD			_dwStyle;
		std::string		_title;
		int				_width;
		int				_height;
		HWND			_hWnd;
		Renderer*		_renderer;
		Scene*			_currentScene;
	protected:
		Event			_event;
		Camera			_camera;
	protected:
		static std::vector<Window*> _allWindow;
	protected:
		static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}