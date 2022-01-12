//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h>  

// Foward Declarations
class Matrix;

// class
class Vect4D : Align16
{
public:
	friend class Matrix;

	// big four
	Vect4D()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};
	
	~Vect4D() = default;

	Vect4D& operator= (const __m128& tmp);

	Vect4D(const __m128& tm) : _m(tm) 
	{};

	
	Vect4D(float tx, float ty, float tz, float tw = 1.0f);



	void set(const float& tx, const float& ty, const float& tz, const float tw = 1.0f);

	const Vect4D operator + (const Vect4D& tmp) const
	{
		return Vect4D(this->x + tmp.x, this->y + tmp.y, this->z + tmp.z, this->w + tmp.w);
	};

	const Vect4D operator - (const Vect4D& tmp) const
	{
		return Vect4D(this->x - tmp.x, this->y - tmp.y, this->z - tmp.z, this->w - tmp.w);
	};
	const Vect4D operator  * (const float  scale) const
	{
		return Vect4D(x * scale, y * scale, z * scale, w * scale);
	};



	const void norm(Vect4D& out)const;
	const void Cross(const Vect4D& vin, Vect4D& vout) const;

	float& operator[](const VECT_ENUM e);

public:

	// anonymous union
	union
	{
		__m128	_m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};


#endif  

// End of file

