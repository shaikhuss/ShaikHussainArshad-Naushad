//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo2.h"
#include "TimeEventMan.h"
#include "SndMan.h"
#include "ASndMan.h"

#include "Demo2_0.h"

void Demo2()
{
	// Center
	Demo2_0* p2A_0 = new Demo2_0();
	assert(p2A_0);

	
	TimeEventMan::Add(p2A_0, 0 * Time(Duration::TIME_ONE_SECOND));
	
	

	TimeEventMan::Dump();

}

// --- End of File ---
