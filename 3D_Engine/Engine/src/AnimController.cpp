//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"

namespace Azul
{
	AnimController::AnimController(AnimTime delta, GraphicsObject_SkinTexture* pSkinGraphicsObject,const char* const pModelFileName)
	{
		// Animation object
		if(strcmp(pModelFileName, "teddy.spu") == 0)
		{
			this->poAnim = new Anim(pModelFileName, pSkinGraphicsObject);
			assert(this->poAnim);
		}
		else {
			this->poAnim = new Anim(pModelFileName, pSkinGraphicsObject);
		assert(this->poAnim);
		}

		// TimerController
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->poTimerControl);

	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerControl;
	}

	void AnimController::Update(Clip* pClip,AnimTime max)
	{
		this->poTimerControl->Update(max);

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime(), pClip);
	}
}

// --- End of File ---
