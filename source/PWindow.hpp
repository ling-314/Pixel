#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <windowsx.h>
#include "PFunction.hpp"
#include "PCamera.hpp"
#include "PRenderer.hpp"
#include "PEvent.hpp"
#include "PType.hpp"
#include "PNode.hpp"

namespace Pixel
{
	// 窗口
	class Window
	{
	public:
		Window(const Window& window);
		Window(std::string title = "Window", unsigned int width = 640, unsigned int height = 480, Window* parent = nullptr);
		virtual ~Window();
		// 初始化
		// 重载这个函数，自定义初始化
		virtual bool Init();
		// 显示
		void Show();
		// 隐藏
		void Hide();
		// 更新窗口
		void Update();
		// 进入场景
		void Enter(Scene* target);
		// 查找
		static Window* Find(HWND hWnd);
	public:
		// 获取标题
		std::string GetTitle() const;
		// 获取大小
		Size GetSize() const;
		// 获取客户区大小
		Size GetClientSize() const;
		// 获取父窗口
		Window* GetParent();
		// 获取当前场景
		Scene* GetCurrentScene();
		// 获取窗口样式
		DWORD GetStyle() const;
		// 获取窗口类
		WNDCLASS GetClass() const;
		// 获取 HWND
		HWND GetHWnd() const;
		// 获取消息
		Event GetEvent() const;
		// 获取渲染器
		Renderer* GetRenderer();
		// 获取摄像机
		Camera* GetCamera();
		// 获取窗口图标
		HICON GetIcon() const;
		// 获取光标
		HCURSOR GetCursor() const;
	public:
		// 设置标题
		void SetTitle(std::string title);
		// 设置大小
		void _SetSize(Size size);
		// 设置客户区大小
		void SetClientSize(Size size);
		// 设置父窗口
		void SetParent(Window* parent);
		// 设置窗口样式
		void SetStyle(DWORD style);
		// 设置窗口类
		void SetClass(WNDCLASS newClass);
		// 设置 HWND 以操作其它窗口
		// 若调用此函数，则不应调用 Init() 函数
		bool SetHWnd(HWND hWnd);
		// 设置窗口图标
		void SetIcon(int resourceName);
		// 设置光标
		void SetCursor(int resourceName);
	private:
		std::string					_title;
		unsigned int				_width;
		unsigned					_height;
		Window*						_parent;
		Scene*						_currentScene;
		HICON						_icon;
		HCURSOR						_cursor;
		DWORD						_style;
		WNDCLASS					_class;
		HWND						_hWnd;
		Camera						_camera;
		Renderer*					_renderer;
		Event						_event;
		static std::vector<Window*> s_windows;
	protected:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}