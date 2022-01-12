//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"
#include <GraphicsObject_SkinTexture.h>

namespace Azul
{
	class AnimController
	{
	public:
		AnimController(AnimTime delta,GraphicsObject_SkinTexture* pSkinGraphicsObject,const char* const pModelFileName);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void Update(Clip* pClip, AnimTime max);

	private:
		TimerController *poTimerControl;

	// hack
	public:
		Anim            *poAnim;

	};
}

#endif

// --- End of File ---
