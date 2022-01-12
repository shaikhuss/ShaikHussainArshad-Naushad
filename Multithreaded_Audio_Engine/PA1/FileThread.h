//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef FILE_THREAD_H
#define FILE_THREAD_H

#include "SharedCV.h"
#include "Buff.h"

using namespace ThreadFramework;

class FileThread : public BannerBase
{
public:
	static const unsigned int BuffSize = 512 * 1024;
	//static const unsigned int NumWaveFiles = 23;
	static const unsigned int NumWaveFiles = 23;
	static const unsigned int StringNameLength = 16;

	struct waveName_t
	{
		char waveName[16];
	};

	enum class status
	{
		Empty,
		Filled,
		Done
	};

public:
	FileThread() = delete;
	FileThread(const FileThread &) = delete;
	FileThread &operator = (const FileThread &) = delete;
	~FileThread();

	FileThread(const char * const pName, 
		std::shared_future<void> &t_future,
		SharedCV &cvFileBuffReady);

	void Launch();
	void CopyData(unsigned char *const pDest, unsigned int &numBytes);

	// Function call operator
	void operator() ();

private:
	void privLoadFile(unsigned int index);

private:
	std::thread                 mThread;
	std::shared_future<void>    mFutureKill;
	std::mutex                  mtx;
	SharedCV                    &cvFileBuffReady;

	Buff			   *poBuff;
	waveName_t			mWaveHolder[NumWaveFiles];
	status				mStatus;
	unsigned int		mCurrFileIndex;
};

#endif

// -- End of File --
