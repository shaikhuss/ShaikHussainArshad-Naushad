//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef HUMANOID_MODEL_H
#define HUMANOID_MODEL_H

#include "Model.h"
#include "SSBO.h"

namespace Azul
{
	class HumanoidModel : public Model
	{
	public:
		HumanoidModel(const char* const modelFileName);
		virtual ~HumanoidModel();

		// tells the compiler do not create or allow it to be used, c++11
		HumanoidModel(const HumanoidModel&) = delete;
		HumanoidModel& operator=(const HumanoidModel& other) = delete;

	public:
		void privCreateVAO(const char* const modelFileName) override;

		GLuint vbo_boneweight;  // Bone_weight
		GLuint vbo_boneindex;   // Bone_index

		unsigned int NumBones;
		unsigned int HeirarchyDepth;
		SSBO* poInversePose_SBO;
		SSBO* poHierarchy_SBO;
	};
}

#endif

// --- End of File ---
