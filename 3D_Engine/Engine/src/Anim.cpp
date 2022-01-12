//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "Anim.h"
#include "Constants.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Mixer.h"
#include "PCSTreeForwardIterator.h"
#include "GameObjectMan.h"
#include "Clip.h"
#include <ChunkHeader.h>
#include <eat.h>
#include <AnimTransition.h>
#include "TransitionManager.h"

namespace Azul
{
	Anim::Anim(const char* const pModelFileName, GraphicsObject_SkinTexture* pSkinGraphicsObject)
		:	poClip(nullptr),
		poClip2(nullptr),
		poClip0(nullptr),
		poSkeleton(nullptr),
		numBones(NUM_BONES),
		boneWidth(BONE_WIDTH)
	{
		if (strcmp(pModelFileName, "teddy.spu") == 0)
		{
			numBones = 20,
			boneWidth = 30.0f;
			animData* anim = nullptr;
			unsigned int animSize = 0;
			eat(pModelFileName, ChunkType::NORMS_TYPE, "", (unsigned char*&)anim, animSize);
			//unsigned int numAnim = animSize / sizeof(animData);

			boneData* bone = nullptr;
			unsigned int chunkSize = 0;
			eat(pModelFileName, ChunkType::BONE_TYPE, "", (unsigned char*&)bone, chunkSize);
			//unsigned int numBone = chunkSize / sizeof(boneData);
			boneData* pBone = bone;

			poClip = new Clip(Clip::Name::Teddy_Run,numBones, pBone, anim[0].frameCount);
			poClip2 = new Clip(Clip::Name::Teddy_Idle, numBones, pBone, anim[0].frameCount);
			poClip0 = poClip;
			this->poSkeleton = new Skeleton(numBones);
			assert(this->poSkeleton);

			assert(this->poClip);
			assert(this->poClip2);

			AnimTransition* pAnimTransition = new AnimTransition(poClip, poClip2);
			pSkinGraphicsObject->pBoneWord_SBO = pAnimTransition->poBoneWorld_SBO;

			TransitionManager::Add(pAnimTransition);
			delete anim;
			delete bone;
		}
		else {
			numBones = 80,
			boneWidth = 10.0f;
			animData* anim = nullptr;
			unsigned int animSize = 0;
			eat(pModelFileName, ChunkType::NORMS_TYPE, "", (unsigned char*&)anim, animSize);
			//unsigned int numAnim = animSize / sizeof(animData);

			boneData* bone = nullptr;
			unsigned int chunkSize = 0;
			eat(pModelFileName, ChunkType::BONE_TYPE, "", (unsigned char*&)bone, chunkSize);	
			//unsigned int numBone = chunkSize / sizeof(boneData);
			boneData* pBone = bone;

			poClip = new Clip(Clip::Name::Human_Run, numBones, pBone, anim[0].frameCount);
			poClip2 = new Clip(Clip::Name::Human_Idle, numBones, pBone, anim[1].frameCount);
			poClip0 = poClip;
			this->poSkeleton = new Skeleton(numBones);
			assert(this->poSkeleton);

			assert(this->poClip);
			assert(this->poClip2);

			AnimTransition* pAnimTransition2 = new AnimTransition(poClip, poClip2);
			pSkinGraphicsObject->pBoneWord_SBO = pAnimTransition2->poBoneWorld_SBO;
			TransitionManager::Add2(pAnimTransition2);
			delete anim;
			delete bone;
		}
	}

	Anim::~Anim()
	{
		delete poSkeleton;
		
		delete poClip;
		delete poClip2;
		
	}
	void Anim::setClip(Clip* pClip)
	{
		poClip0 = pClip;
	}
	Clip* Anim::getClip()
	{

		return poClip0;

	}
	Clip* Anim::getClip2()
	{

		return poClip2;

	}
	AnimTime Anim::FindMaxTime()
	{
		assert(poClip);
		return this->poClip->GetTotalTime();
	}

	void Anim::Animate(AnimTime tCurr,Clip* pClip)
	{
		pClip->AnimateBones(tCurr);
	}


}

//--- End of File ----
