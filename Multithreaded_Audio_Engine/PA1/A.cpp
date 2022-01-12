//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "A.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

A::A(const char *const pName)
: BannerBase(pName)
{
}

void A::operator()()
{
	START_BANNER_DERIVED;

	// burn time
	int i = 0;
	for (int j = 0; j < 10; j++)
	{
		Debug::out("count:%d\n", i++);

		std::this_thread::sleep_for(500ms);
	}

}

// --- End of File ---
