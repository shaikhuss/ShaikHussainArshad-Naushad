//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef MODEL_LINK_H
#define MODEL_LINK_H

namespace Azul
{
	class ModelLink
	{
	public:
		ModelLink();
		ModelLink(const ModelLink &) = default;
		ModelLink &operator = (const ModelLink &) = default;
		virtual ~ModelLink();

	// data:
		ModelLink* next;
		ModelLink* prev;
	};

}

#endif

// ---  End of File ---
