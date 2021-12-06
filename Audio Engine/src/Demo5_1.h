//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_1_H
#define DEMO5_1_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"
#include "Demo5_0.h"

class Demo5_1 : public Command
{
public:
	Demo5_1() = default;
	~Demo5_1() = default;
	Demo5_1(const Demo5_1&) = delete;
	Demo5_1& operator = (const Demo5_1&) = delete;

	
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 5s \n");


		//Timer T1;
		//T1.tic();
		//if (WaitForTime(T1, 3 * Time(TIME_ONE_SECOND)))
		//{
		Snd* pSndL = SndMan::Add(SndID::Alarm,nullptr, 50);
		assert(pSndL);

		// Vol & Pan
		assert(pSndL->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndL->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndL->Play() == Handle::Status::SUCCESS);

	}
};

#endif

// --- End of File ---
