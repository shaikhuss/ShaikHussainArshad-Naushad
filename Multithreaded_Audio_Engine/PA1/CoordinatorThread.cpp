//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "CoordinatorThread.h"
#include "ThreadCountProxy.h"
#include "WaveThread.h"
using namespace ThreadFramework;
using namespace std::chrono_literals;
using namespace std::chrono;

//std::condition_variable cond;
//std::mutex mu;
CoordinatorThread::CoordinatorThread(const char *const pName,
	std::shared_future<void> &fut_Kill,
	SharedCV &_cvFileBuffReady,
	FileThread &_fileThread)
	: BannerBase(pName),
	mThread(),
	mFutureKill(fut_Kill),
	mtx(),
	cvFileBuffReady(_cvFileBuffReady),
	mFileThread(_fileThread),
	poBuffA(new Buff(CoordinatorThread::BuffSize)),
	poBuffB(new Buff(CoordinatorThread::BuffSize)),
	pFront(nullptr),
	pBack(nullptr),
	mMode(Mode::STARTUP)
{
	assert(poBuffA);
	assert(poBuffB);
}

CoordinatorThread::~CoordinatorThread()
{
	delete this->poBuffA;
	delete this->poBuffB;
	
	// Every thread needs to be joined or detach before destruction
	if (mThread.joinable())
	{
		mThread.join();
	}
}

void CoordinatorThread::Launch()
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

void CoordinatorThread::End()
{
	mMode = Mode::STARTUP;
}
void CoordinatorThread::Fill()
{
	mMode = Mode::FILL_BUFFER;
}
Buff* CoordinatorThread::getbuff()
{	
	//std::unique_lock<std::mutex> locker(mu);

	//cond.wait(locker);
	if (poBuffA->mFullFlag == true)
	{
		Buff* pTmp = poBuffA;
		
		poBuffA->mFullFlag = false;
		poBuffA->SetEmpty();
		
		return pTmp;
	}
	if (poBuffB->mFullFlag == true)
	{
		Buff* pTmp = poBuffB;
		poBuffB->mFullFlag = false;
		poBuffB->SetEmpty();
		
		return pTmp;
	}
	else {
		
		return nullptr;
	}
	
}



void CoordinatorThread::operator() ()
{
	START_BANNER_DERIVED;

	KILL_THREAD_ENABLE

	int count(0);
	int scount(0);


	while (!mFutureKill._Is_ready())
	{
		count++;

		if (mMode == Mode::STARTUP)
		{
			// Load up both buffers before starting
			std::unique_lock<std::mutex> lock(mtx);

			cvFileBuffReady.Wait(std::move(lock));

			Debug::out("Ready to transfer bytes to A <--- \n");

			mFileThread.CopyData(poBuffA->GetBuff(), poBuffA->GetCurrSize());
			cvFileBuffReady.Clear();
			poBuffA->mFullFlag = true;
			pFront = poBuffA;

			pFront->SetFull();
			// its currently locked... so we can reuse it.
			cvFileBuffReady.Wait(std::move(lock));

				Debug::out("Ready to transfer bytes to B <--- \n");

			mFileThread.CopyData(poBuffB->GetBuff(), poBuffB->GetCurrSize());
			cvFileBuffReady.Clear();
			poBuffB->mFullFlag = true;
			pBack = poBuffB;
			pBack->SetFull();

			mMode = Mode::NORMAL;	
		}


		if (mMode == Mode::FILL_BUFFER)
		{
			std::unique_lock<std::mutex> lock(mtx);

			cvFileBuffReady.Wait(std::move(lock));

			Debug::out("Ready to transfer bytes <--- \n");
			mFileThread.CopyData(poBuffA->GetBuff(), poBuffA->GetCurrSize());
			cvFileBuffReady.Clear();
			poBuffA->mFullFlag = true;
			pFront = poBuffA;
			pFront->SetFull();
			mMode = Mode::NORMAL;
		}
		
		if ((count % 20000000) == 0)
		{
			count = 0;
			Debug::out("count:%d \n", scount++);
		}

		Debug::out("count:%d \n", scount++);
		std::this_thread::sleep_for(1s);
	}
}

void CoordinatorThread::SwapBuff()
{
	// Swap Front and Back buffer.
	Buff *pTmp = pFront;
	pFront = pBack;
	pBack = pTmp;
}

// --- End of File---
