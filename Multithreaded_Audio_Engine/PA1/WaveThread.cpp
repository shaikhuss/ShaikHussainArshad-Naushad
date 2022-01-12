//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "WaveThread.h"
#include "ThreadCountProxy.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

WaveThread::WaveThread(const char *const pName,
	std::shared_future<void> &fut_Kill,
	WaveMan &_waveMan)
	: BannerBase(pName),
	mThread(),
	mFutureKill(fut_Kill),
	mtx(),
	mWaveMan(_waveMan),
	mWaveHdr{0},
	po1Buff(new Buff(WaveThread::BuffSize)),
	poWaveName(new char[WaveThread::WaveNameSize]()),
	mStatus(status::Empty),
	wdflag(false)
{
	assert(po1Buff);
	assert(poWaveName);
	assert(pName);

	// Add string for the buffer - used in debugging	
	mWaveHdr.dwBufferLength = (DWORD)WaveThread::BuffSize;
	mWaveHdr.lpData = (char *)po1Buff->GetBuff();

	memset(poWaveName, 0, WaveThread::WaveNameSize);
	strcpy_s(poWaveName, WaveThread::WaveNameSize, pName);
	mWaveHdr.dwUser = (DWORD_PTR)poWaveName;

	// Prepare
	MMRESULT result;   // for waveOut return values 
	result = waveOutPrepareHeader(mWaveMan.GetHandle(), &mWaveHdr, sizeof(WAVEHDR));

	assert(result == MMSYSERR_NOERROR);

}

WaveThread::~WaveThread()
{
	MMRESULT result;   // for waveOut return values
	result = waveOutUnprepareHeader(mWaveMan.GetHandle(), &mWaveHdr, sizeof(WAVEHDR));
	assert(result == MMSYSERR_NOERROR);

	delete po1Buff;
	delete poWaveName;

	// Every thread needs to be joined or detach before destruction
	if (mThread.joinable())
	{
		mThread.join();
	}
}


void WaveThread::Launch()
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

void WaveThread::Kick()
{
	waveOutWrite(mWaveMan.GetHandle(), &mWaveHdr, sizeof(WAVEHDR));
}

void WaveThread::WriteToBuffer(unsigned char*const pSrc,unsigned int pSize)
{
	std::lock_guard<std::mutex> lock(mtx);
	mWaveHdr.dwBufferLength = pSize;
	memcpy(po1Buff->GetBuff(), pSrc, pSize);
	po1Buff->SetCurrSize(pSize);
}

void WaveThread::operator() ()
{
	START_BANNER_DERIVED

	KILL_THREAD_ENABLE

	//int i = 0;
	while (!mFutureKill._Is_ready())
	{
	
		// sleep that is interruptable
		//Debug::out("--- nothing %d ---\n", i++);
		mFutureKill.wait_for(400ms);
	}
}


// -- End of File --

