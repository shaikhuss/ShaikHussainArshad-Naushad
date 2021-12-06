//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rigIts reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_7_H
#define DEMO3_7_H

#include "Command.h"
#include "SndMan.h"

class Demo3_7 : public Command
{
public:
	Demo3_7() = default;
	~Demo3_7() = default;
	Demo3_7(const Demo3_7&) = delete;
	Demo3_7& operator = (const Demo3_7&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part7: 7s \n");

		// Play A

		Snd* pSndI = nullptr;

		pSndI = SndMan::Add(SndID::Coma, nullptr, 75);
		assert(pSndI);
		//pSndI->RemoveSamePriority();
		// Vol & Pan
		assert(pSndI->Vol(0.1f) == Handle::Status::SUCCESS);
		assert(pSndI->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndI->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
