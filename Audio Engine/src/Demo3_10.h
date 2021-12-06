//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_10_H
#define DEMO3_10_H

#include "Command.h"
#include "SndMan.h"

class Demo3_10 : public Command
{
public:
	Demo3_10() = default;
	~Demo3_10() = default;
	Demo3_10(const Demo3_10&) = delete;
	Demo3_10& operator = (const Demo3_10&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part10: 13s \n");

	
		Snd::RemoveAll();

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---

