//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1_4_H
#define DEMO1_4_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound

// Command
class Demo1_4 : public Command
{
public:
	Demo1_4() = default;
	~Demo1_4() = default;
	Demo1_4(const Demo1_4&) = delete;
	Demo1_4& operator = (const Demo1_4&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 SongA&B:  \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Snd* pSndA = SndMan::Add(SndID::SongA);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		Snd* pSndB = SndMan::Add(SndID::SongB);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->Vol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);

	}
};


#endif

// --- End of File ---




