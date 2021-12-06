//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventMan.h"

#include "Demo5.h"
#include "Demo5_0.h"
#include "Demo5_1.h"
#include "Demo5_2.h"
#include "Demo5_3.h"
#include "Demo5_4.h"
#include "Demo5_5.h"
#include "Demo5_6.h"

void Demo5()
{
	Demo5_0 *p_0 = new Demo5_0();
	assert(p_0);
	TimeEventMan::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1 = new Demo5_1();
	assert(p_1);
	TimeEventMan::Add(p_1, 5 * Time(Duration::TIME_ONE_SECOND));

	Demo5_2* p_2 = new Demo5_2();
	assert(p_2);
	TimeEventMan::Add(p_2, 10 * Time(Duration::TIME_ONE_SECOND));


	Demo5_3* p_3 = new Demo5_3();
	assert(p_3);
	TimeEventMan::Add(p_3, 15 * Time(Duration::TIME_ONE_SECOND));


	Demo5_4* p_4 = new Demo5_4();
	assert(p_4);
	TimeEventMan::Add(p_4, 20 * Time(Duration::TIME_ONE_SECOND));

	Demo5_5* p_5 = new Demo5_5();
	assert(p_5);
	TimeEventMan::Add(p_5, 25 * Time(Duration::TIME_ONE_SECOND));

	Demo5_6* p_6 = new Demo5_6();
	assert(p_6);
	TimeEventMan::Add(p_6, 60 * Time(Duration::TIME_ONE_SECOND));
	//TimeEventMan::Dump();
}


// --- End of File ---
