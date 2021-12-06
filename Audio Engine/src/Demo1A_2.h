//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1A_2_H
#define DEMO1A_2_H

#include "Command.h"
#include "SndMan.h"
#include "Demo1A_0.h"
#include "Timer.h"


class Demo1A_2 : public Command
{
public:
	Demo1A_2() = default;
	~Demo1A_2() = default;
	Demo1A_2(const Demo1A_2 &) = delete;
	Demo1A_2 & operator = (const Demo1A_2 &) = delete;


	//bool WaitForTime(Timer& t, Time TriggerTime)
	//{
	//	Time deltaTime(TIME_ZERO);
	//
	//	if (deltaTime != TriggerTime)
	//	{
	//		while (!Time::quotient(deltaTime, TriggerTime))
	//		{
	//			// Spin
	//			deltaTime = t.toc();
	//		}
	//	}
	//	return true;
	//}
	
	// Behold the demo
	virtual void Execute() override
	{

		Timer T1;
	
		T1.tic();
		Trace::out("Demo1 partA: 2 \n");

		// Create a Snd Call
		Snd *pSndA = SndMan::Add(SndID::Fiddle);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.05f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(1) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
		//if (WaitForTime(T1, 5 * Time(TIME_ONE_SECOND)))
		//{
		//	pSndA->Stop();
		//}
	}
};

#endif

// --- End of File ---
