//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef A_H
#define A_H

using namespace ThreadFramework;

class A : public BannerBase
{
public:
	A(const char *const pName);

	// functor
	void operator()();

};


#endif
