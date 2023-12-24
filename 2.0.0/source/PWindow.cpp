#include "PWindow.h"

std::vector<Pixel::Window*> Pixel::Window::allWindow;

Pixel::Window::Window(std::string title, int width, int height, Window* parent) :
	wc{ CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"PixelApp" },
	dwStyle(parent ? WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CHILD : WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
	title(title),
	width(width),
	height(height),
	parent(parent)
{
	allWindow.push_back(this);
}

Pixel::Window::Window(const Window& window) :
	title(window.GetTitle()),
	width(window.GetWidth()),
	height(window.GetHeight())
{
}

Pixel::Window::~Window()
{
	if (renderer) delete renderer;
	if (!hWnd) return;
	for (size_t i = 0; i <= allWindow.size(); i++)
	{
		if (allWindow[i] == this)
		{
			allWindow.erase(allWindow.begin() + i);
			break;
		}
	}
}

bool Pixel::Window::Init()
{
	RegisterClass(&wc);

	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, dwStyle, false);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindowA(
		"PixelApp",
		title.c_str(),
		dwStyle,
		(screenWidth - windowWidth) / 2,
		(screenHeight - windowHeight) / 2,
		windowWidth,
		windowHeight,
		parent ? parent->GetHwnd() : nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	renderer = new Renderer(hWnd, &camera);
	
	return (hWnd && renderer->Init()) ? true : false;
}

void Pixel::Window::Update()
{
	UpdateWindow(hWnd);

	// »æÖÆÄÚÈÝ
	renderer->GetRenderTarget()->BeginDraw();
	if (currentScene)
	{
		renderer->GetRenderTarget()->Clear(D2D1::ColorF(
			(float)currentScene->GetBackground().r / 255,
			(float)currentScene->GetBackground().g / 255,
			(float)currentScene->GetBackground().b / 255,
			(float)currentScene->GetBackground().a / 255
		));
		currentScene->Update();
		currentScene->Render(renderer);
	}
	else renderer->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
	renderer->GetRenderTarget()->EndDraw();

	static MSG msg;
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Pixel::Window::Enter(Scene* target)
{
	currentScene = target;
}

void Pixel::Window::Show()
{
	ShowWindow(hWnd, SW_SHOW);
}

void Pixel::Window::Hide()
{
	ShowWindow(hWnd, SW_HIDE);
}

Pixel::Window* Pixel::Window::Find(HWND hWnd)
{
	for (auto window : allWindow)
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
	return hWnd;
}

std::string Pixel::Window::GetTitle() const
{
	return title;
}

int Pixel::Window::GetWidth() const
{
	RECT wr;
	GetClientRect(hWnd, &wr);
	return wr.right - wr.left;
}

int Pixel::Window::GetHeight() const
{
	RECT wr;
	GetClientRect(hWnd, &wr);
	return wr.bottom - wr.top;
}

Pixel::Window* Pixel::Window::GetParent() const
{
	return parent;
}

void Pixel::Window::SetTitle(std::string title)
{
	this->title = title;
	SetWindowTextA(hWnd, title.c_str());
}

void Pixel::Window::SetSize(int width, int heiht)
{
	this->width = width;
	this->height = height;

	DWORD dwStyle = parent ? WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CHILD : WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, dwStyle, false);

	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(hWnd, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, true);
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
	if (fixedSize) dwStyle = parent ? WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CHILD : WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	else dwStyle = parent ? WS_OVERLAPPEDWINDOW | WS_CHILD : WS_OVERLAPPEDWINDOW;
	SetWindowLongPtr(hWnd, GWL_STYLE, dwStyle);
}

LRESULT Pixel::Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = Find(hWnd);
	
	if (!window) return DefWindowProc(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		window->event.mousePosition = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		window->event.mouseDown = true;
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			window->event.keyStatus[left] = true;
			break;
		case WM_MBUTTONDOWN:
			window->event.keyStatus[middle] = true;
			break;
		case WM_RBUTTONDOWN:
			window->event.keyStatus[right] = true;
			break;
		}
		break;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		window->event.mouseDown = false;
		switch (uMsg)
		{
		case WM_LBUTTONDOWN:
			window->event.keyStatus[left] = false;
			break;
		case WM_MBUTTONDOWN:
			window->event.keyStatus[middle] = false;
			break;
		case WM_RBUTTONDOWN:
			window->event.keyStatus[right] = false;
			break;
		}
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		if (uMsg == WM_KEYDOWN)
		{
			window->event.keyDown = true;
			window->event.keyStatus[KeyCode(wParam)] = true;
		}
		else
		{
			window->event.keyDown = false;
			window->event.keyStatus[KeyCode(wParam)] = false;
		}
		break;
	case WM_SIZE:
	{
		RECT wr;
		GetClientRect(hWnd, &wr);
		window->renderer->GetRenderTarget()->Resize(D2D1::SizeU(
			wr.right - wr.left,
			wr.bottom - wr.top
		));
		break;
	}
	case WM_CLOSE:
		window->event.close = true;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
