//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1.h"
#include "TimeEventMan.h"
#include "SndMan.h"
#include "ASndMan.h"

void Demo1()
{
	 //Center
	Demo1A_0 *p1A_0 = new Demo1A_0();
	assert(p1A_0);
	
	// Left
	Demo1A_1 *p1A_1 = new Demo1A_1();
	assert(p1A_1);
	
	// Right
	Demo1A_2 *p1A_2 = new Demo1A_2();
	assert(p1A_2);
	
	TimeEventMan::Add(p1A_0, 0 * Time(Duration::TIME_ONE_SECOND));
    TimeEventMan::Add(p1A_1, 3 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(p1A_2, 6 * Time(Duration::TIME_ONE_SECOND));
	
	Demo1B_0* p1B_0 = new Demo1B_0();
	assert(p1B_0);
	
	TimeEventMan::Add(p1B_0, 10 * Time(Duration::TIME_ONE_SECOND));

	Demo1B_1* p1B_1 = new Demo1B_1();
	assert(p1B_1);

	TimeEventMan::Add(p1B_1, 15 * Time(Duration::TIME_ONE_SECOND));

	
	Demo1C_0* p1C = new Demo1C_0();
	assert(p1C);
	
	TimeEventMan::Add(p1C, 20 * Time(Duration::TIME_ONE_SECOND));

	Demo1C_2* p1C_2 = new Demo1C_2();
	assert(p1C_2);
	
	TimeEventMan::Add(p1C_2, 25 * Time(Duration::TIME_ONE_SECOND));

	
	Demo1_4* p14 = new Demo1_4();
	assert(p14);
	
	TimeEventMan::Add(p14, 30 * Time(Duration::TIME_ONE_SECOND));
	
	
	Demo1_5* p15 = new Demo1_5();
	assert(p15);
	
	TimeEventMan::Add(p15, 35 * Time(Duration::TIME_ONE_SECOND));
	
	
	Demo1_6* p16 = new Demo1_6();
	assert(p16);
	
	TimeEventMan::Add(p16, 38 * Time(Duration::TIME_ONE_SECOND));
	
	
	Demo1_7* p17 = new Demo1_7();
	assert(p17);
	
	TimeEventMan::Add(p17, 60 * Time(Duration::TIME_ONE_SECOND));
	
	
	Demo1_8* p18 = new Demo1_8();
	assert(p18);
	
	TimeEventMan::Add(p18, 72 * Time(Duration::TIME_ONE_SECOND));
	
	
	Demo1_9* p19 = new Demo1_9();
	assert(p19);
	
	TimeEventMan::Add(p19, 80 * Time(Duration::TIME_ONE_SECOND));
	
	

	TimeEventMan::Dump();

}

// --- End of File ---
