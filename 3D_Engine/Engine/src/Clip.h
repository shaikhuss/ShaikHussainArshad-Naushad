//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CLIP_H
#define CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "sb7.h"
#include "SSBO.h"
#include <ChunkHeader.h>

namespace Azul
{
	class Clip
	{
	public:
		enum class Name
		{
			Teddy_Run,
			Teddy_Idle,
			Human_Run,
			Human_Idle
		};

	public:
		struct FrameBucket
		{
			FrameBucket();
			FrameBucket(const FrameBucket &) = default;
			FrameBucket &operator = (const FrameBucket &) = default;
			~FrameBucket();

			FrameBucket *nextBucket;
			FrameBucket *prevBucket;
			AnimTime     KeyTime;

			SSBO        *poKeyframe;   
		};

	public:
		Clip(Name name, int _numBones, boneData*& pBone, int framecnt);

		Clip() = delete;
		Clip(const Clip &) = delete;
		Clip &operator = (const Clip &) = delete;
		~Clip();

		AnimTime GetTotalTime();
		void AnimateBones(AnimTime tCurr);
		int GetNumBones();

	private:
		void privSetAnimationData(Name name, boneData*& pBone, int framecnt, int bonecnt);
		void privSetAnimationDataHumanRun(boneData*& pBone, int framecnt, int bonecnt);
		AnimTime privFindMaxTime();
		int  privFindNumFrames();

		void privSetAnimationDataTeddyRun();
		void privSetAnimationDataHumanIdle(boneData*& pBone, int framecnt, int bonecnt);
		void privSetAnimationDataTeddyIdle(boneData*& pBone, int framecnt, int bonecnt);

	private:
		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket *poHead;

	public:
		Name        name;
		SSBO		*pSSBO_Result;
	};
}

#endif

//--- End of File ---
