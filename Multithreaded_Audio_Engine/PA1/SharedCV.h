//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SHARED_CV_H
#define SHARED_CV_H

using namespace ThreadFramework;

class SharedCV
{
public:
	enum class Signal
	{
		SEND,
		READ
	};

public:
	SharedCV();
	SharedCV(const SharedCV &) = delete;
	SharedCV &operator = (const SharedCV &) = delete;
	~SharedCV() = default;

	bool IsReady();
	void Set();
	void Clear();

	// Wrappers
	void NotifyOne();
	void Wait(std::unique_lock<std::mutex> &&lock);

public:
	std::condition_variable cv;
	bool                    mFlag;
};

#endif

// -- End of File --
