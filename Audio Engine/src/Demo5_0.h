//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_0_H
#define DEMO5_0_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"

class Demo5_0 : public Command
{
public:
	Demo5_0() = default;
	~Demo5_0() = default;
	Demo5_0(const Demo5_0 &) = delete;
	Demo5_0 & operator = (const Demo5_0 &) = delete;

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
		Trace::out("Demo5 part: 0s \n");

		
		Snd* pSndKL = SndMan::Add(SndID::Electro, nullptr, 20);
		assert(pSndKL);

		// Vol & Pan
		assert(pSndKL->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndKL->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndKL->Play() == Handle::Status::SUCCESS);

		Snd* pSndAL = SndMan::Add(SndID::Alarm, nullptr, 30);
		assert(pSndAL);

		// Vol & Pan
		assert(pSndAL->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndAL->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndAL->Play() == Handle::Status::SUCCESS);
			

		FileUserCallback* pFileCB = new FileUserCallback();
		assert(pFileCB);

		// Set the sound to play once finished loading

		pFileCB->Set(SndID::Beethoven);
		// Start the load

		FileMan::Add("../../MS2_AudioFiles/Beethoven_stereo.wav", Wave::ID::Beethoven, pFileCB);


			
		


	}
};

#endif

// --- End of File ---
