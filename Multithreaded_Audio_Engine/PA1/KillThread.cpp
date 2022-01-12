//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "KillThread.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

KillThread::KillThread(const char * const pName, std::promise<void>& t_promKill, std::promise<void>& t_promEnd, std::condition_variable *cv_KeyPress, std::condition_variable* cv_ThreadCount)
	: BannerBase(pName),
	mThread(),
	mPromiseKill(std::move(t_promKill)),
	mPromiseEnd(std::move(t_promEnd))
{
	pcv_KeyPress = cv_KeyPress;
	pcv_ThreadCount = cv_ThreadCount;
}

KillThread::~KillThread()
{
	// Every thread needs to be joined or detach before destruction
	if (mThread.joinable())
	{
		mThread.join();
	}
}

void KillThread::Launch()
{
	// make sure the thread wasn't started
	if (mThread.joinable() == false)
	{
		mThread = std::thread(std::ref(*this));
	}
	else
	{
		// Lock up
		assert(false);
	}
}

void KillThread::operator() ()
{
	START_BANNER_DERIVED;

	// waiting for a key press...
	std::unique_lock<std::mutex> lock_key(mtx_KeyPress);
	pcv_KeyPress->wait(lock_key);

	Debug::out("key pressed <----  \n");

	// kill them now
	mPromiseKill.set_value();

	// wait until all are done
	std::unique_lock<std::mutex> lock_ct(mtx_ThreadCount);
	pcv_ThreadCount->wait(lock_ct);

	mPromiseEnd.set_value();

}

// -- End of File --
