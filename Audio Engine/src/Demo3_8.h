//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rigIts reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_8_H
#define DEMO3_8_H

#include "Command.h"
#include "SndMan.h"

class Demo3_8 : public Command
{
public:
	Demo3_8() = default;
	~Demo3_8() = default;
	Demo3_8(const Demo3_8&) = delete;
	Demo3_8& operator = (const Demo3_8&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part8: 8s \n");

		// Play A

		Snd* pSndJ = nullptr;

		pSndJ = SndMan::Add(SndID::Coma, nullptr, 75);
		assert(pSndJ);
		//pSndI->RemoveSamePriority();
		// Vol & Pan
		assert(pSndJ->Vol(0.1f) == Handle::Status::SUCCESS);
		assert(pSndJ->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndJ->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
