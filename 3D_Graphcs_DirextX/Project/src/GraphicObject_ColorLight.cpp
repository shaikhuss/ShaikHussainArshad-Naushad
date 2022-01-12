#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount() * 3;
	MeshMaterials = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		MeshMaterials[i] = Vect(0, 0, 0);
	}
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] MeshMaterials;
}

void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec)
{
	for (int i = 0; i < this->pModel->GetMeshCount() * 3; i += 3)
	{
		MeshMaterials[i] = amb;
		MeshMaterials[i + 1] = diff;
		MeshMaterials[i + 2] = spec;
	}
}

void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshMaterials[meshnum * 3] = amb;
	MeshMaterials[meshnum * 3 + 1] = diff;
	MeshMaterials[meshnum * 3 + 2] = spec;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_ColorLight::Render()
{
	pModel->BindVertexIndexBuffers(pShader->GetContext());
	int count = 0;
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshMaterials[count], MeshMaterials[count + 1], MeshMaterials[count + 2]);
		pModel->RenderMesh(pShader->GetContext(), i);
		count += 3;
	}
}