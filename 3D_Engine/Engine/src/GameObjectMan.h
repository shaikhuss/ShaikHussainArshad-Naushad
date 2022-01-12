//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"

namespace Azul
{

	// Singleton
	class GameObjectMan
	{
	public:
		static void Add(GameObject *pObj, GameObject *pParent);
		static void Draw(void);
		static void Update(const char* buff, AnimTime currentTime);
		static GameObject *GetRoot(void);
		static PCSTree *GetPCSTree();
		static void AddTeddyRigid(GameObject* pRigid)
		{
			GameObjectMan* pGameMan = GameObjectMan::privGetInstance();
			assert(pGameMan);
			
			pGameMan->pGameRigid = pRigid;
			// Now add it to the manager
			pGameMan->Add(pRigid, GameObjectMan::GetRoot());
		}
		static GameObject* FindTeddyRigid()
		{
			GameObjectMan* pGameMan = GameObjectMan::privGetInstance();
			assert(pGameMan);


			return pGameMan->pGameRigid;
		}

		static void AddHumanRigid(GameObject* pRigid)
		{
			GameObjectMan* pGameMan = GameObjectMan::privGetInstance();
			assert(pGameMan);

			pGameMan->pHumanRigid = pRigid;
			// Now add it to the manager
			pGameMan->Add(pRigid, GameObjectMan::GetRoot());
		}
		static GameObject* FindHumanRigid()
		{
			GameObjectMan* pGameMan = GameObjectMan::privGetInstance();
			assert(pGameMan);


			return pGameMan->pHumanRigid;
		}
		static void Destroy();
		static void Create();
		//GameObjectMan(const GameObjectMan&)
		//{
		//	flag = nullptr;
		//}
		
		GameObjectMan &operator = (const GameObjectMan &) = delete;
		~GameObjectMan();
		//char* flag;
	private:
		GameObjectMan();
		GameObject* pGameRigid;
		GameObject* pHumanRigid;
		static GameObjectMan* privGetInstance();

		// data
		PCSTree* poRootTree;
	};

}

#endif


// --- End of File ---
