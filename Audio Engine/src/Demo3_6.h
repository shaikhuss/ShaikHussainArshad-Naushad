//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_6_H
#define DEMO3_6_H

#include "Command.h"
#include "SndMan.h"

class Demo3_6 : public Command
{
public:
	Demo3_6() = default;
	~Demo3_6() = default;
	Demo3_6(const Demo3_6&) = delete;
	Demo3_6& operator = (const Demo3_6&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part6: 6s \n");

		// Play A

		Snd* pSndH = nullptr;

		pSndH = SndMan::Add(SndID::Coma, nullptr, 150);
		assert(pSndH);
		//pSndH->RemoveSamePriority();
		// Vol & Pan
		assert(pSndH->Vol(0.1f) == Handle::Status::SUCCESS);
		assert(pSndH->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndH->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
