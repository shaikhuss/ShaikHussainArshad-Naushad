//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef Playback_THREAD_H
#define Playback_THREAD_H

#include "CircularIndex.h"
#include "CircularData.h"
#include "CoordinatorThread.h"
#include "WaveThread.h"
using namespace ThreadFramework;

class Playback : public BannerBase
{
public:
	


	enum class status
	{
		Empty,
		Filled,
		Done
	};

public:
	Playback() = delete;
	Playback(const Playback&) = delete;
	Playback& operator = (const Playback&) = delete;
	~Playback();

	Playback(const char* const pName,
		std::shared_future<void>& t_future, CoordinatorThread& Coord, WaveThread& Waat, WaveThread& Wat, WaveThread& wt3, WaveThread& wt4, WaveThread& wt5,WaveThread& wt6, WaveThread& wt7, WaveThread& wt8, WaveThread& wt9, WaveThread& wt10, WaveThread& wt11, WaveThread& wt12, WaveThread& wt13, WaveThread& wt14, WaveThread& wt15, WaveThread& wt16, WaveThread& wt17, WaveThread& wt18, WaveThread& wt19, WaveThread& wt20, WaveThread& wt21, WaveThread& wt22, WaveThread& wt23);

	void Launch();

	// Function call operator
	void operator() ();

private:
	std::thread                 mThread;
	std::shared_future<void>    mFutureKill;
	std::mutex                  mtx;
	status				mStatus;
	CoordinatorThread& ct;
	WaveThread& Wt;
	WaveThread& Wt2;
	WaveThread& Wt3;
	WaveThread& Wt4;
	WaveThread& Wt5;
	WaveThread& Wt6;
	WaveThread& Wt7;
	WaveThread& Wt8;
	WaveThread& Wt9;
	WaveThread& Wt10;
	WaveThread& Wt11;
	WaveThread& Wt12;
	WaveThread& Wt13;
	WaveThread& Wt14;
	WaveThread& Wt15;
	WaveThread& Wt16;
	WaveThread& Wt17;
	WaveThread& Wt18;
	WaveThread& Wt19;
	WaveThread& Wt20;
	WaveThread& Wt21;
	WaveThread& Wt22;
	WaveThread& Wt23;
	
};

#endif

// -- End of File --
