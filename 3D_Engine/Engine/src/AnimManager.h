//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_MANAGER_H
#define ANIM_MANAGER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"
#include "AnimTime.h"
#include <AnimController.h>
namespace Azul
{
	class AnimManager
	{
		AnimManager()
		{
			pTmp = nullptr;
			pTmp2 = nullptr;
		}
		static AnimManager* privGetInstance()
		{
			static AnimManager animman;
			return &animman;
		}

	public:
		static void Create()
		{
			// Get the instance to the manager
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);
			AZUL_UNUSED_VAR(pManager);
		}
		static void Add(AnimController* pController)
		{
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);

			pManager->pTmp = pController;
		}

		static void Add2(AnimController* pController)
		{
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);

			pManager->pTmp2 = pController;
		}

		static AnimController* getAnimController()
		{
			// Get the instance to the manager
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);

			assert(pManager->pTmp);
			return pManager->pTmp;
		}
		static AnimController* getAnimController2()
		{
			// Get the instance to the manager
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);

			assert(pManager->pTmp2);
			return pManager->pTmp2;
		}
		static void Destroy()
		{
			AnimManager* pManager = AnimManager::privGetInstance();
			assert(pManager);
			delete pManager->pTmp2;
			delete pManager->pTmp;
		}

	public:
		AnimController* pTmp;
		AnimController* pTmp2;
	};
}
#endif