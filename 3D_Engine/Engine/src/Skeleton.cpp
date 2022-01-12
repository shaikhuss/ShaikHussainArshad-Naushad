//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "PyramidModel.h"
#include "GraphicsObject_TextureLight.h"
#include "GameObjectMan.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "GameObjectRigid.h"
#include "GraphicsObject_Null.h"
#include "NullModel.h"
#include "Skeleton.h"
#include "PCSTreeForwardIterator.h"
#include "GameObjectMan.h"

namespace Azul
{
	

	// Needs to move to binary file
	//Skeleton::Data skel[]
	//{
	//	{ "Bip01", 0, -1 },
	//	{ "Bip01_Pelvis", 1, 0 },
	//	{ "Bip01_Spine", 2, 1 },
	//	{ "Bip01_L_Thigh", 3, 2 },
	//	{ "Bip01_L_Calf", 4, 3 },
	//	{ "Bip01_L_Foot", 5, 4 },
	//	{ "Bip01_R_Thigh", 6, 2 },
	//	{ "Bip01_R_Calf", 7, 6 },
	//	{ "Bip01_R_Foot", 8, 7 },
	//	{ "Bip01_Spine1", 9, 2 },
	//	{ "Bip01_Neck", 10, 9 },
	//	{ "Bip01_L_Clavicle", 11, 10 },
	//	{ "Bip01_L_UpperArm", 12, 11 },
	//	{ "Bip01_L_Forearm", 13, 12 },
	//	{ "Bip01_L_Hand", 14, 13 },
	//	{ "Bip01_R_Clavicle", 15, 10 },
	//	{ "Bip01_R_UpperArm", 16, 15 },
	//	{ "Bip01_R_Forearm", 17, 16 },
	//	{ "Bip01_R_Hand", 18, 17 },
	//	{ "Bip01_Head", 19, 10 }
	//};

	Skeleton::Skeleton(int _numBones)
	: 	numBones(_numBones)
	{
		this->privSetAnimationHierarchy(numBones);
	}


	Skeleton::~Skeleton()
	{

	}



	void Skeleton::privSetAnimationHierarchy(int nBones)
	{
		// Load the model
		

		// Create/Load Shader 
		//ShaderObject *pShaderObject_textureLight = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff", ShaderObject::Type::GRAPHICS);
		//assert(pShaderObject_textureLight);
		//ShaderMan::Add(pShaderObject_textureLight);

		ShaderObject *pShaderObject_null = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_null);
		ShaderMan::Add(pShaderObject_null);

		// Create GameObject
		Vect color;
		Vect pos(1, 1, 1);

		// Null object
		NullModel *pNullModel = new NullModel(0);
		ModelMan::Add(pNullModel);
		GraphicsObject_Null *pGraphicsObjNull = new GraphicsObject_Null(pNullModel, pShaderObject_null);
		GameObjectRigid* pGameRigid;
		pGameRigid = new GameObjectRigid(pGraphicsObjNull);
		//pGameRigid->angle_x = MATH_PI2;
		//pGameRigid->angle_z = 1.7f;
		//20 for Teddy 80 for humanoid
		if (nBones==20)
		{
			pGameRigid->SetName("Teddy_Rigid");
			GameObjectMan::AddTeddyRigid(pGameRigid);
		}
		else {
			pGameRigid->SetName("Humanoid_Rigid");
			GameObjectMan::AddHumanRigid(pGameRigid);
		}

		//pGameRigid->SetName("Rigid");
		//GameObjectMan::AddTeddyRigid(pGameRigid);

	//	color.set(1.0f, 0.0f, 0.0f, 1.0f);


	}
}

// --- End of File ---
