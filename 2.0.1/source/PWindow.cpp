#include "PWindow.h"

std::vector<Pixel::Window*> Pixel::Window::_allWindow;

Pixel::Window::Window(std::string title, int width, int height) :
	_wc{ CS_HREDRAW | CS_VREDRAW, _WndProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"PixelApp"},
	_dwStyle(WS_OVERLAPPEDWINDOW),
	_title(title),
	_width(width),
	_height(height)
{
	_allWindow.push_back(this);
}

Pixel::Window::Window(const Window& window) :
	_title(window.GetTitle()),
	_width(window.GetWidth()),
	_height(window.GetHeight())
{
}

Pixel::Window::~Window()
{
	if (_renderer) delete _renderer;
	if (!_hWnd) return;
	for (size_t i = 0; i <= _allWindow.size(); i++)
	{
		if (_allWindow[i] == this)
		{
			_allWindow.erase(_allWindow.begin() + i);
			break;
		}
	}
}

bool Pixel::Window::Init()
{
	RegisterClass(&_wc);

	RECT wr = { 0, 0, _width, _height };
	AdjustWindowRect(&wr, _dwStyle, false);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	_hWnd = CreateWindow(
		L"PixelApp",
		ToWideString(_title).c_str(),
		_dwStyle,
		(screenWidth - windowWidth) / 2,
		(screenHeight - windowHeight) / 2,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	
	_renderer = new Renderer(_hWnd, &_camera);

	return (_hWnd && _renderer->Init()) ? true : false;
}

void Pixel::Window::Update()
{
	UpdateWindow(_hWnd);

	// »æÖÆÄÚÈÝ
	_renderer->GetRenderTarget()->BeginDraw();
	if (_currentScene)
	{
		_renderer->GetRenderTarget()->Clear(D2D1::ColorF(
			(float)_currentScene->GetBackground().r / 255,
			(float)_currentScene->GetBackground().g / 255,
			(float)_currentScene->GetBackground().b / 255,
			(float)_currentScene->GetBackground().a / 255
		));
		_currentScene->Update();
		_currentScene->_Render(_renderer);
	}
	else _renderer->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	_renderer->GetRenderTarget()->EndDraw();

	static MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Pixel::Window::Enter(Scene* target)
{
	_currentScene = target;
}

void Pixel::Window::Show()
{
	ShowWindow(_hWnd, SW_SHOW);
}

void Pixel::Window::Hide()
{
	ShowWindow(_hWnd, SW_HIDE);
}

Pixel::Window* Pixel::Window::Find(HWND hWnd)
{
	for (auto window : _allWindow)
	{
		if (window->GetHwnd() == hWnd)
		{
			return window;
		}
	}
	return nullptr;
}

HWND Pixel::Window::GetHwnd() const
{
	return _hWnd;
}

std::string Pixel::Window::GetTitle() const
{
	return _title;
}

int Pixel::Window::GetWidth() const
{
	RECT wr;
	GetClientRect(_hWnd, &wr);
	return wr.right - wr.left;
}

int Pixel::Window::GetHeight() const
{
	RECT wr;
	GetClientRect(_hWnd, &wr);
	return wr.bottom - wr.top;
}

Pixel::Event Pixel::Window::GetEvent() const
{
	return _event;
}

Pixel::Camera* Pixel::Window::GetCamera()
{
	return &_camera;
}

void Pixel::Window::SetTitle(std::string title)
{
	this->_title = title;
	SetWindowTextA(_hWnd, title.c_str());
}

void Pixel::Window::SetSize(int width, int height)
{
	this->_width = width;
	this->_height = height;

	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, _dwStyle, false);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(_hWnd, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, true);
}

void Pixel::Window::SetWidth(int width)
{
	SetSize(width, GetHeight());
}

void Pixel::Window::SetHeight(int height)
{
	SetSize(GetWidth(), height);
}

void Pixel::Window::SetFixedSize(bool fixedSize)
{
	if (fixedSize) _dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX;
	else _dwStyle = WS_OVERLAPPEDWINDOW;
	SetWindowLongPtr(_hWnd, GWL_STYLE, _dwStyle);
}

LRESULT Pixel::Window::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = Find(hWnd);

	if (!window) return DefWindowProc(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		window->_event._mousePosition = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		window->_event._mouseDown = true;
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			window->_event._mouseStatus[left] = true;
			break;
		case WM_MBUTTONDOWN:
			window->_event._mouseStatus[middle] = true;
			break;
		case WM_RBUTTONDOWN:
			window->_event._mouseStatus[right] = true;
			break;
		}
		break;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		window->_event._mouseDown = false;
		switch (uMsg)
		{
		case WM_LBUTTONUP:
			window->_event._mouseStatus[left] = false;
			break;
		case WM_MBUTTONUP:
			window->_event._mouseStatus[middle] = false;
			break;
		case WM_RBUTTONUP:
			window->_event._mouseStatus[right] = false;
			break;
		}
		break;
	case WM_KEYDOWN:
		window->_event._keyDown = true;
		break;
	case WM_KEYUP:
		window->_event._keyDown = false;
		break;
	case WM_SIZE:
	{
		RECT wr;
		GetClientRect(hWnd, &wr);
		window->_renderer->GetRenderTarget()->Resize(D2D1::SizeU(
			wr.right - wr.left,
			wr.bottom - wr.top
		));
		break;
	}
	case WM_CLOSE:
		window->_event._close = true;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
