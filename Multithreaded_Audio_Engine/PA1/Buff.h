//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef BUFF_H
#define BUFF_H

class Buff
{
public:
	Buff() = delete;
	Buff(const Buff &) = delete;
	Buff &operator = (const Buff &) = delete;
	~Buff();

	Buff(unsigned int reservedSize);
	unsigned char *GetBuff();
	unsigned int &GetCurrSize();
	void SetCurrSize(unsigned int size);

	void SetFull();
	void SetEmpty();

public:
	unsigned char *poBuff;
	unsigned int  mCurrSize;
	unsigned int  mReservedSize;
	bool          mFullFlag;
};

#endif

// -- End of File --
