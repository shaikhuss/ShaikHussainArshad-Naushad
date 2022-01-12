//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "ThreadCount.h"
#include "ThreadCountProxy.h"

ThreadCountProxy::ThreadCountProxy()
{
	ThreadCount::Increment();
}

ThreadCountProxy::~ThreadCountProxy()
{
	ThreadCount::Decrement();
}

// -- End of File --
