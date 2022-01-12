//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef COORDINATOR_THREAD_H
#define COORDINATOR_THREAD_H

#include "SharedCV.h"
#include "FileThread.h"
#include "Buff.h"


using namespace ThreadFramework;

class CoordinatorThread : public BannerBase
{
public:
	static const unsigned int BuffSize = 512 * 1024;

	enum class Mode
	{
		STARTUP,
		FILL_BUFFER,
		NORMAL
	};

public:
	CoordinatorThread(const char * const pName, 
		std::shared_future<void>& fut_Kill, 
		SharedCV &cvFileBuffReady,
		FileThread &_fileThread);

	CoordinatorThread() = delete;
	CoordinatorThread(const CoordinatorThread&) = delete;
	CoordinatorThread& operator = (const CoordinatorThread&) = delete;
	~CoordinatorThread();

	void SwapBuff();
	void Launch();
	void End();
	void Fill();
	Buff* getbuff();
	
	void operator()();

private:
	std::thread                 mThread;
	std::shared_future<void>    mFutureKill;
	std::mutex                  mtx;
	SharedCV                    &cvFileBuffReady;
	FileThread                  &mFileThread;

	Buff *poBuffA;
	Buff *poBuffB;

	Buff *pFront;
	Buff *pBack;	
	

	Mode  mMode;
};

#endif

// -- End of File --
