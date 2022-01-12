//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H

#include "GameObject.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"

namespace Azul
{
	class SimpleGameObject : public GameObject
	{
	public:
		enum MoveDir
		{
			Move_X,
			Move_Y,
			Move_Z,
			Rot_X,
			Rot_Y,
			Move_None
		};

	public:
	public:
		SimpleGameObject(GraphicsObject* graphicsObject);

		// Big four
		SimpleGameObject() = delete;
		SimpleGameObject(const SimpleGameObject&) = delete;
		SimpleGameObject& operator=(SimpleGameObject&) = delete;
		virtual ~SimpleGameObject();

		virtual void Update(const char* buff, AnimTime t);

		void SetScale(float sx, float sy, float sz);
		void SetPos(float x, float y, float z);

		void setMove(MoveDir move);

		void privUpdate(const char* buff, AnimTime currentTime);


	public:   // add accessors later
		Vect* poScale;
		Vect* poTrans;
		float posX;
		float posY;
		float deltaRotY;
		float deltaRotZ;
		float rotY;
		float rotZ;

		MoveDir moveDir;

	};

}

#endif

// --- End of File ---
