//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <Math.h>
#include "Vect4D.h"
#include "Matrix.h"

Matrix::Matrix()
{	// constructor for the matrix
	this->m0 = 0.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 0.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 0.0f;
	this->m11 = 0.0f;

	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 0.0f;
	

}

Matrix::Matrix(const Matrix& t)
{ 

	this->m0 = t.m0;
	this->m1 = t.m1;
	this->m2 = t.m2;
	this->m3 = t.m3;

	this->m4 = t.m4;
	this->m5 = t.m5;
	this->m6 = t.m6;
	this->m7 = t.m7;

	this->m8 = t.m8;
	this->m9 = t.m9;
	this->m10 = t.m10;
	this->m11 = t.m11;

	this->m12 = t.m12;
	this->m13 = t.m13;
	this->m14 = t.m14;
	this->m15 = t.m15;
}

Matrix::Matrix(const float& _m0, const float& _m1, const float& _m2, const float& _m3,
	const float& _m4, const float& _m5, const float& _m6, const float& _m7,
	const float& _m8, const float& _m9, const float& _m10, const float& _m11,
	const float& _m12, const float& _m13, const float& _m14, const float& _m15)
{ 

	this->m0 = _m0;
	this->m1 = _m1;
	this->m2 = _m2;
	this->m3 = _m3;

	this->m4 = _m4;
	this->m5 = _m5;
	this->m6 = _m6;
	this->m7 = _m7;

	this->m8 = _m8;
	this->m9 = _m9;
	this->m10 = _m10;
	this->m11 = _m11;

	this->m12 = _m12;
	this->m13 = _m13;
	this->m14 = _m14;
	this->m15 = _m15;
}

Matrix& Matrix::operator= (const Matrix& t)
{

	this->m0 = t.m0;
	this->m1 = t.m1;
	this->m2 = t.m2;
	this->m3 = t.m3;

	this->m4 = t.m4;
	this->m5 = t.m5;
	this->m6 = t.m6;
	this->m7 = t.m7;

	this->m8 = t.m8;
	this->m9 = t.m9;
	this->m10 = t.m10;
	this->m11 = t.m11;

	this->m12 = t.m12;
	this->m13 = t.m13;
	this->m14 = t.m14;
	this->m15 = t.m15;
	return *this;
}

Matrix::Matrix(const Vect4D& _v0, const Vect4D& _v1, const Vect4D& _v2, const Vect4D& _v3)
{
	{
		this->v0 = _v0;
		this->v1 = _v1;
		this->v2 = _v2;
		this->v3 = _v3;
	}
}


void Matrix::setIdentMatrix()
{
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;

	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 1.0f;
}

void Matrix::setTransMatrix(Vect4D* t)
{ 
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;

	this->m12 = t->x;
	this->m13 = t->y;
	this->m14 = t->z;
	this->m15 = 1.0f;
}

void Matrix::set(MatrixRowEnum row, Vect4D* t)
{

	switch (row)
	{
	case MATRIX_ROW_0:
		this->m0 = t->x;
		this->m1 = t->y;
		this->m2 = t->z;
		this->m3 = t->w;
		break;

	case MATRIX_ROW_1:
		this->m4 = t->x;
		this->m5 = t->y;
		this->m6 = t->z;
		this->m7 = t->w;
		break;

	case MATRIX_ROW_2:
		this->m8 = t->x;
		this->m9 = t->y;
		this->m10 = t->z;
		this->m11 = t->w;
		break;

	case MATRIX_ROW_3:
		this->m12 = t->x;
		this->m13 = t->y;
		this->m14 = t->z;
		this->m15 = t->w;
		break;

	default:
		assert(0);
	}
}

float& Matrix::operator[](INDEX_ENUM e)
{
	// get the individual elements
	switch (e)
	{
	case 0:
		return m0;
		break;
	case 1:
		return m1;
		break;
	case 2:
		return m2;
		break;
	case 3:
		return m3;
		break;
	case 4:
		return m4;
		break;
	case 5:
		return m5;
		break;
	case 6:
		return m6;
		break;
	case 7:
		return m7;
		break;
	case 8:
		return m8;
		break;
	case 9:
		return m9;
		break;
	case 10:
		return m10;
		break;
	case 11:
		return m11;
		break;
	case 12:
		return m12;
		break;
	case 13:
		return m13;
		break;
	case 14:
		return m14;
		break;
	case 15:
		return m15;
		break;
	default:
		assert(0);
		return m0;
		break;
	}
}

void Matrix::get(MatrixRowEnum row, Vect4D* t)
{ // get a row of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		t->x = this->m0;
		t->y = this->m1;
		t->z = this->m2;
		t->w = this->m3;
		break;

	case MATRIX_ROW_1:
		t->x = this->m4;
		t->y = this->m5;
		t->z = this->m6;
		t->w = this->m7;
		break;

	case MATRIX_ROW_2:
		t->x = this->m8;
		t->y = this->m9;
		t->z = this->m10;
		t->w = this->m11;
		break;

	case MATRIX_ROW_3:
		t->x = this->m12;
		t->y = this->m13;
		t->z = this->m14;
		t->w = this->m15;
		break;

	default:
		assert(0);
	}
}

