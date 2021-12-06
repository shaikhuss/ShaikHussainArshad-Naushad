//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <chrono>
#include "Timer.h"
#include "ThreadHelper.h"
#include "LeftRightPan.h"

using namespace std::chrono_literals;



float Lerp(float A, float B, float t)
{
	float tmp;
	tmp = A + t * (B - A);
	return tmp;
}

void UpdatePan(float pan, float &left, float &right)
{
	left = 0.5f - pan * 0.5f;
	right = 0.5f + pan *0.5f;
}

void LeftRightPan_Main()
{
	Trace::out("\n");
	ThreadHelper::DebugBegin(2);
	Trace::out("\n");

	ThreadHelper::TabMe(2);
	Trace::out("- LEFT TO RIGHT PANNING - \n");

	float pan(0.0f);
	float left(0.0f);
	float right(0.0f);
	float time(0.0f);
	float delta_time = 1.0f / 2000.0f;

	int currentTime = 0;
	Timer T1;
	T1.tic();

	for(int i = 0; i<2000; i++)
	{
		pan = Lerp(-1.0f, 1.0f, time);
		UpdatePan(pan, left, right);

		if ((i % 20) == 0)
		{
			ThreadHelper::TabMe(2);
			Trace::out("l:%f r:%f\n", left, right);
		}

		time += delta_time;
		//std::this_thread::sleep_for(1ms);	// taking WAY too long

		// wait for 1 ms without surrendering the core, works fine
		WaitForTime(T1, currentTime * Time(TIME_ONE_MILLISECOND));
		++currentTime;
	}


	Trace::out("\n");
	ThreadHelper::DebugEnd(2);
	Trace::out("\n");
}



// End of File 
