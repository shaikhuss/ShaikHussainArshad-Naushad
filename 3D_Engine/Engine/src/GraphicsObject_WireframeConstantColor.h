//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H

#include "GraphicsObject.h"

namespace Azul
{
	class GraphicsObject_WireframeConstantColor :public GraphicsObject
	{
	public:
		GraphicsObject_WireframeConstantColor() = delete;
		GraphicsObject_WireframeConstantColor(const GraphicsObject_WireframeConstantColor &) = delete;
		GraphicsObject_WireframeConstantColor &operator = (const GraphicsObject_WireframeConstantColor &) = delete;
		~GraphicsObject_WireframeConstantColor();

		GraphicsObject_WireframeConstantColor(Model *model, ShaderObject *pShaderObj, Vect &wireColor);

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

	public:
		// data:  place uniform instancing here
		Vect *poWireColor;

	};
}

#endif

// --- End of File ---
