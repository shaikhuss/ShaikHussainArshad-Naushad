//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SpuModel.h"
#include "ModelFileHdr.h"
#include "File.h"
#include "BoundingSphere.h"
#include "eat.h"
#include "PackageHeader.h"
#include "ChunkHeader.h"
#include "TextureMan.h"



namespace Azul
{
	struct Vert_xyzuvn
	{
		float x;
		float y;
		float z;
		float u;
		float v;
		float nx;
		float ny;
		float nz;

	};
	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;

	};


	void SpuModel::privCreateVAO(const char* const pModelFileName)
	{

		unsigned int chunkSize;
		Vert_xyzuvn* pVerts;
		bool Result = eat(pModelFileName, ChunkType::HIER_TYPE, "", (unsigned char*&)pVerts, chunkSize);
		this->numVerts = (int)(chunkSize / sizeof(Vert_xyzuvn));

		Tri_index* pTri;
		Result = eat(pModelFileName, ChunkType::ANIM_TYPE, "", (unsigned char*&)pTri, chunkSize);
		this->numTris = (int)(chunkSize / sizeof(Tri_index));

		// Data is in RAM...
		// Configure and send data to GPU

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_trilist);
		assert(this->vbo_trilist != 0);


		// Find Bounding Volume - quick hack
		// MOVE this to converter!!!!!


		//Result = eat(pModelFileName, ChunkType::UV_TYPE, "", (unsigned char*&)pTri, chunkSize);
		//for (int i = 0; i < this->numVerts; i++)
		//{
		//	pVerts[i].set(pVerts[i].x, pVerts[i].y, pVerts[i].z);
		//	Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
		//}
		//
		//assert(this->poRefSphere);
		//this->poRefSphere->RitterSphere(pVerts, this->numVerts);
		//Trace::out("Ritter: cntr:%f %f %f  rad: %f ", this->poRefSphere->cntr[x], this->poRefSphere->cntr[y], this->poRefSphere->cntr[z], this->poRefSphere->rad);


		Vect* pVert = new Vect[(unsigned int)this->numVerts];
		for (int i = 0; i < this->numVerts; i++)
		{
			pVert[i].set(pVerts[i].x, pVerts[i].y, pVerts[i].z);
			//Trace::out(" Bounding Sphere %d:  %f %f %f\n", i, pVert[i][x], pVert[i][y], pVert[i][z]);
		}

		assert(this->poRefSphere);
		this->poRefSphere->RitterSphere(pVert, this->numVerts);
		//Trace::out("Ritter: cntr:%f %f %f  rad: %f ", this->poRefSphere->cntr[x], this->poRefSphere->cntr[y], this->poRefSphere->cntr[z], this->poRefSphere->rad);

		delete[] pVert;

		// Load the combined data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pVerts, GL_STATIC_DRAW);




		// Define an array of generic vertex attribute data

		// todo make a table or enum - locations needs enums...

		// Vert data is location: 0  (used in vertex shader)
		void* offsetVert = (void*)((unsigned int)&pVerts[0].x - (unsigned int)pVerts);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data is location: 1  (used in vertex shader)
		void* offsetTex = (void*)((unsigned int)&pVerts[0].u - (unsigned int)pVerts);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
		glEnableVertexAttribArray(1);

		// normals data in location 2 (used in vertex shader
		void* offsetNorm = (void*)((unsigned int)&pVerts[0].nx - (unsigned int)pVerts);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
		glEnableVertexAttribArray(2);

		//delete pCubeData;
		delete[] pVerts;
		// Load the index data: ---------------------------------------------------------

			/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), pTri, GL_STATIC_DRAW);
		delete pTri;

		if (strcmp(pModelFileName, "warbear.spu") == 0)
		{
			TextureMan::AddSpu(pModelFileName, Texture::Name::WARBEAR);
		}
		if (strcmp(pModelFileName, "buggy.spu") == 0)
		{
			TextureMan::AddSpu(pModelFileName, Texture::Name::BUGGY);
		}
		if (strcmp(pModelFileName, "astroboy.spu") == 0)
		{
			TextureMan::AddSpu(pModelFileName, Texture::Name::ASTRO);
		}
		if (strcmp(pModelFileName, "space_frigate.spu") == 0)
		{
			TextureMan::AddSpu(pModelFileName, Texture::Name::SPACE);
		}
		if (strcmp(pModelFileName, "robo.spu") == 0)
		{
			TextureMan::AddSpu(pModelFileName, Texture::Name::ROBO);
		}
		else {
			TextureMan::AddSpu(pModelFileName, Texture::Name::HOTPINK);
		}
	}

	SpuModel::SpuModel(const char* const pModelFileName)
		: Model()
	{
		assert(pModelFileName);
		this->privCreateVAO(pModelFileName);
	}

	SpuModel::~SpuModel()
	{
		// remove anything dynamic here
	}
}

// --- End of File ---
