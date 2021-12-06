//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1C_2.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1C_2Main(Snd* pSnd)
{
	Trace::out("---> Start of thread: Demo1C_2 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;
	float delta;
	float vol;
	int TimeElapsed_ms;

	delta = -(0.0f - (-1.0f)) / 1000.0f;
	vol = 1.0f;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Loop for 2 seconds
	while (TimeElapsed_ms < 2000)
	{
		// Set panning	
		vol+=delta;
		//Trace::out("Vol:%f\n", vol);
		if (vol > 1.0f)
			vol = 1.0f;
		if (vol < 0.0f)
			vol = 0.0f;
		
		status = pSnd->Vol(vol);

		if (status != Handle::Status::SUCCESS)
		{
			assert(false);
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
		//	Trace::out("pan:%f\n", pan);

			// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}

	Trace::out("---> End of thread: Demo1C_1 \n");
}

// --- End of File ---
