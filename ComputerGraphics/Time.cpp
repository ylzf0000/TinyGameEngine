#include "stdafx.h"
#include "Time.h"

CG_BEGIN
time_t Time::SetDeltaTime()
{
	time_t curtime = clock();
	deltaTime = difftime(curtime, time);
	time = curtime;
	return deltaTime;
}
time_t Time::time = clock();
time_t Time::deltaTime = Time::SetDeltaTime();
CG_END