//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_RIGID_H
#define GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "MathEngine.h"
#include "GraphicsObject.h"

namespace Azul
{
	// Keenan(33)
	class GameObjectRigid : public GameObject
	{
	public:
		GameObjectRigid(GraphicsObject *graphicsObject);

		// Big four
		GameObjectRigid() = delete;
		GameObjectRigid(const GameObjectRigid &) = delete;
		GameObjectRigid &operator=(GameObjectRigid &) = delete;
		virtual ~GameObjectRigid() override;

		virtual void Update(const char* buff, AnimTime currentTime);

	private:
		void privUpdate(const char* buff, AnimTime currentTime);

	public:
		Vect *poScale;
		Vect *poTrans;
		float angle_x;
		float angle_y;
		float angle_z;

	};
}

#endif

// --- End of File ---
