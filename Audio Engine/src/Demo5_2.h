//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_2_H
#define DEMO5_2_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"

class Demo5_2 : public Command
{
public:
	Demo5_2() = default;
	~Demo5_2() = default;
	Demo5_2(const Demo5_2&) = delete;
	Demo5_2& operator = (const Demo5_2&) = delete;

	
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 10s \n");


		//Timer T1;
		//T1.tic();
		//if (WaitForTime(T1, 3 * Time(TIME_ONE_SECOND)))
		//{
		Snd* pSndB = SndMan::Add(SndID::Alarm);
		assert(pSndB);
		
		// Vol & Pan
		assert(pSndB->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(-1.0f) == Handle::Status::SUCCESS);
		
		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);
			
		}


};

#endif

// --- End of File ---
