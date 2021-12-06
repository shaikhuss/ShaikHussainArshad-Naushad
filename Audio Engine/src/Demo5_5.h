//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_5_H
#define DEMO5_5_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"

class Demo5_5 : public Command
{
public:
	Demo5_5() = default;
	~Demo5_5() = default;
	Demo5_5(const Demo5_5&) = delete;
	Demo5_5& operator = (const Demo5_5&) = delete;

	
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 25s \n");


		
		Snd* pSndE = SndMan::Add(SndID::Alarm);
		assert(pSndE);
		
		// Vol & Pan
		assert(pSndE->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndE->Pan(-1.0f) == Handle::Status::SUCCESS);
		
		// Call the sound
		assert(pSndE->Play() == Handle::Status::SUCCESS);
			
		

	}
};

#endif

// --- End of File ---
