//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "ThreadCount.h"

ThreadCount* ThreadCount::privGetInstance(void)
{
	// This is where its actually stored (BSS section)
	static ThreadCount threadCount;
	return &threadCount;
}

void ThreadCount::Increment()
{
	ThreadCount* ptc = ThreadCount::privGetInstance();
	assert(ptc);
	
	std::lock_guard<std::mutex> lock(ptc->mtx_ThreadCount);

	ptc->mCount++;
	//Trace::out("TC:%d \n", ptc->mCount);
}

void ThreadCount::Decrement()
{
	ThreadCount* ptc = ThreadCount::privGetInstance();
	assert(ptc);

	std::lock_guard<std::mutex> lock(ptc->mtx_ThreadCount);

	ptc->mCount--;
	//Trace::out("TC:%d \n", ptc->count);

	if (ptc->mCount == 0)
	{
		ptc->pcv_ThreadCount->notify_one();
	}
}

ThreadCount::ThreadCount()
	:mCount(0),
	mtx_ThreadCount(),
	pcv_ThreadCount(nullptr)
{

}

void ThreadCount::SetCV(std::condition_variable* cv_ThreadCount)
{
	ThreadCount* ptc = ThreadCount::privGetInstance();
	assert(ptc);


	ptc->pcv_ThreadCount = cv_ThreadCount;
}

ThreadCount::~ThreadCount()
{
	std::lock_guard<std::mutex> lock(this->mtx_ThreadCount);

	assert(mCount == 0);

}

// -- End of File --
