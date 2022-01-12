//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "GraphicsObject_SkinTexture.h"
#include "TextureMan.h"
#include "Model.h"
#include "CameraMan.h"
#include "TeddyModel.h"
#include "GameObjectRigid.h"
#include"GameObjectMan.h"
#include <HumanoidModel.h>
namespace Azul
{

	std::string GraphicsObject_SkinTexture::connectionString = "Teddy";

	GraphicsObject_SkinTexture::GraphicsObject_SkinTexture(const Model *const _pModel, const ShaderObject *const _pShaderObj, Texture::Name _name)
		: GraphicsObject(_pModel, _pShaderObj), textName(_name)
	{
		// check the base class
		assert(this->pModel);
		assert(this->pShaderObj);
		assert(this->poWorld);
		
		this->poLight = new Vect(1.0f, 10.0f, 1.0f);
		this->poLightColor = new Vect(1.50f, 1.50f, 1.50f, 1.0f);
	}
	

	void GraphicsObject_SkinTexture::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = TextureMan::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

	void GraphicsObject_SkinTexture::SetDataGPU()
	{
		// use this shader
		this->pShaderObj->SetActive();

		// set the vao
		glBindVertexArray(this->GetModel()->vao);


		// Set Wirefram
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDisable(GL_CULL_FACE);


		Camera *pCam = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		assert(pCam);

		Matrix view = pCam->getViewMatrix();
		Matrix proj = pCam->getProjMatrix();
		GameObjectRigid* pGameRigid = nullptr;
		if (connectionString == "Teddy")
		{
			TeddyModel* pTeddyModel = (TeddyModel*)this->GetModel();
			pGameRigid = (GameObjectRigid*)GameObjectMan::FindTeddyRigid();
			// Bine the SBOs
			pTeddyModel->poInversePose_SBO->Bind(0);
			this->pBoneWord_SBO->Bind(1);
			connectionString = "Humanoid";
			
		}
		else {
			HumanoidModel* pHumanoidModel = (HumanoidModel*)this->GetModel();
			pGameRigid = (GameObjectRigid*)GameObjectMan::FindHumanRigid();
			// Bine the SBOs
			pHumanoidModel->poInversePose_SBO->Bind(0);
			this->pBoneWord_SBO->Bind(1);
			connectionString = "Teddy";
		}
		// Send over Uniforms
		

		Vect light = *this->poLight;
		Vect color = *this->poLightColor;
		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("local_matrix"), 1, GL_FALSE, (float*)pGameRigid->GetWorld());

		glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)&light);
		glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)&color);



		// Texture - linked to Texture 0
		glUniform1i(this->pShaderObj->GetLocation("tex_object"), 0);
	}

	void GraphicsObject_SkinTexture::Draw()
	{
		//The starting point of the IBO
		glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_SkinTexture::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}
	

}

//--- End of File ----

