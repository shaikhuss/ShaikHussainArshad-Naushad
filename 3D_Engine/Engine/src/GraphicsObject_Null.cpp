//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "GraphicsObject_Null.h"

namespace Azul
{
	GraphicsObject_Null::GraphicsObject_Null(const Model* const pModel, const ShaderObject* const pShaderObj)
		: GraphicsObject(pModel, pShaderObj)
	{
		assert(pModel);
		assert(pShaderObj);
	}

	void GraphicsObject_Null::SetState()
	{

	}

	void GraphicsObject_Null::SetDataGPU()
	{

	}

	void GraphicsObject_Null::Draw()
	{

	}

	void GraphicsObject_Null::RestoreState()
	{

	}

}

// ---  End of File ---
