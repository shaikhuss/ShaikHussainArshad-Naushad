//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_0_H
#define DEMO3_0_H

#include "Command.h"
#include "SndMan.h"

class Demo3_0 : public Command
{
public:
	Demo3_0() = default;
	~Demo3_0() = default;
	Demo3_0(const Demo3_0 &) = delete;
	Demo3_0 & operator = (const Demo3_0 &) = delete;

	bool WaitForTime(Timer& t, Time TriggerTime)
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
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part0: 0s \n");

		// Play A

			Snd *pSndA = nullptr;
		
			pSndA = SndMan::Add(SndID::Coma, nullptr, 10);
			assert(pSndA);

			// Vol & Pan
			assert(pSndA->Vol(0.1f) == Handle::Status::SUCCESS);
			assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Play B

			Snd *pSndB = nullptr;

			pSndB = SndMan::Add(SndID::Coma,nullptr, 50);
			assert(pSndB);

			// Vol & Pan
			assert(pSndB->Vol(0.1f) == Handle::Status::SUCCESS);
			assert(pSndB->Pan(0.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndB->Play() == Handle::Status::SUCCESS);

			
		// Play C

			Snd *pSndC = nullptr;

			pSndC = SndMan::Add(SndID::Coma,nullptr, 150);
			assert(pSndC);

			// Vol & Pan
			assert(pSndC->Vol(0.1f) == Handle::Status::SUCCESS);
			assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndC->Play() == Handle::Status::SUCCESS);
			Snd::PrintPriorityTable();
		// Print snd priority table
			//Timer T1;
			//T1.tic();
			//if (WaitForTime(T1, 13 * Time(TIME_ONE_SECOND)))
			//{
			//	pSndA->Stop();
			//	pSndB->Stop();
			//	pSndC->Stop();
			//	Snd::PrintPriorityTable();
			//}
			//T1.toc();
			//Trace::out("\nDemo0 Doneeeeeeeeeeeeeeeeeee");
	}

};

#endif

// --- End of File ---

