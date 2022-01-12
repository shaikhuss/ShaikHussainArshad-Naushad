//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h>  
#include "Vect4D.h"

// forward declare
class Vect4D;

// class
class Matrix : Align16
{
public:

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	// big four
	Matrix();
	Matrix(const Matrix& t);
	~Matrix() = default;
	Matrix& operator= (const Matrix&);

	Matrix(const Vect4D& _v0, const Vect4D& _v1, const Vect4D& _v2, const Vect4D& _v3);
	

	Matrix::Matrix(const float& _m0, const float& _m1, const float& _m2, const float& _m3,
	const float& _m4, const float& _m5, const float& _m6, const float& _m7,
	const float& _m8, const float& _m9, const float& _m10, const float& _m11,
	const float& _m12, const float& _m13, const float& _m14, const float& _m15);

	void set(MatrixRowEnum row, Vect4D* t);
	void get(MatrixRowEnum row, Vect4D* vOut);

	void setIdentMatrix();
	void setTransMatrix(Vect4D* t);
	void setScaleMatrix(Vect4D* s);
	void setRotZMatrix(float Z_Radians);

	float& operator[](INDEX_ENUM e);

	Matrix operator*(Matrix& t);
	Matrix operator-(Matrix& t);



	Matrix& Matrix::operator/=(float t);

	void Matrix::Inverse(Matrix& out);

	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};


#endif 

// End of File

