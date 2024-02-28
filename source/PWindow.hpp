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
	// ����
	class Window
	{
	public:
		Window(const Window& window);
		Window(std::string title = "Window", unsigned int width = 640, unsigned int height = 480, Window* parent = nullptr);
		virtual ~Window();
		// ��ʼ��
		// ��������������Զ����ʼ��
		virtual bool Init();
		// ��ʾ
		void Show();
		// ����
		void Hide();
		// ���´���
		void Update();
		// ���볡��
		void Enter(Scene* target);
		// ����
		static Window* Find(HWND hWnd);
	public:
		// ��ȡ����
		std::string GetTitle() const;
		// ��ȡ��С
		Size GetSize() const;
		// ��ȡ�ͻ�����С
		Size GetClientSize() const;
		// ��ȡ������
		Window* GetParent();
		// ��ȡ��ǰ����
		Scene* GetCurrentScene();
		// ��ȡ������ʽ
		DWORD GetStyle() const;
		// ��ȡ������
		WNDCLASS GetClass() const;
		// ��ȡ HWND
		HWND GetHWnd() const;
		// ��ȡ��Ϣ
		Event GetEvent() const;
		// ��ȡ��Ⱦ��
		Renderer* GetRenderer();
		// ��ȡ�����
		Camera* GetCamera();
		// ��ȡ����ͼ��
		HICON GetIcon() const;
		// ��ȡ���
		HCURSOR GetCursor() const;
	public:
		// ���ñ���
		void SetTitle(std::string title);
		// ���ô�С
		void _SetSize(Size size);
		// ���ÿͻ�����С
		void SetClientSize(Size size);
		// ���ø�����
		void SetParent(Window* parent);
		// ���ô�����ʽ
		void SetStyle(DWORD style);
		// ���ô�����
		void SetClass(WNDCLASS newClass);
		// ���� HWND �Բ�����������
		// �����ô˺�������Ӧ���� Init() ����
		bool SetHWnd(HWND hWnd);
		// ���ô���ͼ��
		void SetIcon(int resourceName);
		// ���ù��
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