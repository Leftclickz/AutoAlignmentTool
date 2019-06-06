#include "HelperPCH.h"

Timestamp::Timestamp()
{

}

void Timestamp::Start()
{
	m_StartPoint = GetTimeStamp();
}

void Timestamp::Stop()
{
	m_EndPoint = GetTimeStamp();
}

double Timestamp::GetElapsedSeconds()
{
	std::chrono::duration<double> elapsed_seconds = m_EndPoint - m_StartPoint;

	return elapsed_seconds.count();
}
