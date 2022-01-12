//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "ImageMan.h"

namespace Azul
{
	ImageMan::ImageMan()
	{
		this->pActive = nullptr;
	}

	ImageMan *ImageMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static ImageMan imageMan;
		return &imageMan;
	}

	void ImageMan::Create()
	{
		ImageMan *pImageMan = ImageMan::privGetInstance();
		assert(pImageMan);
	}

	void ImageMan::Destroy()
	{
		ImageMan *pImageMan = ImageMan::privGetInstance();
		assert(pImageMan);

		Image *pLink = pImageMan->pActive;

		while (pLink != nullptr)
		{
			Image *pTmp = pLink;
			pLink = (Image *)pLink->next;
			pImageMan->privRemove(pTmp, pImageMan->pActive);
			delete pTmp;
		}
	}

	void ImageMan::Add(Image *pImage)
	{
		// Get the instance to the manager
		ImageMan *pImageMan = ImageMan::privGetInstance();
		assert(pImageMan);

		// Create a Image
		assert(pImage);

		// Now add it to the manager
		pImageMan->privAddToFront(pImage, pImageMan->pActive);
	}

	void ImageMan::privAddToFront(Image *node, Image *&head)
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

	void ImageMan::privRemove(Image *pNode, Image *&poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (Image *)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}

	}
}

//--- End of File ---
