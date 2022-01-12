//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------
#include "ModelMan.h"

namespace Azul
{    
	ModelMan::ModelMan()
	{  
		this->pActive = nullptr;
	} 

	ModelMan* ModelMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static ModelMan shaderMan;
		return &shaderMan;
	}

	void ModelMan::Create()
	{
		ModelMan* pModelMan;
		pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);
	}

	void ModelMan::Destroy()
	{
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		Model* pLink = pModelMan->pActive;

		while (pLink != nullptr)
		{
			Model* pTmp = pLink;
			pLink = (Model*)pLink->next;
			pModelMan->privRemove(pTmp, pModelMan->pActive);
			delete pTmp;
		}
	}

	void ModelMan::Add(Model* pModel)
	{
		// Get the instance to the manager
		ModelMan* pModelMan = ModelMan::privGetInstance();
		assert(pModelMan);

		// Create a Model
		assert(pModel);

		// Now add it to the manager
		pModelMan->privAddToFront(pModel, pModelMan->pActive);
	}

	void ModelMan::privAddToFront(Model* node, Model*& head)
	{
		assert(node);

		if (head == nullptr)
		{
			head = node;
			node->next = nullptr;
			node->prev = nullptr;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	void ModelMan::privRemove(Model* pNode, Model*& poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Model*)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}

	}

}

// ---  End of File ---
