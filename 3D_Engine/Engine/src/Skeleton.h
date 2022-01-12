//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"

namespace Azul
{
	class Skeleton
	{
	public:
		struct Data
		{
			Data() = default;
			Data(const Data &) = default;
			Data &operator = (const Data &) = default;
			~Data() = default;

			// Data:
			char name[64];
			int  index;
			int  parentIndex;
		};

	public:
		Skeleton(int numBones);

		Skeleton() = delete;
		Skeleton(const Skeleton &) = delete;
		Skeleton &operator = (const Skeleton &) = delete;
		~Skeleton();

	//	GameObjectAnim *GetFirstBone();
		
	private:
		void privSetAnimationHierarchy(int numBones);
	//	GameObjectAnim *privFindBoneByIndex(int index);

	private:
		//GameObjectAnim *pFirstBone;
		int             numBones;
	};
}

#endif

// --- End of File ---
