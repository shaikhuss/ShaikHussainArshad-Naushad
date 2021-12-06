//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO4_1_H
#define DEMO4_1_H

#include "Command.h"
#include "SndMan.h"
#include "UserCallBack.h"

class Demo4_1 : public Command
{
public:
	Demo4_1() = default;
	~Demo4_1() = default;
	Demo4_1(const Demo4_1&) = delete;
	Demo4_1& operator = (const Demo4_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo4 part2: 3.5s \n");

		// Play A

		Snd* pSndA = nullptr;
		UserCallback* pCallback_A = new UserCallback();

		pSndA = SndMan::Add(SndID::Donkey, pCallback_A);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Play B


	}

};

#endif

// --- End of File ---
