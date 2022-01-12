//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "SimpleGameObject.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Model.h"

namespace Azul
{
	SimpleGameObject::SimpleGameObject(GraphicsObject* pGraphicsObject)
		: GameObject(pGraphicsObject)
	{
		assert(pGraphicsObject);
		this->poTrans = new Vect(0.1f, 0.2f, 0.4f);
		this->poScale = new Vect(1.0f, 1.0f, 1.0f);
		assert(this->poTrans);
		assert(this->poScale);

		this->rotY = 2.0f;
		this->rotZ = 0.0f;
		this->deltaRotZ = 0.0f;
		this->deltaRotY = 0.0f;
	}

	SimpleGameObject::~SimpleGameObject()
	{
		delete this->poTrans;
		delete this->poScale;
	}

	void SimpleGameObject::setMove(MoveDir move)
	{
		this->moveDir = move;
	};

	void SimpleGameObject::privUpdate(const char* buff, AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);
		AZUL_UNUSED_VAR(buff);
		float delta = 0.01f;

		static float dirX = -1.0f;
		static float dirY = 1.5f;
		static float dirZ = 1.0f;

		switch (this->moveDir)
		{
		case Move_X:
			this->poTrans->x() += (delta * dirX);
			if (this->poTrans->x() > 6.0f || this->poTrans->x() < -6.0f)
			{
				dirX *= -1.0f;
			}
			break;

		case Rot_Y:
			this->rotY += 0.1f;

			break;

		case Rot_X:
			this->rotZ += 0.05f;

			break;
		case Move_Y:
			this->poTrans->y() += (delta * dirY);
			if (this->poTrans->y() > 4.0f || this->poTrans->y() < -4.0f)
			{
				dirY *= -1.0f;
			}
			break;

		case Move_Z:
			this->poTrans->z() += (delta * dirZ);
			if (this->poTrans->z() > 7.0f || this->poTrans->z() < -5.0f)
			{
				dirZ *= -1.0f;
			}
			break;

		case Move_None:
		default:
			break;
		}

		// Goal: update the world matrix

		this->rotY += deltaRotY;
		this->rotZ += deltaRotZ;
		Vect Trans = Vect(-150.5f, 200.5f, 300.0f);
		Matrix T = Matrix(Matrix::Trans::XYZ, *this->poTrans);
		Matrix Scale = Matrix(Matrix::Scale::XYZ, *this->poScale);
		//Matrix TransA(Matrix::Trans::XYZ, 0.5f, 0.25f, 0.1f);
		Matrix RotY(Matrix::Rot1::Y, this->rotY);
		Matrix RotZ(Matrix::Rot1::Z, this->rotZ);

		// world matrix
		*this->poWorld = Scale * RotY * RotZ * T;
	}

	void SimpleGameObject::Update(const char* buff, AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(buff, currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void SimpleGameObject::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void SimpleGameObject::SetPos(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

}

// --- End of File ---
