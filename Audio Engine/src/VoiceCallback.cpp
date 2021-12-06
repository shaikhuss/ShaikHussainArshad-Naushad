//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceCallback.h"
#include "ACommandQueue.h"
#include "ASndMan.h"
#include "SndMan.h"

VoiceCallback::VoiceCallback()
	:pASnd(nullptr)
{
}

VoiceCallback::~VoiceCallback()
{
}

bool VoiceCallback::IsFinished() const
{
	return false;
}

void VoiceCallback::SetASnd(ASnd* _pASnd)
{
	assert(_pASnd);
	this->pASnd = _pASnd;
}

ASnd* VoiceCallback::GetASnd()
{
	assert(this->pASnd);
	return this->pASnd;
}


void STDMETHODCALLTYPE VoiceCallback::OnStreamEnd() noexcept
{
	Trace::out("VoiceCallback: StreamEnd\n");
	Snd* pSnd = SndMan::Find(SndID::End);

	if (this->pNextVoice == pSnd)
	{
		Trace::out("\n End");
	}
	assert(this->pASnd);
	ACommandQueue::SndEnd(this->pASnd);
	if (this->pNextVoice != nullptr)
	{

		Trace::out("start new voice \n");
	
		this->pNextVoice->Play();

		//Snd* pSnd = SndMan::Find(SndID::Sequence);
		//pSnd->Play();
	}


	else
	{
		finished = true;
	}
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassEnd() noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassStart(UINT32) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnBufferEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnBufferStart(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnLoopEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceError(void*, HRESULT) noexcept
{
}


// --- End of File ---