//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "Vect4D.h"


Vect4D::Vect4D(float tx, float ty, float tz, float tw)

{
	
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;

}





Vect4D& Vect4D::operator = (const __m128& tmp)
{

	this->_m.m128_f32[0] = tmp.m128_f32[0];
	this->_m.m128_f32[1] = tmp.m128_f32[1];
	this->_m.m128_f32[2] = tmp.m128_f32[2];
	this->_m.m128_f32[3] = tmp.m128_f32[3];

	return *this;
}





const void Vect4D::norm(Vect4D& out) const
{
	
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	mag = 1.0f / mag;

	
	out._m = _mm_setr_ps(this->x * mag, this->y * mag, this->z * mag, 1.0f);

	
}





float& Vect4D::operator[](const VECT_ENUM e)
{
	switch (e)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		assert(0);
		return x;
	}
}

const void Vect4D::Cross(const Vect4D& vin, Vect4D& vout) const
{
	
	vout.x = (y * vin.z - z * vin.y);
	vout.y = (z * vin.x - x * vin.z);
	vout.z = (x * vin.y - y * vin.x);
	
}

void Vect4D::set(const float& tx, const float& ty, const float& tz, const float tw)
{
	
	this->_m = _mm_set_ps(tw, tz, ty, tx);
}

// End of file
