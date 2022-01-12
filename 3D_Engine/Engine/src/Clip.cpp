
//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------
#include "eat.h"
#include "ChunkHeader.h"
#include"PackageHeader.h"
#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"
#include "ShaderMan.h"
#include "TeddyModel.h"
//#include "AnimController.h"
#include "GameObjectRigid.h"

namespace Azul
{
	// Get from the manager
	//extern TeddyModel* pTeddyModel;
	//extern GameObjectRigid* pGameRigid;
	//extern SSBO* pBoneWorld_SBO;

	Clip::FrameBucket::FrameBucket()
		:nextBucket(nullptr),
		prevBucket(nullptr),
		KeyTime(),
		//poBone(nullptr),
		poKeyframe(nullptr)
	{
	}

	Clip::FrameBucket::~FrameBucket()
	{
		//delete[] poBone;
		delete poKeyframe;
	}

	Clip::Clip(Name _name, int _numBones , boneData*& pBone, int framecnt)
	: numBones(_numBones),
	numFrames(0),
	//TotalTime1(AnimTime::Duration::ZERO),
	TotalTime(AnimTime::Duration::ZERO),
	poHead(nullptr),
	name(_name),
	pSSBO_Result(nullptr)
	{
		this->privSetAnimationData(this->name, pBone, framecnt, numBones);
		this->TotalTime = this->privFindMaxTime();
		this->numFrames = this->privFindNumFrames();

		this->pSSBO_Result = new SSBO();

		// Only done once per clip
		Bone* poBone = new Bone[(unsigned int)numBones]();
		assert(poBone);
		this->pSSBO_Result->Set((unsigned int)numBones, sizeof(Bone), poBone);
		delete[] poBone;

	}

	Clip::~Clip()
	{
		FrameBucket *pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket *pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}

