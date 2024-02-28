#include "PWindow.hpp"

std::vector<Pixel::Window*> Pixel::Window::s_windows;

Pixel::Window::Window(const Window& window) :
	Window(window._title, window._width, window._height, window._parent)
{
}

Pixel::Window::Window(std::string title, unsigned int width, unsigned int height, Window* parent) :
	_title(title),
	_width(width),
	_height(height),
	_parent(parent),
	_currentScene(nullptr),
	_icon(LoadIcon(nullptr, IDI_APPLICATION)),
	_cursor(LoadCursor(nullptr, IDC_ARROW)),
	_style(parent ? WS_CHILD : WS_OVERLAPPEDWINDOW),
	_class{ CS_VREDRAW | CS_HREDRAW, WndProc, 0, 0, GetModuleHandle(nullptr), _icon, _cursor, nullptr, nullptr, L"Pixel Window" },
	_hWnd(nullptr),
	_renderer(nullptr)
{
	s_windows.push_back(this);
}

Pixel::Window::~Window()
{
	s_windows.erase(std::find(s_windows.begin(), s_windows.end(), this));
}

bool Pixel::Window::Init()
{
	RegisterClass(&_class);

	RECT wr{ 0, 0, (LONG)_width, (LONG)_height };
	AdjustWindowRect(&wr, _style, false);
	unsigned int width = wr.right - wr.left;
	unsigned int height = wr.bottom - wr.top;

	_hWnd = CreateWindow(
		L"Pixel Window",
		ToWideString(_title).c_str(),
		_style,
		(GetSystemMetrics(SM_CXSCREEN) -width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width,
		height,
		_parent ? _parent->GetHWnd() : nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	if (!_hWnd) return false;

	_renderer = new Renderer(_hWnd, &_camera);

	return _renderer->Init();
}

void Pixel::Window::Show()
{
	ShowWindow(_hWnd, SW_SHOW);
}

void Pixel::Window::Hide()
{
	ShowWindow(_hWnd, SW_HIDE);
}

void Pixel::Window::Update()
{
	if (_currentScene) _currentScene->_Update();

	_renderer->GetRenderTarget()->BeginDraw();
	if (_currentScene)
	{
		_renderer->Clear(_currentScene->GetBackground());
		_currentScene->_Render(_renderer);
	}
	else _renderer->Clear();
	HRESULT hr = _renderer->GetRenderTarget()->EndDraw();

	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
}

void Pixel::Window::Enter(Scene* target)
{
	_currentScene = target;
}

Pixel::Window* Pixel::Window::Find(HWND hWnd)
{
	for (auto window : s_windows)
	{
		if (window->GetHWnd() == hWnd) return window;
	}
	return nullptr;
}

Pixel::Scene* Pixel::Window::GetCurrentScene()
{
	return _currentScene;
}

DWORD Pixel::Window::GetStyle() const
{
	return _style;
}

WNDCLASS Pixel::Window::GetClass() const
{
	return _class;
}

HWND Pixel::Window::GetHWnd() const
{
	return _hWnd;
}

Pixel::Event Pixel::Window::GetEvent() const
{
	return _event;
}

Pixel::Renderer* Pixel::Window::GetRenderer()
{
	return _renderer;
}

Pixel::Camera* Pixel::Window::GetCamera()
{
	return &_camera;
}

HICON Pixel::Window::GetIcon() const
{
	return _icon;
}

HCURSOR Pixel::Window::GetCursor() const
{
	return _cursor;
}

std::string Pixel::Window::GetTitle() const
{
	if (_hWnd)
	{
		wchar_t title[255];
		GetWindowText(_hWnd, title, 255);
		return ToByteString(title);
	}
	else return _title;
}

Pixel::Size Pixel::Window::GetSize() const
{
	if (_hWnd)
	{
		RECT wr;
		GetWindowRect(_hWnd, &wr);
		return wr;
	}
	else return Size(.0f, .0f, (float)_width, (float)_height);
}

Pixel::Size Pixel::Window::GetClientSize() const
{
	if (_hWnd)
	{
		RECT rect;
		GetClientRect(_hWnd, &rect);
		return rect;
	}
	else return Size();
}

Pixel::Window* Pixel::Window::GetParent()
{
	return _parent;
}

bool Pixel::Window::SetHWnd(HWND hWnd)
{
	_hWnd = hWnd;
	delete _renderer;
	_renderer = new Renderer(_hWnd, &_camera);
	return _renderer->Init();
}

void Pixel::Window::SetIcon(int resourceName)
{
	_icon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(resourceName));
	if (_hWnd) SendMessage(_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)_icon);
	_class.hIcon = _icon;
}

