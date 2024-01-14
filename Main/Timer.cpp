#include <windows.h>
#include "Timer.h"

Timer::Timer()
	: secondsPerCount(0.0), deltaTime(-1.0), baseTime(0), stopTime(0),
	pausedTime(0), previousTime(0), currentTime(0), isStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	secondsPerCount = 1.0 / (double)countsPerSec;
}

// Returns the total time elapsed since Reset() was called, NOT counting any
// time when the clock is stopped.
float Timer::TotalTime() const
{
	// Only needed because pausedTime is not incrementally updated when we are paused.
	if (isStopped)
	{
		return (float)(((stopTime - pausedTime) - baseTime) * secondsPerCount);
	}
	else
	{
		return (float)(((currentTime - pausedTime) - baseTime) * secondsPerCount);
	}
}

// Time between most recent two frames
float Timer::DeltaTime() const
{
	return (float)deltaTime;
}

void Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	baseTime = currTime;
	previousTime = currTime;
	stopTime = 0;
	isStopped = false;
}

void Timer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (isStopped)
	{
		pausedTime += (startTime - stopTime);

		previousTime = startTime;
		stopTime = 0;
		isStopped = false;
	}
}

void Timer::Stop()
{
	if (isStopped)
		return;

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	stopTime = currTime;
	isStopped = true;
}

void Timer::Tick()
{
	if (isStopped)
	{
		deltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	currentTime = currTime;

	// Time difference between this frame and the previous.
	deltaTime = (currentTime - previousTime) * secondsPerCount;

	// Prepare for next frame.
	previousTime = currentTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then deltaTime can be negative.
	if (deltaTime < 0.0)
	{
		deltaTime = 0.0;
	}
}

