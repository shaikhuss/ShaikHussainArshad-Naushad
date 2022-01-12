//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef WAVE_THREAD_H
#define WAVE_THREAD_H

#include "Buff.h"
#include "WaveMan.h"

using namespace ThreadFramework;

class WaveThread : public BannerBase
{
public:
	static const unsigned int BuffSize = 512 * 1024;
	static const unsigned int WaveNameSize = 64;
	enum class status
	{
		Empty,
		Filled,
		Done
	};

public:
	WaveThread() = delete;
	WaveThread(const WaveThread &) = delete;
	WaveThread &operator = (const WaveThread &) = delete;
	~WaveThread();

	//void Add(WaveThread& wt);
	//
	//static WaveThread* privGetInstance();
	//
	//void privAddToFront(WaveThread* node);

	WaveThread(const char *const pName, 
		std::shared_future<void>  &mFutureKill,
		WaveMan &waveMan);

	void Launch();
	void Kick();
	void WriteToBuffer(unsigned char* const pSrc, unsigned int pSize);

	// Function call operator
	void operator() ();
	bool wdflag;
private:
	std::thread                 mThread;
	std::shared_future<void>    mFutureKill;
	std::mutex                  mtx;
	WaveMan				&mWaveMan;
	WAVEHDR				mWaveHdr;
	Buff				*po1Buff;
	char                *poWaveName;
	status				mStatus;
	
};

#endif

// -- End of File --
