//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TRANSITION_MANAGER_H
#define TRANSITION_MANAGER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"
#include "AnimTime.h"
#include <AnimTransition.h>
namespace Azul
{
	class TransitionManager
	{
		TransitionManager()
		{
			pTmp = nullptr;
			pTmp2 = nullptr;
		}
		static TransitionManager* privGetInstance()
		{
			static TransitionManager animman;
			return &animman;
		}

	public:
		static void Create()
		{
			// Get the instance to the manager
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);
			AZUL_UNUSED_VAR(pManager);
		}
		static void Add(AnimTransition* pController)
		{
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);

			pManager->pTmp = pController;
		}

		static void Add2(AnimTransition* pController)
		{
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);

			pManager->pTmp2 = pController;
		}

		static AnimTransition* getAnimTransition()
		{
			// Get the instance to the manager
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);

			assert(pManager->pTmp);
			return pManager->pTmp;
		}
		static AnimTransition* getAnimTransition2()
		{
			// Get the instance to the manager
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);

			assert(pManager->pTmp2);
			return pManager->pTmp2;
		}
		static void Destroy()
		{
			TransitionManager* pManager = TransitionManager::privGetInstance();
			assert(pManager);
			delete pManager->pTmp2;
			delete pManager->pTmp;
		}

	public:
		AnimTransition* pTmp;
		AnimTransition* pTmp2;
	};
}
#endif