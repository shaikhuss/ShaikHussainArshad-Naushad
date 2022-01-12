//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"
#include "Command.h"
#include "WaveThread.h"
class CircularData
{
public:
	static const int CIRCULAR_DATA_SIZE = 32;

public:
	CircularData();
	
	CircularData(const CircularData &) = delete;
	const CircularData &operator = (const CircularData &) = delete;
	~CircularData() = default;

	bool PushBack(Command *pCmd);
	bool PopWaveFront(WaveThread* pCmd);
	bool PopFront(Command *& pCmd);

	bool IsEmpty();

private:
	Command *data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;

	std::mutex mtx;
};

#endif
