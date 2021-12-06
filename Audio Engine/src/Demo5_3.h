//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_3_H
#define DEMO5_3_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"

class Demo5_3 : public Command
{
public:
	Demo5_3() = default;
	~Demo5_3() = default;
	Demo5_3(const Demo5_3&) = delete;
	Demo5_3& operator = (const Demo5_3&) = delete;

	
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 15s \n");



		Snd* pSndC = SndMan::Add(SndID::Alarm);
		assert(pSndC);

		// Vol & Pan
		assert(pSndC->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndC->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndC->Play() == Handle::Status::SUCCESS);

	}
};

#endif

// --- End of File ---
