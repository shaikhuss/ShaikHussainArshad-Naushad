//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1C_2_H
#define DEMO1C_2_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1C_2Main(Snd* pSnd);

// Command
class Demo1C_2 : public Command
{
public:
	Demo1C_2() = default;
	~Demo1C_2() = default;
	Demo1C_2(const Demo1C_2&) = delete;
	Demo1C_2& operator = (const Demo1C_2&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partB: 0 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Snd* pSndA = SndMan::Add(SndID::Oboe);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

		std::thread  Demo1C_2_Thread(Demo1C_2Main, pSndA);
		ThreadHelper::SetThreadName(Demo1C_2_Thread, "DEMO_1C_2");
		Demo1C_2_Thread.detach();
	}
};




#endif

// --- End of File ---

