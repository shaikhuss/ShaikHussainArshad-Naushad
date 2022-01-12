//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef MODEL_MAN_H
#define MODEL_MAN_H

#include "Model.h"

namespace Azul
{
	class ModelMan
	{
	public:
		static void Add(Model* pModel);
		static void Create();
		static void Destroy();
		static void AddTeddy(Model* pModel)
		{
			ModelMan* pModelMan = ModelMan::privGetInstance();
			assert(pModelMan);

			// Create a Model
			assert(pModel);
			pModelMan->pTeddy = pModel;
			// Now add it to the manager
			pModelMan->privAddToFront(pModel, pModelMan->pActive);
		}
		static Model* FindTeddy()
		{
			ModelMan* pModelMan = ModelMan::privGetInstance();
			assert(pModelMan);


			return pModelMan->pTeddy;
		}

		static void AddHumanoid(Model* pModel)
		{
			ModelMan* pModelMan = ModelMan::privGetInstance();
			assert(pModelMan);

			// Create a Model
			assert(pModel);
			pModelMan->pHumanoid = pModel;
			// Now add it to the manager
			pModelMan->privAddToFront(pModel, pModelMan->pActive);
		}
		static Model* FindHumanoid()
		{
			ModelMan* pModelMan = ModelMan::privGetInstance();
			assert(pModelMan);


			return pModelMan->pHumanoid;
		}
		ModelMan(const ModelMan &) = delete;
		ModelMan &operator = (const ModelMan &) = delete;
		~ModelMan() = default;

	private:  // methods

		static ModelMan* privGetInstance();
		ModelMan();

		void privAddToFront(Model* node, Model*& head);
		void privRemove(Model* node, Model*& head);

	private:  // add
		Model* pTeddy;
		Model* pHumanoid;

		Model *pActive;

	};

}

#endif

// ---  End of File ---
