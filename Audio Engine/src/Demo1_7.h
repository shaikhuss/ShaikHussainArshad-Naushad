//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1_7_H
#define DEMO1_7_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound

// Command
class Demo1_7 : public Command
{
public:
	Demo1_7() = default;
	~Demo1_7() = default;
	Demo1_7(const Demo1_7&) = delete;
	Demo1_7& operator = (const Demo1_7&) = delete;

	// Behold the demo
	virtual void Execute() override
	{

		Snd::PrintPriorityTable();
		//Trace::out("Demo1 part5: 1 \n");
		Snd* pSnd = SndMan::Find(SndID::SongA);
		pSnd->Stop();

		
		

	}
};


#endif

// --- End of File ---




