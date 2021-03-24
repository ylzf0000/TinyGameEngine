#ifndef CG_TIME_H
#define CG_TIME_H
#include "stdafx.h"
#include <time.h>
CG_BEGIN
class Time
{
public:
	static time_t SetDeltaTime();
	static time_t time;
	static time_t deltaTime;
};
CG_END
#endif // CG_TIME_H
