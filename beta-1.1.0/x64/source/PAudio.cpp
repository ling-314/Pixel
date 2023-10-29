#include "PAudio.h"

Pixel::Audio::Audio(std::wstring path) :
	playing(false)
{
	Open(path);
}

Pixel::Audio::~Audio()
{
	std::wstring command;
	command = L"close " + path;
	mciSendString(command.c_str(), 0, 0, 0);
}

void Pixel::Audio::Open(std::wstring path)
{
	this->path = path;
	std::wstring command;
	command = L"close " + path;
	mciSendString(command.c_str(), 0, 0, 0);
	command = L"open " + path + L"aliae " + path;
	mciSendString(command.c_str(), 0, 0, 0);
}

void Pixel::Audio::Play()
{
	playing = true;
	std::wstring command;
	command = L"play " + path;
	mciSendString(command.c_str(), 0, 0, 0);
}

void Pixel::Audio::Stop()
{
	playing = false;
	std::wstring command;
	command = L"pause " + path;
	mciSendString(command.c_str(), 0, 0, 0);
}

void Pixel::Audio::Resume()
{
	playing = true;
	std::wstring command;
	command = L"resume " + path;
	int i = mciSendString(command.c_str(), 0, 0, 0);
	return;
}

std::wstring Pixel::Audio::GetPath() const
{
	return path;
}

bool Pixel::Audio::IsPlaying() const
{
	return playing;
}

void Pixel::Audio::SetPath(std::wstring path)
{
	this->path = path;
}
