//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_REVERSE_ITERATOR_H
#define PCSTREE_REVERSE_ITERATOR_H

#include "PCSTreeIterator.h"

namespace Azul
{
	class PCSTreeReverseIterator : public PCSTreeIterator
	{
	public:

		PCSTreeReverseIterator(PCSNode* rootNode);

		virtual PCSNode* First() override;
		virtual PCSNode* Next() override;
		virtual bool IsDone() override;
		virtual PCSNode* CurrentItem() override;

		virtual ~PCSTreeReverseIterator() = default;

	private:
		PCSNode* root;
		PCSNode* current;
		PCSNode* prevNode;
	};

}

#endif

// ---  End of File ---------------