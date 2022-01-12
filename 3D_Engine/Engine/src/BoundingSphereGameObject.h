//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef BOUNDING_SPHERE_GAME_OBJECT_H
#define BOUNDING_SPHERE_GAME_OBJECT_H

#include "MathEngine.h"
#include "GameObject.h"
#include "AnimTime.h"

namespace Azul
{
	class BoundingSphereGameObject : public GameObject
	{
	public:
		BoundingSphereGameObject(GraphicsObject *graphicsObject);

		// Big four
		BoundingSphereGameObject() = delete;
		BoundingSphereGameObject(const BoundingSphereGameObject &) = delete;
		BoundingSphereGameObject &operator=(BoundingSphereGameObject &) = delete;
		virtual ~BoundingSphereGameObject();

		void SetBoundingSphereReference(GameObject *pGameObj);

		virtual void Update(const char* buff, AnimTime currentTime) override;

	private:
		void privUpdate(const char* buff, AnimTime currentTime);
		void privUpdateBoundingSphereReference(const char* buff, AnimTime currentTime);

		// Data: ------------------
		GameObject *pRefGameObj;

	public:
		Vect *poScale;
		Vect *poTrans;
	};

}

#endif

// --- End of File ---
