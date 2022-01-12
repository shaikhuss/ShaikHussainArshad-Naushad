
#include "AnimTransition.h"
#include "Clip.h"
#include "Mixer.h"
#include "TeddyModel.h"
#include "ShaderMan.h"
#include "MathApp.h"
#include "ModelMan.h"
#include <HumanoidModel.h>
namespace Azul
{
	//extern TeddyModel* pTeddyModel;

	AnimTransition::AnimTransition(Clip* pClipA, Clip* pClipB)
		: pSSBO_A(nullptr),
		pSSBO_B(nullptr),
		poSSBO_Result(nullptr),
		poBoneWorld_SBO(nullptr),
		numBones(-1),
		tS(0.0f),
		StartEnable(false)
	{
		assert(pClipA);
		assert(pClipB);

		this->pSSBO_A = pClipA->pSSBO_Result;
		this->pSSBO_B = pClipB->pSSBO_Result;

		assert(this->pSSBO_A);
		assert(this->pSSBO_A);

		assert(pClipA->GetNumBones() == pClipB->GetNumBones());

		this->numBones = pClipA->GetNumBones();

		this->poSSBO_Result = new SSBO();
		Bone* pBone = new Bone[(unsigned int)numBones]();
		this->poSSBO_Result->Set((unsigned int)numBones, sizeof(Bone), pBone);
		delete[] pBone;

		this->poBoneWorld_SBO = new SSBO();		
		Matrix *pResultMatrix = new Matrix[(unsigned int)numBones]();
		this->poBoneWorld_SBO->Set((unsigned int)numBones, sizeof(Matrix), pResultMatrix);
		delete[] pResultMatrix;
	}

	AnimTransition::~AnimTransition()
	{
		delete this->poSSBO_Result;
		delete this->poBoneWorld_SBO;
	}

	void AnimTransition::StartTransition()
	{
		this->StartEnable = true;
	}

	void AnimTransition::privTransitionTime()
	{
		if (this->StartEnable)
		{
			float t_delta = 0.03f;
			float b = 1.0f;
			float a = 0.0f;
			static float t = 0.0f;
			t += t_delta;
			if (t > 1.0f)
			{
				t = 1.0f;
			}

			this->tS = a + t * (b - a);
		}
	}

	void AnimTransition::Update()
	{
		this->privTransitionTime();

		Mixer::Blend_GPU(this->pSSBO_A, this->pSSBO_B, this->poSSBO_Result, tS, this->numBones);
		if (numBones == 20)
			// ------------------------------------------------
			// Compute local to world shader - move this
			// ------------------------------------------------
		{
			// Lock and load the shader...
			ShaderObject* pComputeShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_WORLD);

			pComputeShader->SetActive();

			TeddyModel* pTeddyModel = (TeddyModel*)ModelMan::FindTeddy();
			//pTeddyModel->
			// need a clean way to store and hold this data...
			SSBO* pBoneLocal = this->poSSBO_Result;
			SSBO* pHierarchyTable = pTeddyModel->poHierarchy_SBO;
			unsigned int hierarchyDepth = pTeddyModel->HeirarchyDepth;

			pBoneLocal->Bind(0);
			pHierarchyTable->Bind(1);
			this->poBoneWorld_SBO->Bind(2);

			glUniform1i(pComputeShader->GetLocation("tableDepth"), (int)hierarchyDepth);
			glUniform1i(pComputeShader->GetLocation("boneCount"), (int)numBones);

			// Dispatch
			pComputeShader->Dispatch(1, 1, 1);

			// Block Waiting for stages to complete
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		}
		else {
			ShaderObject* pComputeShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_WORLD);

			pComputeShader->SetActive();

			HumanoidModel* pHumanModel = (HumanoidModel*)ModelMan::FindHumanoid();
			//pTeddyModel->
			// need a clean way to store and hold this data...
			SSBO* pBoneLocal = this->poSSBO_Result;
			SSBO* pHierarchyTable = pHumanModel->poHierarchy_SBO;
			unsigned int hierarchyDepth = pHumanModel->HeirarchyDepth;

			pBoneLocal->Bind(0);
			pHierarchyTable->Bind(1);
			this->poBoneWorld_SBO->Bind(2);

			glUniform1i(pComputeShader->GetLocation("tableDepth"), (int)hierarchyDepth);
			glUniform1i(pComputeShader->GetLocation("boneCount"), (int)numBones);

			// Dispatch
			pComputeShader->Dispatch(4, 1, 1);

			// Block Waiting for stages to complete
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		}
	}

}