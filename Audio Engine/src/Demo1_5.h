//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1_5_H
#define DEMO1_5_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound

// Command
class Demo1_5 : public Command
{
public:
	Demo1_5() = default;
	~Demo1_5() = default;
	Demo1_5(const Demo1_5&) = delete;
	Demo1_5& operator = (const Demo1_5&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 part5: 1 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Snd::PrintPriorityTable();

	}
};


#endif

// --- End of File ---




