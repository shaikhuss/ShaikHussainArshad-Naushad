//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SndMan.h"
#include "ACreateSnd.h"
#include "AQuit.h"
#include "Timer.h"

SndMan* SndMan::poInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object - Image Default
//  * Dependency - TextureMan needs to be initialized before ImageMan
//
//---------------------------------------------------------------------------------------------------------


SndMan::SndMan(int reserveNum, int reserveGrow)
//: Manager() // <--- Kick the can (delegate)
{
	// At this point ImageMan is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Snd();
	assert(this->poNodeCompare != nullptr);

	this->poAudioInQueue = new CircularData();
	assert(poAudioInQueue);

	this->poGameInQueue = new CircularData();
	assert(poGameInQueue);

}

SndMan::~SndMan()
{
	// We created it... so we delete it
	delete this->poNodeCompare;
	Command* pCmd = nullptr;
	while (this->poAudioInQueue->PopFront(pCmd))
	{
		delete pCmd;
	}
	delete this->poAudioInQueue;
	while (this->poGameInQueue->PopFront(pCmd))
	{
		delete pCmd;
	}
	delete this->poGameInQueue;

	Trace::out("---> ~ASndMan()\n");

	// Next stop - base class
}


//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------

CircularData* SndMan::GetAudioInQueue()
{
	SndMan* pMan = SndMan::privGetInstance();
	return pMan->poAudioInQueue;
}

CircularData* SndMan::GetGameInQueue()
{
	SndMan* pMan = SndMan::privGetInstance();
	return pMan->poGameInQueue;
}

void SndMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new SndMan(reserveNum, reserveGrow);
	}

}

void SndMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// Get the instance
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}


void SndMan::Quit(SndID snd_id)
{
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	Snd* pNode = (Snd*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	//    priority = 0... !immediate
	//pNode->Stop();
	//while(pNode->pNext)
	
	pNode->Set(snd_id, 0,pNode);
	
	
	// Now create a the sound call on the Audio thread
	// Place the "Quit" command in the queue to the Audio thread
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	Command* pCmd = new AQuit(SndID::Quit, pNode);
	assert(pCmd);

	pOut->PushBack(pCmd);
}


Snd* SndMan::Add(SndID snd_id, UserCallback* pCallback, SndPriority snd_priority)
{
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	Snd* pNode = (Snd*)pMan->BaseAdd();
	
	assert(pNode != nullptr);
	if (snd_priority != 0)
	{
		pNode->RemoveSamePriority(snd_priority);
	}
	// Create a new one given a wash
	//pNode->Set(snd_id);
	pNode->Set(snd_id, snd_priority,pNode);
	
	// Now create a the sound call on the Audio thread
	// Place the "Create" command in the queue to the Audio thread
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);
	//pNode->RemoveFromPriorityTable();
	// Doesn't need to know snd_priority its only on game side
	Command* pCmd = new ACreateSnd(snd_id, pNode, pCallback);
	assert(pCmd);
	
	//Sound

	pOut->PushBack(pCmd);

	return pNode;
}

Snd* SndMan::Find(SndID snd_id)
{
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetID(snd_id);
	
	Snd* pData = (Snd*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void SndMan::Remove(Snd* pNode)
{
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void SndMan::Dump()
{
	SndMan* pMan = SndMan::privGetInstance();
	assert(pMan != nullptr);

	Trace::out("\n**************************************\n");
	Trace::out("SndMan::Dump()  \n");
	pMan->BaseDump();
	Trace::out("\n**************************************\n\n");
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* SndMan::DerivedCreateNode()
{
	DLink* pNode = new Snd();
	assert(pNode != nullptr);

	return pNode;
}

bool SndMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Snd* pDataA = (Snd*)pLinkA;
	Snd* pDataB = (Snd*)pLinkB;

	bool status = false;
	SndID A_id;
	SndID B_id;

	pDataA->GetID(A_id);
	pDataB->GetID(B_id);

	if (A_id == B_id)
	{
		status = true;
	}

	return status;
}

void SndMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Snd* pNode = (Snd*)pLink;
	pNode->Wash();
}

void SndMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Snd* pData = (Snd*)pLink;
	pData->Dump();
}

void SndMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Snd* pData = (Snd*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
SndMan* SndMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(poInstance != nullptr);

	return poInstance;
}

// --- End of File ---
