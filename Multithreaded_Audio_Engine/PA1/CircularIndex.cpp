//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "CircularIndex.h"

CircularIndex::CircularIndex(int buffSize)
{
	// Need to be a power of two...
	this->size = buffSize;
	this->mask = (unsigned int)(buffSize - 1);
	this->index = 0;
}

// postfix
int CircularIndex::operator++(int)
{
	this->index++;

	// Circular 
	this->index = this->index & (int)this->mask;

	return this->index;
}

bool CircularIndex::operator==(const CircularIndex &tmp)
{
	assert(this->size == tmp.size);
	return (this->index == tmp.index);
}

bool CircularIndex::operator!=(const CircularIndex &tmp)
{
	assert(this->size == tmp.size);
	return (this->index != tmp.index);
}

int CircularIndex::getIndex() const
{
	return this->index;
}