void Pixel::Window::SetCursor(int resourceName)
{
	_cursor = LoadCursor(GetModuleHandle(nullptr), (LPCWSTR)resourceName);
	if (_hWnd) ::SetCursor(_cursor);
	_class.hCursor = _cursor;
}

void Pixel::Window::SetTitle(std::string title)
{
	_title = title;
	if (_hWnd) SetWindowText(_hWnd, ToWideString(title).c_str());
}

void Pixel::Window::_SetSize(Size size)
{
	_width = (unsigned int)size.width;
	_height = (unsigned int)size.height;
	if (_hWnd) SetWindowPos(
		_hWnd,
		nullptr,
		(GetSystemMetrics(SM_CXSCREEN) - _height) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - _height) / 2,
		_width,
		_height,
		SWP_NOZORDER
	);
}

void Pixel::Window::SetClientSize(Size size)
{
	RECT wr;
	AdjustWindowRect(&wr, _style, false);

	_width = (unsigned int)size.width;
	_height = (unsigned int)size.height;
	if (_hWnd) SetWindowPos(
		_hWnd,
		nullptr,
		(GetSystemMetrics(SM_CXSCREEN) - wr.right + wr.left) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - wr.bottom + wr.top) / 2,
		_width,
		_height,
		SWP_NOZORDER
	);
}

void Pixel::Window::SetParent(Window* parent)
{
	_parent = parent;
	::SetParent(_hWnd, parent->GetHWnd());
}

void Pixel::Window::SetStyle(DWORD style)
{
	_style = style;
}

void Pixel::Window::SetClass(WNDCLASS newClass)
{
	_class = newClass;
}

LRESULT Pixel::Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = Find(hWnd);
	if (!window) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	Event* event = &window->_event;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		if (std::find(event->_pressed.begin(), event->_pressed.end(), LeftBtn) == event->_pressed.end()) event->_pressed.push_back(LeftBtn);
		event->_mouseDown = true;
		break;
	case WM_RBUTTONDOWN:
		if (std::find(event->_pressed.begin(), event->_pressed.end(), RightBtn) == event->_pressed.end()) event->_pressed.push_back(RightBtn);
		event->_mouseDown = true;
		break;
	case WM_MBUTTONDOWN:
		if (std::find(event->_pressed.begin(), event->_pressed.end(), MiddleBtn) == event->_pressed.end()) event->_pressed.push_back(MiddleBtn);
		event->_mouseDown = true;
		break;
	case WM_LBUTTONUP:
	{
		auto del = std::find(event->_pressed.begin(), event->_pressed.end(), LeftBtn);
		if (del != event->_pressed.end()) event->_pressed.erase(del);
		event->_mouseDown = false;
	}
	break;
	case WM_RBUTTONUP:
	{
		auto del = std::find(event->_pressed.begin(), event->_pressed.end(), LeftBtn);
		if (del != event->_pressed.end()) event->_pressed.erase(del);
		event->_mouseDown = false;
	}
	break;
	case WM_MBUTTONUP:
	{
		auto del = std::find(event->_pressed.begin(), event->_pressed.end(), LeftBtn);
		if (del != event->_pressed.end()) event->_pressed.erase(del);
		event->_mouseDown = false;
	}
	break;
	case WM_KEYDOWN:
		if (std::find(event->_pressed.begin(), event->_pressed.end(), (KeyCode)wParam) == event->_pressed.end()) event->_pressed.push_back((KeyCode)wParam);
		event->_keyDown = true;
		break;
	case WM_KEYUP:
	{
		auto del = std::find(event->_pressed.begin(), event->_pressed.end(), (KeyCode)wParam);
		if (del != event->_pressed.end()) event->_pressed.erase(del);
		event->_keyDown = false;
	}
	break;
	case WM_MOUSEMOVE:
		event->_mouseMove = true;
		event->_mousePosition = Point((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
		break;
	case WM_CLOSE:
		event->_close = true;
		break;
	case WM_SIZE:
	{
		RECT wr;
		GetClientRect(hWnd, &wr);
		window->GetRenderer()->GetRenderTarget()->Resize(
			D2D1::SizeU(
				wr.right - wr.left,
				wr.bottom - wr.top
			)
		);
	}
	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT) ::SetCursor(window->_cursor);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		event->_mouseMove = false;
		event->_mouseDown = false;
		event->_keyDown = false;
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
