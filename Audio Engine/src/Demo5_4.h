//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_4_H
#define DEMO5_4_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"

class Demo5_4 : public Command
{
public:
	Demo5_4() = default;
	~Demo5_4() = default;
	Demo5_4(const Demo5_4&) = delete;
	Demo5_4& operator = (const Demo5_4&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 20s \n");


		
	Snd* pSndD = SndMan::Add(SndID::Alarm);
	assert(pSndD);
	
	// Vol & Pan
	assert(pSndD->Vol(0.3f) == Handle::Status::SUCCESS);
	assert(pSndD->Pan(-1.0f) == Handle::Status::SUCCESS);
	
	// Call the sound
	assert(pSndD->Play() == Handle::Status::SUCCESS);
		
		



	}
};

#endif

// --- End of File ---
