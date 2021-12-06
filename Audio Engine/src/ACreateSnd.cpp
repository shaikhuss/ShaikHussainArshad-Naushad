//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ACreateSnd.h"
#include "ASndMan.h"
#include "VoiceCallback.h"
#include "SndMan.h"
#include "UserCallBack.h"

ACreateSnd::ACreateSnd(SndID snd_id, Snd* p, UserCallback* _pUserCallback)
	:ACommand(snd_id, p),
	pUserCallback(_pUserCallback)
{
}

void ACreateSnd::Execute()
{
	assert(this->id != SndID::Uninitialized);

	ASnd* pA = ASndMan::Add(this->id);
	assert(pA);

	// Update the SND call
	// This way its faster to execute commands on the Audio thread side

	assert(this->pSnd);
	pSnd->proSetASnd(pA);
	pA->SetSnd(pSnd);

	// user callback
	pA->poUserCallback = this->pUserCallback;

	// Set the ASnd pointer in the VoiceCallback - HACK
	// Not sure if this is the best place for this...
	Playlist* pPlaylist = pA->pPlaylist;
	assert(pPlaylist);

	Voice* pVoice = pPlaylist->pVoice;
	assert(pVoice);

	// OK to down cast this... might want to change voice.h to use VoiceCallback
	VoiceCallback* pCallback = (VoiceCallback*)pVoice->poCallback;
	assert(pCallback);

	if (this->id == SndID::Intro)
	{

		Trace::out("\n Intro");
		Snd* pSnd1 = SndMan::Find(SndID::A);
		pCallback->SetNextVoice(pSnd1);
	}

	if (this->id == SndID::A)
	{
		Snd* pSnd2 = SndMan::Find(SndID::AtoB);
		pCallback->SetNextVoice(pSnd2);
	}

	if (this->id == SndID::AtoB)
	{
		Snd* pSnd3 = SndMan::Find(SndID::B);
		pCallback->SetNextVoice(pSnd3);
	}

	if (this->id == SndID::B)
	{
		Snd* pSnd4 = SndMan::Find(SndID::BtoC);
		pCallback->SetNextVoice(pSnd4);
	}

	if (this->id == SndID::BtoC)
	{
		Snd* pSnd5 = SndMan::Find(SndID::C);
		pCallback->SetNextVoice(pSnd5);
	}

	if (this->id == SndID::C)
	{
		Trace::out("\nC");
		Snd* pSnd6 = SndMan::Find(SndID::CtoA);
		pCallback->SetNextVoice(pSnd6);
	}

	if (this->id == SndID::CtoA)
	{
		Trace::out("\nC");
		//Snd* pSnd7 = SndMan::Find(SndID::End);
		pCallback->SetNextVoice(nullptr);
	}

	

	if (this->id != SndID::CtoA && this->id != SndID::C && this->id != SndID::Intro && this->id != SndID::A && this->id != SndID::AtoB && this->id != SndID::B && this->id != SndID::BtoC)
	{
		
		pCallback->SetNextVoice(nullptr);
	}

	//else {
	//	pCallback->SetNextVoice(nullptr);
	//}


	//pCallback->SetNextVoice(nullptr);
	pCallback->SetASnd(pA);
}

// --- End of File ---
