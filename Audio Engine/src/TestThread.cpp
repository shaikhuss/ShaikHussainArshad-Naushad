//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "TestThread.h"
#include "Timer.h"
#include "LeftRightPan.h"

bool WaitForTime(Timer &t, Time TriggerTime )
{
	Time deltaTime(TIME_ZERO);

	if (deltaTime != TriggerTime)
	{
		while (!Time::quotient(deltaTime, TriggerTime))
		{
			// Spin
			deltaTime = t.toc();
		}
	}
	return true;
}

void Test_Main()
{
	ThreadHelper::DebugBegin(1);
	Trace::out("\n");

	Timer T1;
	T1.tic();

	if (WaitForTime(T1, Time(TIME_ZERO)))
	{
		ThreadHelper::TabMe(1);
		Trace::out("-  0 Sec - Part A: center\n");
	}

	if (WaitForTime(T1, 3 * Time(TIME_ONE_SECOND)))
	{
		ThreadHelper::TabMe(1);
		Trace::out("-  3 Sec - Part A: left\n");
	}

	if (WaitForTime(T1, 6 * Time(TIME_ONE_SECOND)))
	{
		ThreadHelper::TabMe(1);
		Trace::out("-  6 Sec - Part A: right\n");
	}

	if (WaitForTime(T1, 10 * Time(TIME_ONE_SECOND)))
	{
		ThreadHelper::TabMe(1);
		Trace::out("- 10 Sec - Part B: PanLeftToRight\n");
		std::thread t(LeftRightPan_Main);
		ThreadHelper::SetThreadName(t, "---LeftRightPan---");
		t.join();
	}

	if (WaitForTime(T1, 15 * Time(TIME_ONE_SECOND)))
	{
		ThreadHelper::TabMe(1);
		Trace::out("- 15 Sec - Part B: blah blah\n");
	}

	Trace::out("\n");
	ThreadHelper::DebugEnd(1);
}


// End of File 
