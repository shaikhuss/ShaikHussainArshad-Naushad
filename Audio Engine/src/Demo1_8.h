//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1_8_H
#define DEMO1_8_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound

// Command
class Demo1_8 : public Command
{
public:
	Demo1_8() = default;
	~Demo1_8() = default;
	Demo1_8(const Demo1_8&) = delete;
	Demo1_8& operator = (const Demo1_8&) = delete;

	// Behold the demo
	virtual void Execute() override
	{

		Snd::PrintPriorityTable();
		//Trace::out("Demo1 part5: 1 \n");
		Snd* pSnd = SndMan::Find(SndID::SongB);
		pSnd->Stop();

		

		

	}
};


#endif

// --- End of File ---




