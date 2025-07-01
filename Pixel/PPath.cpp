#include "PPath.hpp"

Pixel::Path::Path() :
	Path("")
{
}

Pixel::Path::Path(std::string path) :
	_path(path)
{
}

std::string Pixel::Path::GetPath() const
{
	return _path;
}

void Pixel::Path::SetPath(std::string path)
{
	_path = path;
}

Pixel::File::File() :
	File("")
{
}

Pixel::File::File(std::string path) :
	Path(path),
	_handle(nullptr),
	_opened(false)
{
	char name[MAX_PATH];
	char type[MAX_PATH];
	_splitpath_s(GetPath().c_str(), nullptr, 0, nullptr, 0, name, MAX_PATH, type, MAX_PATH);
	_name = name;
	_type = type;
}

bool Pixel::File::Create(std::string path)
{
	return SUCCEEDED(
		CreateFileA(path.c_str(), GENERIC_ALL, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr)
	) ? true : false;
}

bool Pixel::File::Delete(std::string path)
{
	return DeleteFileA(path.c_str());
}

bool Pixel::File::Open(AccessRight accessRight)
{
	if (_opened) return false;

	_handle = CreateFileA(GetPath().c_str(), accessRight, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	
	if (SUCCEEDED(_handle))
	{
		_opened = true;
		return true;
	}
	else
		return false;
}

bool Pixel::File::Close()
{
	if (CloseHandle(_handle))
	{
		_handle = nullptr;
		_opened = false;
		return true;
	}
	else
		return false;
}

std::string Pixel::File::Read(size_t numberOfBytesToRead)
{
	auto content = new char[numberOfBytesToRead + 1 /* numberOfBytesToRead 为内容的长度，还需一个额外的结束符“\0” */]();
	memset(content, 0, numberOfBytesToRead);
	ReadFile(_handle, content, numberOfBytesToRead, 0, 0);
	std::string str(content);
	delete[] content;
	return str;
}

DWORD Pixel::File::Write(std::string buffer)
{
	DWORD numberOfBytesWritten;
	WriteFile(_handle, buffer.c_str(), buffer.length(), &numberOfBytesWritten, 0);
	return numberOfBytesWritten;
}

size_t Pixel::File::GetSize() const
{
	return GetFileSize(_handle, nullptr);
}

Pixel::Folder::Folder() :
	Folder("")
{
}

Pixel::Folder::Folder(std::string name) :
	_name(name)
{
}

bool Pixel::Folder::Create(std::string path)
{
	return CreateDirectoryA(path.c_str(), nullptr);
}

bool Pixel::Folder::Delete(std::string path)
{
	return RemoveDirectoryA(path.c_str());
}
