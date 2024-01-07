#include "PTimer.h"

Pixel::Timer::Timer() :
	_isRunning(false),
	_startTime(0),
	_endTime(0)
{
}

void Pixel::Timer::Start()
{
	if (!_isRunning)
	{
		_startTime = clock();
		_isRunning = true;
	}
}

void Pixel::Timer::Stop()
{
	if (_isRunning)
	{
		_endTime = clock();
		_isRunning = false;
	}
}

void Pixel::Timer::Reset()
{
	_startTime = _endTime = 0;
}

bool Pixel::Timer::IsRunning() const
{
	return _isRunning;
}

clock_t Pixel::Timer::GetTime() const
{
	return _endTime - _startTime;
}

clock_t Pixel::Timer::GetNow() const
{
	return clock() - _startTime;
}
