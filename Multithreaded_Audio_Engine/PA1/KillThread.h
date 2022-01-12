//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef KILL_THREAD_H
#define KILL_THREAD_H

using namespace ThreadFramework;

class KillThread : public BannerBase
{
public:
	KillThread() = delete;
	KillThread(const KillThread&) = delete;
	KillThread& operator = (const KillThread&) = delete;
	~KillThread();

	KillThread(const char * const pName, std::promise<void>& t_promKill, std::promise<void>& t_promEnd, std::condition_variable *cv_KeyPress, std::condition_variable *cv_ThreadCount);

	void Launch();

	// Function call operator
	void operator()();

private:
	std::thread				mThread;

	std::promise<void>		mPromiseKill;
	std::promise<void>      mPromiseEnd;

	std::condition_variable *pcv_KeyPress;
	std::mutex				mtx_KeyPress;

	std::condition_variable *pcv_ThreadCount;
	std::mutex				mtx_ThreadCount;
};

#endif

// -- End of File --
