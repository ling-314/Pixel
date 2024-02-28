#include "PAudio.hpp"

Pixel::Audio::Audio() :
	Audio("")
{
}

Pixel::Audio::Audio(std::string path)
{
	SetPath(path);
}

Pixel::Audio::~Audio()
{
	Stop();
	Close();
}

void Pixel::Audio::Play()
{
	std::wstring command = L"play \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void Pixel::Audio::Pause()
{
	std::wstring command = L"pause \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void Pixel::Audio::Continue()
{
	std::wstring command = L"resume \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void Pixel::Audio::Stop()
{
	std::wstring command = L"stop \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void Pixel::Audio::Close()
{
	std::wstring command = L"close \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}

std::string Pixel::Audio::GetPath() const
{
	return _path;
}

void Pixel::Audio::SetPath(std::string path)
{
	Stop();
	Close();

	_path = path;

	std::wstring command = L"open \"" + ToWideString(_path) + L"\"";
	mciSendString(command.c_str(), nullptr, 0, nullptr);
}
