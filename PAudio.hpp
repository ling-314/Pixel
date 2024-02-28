#pragma once
#include <string>
#include <Windows.h>
#include "PFunction.hpp"

namespace Pixel
{
	// 音频
	class Audio
	{
	public:
		Audio();
		Audio(std::string path);
		~Audio();
		// 播放
		void Play();
		// 暂停
		void Pause();
		// 继续播放
		void Continue();
		// 停止
		void Stop();
		// 关闭音频文件
		void Close();
	public:
		// 获取音频路径
		std::string GetPath() const;
		// 是否
	public:
		// 设置音频路径
		void SetPath(std::string path);
	private:
		std::string _path;
	};
}