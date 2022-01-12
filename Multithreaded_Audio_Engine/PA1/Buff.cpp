//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "Buff.h"

Buff::Buff(unsigned int _reservedSize)
	: poBuff(new unsigned char[_reservedSize]() ),
	mCurrSize(0),
	mReservedSize(_reservedSize),
	mFullFlag(false)
{
	assert(poBuff);
}

Buff::~Buff()
{
	delete poBuff;
}

unsigned char * Buff::GetBuff()
{
	assert(poBuff);
	return poBuff;
}

unsigned int &Buff::GetCurrSize()
{
	return mCurrSize;
}

void Buff::SetCurrSize(unsigned int size)
{
	mCurrSize = size;
}

void Buff::SetFull()
{
	mFullFlag = true;
}

void Buff::SetEmpty()
{
	mFullFlag = false;
}


// -- End of File --
