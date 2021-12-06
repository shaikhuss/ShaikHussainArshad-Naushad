//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "XAudio2Wrapper.h"
#include <x3daudio.h>
#include "AudioEngine.h"
#include "Voice.h"
#include "VoiceCallback.h"

struct VoiceNameTable
{
	Voice::ID id;
	const char *pString;
};

VoiceNameTable table[] =
{
	{ Voice::ID::Fiddle, "Fiddle" },
	{ Voice::ID::Bassoon, "Bassoon" },
	{ Voice::ID::Calliope, "Calliope" },
	{ Voice::ID::Beethoven, "Beethoven" },
	{ Voice::ID::Electro, "Electro" },
	{ Voice::ID::Alarm, "Alarm" },
	{ Voice::ID::Oboe, "Oboe" },
	{ Voice::ID::SongA, "SongA" },
	{ Voice::ID::SongB, "SongB" },
	{ Voice::ID::Intro, "Intro" },
	{ Voice::ID::A, "A" },
	{ Voice::ID::AtoB, "AtoB" },
	{ Voice::ID::B, "B" },
	{ Voice::ID::BtoC, "BtoC" },
	{ Voice::ID::C, "C" },
	{ Voice::ID::CtoA, "CtoA" },
	{ Voice::ID::End, "End" },
	{ Voice::ID::Uninitialized, "Uninitialized"}
};

#define VoiceTableCount  (sizeof(table) / sizeof(table[0]))

Voice::Voice()
	: poBuff(nullptr),
	poCallback(nullptr),
	poSourceVoice(nullptr),
	pWave(nullptr),
	id(ID::Uninitialized),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status Voice::Set(Voice::ID _id, Wave *_pWave)
{	
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// set id
		this->id = _id;

		// Set the wave pointer
		assert(_pWave);
		this->pWave = _pWave;

		// Create a voice callback
		this->poCallback = new VoiceCallback();
		assert(this->poCallback);

		// create and setup xaudio2 buffer
		this->poBuff = new XAUDIO2_BUFFER_ALIAS();
		assert(this->poBuff);

		// Set the Buffer info...
		*this->poBuff = { 0 };	  // zeros out the complete structure
		this->poBuff->AudioBytes = pWave->rawBuffSize;  //buffer containing audio data
		this->poBuff->pAudioData = pWave->poRawBuff;  //size of the audio buffer in bytes
		assert(pWave->poRawBuff);

		this->poBuff->Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
		this->poBuff->LoopCount = 0;


		// Get XAudio2 from manager
		IXAudio2* pXAudio2 = AudioEngine::GetXAudio2();
		assert(pXAudio2);

		// Create Source Voice
		this->poSourceVoice = nullptr;

		HRESULT hr;
		hr = pXAudio2->CreateSourceVoice(&this->poSourceVoice, (WAVEFORMATEX*)this->pWave->poWfx, 0, XAUDIO2_MAX_FREQ_RATIO, this->poCallback);
		assert(hr == S_OK);
		assert(this->poSourceVoice);

		// Submit it
		hr = this->poSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)this->poBuff);
		assert(hr == S_OK);
		assert(this->poBuff);
	}
	return lock;
}

Voice::~Voice()
{
	// ------------------------------------------------------------------------
	//   Handle is invalidated automatically - through ~handle() destructor
	// ------------------------------------------------------------------------
	this->privClear();

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Voice::Start()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->Start(0);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::Stop()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->Stop(0);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::Vol(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->SetVolume(snd_vol);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::Pan(float snd_pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Get the Audio Engine... 
		IXAudio2MasteringVoice *pMasterVoice = AudioEngine::GetMasterVoice();
		assert(pMasterVoice);
		assert(this->poSourceVoice);

		DWORD dwChannelMask;
		pMasterVoice->GetChannelMask(&dwChannelMask);

		// SPEAKER_STEREO // SPEAKER_FRONT_LEFT (0x1) | SPEAKER_FRONT_RIGHT (0x2)
		//assert(dwChannelMask == 0x3);
		//int pan = 0;
		// pan of -1.0 indicates all left speaker, 
		// 1.0 is all right speaker, 0.0 is split between left and right
		float left = 0.5f - snd_pan / 2;
		float right = 0.5f + snd_pan / 2;
		//float left = 0.5f -  / 2.0f;
		//float right = 0.5f + -1.0f / 2.0f;
		snd_pan;
		float outputMatrix[8];
		for (int i = 0; i < 8; i++)
		{
			outputMatrix[i] = 0;
		}
		
		//outputMatrix[snd_pan] = 1.0f;

		switch (dwChannelMask)
		{
		case SPEAKER_MONO:
			outputMatrix[0] = 1.0;
			break;
		case SPEAKER_STEREO:
		case SPEAKER_2POINT1:
		case SPEAKER_SURROUND:
			outputMatrix[0] = left;
			outputMatrix[1] = right;
			break;
		case SPEAKER_QUAD:
			outputMatrix[0] = outputMatrix[2] = left;
			outputMatrix[1] = outputMatrix[3] = right;
			break;
		case SPEAKER_4POINT1:
			outputMatrix[0] = outputMatrix[3] = left;
			outputMatrix[1] = outputMatrix[4] = right;
			break;
		case SPEAKER_5POINT1:
		case SPEAKER_7POINT1:
		case SPEAKER_5POINT1_SURROUND:
			outputMatrix[0] = outputMatrix[4] = left;
			outputMatrix[1] = outputMatrix[5] = right;
			break;
		case SPEAKER_7POINT1_SURROUND:
			outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
			outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
			break;
		}
		//outputMatrix[snd_pan] = right;
		//this->poCallback->OnStreamEnd();
		// Assuming pVoice sends to pMasteringVoice
		XAUDIO2_VOICE_DETAILS VoiceDetails;
		this->poSourceVoice->GetVoiceDetails(&VoiceDetails);

		XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
		pMasterVoice->GetVoiceDetails(&MasterVoiceDetails);

		HRESULT hr;
		hr = this->poSourceVoice->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
		assert(hr == S_OK);

	}
	return lock;
}

Handle::Status Voice::GetId(Voice::ID &_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

const char *Voice::privGetStringName()
{
	const char* p = "NOT_FOUND";
	const char* pTmp = p;

	for (int i = 0; i < VoiceTableCount; i++)
	{
		if (this->id == table[i].id)
		{
			pTmp = table[i].pString;
			break;
		}
	}

	return pTmp;
}

Handle::Status Voice::SetId(Voice::ID _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = _id;
	}
	return lock;
}

void Voice::privClear()
{
	if (this->poSourceVoice)
	{
		// in case it was playing... 
		this->poSourceVoice->Stop();

		// Voice was initialized in XAudio2... so its destroyed there
		this->poSourceVoice->DestroyVoice();
	}
	this->poSourceVoice = nullptr;

	delete this->poBuff;
	this->poBuff = nullptr;

	// New warning C5205 warning... problem its in <xaudio2.h>
	delete this->poCallback;
	this->poCallback = nullptr;

}

Handle::Status Voice::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Wash - clear the entire hierarchy
		DLink::Clear();

		// Sub class clear
		this->privClear();
	}
	return lock;
}

Handle::Status Voice::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %s (%p) \n", this->privGetStringName(), this);
	}
	return lock;
}

// --- End of File ---
