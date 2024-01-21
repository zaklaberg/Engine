#pragma once

class Timer
{
public:
	Timer();

	float TotalTime() const; // in seconds
	float DeltaTime() const; // in seconds

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPreviousTime;
	__int64 mCurrentTime;

	bool mIsStopped;
};