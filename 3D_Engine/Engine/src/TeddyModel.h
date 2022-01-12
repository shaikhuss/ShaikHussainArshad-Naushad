//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef TEDDY_MODEL_H
#define TEDDY_MODEL_H

#include "Model.h"
#include "SSBO.h"

namespace Azul
{
	class TeddyModel : public Model
	{
	public:
		TeddyModel(const char *const modelFileName);
		virtual ~TeddyModel();

		// tells the compiler do not create or allow it to be used, c++11
		TeddyModel(const TeddyModel &) = delete;
		TeddyModel &operator=(const TeddyModel &other) = delete;

	public:
		void privCreateVAO(const char *const modelFileName) override;

		GLuint vbo_boneweight;  // Bone_weight
		GLuint vbo_boneindex;   // Bone_index

		unsigned int NumBones;
		unsigned int HeirarchyDepth;
		SSBO	*poInversePose_SBO;
		SSBO	*poHierarchy_SBO;
	};
}

#endif

// --- End of File ---
