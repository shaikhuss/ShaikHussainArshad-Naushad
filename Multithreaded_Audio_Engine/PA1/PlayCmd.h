//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef PLAY_CMD_H
#define PLAY_CMD_H

#include "Command.h"
#include "WaveMan.h"
#include "WaveThread.h"
using namespace ThreadFramework;

class PlayCmd : public Command
{
public:
	Command* Wt22 = nullptr;
	WaveThread* wto = nullptr;
	unsigned char* pFileBuff1 = nullptr;
	Buff* pBuff1 = nullptr;

	PlayCmd(WaveThread& pComma,Buff* pBuff11)
	{
		wto = &pComma;
		pFileBuff1 = new unsigned char[pBuff11->GetCurrSize()];
		memcpy(pFileBuff1, pBuff11->GetBuff(), pBuff11->GetCurrSize());
		pBuff1 = pBuff11;
	}

	virtual void Execute() override
	{
		
		wto->WriteToBuffer(pFileBuff1, pBuff1->GetCurrSize());
		wto->Kick();
		Trace::out("Kick");
		
	}
	~PlayCmd()
	{
		delete[] pFileBuff1;
	}
	
};

#endif

// -- End of File --
