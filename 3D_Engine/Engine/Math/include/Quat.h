//-----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Matrix.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace Azul
{
	class Quat final : public Align16
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

		// Do your magic here

		// Constructors

			// default Constructor 
		explicit Quat(void);

		// copy constructor
		Quat(const Quat &qIn);

		// set real, vector	component
		Quat(const Vect &vect, const float real);

		// set every component	
		Quat(const float vx, const float vy, const float vz, const float real);

		// by matrix ( essentially Quat to Matrix conversion )
		explicit Quat(const Matrix &mIn);

		//	Initialize to Identity Rotation
		explicit Quat(const Special  value);

		// Rotations by 1 angle:
		Quat(const Rot1 type, const float angle);

		// Rotations by 3 angle:
		Quat(const Rot3 type, const float angle_0, const float angle_1, const float angle_2);

		// Axis and Angle:
		Quat(const Rot type, const Vect &vAxis, const float angle_radians);

		// Orientation:
		Quat(const Orient, const Vect &dof, const Vect &up);

		// Destructors

			// default Destructor 
		~Quat(void);

		// Set
		void set(const Special type);
		void set(const Rot1 type, const float angle);
		void set(const Rot3 type, const float angle_0, const float angle_1, const float angle_2);

		// Axis and Angle:
		void set(const Rot type, const Vect &vAxis, const float angle_radians);

		// Orientation:
		void set(const Orient, const Vect &dof, const Vect &up);

		// set every component	
		void set(const float vx, const float vy, const float vz, const float real);

		// Set x value
		float &operator[](const x_enum value);

		// Set y value
		float &operator[](const y_enum value);

		// Set z value
		float &operator[](const z_enum value);

		// Set w value
		float &operator[](const w_enum value);

		float &qx();
		float &qy();
		float &qz();
		float &real();

		// set by Vector component, does not set the real component
		void setVect(const Vect &vect);

		// set real, vector	
		void set(const Vect &vect, const float real);

		// set by matrix ( essentially Quat to Matrix conversion )
		void set(const Matrix &m);

		// Get

			// Return the X component
		const float operator[](const x_enum value) const;

		// Return the Y component
		const float operator[](const y_enum value) const;

		// Return the Z component		
		const float operator[](const z_enum value) const;

		// Return the W (Real) component
		const float operator[](const w_enum value) const;

		const float qx()const;
		const float qy()const;
		const float qz()const;
		const float real()const;

		// Get Angle of rotation about the axis of rotation
		const float getAngle(void) const;

		// Get Vector component
		void getVect(Vect &vOut) const;

		// Get Axis of rotation
		void getAxis(Vect &vOut) const;

		// General member functions

		// dot product of two quaternions (4D)
		const float dot(const Quat &qin) const;

		// Magnitude

			// magnitude 
		const float mag(void) const;

		// magnitude Squared (Remember for Unit Quats, magSquared == 1.0f );
		const float magSquared(void) const;

		// inverse magnitude
		const float invMag(void) const;

		// Conjugate

			// Conjugate Quat in place
		Quat &conj(void);

		// Return conjuate Quat
		Quat getConj(void) const;

		// Transpose

		// Inverse Quat in place
		Quat &T(void);

		// Return inverse Quat	
		Quat getT(void) const;

		// Inverse

			// Inverse Quat in place
		Quat &inv(void);

		// Return inverse Quat
		Quat getInv(void) const;

		// Normalize

		// Normalize Quat in place
		Quat &norm(void);

		// Return Normalize Quat
		Quat getNorm(void) const;

		// Linear Operator

			// Linear Operator vout = Quat * Vector * Quat(conjugate)
			// vOut = Quat * vIn * Quat.conj()
		void Lqvqc(const Vect &vIn, Vect &vOut) const;

		// Linear Operator  vOut = Quat(conjugate) * Vector * Quat
		// vOut = Quat.conj() * vIn * Quat		
		void Lqcvq(const Vect &vIn, Vect &vOut) const;

		// Test functions

			// Return true if the two Quats are equal within epsilon of each other
		const bool isEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equivalent within epsilon of each other
		const bool isEquivalent(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equal but negative in direction within epsilon of each other
		const bool isNegEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equal but conjugate within epsilon of each other
		const bool isConjugateEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat represents Identity Rotation
		const bool isIdentity(const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat is normalized
		const bool isNormalized(const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat is a ZERO quat
		const bool isZero(const float epsilon = MATH_TOLERANCE) const;

		// Overload the = operator  

			// Assignment operator
		const Quat &operator=(const Quat &q);

		// Assignment operator
		const Quat &operator=(const Matrix &m);

		// Overload the + operator

			// +Quat
		const Quat operator+(void) const;

		// Quat + Quat 
		const Quat operator+(const Quat &q) const;

		// Quat += Quat
		const Quat &operator+=(const Quat &q);

		// Quat + Constant
		Quat operator+(const float a) const;

		// Quat += Constant
		const Quat &operator+=(const float a);

		// Constant + Quat
		friend Quat operator+(const float a, const Quat &q);

		// Overload the - operator

			// -Quat
		const Quat operator-(void) const;

		// Quat - Quat 
		Quat operator-(const Quat &q) const;

		// Quat -= Quat
		const Quat &operator-=(const Quat &q);

		// Quat - Constant
		Quat operator-(const float a) const;

		// Quat -= Constant
		const Quat &operator-=(const float a);

		// Constant - Quat
		friend Quat operator-(const float a, const Quat &q);

		// Overload the * operator

			// Quat * Quat 
		Quat operator*(const Quat &q) const;

		// Quat *= Quat
		const Quat &operator*=(const Quat &q);

		// Quat * Constant
		Quat operator*(const float a) const;

		// Quat *= Constant
		const Quat &operator*=(const float a);

		// Constant * Quat
		friend Quat operator*(const float a, const Quat &q);

		// Quat *= Matrix
		const Quat &operator*=(const Matrix &m);

		// Quat * Matrix 
		Matrix operator*(const Matrix &m) const;

		// Overload the / operator

			// Quat / Quat 
		Quat operator/(const Quat &q) const;

		// Quat /= Quat
		const Quat &operator/=(const Quat &q);

		// Quat / Constant
		Quat operator/(const float a) const;

		// Quat /= Constant
		const Quat &operator/=(const float a);

		// Constant / Quat
		friend Quat operator/(const float a, const Quat &q);

		// Multiply by element

			// Quat * Quat 
		const Quat multByElement(const Quat &q) const;

	private:
		void privSetRotX(const float a);
		void privSetRotXYZ(const float a, const float b, const float c);
		void privSetRotY(const float a);
		void privSetRotZ(const float a);
		void privSetRotAxisAngle(const Vect &axis, const float angle);

	private:

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};
		};

	};
}

#endif 

// ---  End of File ---------------