		delete this->pSSBO_Result;
	}
	
	int Clip::GetNumBones()
	{
		return this->numBones;
	}

	void Clip::AnimateBones(AnimTime tCurr)
	{
		// First one 
		FrameBucket *pTmp = this->poHead;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket *pA = pTmp->prevBucket;
		FrameBucket *pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend_GPU( pA->poKeyframe, pB->poKeyframe, this->pSSBO_Result, tS, numBones);

	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

	void Clip::privSetAnimationData(Name _name, boneData*& pBone, int framecnt, int bonecnt)
	{

		// SHould be driven by file load... not hard set
		switch (_name)
		{
		case Clip::Name::Teddy_Idle:
			this->privSetAnimationDataTeddyIdle(pBone, framecnt, bonecnt);
			break;

		case Clip::Name::Teddy_Run:
			this->privSetAnimationDataTeddyRun();
			break;

		case Clip::Name::Human_Run:
			this->privSetAnimationDataHumanRun(pBone, framecnt, bonecnt);
			break;

		case Clip::Name::Human_Idle:
			this->privSetAnimationDataHumanIdle(pBone, framecnt, bonecnt);
			break;

		default:
			assert(false);


		}

	}

	void Clip::privSetAnimationDataHumanRun(boneData*& pBone, int framecnt, int bonecnt)
	{
		Bone* poBone = new Bone[(unsigned int)bonecnt];
		numFrames = framecnt;

		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = new FrameBucket();
		pTmp->prevBucket = nullptr;
		pTmp->nextBucket = nullptr;
		pTmp->KeyTime = 0 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		poHead = pTmp;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		for (int k = 0; k < bonecnt; k++)
		{
			poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
			poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
			poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);

			pBone++;
		}

		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);


		for (int j = 1; j < framecnt; j++)
		{

			FrameBucket* pTmp2 = new FrameBucket();
			pTmp2->prevBucket = pTmp;
			pTmp2->nextBucket = nullptr;
			pTmp2->KeyTime = j * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
			pTmp->nextBucket = pTmp2;
			pTmp = pTmp2;
			pTmp->poKeyframe = new SSBO();
			assert(pTmp->poKeyframe);
			for (int k = 0; k < bonecnt; k++)
			{
				poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
				poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
				poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);
				pBone++;

			}

			// W9(1) Keenan
			pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);

		}


		delete[] poBone;
	}

	void Clip::privSetAnimationDataHumanIdle(boneData*& pBone, int framecnt, int bonecnt)
	{
		Bone* poBone = new Bone[(unsigned int)bonecnt];
		numFrames = framecnt;

		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = new FrameBucket();
		pTmp->prevBucket = nullptr;
		pTmp->nextBucket = nullptr;
		pTmp->KeyTime = 0 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		poHead = pTmp;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		for (int k = 0; k < bonecnt; k++)
		{
			poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
			poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
			poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);

			pBone++;
		}

		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);


		for (int j = 1; j < 30; j++)
		{

			FrameBucket* pTmp2 = new FrameBucket();
			pTmp2->prevBucket = pTmp;
			pTmp2->nextBucket = nullptr;
			pTmp2->KeyTime = j * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
			pTmp->nextBucket = pTmp2;
			pTmp = pTmp2;
			pTmp->poKeyframe = new SSBO();
			assert(pTmp->poKeyframe);
			for (int k = 0; k < bonecnt; k++)
			{
				poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
				poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
				poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);
				pBone++;

			}

			// W9(1) Keenan
			pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);

		}


		delete[] poBone;
	}
	void Clip::privSetAnimationDataTeddyIdle(boneData*& pBone, int framecnt, int bonecnt)
	{
		Bone* poBone = new Bone[(unsigned int)bonecnt];


		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = new FrameBucket();
		pTmp->prevBucket = nullptr;
		pTmp->nextBucket = nullptr;
		pTmp->KeyTime = 0 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
		
		poHead = pTmp;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		for (int k = 0; k < bonecnt; k++)
		{
			poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
			poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
			poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);

			pBone++;
		}

		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);

		
		for (int j = 1; j < framecnt; j++)
		{
			
			FrameBucket* pTmp2 = new FrameBucket();
			pTmp2->prevBucket = pTmp;
			pTmp2->nextBucket = nullptr;
			pTmp2->KeyTime = j * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
			pTmp->nextBucket = pTmp2;
			pTmp = pTmp2;
			pTmp->poKeyframe = new SSBO();
			assert(pTmp->poKeyframe);
				for (int k = 0; k < bonecnt; k++)
				{
					poBone[k].T = Vect(pBone->tx, pBone->ty, pBone->tz);
					poBone[k].Q = Quat(Quat::Rot3::XYZ, pBone->qx, pBone->qy, pBone->qz);
					poBone[k].S = Vect(pBone->sx, pBone->sy, pBone->sz);
					pBone++;

				}

			// W9(1) Keenan
			pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &poBone[0]);

		}
		

		delete[] poBone;
	}

	void Clip::privSetAnimationDataTeddyRun()
	{
		Bone* pBone = new Bone[(unsigned int)this->numBones]();


		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = new FrameBucket();
		pTmp->prevBucket = nullptr;
		pTmp->nextBucket = nullptr;
		pTmp->KeyTime = 0 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
		this->poHead = pTmp;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		//------- Key Time: 0  ms: 0 ------------------ 

		//   Node Name: Bip01
		pBone[0].T = Vect(-1.100515f, 0.276832f, -1.647785f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.002449f, -1.501696f, -1.573294f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016713f, -0.014116f, 0.000054f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.000059f, 0.000014f, 0.101584f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-5.984611f, 0.623426f, 13.671310f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.067054f, -0.186033f, 2.266385f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.064398f, -0.023409f, -0.913204f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.005173f, -0.153760f, 0.220085f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.984191f, 0.624999f, -13.671410f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.090553f, 0.256951f, 2.878009f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.089739f, 0.026946f, -0.876180f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.073008f, 0.176929f, 0.802990f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.000109f, 0.000034f, 0.201577f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, 0.075335f, 1.373003f, 0.252085f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.001051f, 0.001344f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.183036f, 0.034523f, -0.532326f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, -1.056533f, -1.227617f, 1.383028f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, 0.000019f, -0.000984f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.197247f, -0.041299f, -0.731994f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000030f, -0.000248f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.779648f, -0.048758f, 0.311560f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.001887f, -0.000295f, 0.047542f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);


		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);

		// --------  Frame 5 ----------------------------

		FrameBucket* pTmp2 = new FrameBucket();
		pTmp2->prevBucket = pTmp;
		pTmp2->nextBucket = nullptr;
		pTmp2->KeyTime = 5 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		pTmp->nextBucket = pTmp2;

		pTmp = pTmp2;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		// ------ - Key Time : 5  ms : 166 ------------------

		//   Node Name: Bip01
		pBone[0].T = Vect(-1.152346f, 0.276832f, -1.699613f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.002449f, -1.501696f, -1.573294f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016811f, -0.014116f, 0.000054f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.000059f, 0.000014f, 0.101584f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-5.984611f, 0.623426f, 13.671310f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.067054f, -0.186031f, 2.266385f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.064398f, -0.023409f, -0.913204f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.005173f, -0.153760f, 0.220085f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.984191f, 0.624999f, -13.671410f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.090553f, 0.256951f, 2.878006f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.089739f, 0.026946f, -0.876187f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.073008f, 0.176929f, 0.802990f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.000109f, 0.000034f, 0.201577f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, 0.075132f, 1.373003f, 0.249265f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.000521f, 0.000675f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.183036f, 0.034523f, -0.532326f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, -1.056564f, -1.227583f, 1.385474f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, 0.000019f, -0.000482f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.197247f, -0.041299f, -0.731994f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000030f, -0.000130f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.779648f, -0.048757f, 0.311560f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.004506f, -0.000295f, 0.047542f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);



		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);

		// --------  Frame 10  ----------------------------

		FrameBucket* pTmp3 = new FrameBucket();
		pTmp3->prevBucket = pTmp;
		pTmp3->nextBucket = nullptr;
		pTmp3->KeyTime = 10 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		pTmp->nextBucket = pTmp3;

		pTmp = pTmp3;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		// ------ - Key Time : 10  ms : 333 ------------------

		//   Node Name: Bip01
		pBone[0].T = Vect(-1.565005f, 0.264652f, -2.305938f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.024605f, -1.501675f, -1.595397f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016826f, -0.014116f, -0.000077f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.003557f, 0.001224f, 0.105048f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-5.998971f, 0.596354f, 13.666230f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.067419f, -0.194250f, 2.269472f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.063915f, -0.024399f, -0.901405f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.004955f, -0.160038f, 0.214685f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.965507f, 0.693582f, -13.676280f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.087596f, 0.251141f, 2.866982f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.088924f, 0.026356f, -0.881250f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.069804f, 0.172426f, 0.800452f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.006960f, 0.002809f, 0.208500f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, -0.048279f, 1.371830f, 0.104781f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.000519f, 0.000677f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.184078f, 0.034892f, -0.546681f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, -0.831838f, -1.296662f, 1.267801f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, -0.000172f, -0.000445f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.187760f, -0.036348f, -0.599715f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000032f, -0.000130f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.790544f, -0.066630f, 0.307476f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.119579f, 0.008509f, 0.042440f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);


		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);

		// --------  Frame 15  ----------------------------

		FrameBucket* pTmp4 = new FrameBucket();
		pTmp4->prevBucket = pTmp;
		pTmp4->nextBucket = nullptr;
		pTmp4->KeyTime = 15 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		pTmp->nextBucket = pTmp4;

		pTmp = pTmp4;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		// ------ - Key Time : 15  ms : 500 ------------------

		//   Node Name: Bip01
		pBone[0].T = Vect(-2.180608f, 0.432678f, -3.171785f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.022143f, -1.501679f, -1.592941f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016847f, -0.014116f, -0.000033f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.008954f, 0.003050f, 0.110835f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-6.020048f, 0.557282f, 13.658600f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.069463f, -0.205525f, 2.276562f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.062150f, -0.026912f, -0.875915f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.007460f, -0.167891f, 0.201228f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.936647f, 0.802085f, -13.682900f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.082917f, 0.242245f, 2.853298f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.087299f, 0.026185f, -0.882903f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.067604f, 0.164552f, 0.794221f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.017512f, 0.007064f, 0.220049f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, -0.213753f, 1.363335f, -0.112716f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.000515f, 0.000679f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.185868f, 0.035657f, -0.572719f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, -0.364687f, -1.372786f, 0.962291f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, -0.000492f, -0.000391f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.176603f, -0.032094f, -0.448146f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000076f, -0.000130f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.807128f, -0.090726f, 0.301444f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.301938f, 0.025651f, 0.039969f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);

		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);




		// --------  Frame 20  ----------------------------

		FrameBucket* pTmp5 = new FrameBucket();
		pTmp5->prevBucket = pTmp;
		pTmp5->nextBucket = nullptr;
		pTmp5->KeyTime = 20 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		pTmp->nextBucket = pTmp5;

		pTmp = pTmp5;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);


		// ------ - Key Time : 20  ms : 700 ------------------


		//   Node Name: Bip01
		pBone[0].T = Vect(-2.644098f, 0.470733f, -3.717821f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.009837f, -1.501693f, -1.580664f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016870f, -0.014116f, 0.000002f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.014475f, 0.004891f, 0.117183f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-6.040656f, 0.519952f, 13.650940f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.072983f, -0.213939f, 2.276213f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.061354f, -0.028219f, -0.859044f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.010230f, -0.172720f, 0.189728f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.906935f, 0.915688f, -13.688590f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.077070f, 0.235790f, 2.837155f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.086759f, 0.025560f, -0.889787f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.066626f, 0.159277f, 0.791948f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.028278f, 0.011425f, 0.232698f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, -0.365080f, 1.345235f, -0.325949f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.000508f, 0.000682f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.188137f, 0.036589f, -0.602137f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, 0.309584f, -1.402055f, 0.441977f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, -0.000724f, -0.000231f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.184576f, -0.034953f, -0.555279f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000058f, -0.000130f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.824705f, -0.112865f, 0.295223f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.459840f, 0.034534f, 0.024561f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);


		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);

		// --------  Frame 25  ----------------------------

		FrameBucket* pTmp6 = new FrameBucket();
		pTmp6->prevBucket = pTmp;
		pTmp6->nextBucket = nullptr;
		pTmp6->KeyTime = 25 * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

		pTmp->nextBucket = pTmp6;

		pTmp = pTmp6;

		// W9(1) Keenan
		pTmp->poKeyframe = new SSBO();
		assert(pTmp->poKeyframe);

		//------ - Key Time : 25  ms : 833 ------------------

		//   Node Name: Bip01
		pBone[0].T = Vect(-3.022779f, 0.111900f, -3.990088f);
		pBone[0].Q = Quat(Quat::Rot3::XYZ, 0.024605f, -1.501675f, -1.595397f);
		pBone[0].S = Vect(0.100000f, 0.100000f, 0.100000f);

		//   Node Name: Bip01 Pelvis
		pBone[1].T = Vect(-0.000000f, 0.000000f, 615.514019f);
		pBone[1].Q = Quat(Quat::Rot3::XYZ, -1.570795f, -1.570796f, 0.000000f);
		pBone[1].S = Vect(17.664900f, 17.664897f, 17.664897f);

		//   Node Name: Bip01 Spine
		pBone[2].T = Vect(6.016886f, -0.014116f, -0.000039f);
		pBone[2].Q = Quat(Quat::Rot3::XYZ, -0.020030f, 0.006655f, 0.123524f);
		pBone[2].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Thigh
		pBone[3].T = Vect(-6.060161f, 0.482196f, 13.643720f);
		pBone[3].Q = Quat(Quat::Rot3::XYZ, -3.074443f, -0.221245f, 2.258287f);
		pBone[3].S = Vect(1.000000f, 0.999999f, 1.000000f);

		//   Node Name: Bip01 L Calf
		pBone[4].T = Vect(16.961590f, 0.000002f, -0.000008f);
		pBone[4].Q = Quat(Quat::Rot3::XYZ, 0.062725f, -0.027225f, -0.873473f);
		pBone[4].S = Vect(1.000001f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Foot
		pBone[5].T = Vect(13.263520f, -0.000005f, -0.000000f);
		pBone[5].Q = Quat(Quat::Rot3::XYZ, 0.009752f, -0.177897f, 0.192125f);
		pBone[5].S = Vect(1.000000f, 1.000000f, 0.999999f);

		//   Node Name: Bip01 R Thigh
		pBone[6].T = Vect(-5.878190f, 1.029800f, -13.692890f);
		pBone[6].Q = Quat(Quat::Rot3::XYZ, 3.069132f, 0.230944f, 2.806634f);
		pBone[6].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Calf
		pBone[7].T = Vect(16.961580f, 0.000000f, -0.000005f);
		pBone[7].Q = Quat(Quat::Rot3::XYZ, -0.088512f, 0.022928f, -0.922597f);
		pBone[7].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Foot
		pBone[8].T = Vect(13.263530f, 0.000000f, 0.000001f);
		pBone[8].Q = Quat(Quat::Rot3::XYZ, 0.065197f, 0.156222f, 0.802103f);
		pBone[8].S = Vect(1.000001f, 1.000001f, 1.000000f);

		//   Node Name: Bip01 Spine1
		pBone[9].T = Vect(17.730410f, -0.017626f, 0.000001f);
		pBone[9].Q = Quat(Quat::Rot3::XYZ, -0.039090f, 0.015709f, 0.245309f);
		pBone[9].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Neck
		pBone[10].T = Vect(22.140869f, -0.008818f, 0.000005f);
		pBone[10].Q = Quat(Quat::Rot3::XYZ, 0.000000f, -0.000000f, -0.000000f);
		pBone[10].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L Clavicle
		pBone[11].T = Vect(0.000023f, 0.008803f, 5.461464f);
		pBone[11].Q = Quat(Quat::Rot3::XYZ, 1.570794f, -1.396266f, 1.570002f);
		pBone[11].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 L UpperArm
		pBone[12].T = Vect(13.067830f, -0.000001f, -0.000003f);
		pBone[12].Q = Quat(Quat::Rot3::XYZ, -0.481949f, 1.319399f, -0.506068f);
		pBone[12].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Forearm
		pBone[13].T = Vect(15.099380f, -0.000499f, 0.000684f);
		pBone[13].Q = Quat(Quat::Rot3::XYZ, 0.190304f, 0.037571f, -0.632018f);
		pBone[13].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 L Hand
		pBone[14].T = Vect(15.099400f, 0.000095f, 0.000103f);
		pBone[14].Q = Quat(Quat::Rot3::XYZ, -1.868661f, 0.117072f, 0.287848f);
		pBone[14].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R Clavicle
		pBone[15].T = Vect(0.000027f, 0.008833f, -5.461464f);
		pBone[15].Q = Quat(Quat::Rot3::XYZ, -1.570798f, 1.396261f, 1.569999f);
		pBone[15].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 R UpperArm
		pBone[16].T = Vect(13.067830f, -0.000001f, 0.000004f);
		pBone[16].Q = Quat(Quat::Rot3::XYZ, 0.938169f, -1.373303f, -0.045250f);
		pBone[16].S = Vect(1.000000f, 1.000000f, 1.000001f);

		//   Node Name: Bip01 R Forearm
		pBone[17].T = Vect(15.099400f, -0.000829f, -0.000064f);
		pBone[17].Q = Quat(Quat::Rot3::XYZ, -0.201134f, -0.043943f, -0.790769f);
		pBone[17].S = Vect(1.000000f, 1.000001f, 1.000001f);

		//   Node Name: Bip01 R Hand
		pBone[18].T = Vect(15.099400f, 0.000061f, -0.000130f);
		pBone[18].Q = Quat(Quat::Rot3::XYZ, 1.844408f, -0.131701f, 0.288733f);
		pBone[18].S = Vect(1.000000f, 1.000000f, 1.000000f);

		//   Node Name: Bip01 Head
		pBone[19].T = Vect(11.079170f, -0.000001f, 0.000002f);
		pBone[19].Q = Quat(Quat::Rot3::XYZ, -0.607393f, 0.022476f, -0.012766f);
		pBone[19].S = Vect(1.000000f, 1.000000f, 1.000000f);


		// W9(1) Keenan
		pTmp->poKeyframe->Set((unsigned int)this->numBones, sizeof(Bone), &pBone[0]);


		delete[] pBone;
	}
}

// --- End of File ---
