#pragma once
#include <Windows.h>
#include <string>
#include <locale>
#include "PType.hpp"

namespace Pixel
{
	class Path
	{
	public:
		Path();
		Path(std::string path);
	public:
		// 获取路径
		std::string GetPath() const;
	public:
		// 设置路径
		void SetPath(std::string path);
	private:
		std::string _path;
	};

	class File :
		public Path
	{
	public:
		File();
		File(std::string path);
		enum AccessRight
		{
			ReadAndWrite = GENERIC_ALL,
			OnlyRead = GENERIC_READ,
			OnlyWrite = GENERIC_WRITE
		};
		// 创建
		static bool Create(std::string path);
		// 删除
		static bool Delete(std::string path);
		// 打开
		bool Open(AccessRight accessRight);
		// 关闭
		bool Close();
		// 读取
		std::string Read(size_t numberOfBytesToRead);
		// 写入
		DWORD Write(std::string buffer);
	public:
		// 获取大小
		size_t GetSize() const;
	private:
		std::string _name;
		std::string _type;
		HANDLE		_handle;
		bool		_opened;
	};

	class Folder :
		public Path
	{
	public:
		Folder();
		Folder(std::string name);
		// 创建
		static bool Create(std::string path);
		// 删除
		static bool Delete(std::string path);
	private:
		std::string _name;
	};
}