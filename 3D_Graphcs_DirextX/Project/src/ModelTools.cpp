#include "ModelTools.h"
//#include "Enum.h"
#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"
#include <vector>


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri, float size)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f * size, 0.5f * size, 0.5f * size, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, 0.5f * size, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, 0.5f * size, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, 0.5f * size, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f * size, 0.5f * size, 0.5f * size, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f * size, -0.5f * size, 0.5f * size, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f * size, 0.5f * size, 0.5f * size, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f * size, -0.5f * size, 0.5f * size, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f * size, 0.5f * size, 0.5f * size, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f * size, 0.5f * size, 0.5f * size, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, -0.5f * size, 0.5f * size, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f * size, -0.5f * size, 0.5f * size, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateSkyBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri, float size)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];
	
	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 1.0f / 3.0f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 1.0f / 3.0f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 2.0f / 3.0f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 2.0f / 3.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 1.0f, 1.0f / 3.0f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0.75f, 1.0f / 3.0f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0.75f, 2.0f / 3.0f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 1.0f, 2.0f / 3.0f);
	pTriList[tind].set(vind + 1, vind + 2, vind);
	pTriList[tind + 1].set(vind + 2, vind + 3, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0.0f, 1.0f / 3.0f);
	pVerts[vind + 1].set(0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 1.0f / 3.0f);
	pVerts[vind + 2].set(0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 2.0f / 3.0f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0.0f, 2.0f / 3.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 1.0f / 3.0f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0.75f, 1.0f / 3.0f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0.75f, 2.0f / 3.0f);
	pVerts[vind + 3].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 2.0f / 3.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0.25f, 0.0f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0.5f, 0.0f);
	pVerts[vind + 2].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 1.0f / 3.0f);
	pVerts[vind + 3].set(0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 1.0f / 3.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 2.0f / 3.0f);
	pVerts[vind + 1].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 2.0f / 3.0f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0.5f, 1.0f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0.25f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 18;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	//back face
	pVerts[0].set(0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[1].set(-0.5f, -0.5f, -0.5f, 1, 1);
	pVerts[2].set(0.0f, 0.5f, 0.0f, 0.5f, 0);
	pTriList[0].set(0, 1, 2);

	//front face
	pVerts[3].set(0.0f, +0.5f, 0.0f, 0.5f, 0);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, 0, 1);
	pVerts[5].set(+0.5f, -0.5f, +0.5f, 1, 1);
	pTriList[1].set(3, 4, 5);

	//left face
	pVerts[6].set(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[7].set(-0.5f, -0.5f, +0.5f, 1, 1);
	pVerts[8].set(0.0f, +0.5f, 0.0f, 0.5f, 0);
	pTriList[2].set(6, 7, 8);

	//right face
	pVerts[9].set(0.0f, +0.5f, 0.0f, 0.5f, 0);
	pVerts[10].set(+0.5f, -0.5f, +0.5f, 0, 1);
	pVerts[11].set(+0.5f, -0.5f, -0.5f, 1, 1);
	pTriList[3].set(9, 10, 11);

	//bottom face
	pVerts[12].set(-0.5f, -0.5f, +0.5f, 1, 0, 0, -1, 0);
	pVerts[13].set(-0.5f, -0.5f, -0.5f, 0, 0, 0, -1, 0);
	pVerts[14].set(+0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pTriList[4].set(12, 13, 14);

	pVerts[15].set(+0.5f, -0.5f, +0.5f, 1, 1, 0, -1, 0);
	pVerts[16].set(-0.5f, -0.5f, +0.5f, 1, 0, 0, -1, 0);
	pVerts[17].set(+0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pTriList[5].set(15, 16, 17);

	for (int i = 0; i < ntri; i++)
	{
		int index1 = pTriList[i].v0;
		int index2 = pTriList[i].v1;
		int index3 = pTriList[i].v2;

		Vect side1 = pVerts[index1].Pos - pVerts[index3].Pos;
		Vect side2 = pVerts[index1].Pos - pVerts[index2].Pos;
		Vect mynormal = side2.cross(side1);

		pVerts[index1].normal = Vect(0, 0, 0);
		pVerts[index2].normal = Vect(0, 0, 0);
		pVerts[index3].normal = Vect(0, 0, 0);

		pVerts[index1].normal += mynormal;
		pVerts[index2].normal += mynormal;
		pVerts[index3].normal += mynormal;
	}

}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, 0.5f, 0.0f, Colors::Cyan);
	pVerts[1].set(0.5f, -0.5f, 0.5f, Colors::Lime);
	pVerts[2].set(-0.5f, -0.5f, 0.5f, Colors::Yellow);
	pVerts[3].set(-0.5f, -0.5f, -0.5f, Colors::Red);
	pVerts[4].set(0.5f, -0.5f, -0.5f, Colors::Magenta);

	//Base
	pTriList[0].set(1, 2, 3);
	pTriList[1].set(1, 3, 4);

	// front face
	pTriList[2].set(0, 2, 1);

	//Left side
	pTriList[3].set(0, 3, 2);

	// Right face
	pTriList[4].set(0, 1, 4);

	//Back face
	pTriList[5].set(0, 4, 3);

}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = (vslice * hslice) + 1;
	ntri = 2 * vslice * (hslice - 1);

	//float pi = MATH_PI;

	pVerts = new StandardVertex[nverts];

	const float pi_1 = MATH_PI / vslice;
	const float pi_2 = MATH_2PI / hslice;

	for (int j = 0; j < vslice; j++)
	{
		const float sin1 = sinf(pi_1 * j);
		const float cos1 = cosf(pi_1 * j);

		for (int i = 0; i < hslice; i++)
		{
			const float sin2 = sinf(pi_2 * i);
			const float cos2 = cosf(pi_2 * i);


			const float x = sin1 * cos2;
			const float y = cos1;
			const float z = sin1 * sin2;

			const float u = ((float)j / vslice) * 1.0f;
			const float v = (1.0f - (float)(i + 1.0f) / (i + 1.0f) * 1.0f);

			pVerts[i + (j * hslice)].set(x, y, z, u, v, x, y, z);
		}
	}
	pVerts[vslice * hslice].set(0.0f, -1.0f, 0.0f, 0, 0, 0.0f, -1.0f, 0.0f);

	pTriList = new TriangleByIndex[ntri];
	int i = 0;

	int tri_1 = hslice + 1;
	int tri_2 = hslice + 1;
	int tri_3 = hslice;
	for (int j = 0; j < hslice - 1; j++)
	{
		pTriList[i++].set(0, tri_2++, tri_3++);

	}
	pTriList[i++].set(0, hslice, (2 * hslice) - 1);

	for (int k = 1; k < vslice - 1; k++)
	{
		tri_1 = hslice * k + 1;
		tri_2 = tri_1 + hslice - 1;
		tri_3 = hslice * k;
		for (int j = 0; j < hslice - 1; j++)
		{
			pTriList[i++].set(tri_1, tri_2++, tri_3);
			pTriList[i++].set(tri_1++, tri_2, tri_3 + hslice);
			tri_3++;
		}
		tri_1 = hslice * k;
		pTriList[i++].set(tri_1, tri_2++, tri_3);
		tri_2 = hslice + (hslice * k);
		pTriList[i++].set(tri_1, tri_2, tri_3 + hslice);
	}

	tri_1 = hslice * vslice;
	tri_2 = tri_1 - 2;
	tri_3 = tri_1 - 1;
	for (int j = 0; j < hslice - 1; j++)
	{
		pTriList[i++].set(tri_1, tri_2--, tri_3--);
	}
	pTriList[i++].set(tri_1, tri_1 - 1, tri_1 - hslice);
}