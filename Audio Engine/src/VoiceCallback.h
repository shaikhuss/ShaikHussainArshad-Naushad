//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef _VOICE_CALLBACK_H_
#define _VOICE_CALLBACK_H_

#include "XAudio2Wrapper.h"
#include "ASnd.h"


//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	VoiceCallback(const VoiceCallback&) = delete;
	VoiceCallback(VoiceCallback&&) = delete;
	VoiceCallback& operator = (const VoiceCallback&) = delete;
	VoiceCallback& operator = (VoiceCallback&&) = delete;

	VoiceCallback();
	virtual ~VoiceCallback();


	bool IsFinished() const;

	void SetNextVoice(Snd* pVoice)
	{

		if (pVoice == nullptr)
		{
			pNextVoice = nullptr;
		}
		else {
			assert(pVoice);
			pNextVoice = pVoice;
		}
	}
	void SetASnd(ASnd* _pASnd);
	ASnd* GetASnd();


	void STDMETHODCALLTYPE OnStreamEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) noexcept override;
	void STDMETHODCALLTYPE OnBufferEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override;
	void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) noexcept override;

	// Data: 
	ASnd* pASnd;
	bool   finished = false;
	int	   count = 0;
	Snd* pNextVoice;
};

#endif

// End of File 
