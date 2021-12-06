//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rigIts reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_9_H
#define DEMO3_9_H

#include "Command.h"
#include "SndMan.h"

class Demo3_9 : public Command
{
public:
	Demo3_9() = default;
	~Demo3_9() = default;
	Demo3_9(const Demo3_9&) = delete;
	Demo3_9& operator = (const Demo3_9&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part9: 9s \n");

		// Play A

		Snd* pSndK = nullptr;

		pSndK = SndMan::Add(SndID::Coma, nullptr, 150);
		assert(pSndK);
		//pSndI->RemoveSamePriority();
		// Vol & Pan
		assert(pSndK->Vol(0.1f) == Handle::Status::SUCCESS);
		assert(pSndK->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndK->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