Matrix Matrix::operator*(Matrix& rhs)
{
	Matrix A;
	__m128 tmp;

	tmp = _mm_set1_ps(this->v0.x);
	A.v0._m = _mm_mul_ps(tmp, rhs.v0._m);

	tmp = _mm_set1_ps(this->v0.y);
	A.v0._m = _mm_add_ps(A.v0._m, _mm_mul_ps(tmp, rhs.v1._m));

	tmp = _mm_set1_ps(this->v0.z);
	A.v0._m = _mm_add_ps(A.v0._m, _mm_mul_ps(tmp, rhs.v2._m));

	tmp = _mm_set1_ps(this->v0.w);
	A.v0._m = _mm_add_ps(A.v0._m, _mm_mul_ps(tmp, rhs.v3._m));


	tmp = _mm_set1_ps(this->v1.x);
	A.v1._m = _mm_mul_ps(tmp, rhs.v0._m);

	tmp = _mm_set1_ps(this->v1.y);
	A.v1._m = _mm_add_ps(A.v1._m, _mm_mul_ps(tmp, rhs.v1._m));

	tmp = _mm_set1_ps(this->v1.z);
	A.v1._m = _mm_add_ps(A.v1._m, _mm_mul_ps(tmp, rhs.v2._m));

	tmp = _mm_set1_ps(this->v1.w);
	A.v1._m = _mm_add_ps(A.v1._m, _mm_mul_ps(tmp, rhs.v3._m));


	tmp = _mm_set1_ps(this->v2.x);
	A.v2._m = _mm_mul_ps(tmp, rhs.v0._m);
		 
	tmp = _mm_set1_ps(this->v2.y);
	A.v2._m = _mm_add_ps(A.v2._m, _mm_mul_ps(tmp, rhs.v1._m));
		 
	tmp = _mm_set1_ps(this->v2.z);
	A.v2._m = _mm_add_ps(A.v2._m, _mm_mul_ps(tmp, rhs.v2._m));
		 
	tmp = _mm_set1_ps(this->v2.w);
	A.v2._m = _mm_add_ps(A.v2._m, _mm_mul_ps(tmp, rhs.v3._m));
		 
		 
	tmp =_mm_set1_ps(this->v3.x);
	A.v3._m = _mm_mul_ps(tmp, rhs.v0._m);
		 
	tmp = _mm_set1_ps(this->v3.y);
	A.v3._m = _mm_add_ps(A.v3._m, _mm_mul_ps(tmp, rhs.v1._m));
		 
	tmp = _mm_set1_ps(this->v3.z);
	A.v3._m = _mm_add_ps(A.v3._m, _mm_mul_ps(tmp, rhs.v2._m));
		 
	tmp = _mm_set1_ps(this->v3.w);
	A.v3._m = _mm_add_ps(A.v3._m, _mm_mul_ps(tmp, rhs.v3._m));

	return A;
}
Matrix Matrix::operator-(Matrix& t)
{


	return Matrix(_mm_sub_ps(this->v0._m, t.v0._m), _mm_sub_ps(this->v1._m, t.v1._m),
		_mm_sub_ps(this->v2._m, t.v2._m), _mm_sub_ps(this->v3._m, t.v3._m));
}




Matrix& Matrix::operator/=(float rhs)
{
	
	float inv_rhs = 1.0f / rhs;

	__m128 tmp = _mm_set_ps1(inv_rhs);

	this->v0._m = _mm_mul_ps(this->v0._m, tmp);
	this->v1._m = _mm_mul_ps(this->v1._m, tmp);
	this->v2._m = _mm_mul_ps(this->v2._m, tmp);
	this->v3._m = _mm_mul_ps(this->v3._m, tmp);

	return *this;
}

void Matrix::Inverse(Matrix& out)
{
	

	out.v0 = this->v0;
	out.v1 = this->v1;
	out.v2 = this->v2;
	out.m12 = this->m12 * -1;
	out.m13 = this->m13 * -1;
	out.m14 = this->m14 * -1;
	out.m15 = this->m15;
}

void Matrix::setScaleMatrix(Vect4D* scale)  	
{
	

	
	this->v0._m = _mm_set_ps(0.0f, 0.0f, 0.0f, scale->x);
	this->v1._m = _mm_set_ps(0.0, 0.0f, scale->y, 0.0f);
	this->v2._m = _mm_set_ps(0.0f, scale->z, 0.0f, 0.0f);
	this->v3._m = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);


}

void Matrix::setRotZMatrix(float az)
{


	Matrix tmp;
	tmp.m0 = cosf(az);
	tmp.m1 = -sinf(az);
	tmp.m2 = 0.0f;
	tmp.m3 = 0.0f;

	tmp.m4 = sinf(az);
	tmp.m5 = cosf(az);
	tmp.m6 = 0.0f;
	tmp.m7 = 0.0f;

	tmp.m8 = 0.0f;
	tmp.m9 = 0.0f;
	tmp.m10 = 1.0f;
	tmp.m11 = 0.0f;

	tmp.m12 = 0.0f;
	tmp.m13 = 0.0f;
	tmp.m14 = 0.0f;
	tmp.m15 = 1.0f;

	*this = tmp;
}

// End of file