#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	int nVerts = side * side;
	int nTris = (side - 1) * (side - 1) * 2;
	int vertInd = 0;
	int triInd = 0;
	float repU = (float)RepeatU / (side - 1);
	float repV = (float)RepeatV / (side - 1);

	float posX = len * 0.5f;
	float posZ = len * 0.5f;
	float incXZ = len / side;

	StandardVertex* pVerts = new StandardVertex[nVerts];
	TriangleByIndex* pTriList = new TriangleByIndex[nTris];

	for (int i = 0; i < (int)side; i++)
	{
		for (int j = 0; j < (int)side; j++)
		{
			float posY = hgtmap->pixels[TexelIndex(side, j, i)] * maxheight / 256;
			pVerts[vertInd].set(posX, posY, posZ, j * repU, i * repV);
			posX -= incXZ;
			vertInd++;
		}

		posZ -= incXZ;
		posX = len * 0.5f;
	}

	vertInd = 0;
	for (int i = 0; i < (int)side - 1; i++)
	{
		for (int j = 0; j < (int)side - 1; j++)
		{
			pTriList[triInd].set(vertInd, vertInd + side + 1, vertInd + 1);
			triInd++;
			pTriList[triInd].set(vertInd, vertInd + side, vertInd + side + 1);
			triInd++;

			vertInd++;


		}
		vertInd++;
	}


	// ** much work to add below **
	pModTerrain = new Model(dev, pVerts, nVerts, pTriList, nTris);
	delete[] pVerts;
	delete[] pTriList;

}

int TerrainModel::TexelIndex(int side, int i, int j) const
{
	return  4 * (j * side + i);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;

}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}