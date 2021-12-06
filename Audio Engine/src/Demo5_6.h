//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_6_H
#define DEMO5_6_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "Snd.h"
#include "SndMan.h"
#include "Demo5_0.h"

class Demo5_6 : public Command
{
public:
	Demo5_6() = default;
	~Demo5_6() = default;
	Demo5_6(const Demo5_6&) = delete;
	Demo5_6& operator = (const Demo5_6&) = delete;

	
	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: Beethoven Stopped \n");



		Snd* pSnd = SndMan::Find(SndID::Beethoven);
		pSnd->Stop();





	}
};

#endif

// --- End of File ---
