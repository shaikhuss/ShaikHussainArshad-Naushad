//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "FileThread.h"
#include "ThreadCountProxy.h"
#include "FileSlow.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

FileThread::FileThread(const char * const pName,
						std::shared_future<void> &fut_Kill, 
						SharedCV &_cvFileBuffReady)
	: BannerBase(pName),
	mThread(),
	mFutureKill(fut_Kill),
	mtx(),
	cvFileBuffReady(_cvFileBuffReady),
	poBuff(new Buff(FileThread::BuffSize)),
	mWaveHolder{0},
	mStatus(status::Empty),
	mCurrFileIndex(0)
{
	assert(poBuff);

	// Fill the name array
	char tmpWaveName[16];
	for (int i = 0; i < NumWaveFiles; i++)
	{
		memset(tmpWaveName, 0, StringNameLength);
		sprintf_s(tmpWaveName, StringNameLength, "wave_%d.wav", i);
		memcpy(&mWaveHolder[i].waveName, tmpWaveName, StringNameLength);
	}

}

FileThread::~FileThread()
{
	delete poBuff;

	// Every thread needs to be joined or detach before destruction
	if (mThread.joinable())
	{
		mThread.join();
	}
}

void FileThread::Launch()
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

void FileThread::CopyData(unsigned char *const pDest, unsigned int &numBytes)
{
	std::lock_guard<std::mutex> lock(mtx);
	memcpy(pDest, poBuff->GetBuff(), poBuff->GetCurrSize());
	numBytes = poBuff->GetCurrSize();
}

void FileThread::operator() ()
{
	START_BANNER_DERIVED

	KILL_THREAD_ENABLE

		int i = 0;
		while (!mFutureKill._Is_ready())
		{
			if (mStatus == status::Empty)
			{
				privLoadFile(mCurrFileIndex);

				Debug::out("File: wave done loading\n");
				cvFileBuffReady.Set();
				cvFileBuffReady.NotifyOne();

				mStatus = status::Empty;
				mCurrFileIndex++;

				if (mCurrFileIndex >= NumWaveFiles)
				{
					mStatus = status::Done;
				}
			}

			// sleep that is interruptable
			Debug::out("--- nothing %d ---\n",i++);
			mFutureKill.wait_for(500ms);
		}
}

void FileThread::privLoadFile(unsigned int index)
{
	FileSlow::Handle fh;
	FileSlow::Error  error;

	char *pWaveName = mWaveHolder[index].waveName;
	error = FileSlow::Open(fh, pWaveName, FileSlow::Mode::READ);
	assert(error == FileSlow::Error::SUCCESS);

	error = FileSlow::Seek(fh, FileSlow::Location::END, 0);
	assert(error == FileSlow::Error::SUCCESS);

	DWORD size;
	error = FileSlow::Tell(fh, size);
	assert(error == FileSlow::Error::SUCCESS);

	error = FileSlow::Seek(fh, FileSlow::Location::BEGIN, 0);
	assert(error == FileSlow::Error::SUCCESS);
	
	Debug::out("File: %s size:%d \n", pWaveName, size);

	error = FileSlow::Read(fh, poBuff->GetBuff(), size);
	assert(error == FileSlow::Error::SUCCESS);
	poBuff->SetCurrSize(size);

	error = FileSlow::Close(fh);
	assert(error == FileSlow::Error::SUCCESS);

	mStatus = status::Filled;
	
}


// -- End of File --

