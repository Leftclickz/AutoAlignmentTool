#pragma once

#define TIME_VAR std::chrono::system_clock::time_point

class Timestamp
{
public:
	Timestamp();

	void Start();
	void Stop();

	double GetElapsedSeconds();


private:

	TIME_VAR GetTimeStamp() { return std::chrono::system_clock::now(); }

	TIME_VAR m_StartPoint;
	TIME_VAR m_EndPoint;
};