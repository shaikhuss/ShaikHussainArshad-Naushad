//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject_ColorByPosition.h"
#include "CameraMan.h"

namespace Azul
{
	GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(const Model* const model, const ShaderObject* const pShaderObj)
		: GraphicsObject(model, pShaderObj)
	{
		assert(pModel);
		assert(pShaderObj);
		assert(poWorld);
	}

	void GraphicsObject_ColorByPosition::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	void GraphicsObject_ColorByPosition::SetDataGPU()
	{
		// use this shader
		this->pShaderObj->SetActive();

		// set the vao
		glBindVertexArray(this->GetModel()->vao);

		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);

		Matrix world = this->GetWorld();
		Matrix view = pCam->getViewMatrix();
		Matrix proj = pCam->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
	}

	void GraphicsObject_ColorByPosition::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_ColorByPosition::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

}

// ---  End of File ---