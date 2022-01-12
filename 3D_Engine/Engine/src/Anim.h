//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "GameObjectAnim.h"
#include "Clip.h"
#include "Skeleton.h"
#include <GraphicsObject_SkinTexture.h>

namespace Azul
{ 
	// For Teddy
	#define NUM_BONES 20
	#define BONE_WIDTH 10.0f

	// For Human
	//#define NUM_BONES 80
	//#define BONE_WIDTH 30.0f

	class Anim
	{
	public:
		Anim(const char* const pModelFileName, GraphicsObject_SkinTexture* pSkinGraphicsObject);
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		~Anim();

		void setClip(Clip* pClip);

		Clip* getClip();

		void Animate(AnimTime tCurr, Clip* poClip);
		void PoseSkeleton(AnimTime tCurr);
		Clip* getClip2();
		AnimTime FindMaxTime();

	private:
		void privSetBonePose(GameObjectAnim *node);

	// hack
	public:	
		Clip* poClip;
		Clip* poClip2;
		Clip* poClip0;
	

	private:
		Skeleton       *poSkeleton;

		int   numBones;
		float boneWidth;
	};


}

#endif

// --- End of File ---
