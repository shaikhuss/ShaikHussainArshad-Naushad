//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1_9_H
#define DEMO1_9_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound

// Command
class Demo1_9 : public Command
{
public:
	Demo1_9() = default;
	~Demo1_9() = default;
	Demo1_9(const Demo1_9&) = delete;
	Demo1_9& operator = (const Demo1_9&) = delete;

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
		Trace::out("Demo1 Basoon Instance: 1 \n");
		Snd* pSndA = SndMan::Add(SndID::Bassoon);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.4f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		Snd* pSndB = SndMan::Add(SndID::Bassoon);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->Vol(0.4f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		//assert(pSndB->Play() == Handle::Status::SUCCESS);

		Snd* pSndC = SndMan::Add(SndID::Bassoon);
		assert(pSndC);

		// Vol & Pan
		assert(pSndC->Vol(0.4f) == Handle::Status::SUCCESS);
		assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		//assert(pSndC->Play() == Handle::Status::SUCCESS);

		Snd* pSndD = SndMan::Add(SndID::Bassoon);
		assert(pSndD);

		// Vol & Pan
		assert(pSndD->Vol(0.4f) == Handle::Status::SUCCESS);
		assert(pSndD->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		//assert(pSndD->Play() == Handle::Status::SUCCESS);

		Timer T1;
		T1.tic();
		if (WaitForTime(T1, 0.5f * Time(TIME_ONE_SECOND)))
		{
			pSndB->Play();
		}

		if (WaitForTime(T1, 1 * Time(TIME_ONE_SECOND)))
		{
			pSndC->Play();
		}

		if (WaitForTime(T1, 1.5f * Time(TIME_ONE_SECOND)))
		{
			pSndD->Play();
		}
		
		if (WaitForTime(T1, 2 * Time(TIME_ONE_SECOND)))
		{
			pSndA->Stop();

			pSndB->Stop();

			pSndC->Stop();



		}
	}
};


#endif

// --- End of File ---




