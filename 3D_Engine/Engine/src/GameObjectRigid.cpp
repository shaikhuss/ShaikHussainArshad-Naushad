//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "GameObjectRigid.h"
#include "GraphicsObject.h"
#include "TeddyModel.h"

namespace Azul
{
	
	GameObjectRigid::GameObjectRigid(GraphicsObject *pGraphicsObject)
		: GameObject(pGraphicsObject)
	{
		assert(pGraphicsObject);

		this->poScale = new Vect(1.5f, 1.5f, 1.5f);
		assert(this->poScale);

		this->poTrans = new Vect(1.0f, 1.0f, 1.0f);
		assert(this->poTrans);

		this->angle_x = 1.0f;
		this->angle_y = 1.0f;
		this->angle_z = 1.0f;
	}

	GameObjectRigid::~GameObjectRigid()
	{
		delete this->poTrans;
		delete this->poScale;
	}

	void GameObjectRigid::privUpdate(const char* buff, AnimTime)
	{
		if (strcmp(buff, "Humanoid_Rigid") == 0)
		{
			//for Humanoid
			//Vect Trans = Vect(280.172638f, 1288.917847f - 500, 526.212402f);
			//Matrix T = Matrix(Matrix::Trans::XYZ, -Trans);
			//Matrix M = T;
			//Matrix R = Matrix(Matrix::Rot1::Z, -80);
			//Matrix S = Matrix(Matrix::Scale::XYZ, 0.5, 0.5, 0.5);
			//
			//*this->poWorld = R;

		}
		// Special transform for Teddy
		else if (strcmp(buff, "Teddy_Rigid") == 0)
		{
			Matrix S = Matrix(Matrix::Scale::XYZ, 2.0, 2.0, 2.0);
			Matrix Rx = Matrix(Matrix::Rot1::X, MATH_PI2);
			Matrix Rz = Matrix(Matrix::Rot1::Z, 1.7f);
			Matrix M = Rx * Rz * S;

			*this->poWorld = M;
		}
		//Skin
		else if ((strcmp(buff, "HumanSkin Object") == 0 || strcmp(buff, "Skin Object") == 0))
		{
			Matrix S(Matrix::Scale::XYZ, *this->poScale);
			Matrix T(Matrix::Trans::XYZ, *this->poTrans);
			Matrix Rx = Matrix(Matrix::Rot1::X, angle_x);
			Matrix Ry = Matrix(Matrix::Rot1::Y, angle_y);
			Matrix Rz = Matrix(Matrix::Rot1::Z, angle_z);
			Matrix M = S * Rx * Ry * Rz * T;
			
			*this->poWorld = M;
			
		}
	
	}

	void GameObjectRigid::Update(const char* buff,AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(buff,currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}
}

// --- End of File ---
