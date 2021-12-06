//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#include "ASnd.h"
#include "PlaylistMan.h"
#include "SndMan.h"
#include "ASndMan.h"
#include "UserCallBack.h"
#include "GUserCallback.h"

ASnd::ASnd()
: id(SndID::Uninitialized),
pPlaylist(nullptr),
pSnd(nullptr),
poUserCallback(nullptr),
vol(0.5f),
pan(0),
handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status ASnd::Stop()
{
	// Command to end the sound
	this->SndEnd();

	// HACK - look at handles... what is needed
	return Handle::Status::SUCCESS;
}

Handle::Status  ASnd::SndEnd()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pPlaylist);

		Trace::out("--------- Snd end() --------------\n");

		// UserCallback?
		if (this->poUserCallback)
		{
			// HaCK ALERT7
			char* pName = this->pPlaylist->pVoice->pWave->strName;
			assert(pName);

			int timeInMS;
			this->pSnd->GetTimeInMS(timeInMS);

			this->poUserCallback->Set(this->pSnd, pName, timeInMS);
			

			GUserCallback* pGUserCB = new GUserCallback(this->poUserCallback);
			assert(pGUserCB);

			// ownership was transfered to GUserCallback
			this->poUserCallback = nullptr;

			CircularData* pQueue = SndMan::GetGameInQueue();
			assert(pQueue);
			pQueue->PushBack(pGUserCB);
			
		}


		// Playlist (which will deal with Voice)
		pPlaylist->SndEnd();

		// Snd needs to be alerted
		assert(this->pSnd);
		this->pSnd->RemoveFromPriorityTable();
		this->pSnd->proSetASnd(nullptr);
		SndMan::Remove(this->pSnd);

		// ASndMan - remove from the active list
		this->pSnd = nullptr;
		ASndMan::Remove(this);

		Snd::PrintPriorityTable();

	}
	return lock;
}

Handle::Status  ASnd::Play()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pPlaylist);

		// Kick the can
		this->pPlaylist->Play();
	}
	return lock;
}

Handle::Status ASnd::Vol(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pPlaylist);

		this->vol = snd_vol;

		// Kick the can
		this->pPlaylist->Vol(this->vol);
	}
	return lock;
}

Handle::Status ASnd::Pan(float snd_pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pPlaylist);

		this->pan = snd_pan;

		// Kick the can
		this->pPlaylist->Pan(this->pan);
	}
	return lock;
}


Handle::Status ASnd::SetId(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
	}
	return lock;
}

Handle::Status ASnd::GetId(SndID &_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

void ASnd::SetSnd(Snd* _pSnd)
{
	assert(_pSnd);
	this->pSnd = _pSnd;
}

Snd* ASnd::GetSnd()
{
	return this->pSnd;
}

Handle::Status ASnd::Wash()
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

Handle::Status ASnd::Set(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pPlaylist = PlaylistMan::Add(snd_id);
		this->id = snd_id;

		this->pSnd = nullptr;
		this->vol = 0.5f;
		this->pan = 0;

	}
	return lock;
}

void ASnd::privClear()
{
	this->id = SndID::Uninitialized;

	// Remove the playlist if recycling
	if (this->pPlaylist)
	{
		PlaylistMan::Remove(this->pPlaylist);
		this->pPlaylist = nullptr;
	}

	delete this->poUserCallback;
	this->poUserCallback = nullptr;

	this->pSnd = nullptr;
	this->vol = 0.5f;
	this->pan = 0;
}

Handle::Status ASnd::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}

ASnd::~ASnd()
{
	this->privClear();
}

// --- End of File ---
