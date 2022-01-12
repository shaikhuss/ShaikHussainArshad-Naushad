//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "NullModel.h"
#include "GraphicsObject_Null.h"

#include "GameObject.h"
#include "GameObjectRigid.h"
#include "GameObjectAnim.h"
#include "GameObjectMan.h"
#include "GameObjectNull.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "PCSTreeForwardIterator.h"

namespace Azul
{
	void GameObjectMan::Add(GameObject *pObj, GameObject *pParent)
	{
		assert(pObj != nullptr);
		assert(pParent != nullptr);

		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();

		// insert object to root
		pGOM->poRootTree->Insert(pObj, pParent);

	}

	void GameObjectMan::Destroy()
	{
		// Get singleton
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSTree* pTree = pGOM->poRootTree;
		PCSNode* pNode = nullptr;

		PCSTreeForwardIterator pForIter(pTree->GetRoot());
		pNode = pForIter.First();
		PCSNode* pTmp = nullptr;
		while (!pForIter.IsDone())
		{
			pTmp = pForIter.CurrentItem();

			pNode = pForIter.Next();
			delete pTmp;
		}
	}

	void GameObjectMan::Create()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);
		AZUL_UNUSED_VAR(pGOM);
	}

	PCSTree *GameObjectMan::GetPCSTree()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		// Get root node
		return pGOM->poRootTree;
	}

	GameObject *GameObjectMan::GetRoot()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		GameObject *pGameObj = (GameObject *)pGOM->poRootTree->GetRoot();
		assert(pGameObj);

		return pGameObj;
	}

	void GameObjectMan::Update(const char* buff, AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(buff);
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);
		//pGOM->flag = "lol";
		PCSNode* pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		// w1(4)
		// PCSTreeForwardIterator pIter(pRootNode->GetChild());
		PCSTreeForwardIterator pIter(pRootNode);

		PCSNode* pNode = pIter.First();

		GameObject* pGameObj = nullptr;

		while (!pIter.IsDone())
		{
			//assert(pNode);
			//// Update the game object
			pGameObj = (GameObject*)pNode;
			char name[PCSNode::NAME_SIZE];
			pNode->GetName(name, PCSNode::NAME_SIZE);
			
			pGameObj->Update(name, currentTime);
			
			pNode = pIter.Next();
		}

	}

	void GameObjectMan::Draw()
	{
		GameObjectMan* pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode* pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode* pNode = pForwardIter.First();

		GameObject *pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject*)pNode;
			char name[PCSNode::NAME_SIZE];
			pNode->GetName(name, PCSNode::NAME_SIZE);
			if (pGameObj->GetDrawEnable())
			{

				pGameObj->Draw();
			}
			else
			{
				//assert(0);
			}

			pNode = pForwardIter.Next();
		}
	}

	GameObjectMan::GameObjectMan()
	{
		// Create the root node (null object)
		NullModel* pModel = new NullModel(nullptr);
		assert(pModel);
		ModelMan::Add(pModel);

		ShaderObject* pShader = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender", ShaderObject::Type::GRAPHICS);
		assert(pShader);
		ShaderMan::Add(pShader);

		GraphicsObject_Null* pGraphicsObject = new GraphicsObject_Null(pModel, pShader);

		GameObjectNull *pGameRoot = new GameObjectNull(pGraphicsObject);
		pGameRoot->SetName("GameObjectNull_Root");

		// Create the tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		// Attach the root node
		this->poRootTree->Insert(pGameRoot, this->poRootTree->GetRoot());
	}

	GameObjectMan::~GameObjectMan()
	{
		delete this->poRootTree;
	}

	GameObjectMan* GameObjectMan::privGetInstance(void)
	{
		// This is where its actually stored (BSS section)
		static GameObjectMan gom;
		return &gom;
	}

}

// --- End of File ---
