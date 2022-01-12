//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SEND_DATA_CMD_H
#define SEND_DATA_CMD_H

#include "Command.h"

using namespace ThreadFramework;

class SendDataCmd : public Command
{
public:
	WaveThread* wtman = nullptr;
	SendDataCmd(WaveThread& thr)
	{
		wtman = &thr;
	}

	WaveThread* Getwave()
	{
		return wtman;
	}


	virtual void Execute() override
	{
		//Trace::out("data: %d \n", this->v);
	}
	//Command* ppt;
};

#endif

// -- End of File --
