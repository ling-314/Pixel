#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>

namespace Pixel
{
	class Audio
	{
	public:
		Audio(std::wstring path);
		~Audio();
		// 打开文件
		void Open(std::wstring path);
		// 播放
		void Play();
		// 停止
		void Stop();
		// 继续
		void Resume();
	public:
		// 获取文件路径
		std::wstring GetPath() const;
		// 是否正在播放
		bool IsPlaying() const;
	public:
		// 设置文件路径
		void SetPath(std::wstring path);
	protected:
		std::wstring path;
		bool playing;
	};
}