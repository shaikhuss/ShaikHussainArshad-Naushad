//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "SharedCV.h"

SharedCV::SharedCV()
	:cv(),
	mFlag(false)
{

}

bool SharedCV::IsReady()
{
	return ( mFlag );
}

void SharedCV::Set()
{
	mFlag = true;
}

void SharedCV::Clear()
{
	mFlag = false;
}

void SharedCV::NotifyOne()
{
	cv.notify_one();
}

void SharedCV::Wait(std::unique_lock<std::mutex> &&lock)
{
	cv.wait(lock, [&]() { return this->IsReady(); });
}

// -- End of File --
