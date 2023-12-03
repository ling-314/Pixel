#pragma once
#include <time.h>

namespace Pixel
{
	class Timer
	{
	public:
		// 启动计时器
		void Start();
		// 关闭计时器
		void Stop();
		// 重置计时器
		void Reset();
	public:
		// 是否正在计时
		bool IsRunning() const;
		// 获取计时时间
		clock_t GetTime() const;
		// 获取已计时时间
		clock_t GetNow() const;
	protected:
		bool isRunning = false;
		clock_t startTime;
		clock_t endTime;
	};
}