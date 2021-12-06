//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AVolSnd.h"
#include "ASndMan.h"

AVolSnd::AVolSnd(SndID snd_id, Snd* p, float snd_vol)
	:ACommand(snd_id, p), vol(snd_vol)
{
}

void AVolSnd::Execute()
{
	// Get the ASnd
	ASnd* pA;

	this->pSnd->proGetASnd(pA);
	if (pA != nullptr)
	{
		pA->Vol(this->vol);
	}

	// Now change its attributes
	

}

// --- End of File ---
