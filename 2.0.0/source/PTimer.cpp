#include "PTimer.h"

void Pixel::Timer::Start()
{
	if (!isRunning)
	{
		startTime = clock();
		isRunning = true;
	}
}

void Pixel::Timer::Stop()
{
	if (isRunning)
	{
		endTime = clock();
		isRunning = false;
	}
}

void Pixel::Timer::Reset()
{
	startTime = endTime = 0;
}

bool Pixel::Timer::IsRunning() const
{
	return isRunning;
}

clock_t Pixel::Timer::GetTime() const
{
	return endTime - startTime;
}

clock_t Pixel::Timer::GetNow() const
{
	return clock() - startTime;
}
