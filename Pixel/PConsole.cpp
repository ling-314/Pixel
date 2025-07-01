#include "PConsole.hpp"

bool destroyed = false;

Pixel::Console::Console()
{
}

Pixel::Console::~Console()
{
	Destory();
}

bool Pixel::Console::Init()
{
	SECURITY_ATTRIBUTES saAttr;
	STARTUPINFO siStarInfo;

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = true;
	saAttr.lpSecurityDescriptor = nullptr;

	HANDLE childInput, childOutput;

	if (!CreatePipe(&childInput, &_output, &saAttr, 0)) return false; // 父写子读 output 写

	if (!CreatePipe(&_input, &childOutput, &saAttr, 0)) // 子写父读 input 读
	{
		CloseHandle(_output);
		CloseHandle(childInput);
		return false;
	}

	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&siStarInfo, sizeof(STARTUPINFO));
	siStarInfo.cb = sizeof(STARTUPINFO);

	siStarInfo.dwFlags |= STARTF_USESTDHANDLES;

	WCHAR cmdLine[255];
	swprintf_s(cmdLine, L"console.exe %p %p", childInput, childOutput);
	if (!CreateProcess(nullptr, cmdLine, NULL, NULL, true, 0, nullptr, nullptr, &siStarInfo, &piProcInfo))
	{
		CloseHandle(childInput);
		CloseHandle(childOutput);
		CloseHandle(_input);
		CloseHandle(_output);
		return false;
	}

	CloseHandle(childInput);
	CloseHandle(childOutput);

	return true;
}

void Pixel::Console::Destory()
{
	if (destroyed) return;
	destroyed = true;
	char q = 'q';
	WriteFile(_output, &q, 1, nullptr, nullptr);
	CloseHandle(_input);
	CloseHandle(_output);
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
}

bool Pixel::Console::SetColor(const char color[3]) const
{
	char c = 'c';
	if (!WriteFile(_output, &c, 1, nullptr, nullptr)) return false;
	return WriteFile(_output, color, 2, nullptr, nullptr);
}

bool Pixel::Console::Output(std::string str) const
{
	// 告诉控制台去写
	unsigned int length = str.length();
	char w = 'w';
	if (!WriteFile(_output, &w, 1, nullptr, nullptr)) return false;
	// 告诉控制台写多少
	if (!WriteFile(_output, &length, sizeof(unsigned int), nullptr, nullptr)) return false;
	// 写
	return WriteFile(_output, str.c_str(), str.length(), nullptr, nullptr);
}

bool Pixel::Console::Input(std::string* str)
{
	// 告诉控制台去读
	char r = 'r';
	if (!WriteFile(_output, &r, 1, nullptr, nullptr)) return false;
	// 询问控制台读了多少
	unsigned int length;
	while (!ReadFile(_input, &length, sizeof(unsigned int), nullptr, nullptr));
	// 读
	char* buf = new char[length + 1];
	bool succeeded;
	while (!(succeeded = ReadFile(_input, buf, length, nullptr, nullptr)));
	// 添加结尾符
	buf[length] = '\0';
	*str = buf;
	return succeeded;
}
