//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "TeddyModel.h"
#include <eat2.h>
#include <CHeader.h>
#include "eat.h"
#include <vector>

namespace Azul
{
	//Struct headers 
	struct FBX_Vertex_vsn
	{
		int index;
		float x;
		float y;
		float z;
		float s;
		float t;
		float nx;
		float ny;
		float nz;

	};
	struct VBO_Trilist
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	struct Bone_weight
	{
		float a;
		float b;
		float c;
		float d;
	};

	struct Bone_index
	{
		unsigned int ia;
		unsigned int ib;
		unsigned int ic;
		unsigned int id;
	};

	struct Mat
	{
		float m0;
		float m1;
		float m2;
		float m3;
		float m4;
		float m5;
		float m6;
		float m7;
		float m8;
		float m9;
		float m10;
		float m11;
		float m12;
		float m13;
		float m14;
		float m15;
	};
	// loaded by file system, made in the converter
	/*int Hierarchy[]
	{
		0, 20, 20, 20,  20,  20,  20,  20,  20,
		0,  1, 20, 20,  20,  20,  20,  20,  20,
		0,  1,  2, 20,  20,  20,  20,  20,  20,
		0,  1,  2,  3,  20,  20,  20,  20,  20,
		0,  1,  2,  3,   4,  20,  20,  20,  20,
		0,  1,  2,  3,   4,   5,  20,  20,  20,
		0,  1,  2,  6,  20,  20,  20,  20,  20,
		0,  1,  2,  6,   7,  20,  20,  20,  20,
		0,  1,  2,  6,   7,   8,  20,  20,  20,
		0,  1,  2,  9,  20,  20,  20,  20,  20,
		0,  1,  2,  9,  10,  20,  20,  20,  20,
		0,  1,  2,  9,  10,  11,  20,  20,  20,
		0,  1,  2,  9,  10,  11,  12,  20,  20,
		0,  1,  2,  9,  10,  11,  12,  13,  20,
		0,  1,  2,  9,  10,  11,  12,  13,  14,
		0,  1,  2,  9,  10,  15,  20,  20,  20,
		0,  1,  2,  9,  10,  15,  16,  20,  20,
		0,  1,  2,  9,  10,  15,  16,  17,  20,
		0,  1,  2,  9,  10,  15,  16,  17,  18,
		0,  1,  2,  9,  10,  19,  20,  20,  20
	};*/


	void TeddyModel::privCreateVAO(const char* const modelFileName)
	{
		AZUL_UNUSED_VAR(modelFileName);

		//Initialize
		FBX_Vertex_vsn* Verts = nullptr;
		VBO_Trilist* TriList = nullptr;
		Bone_weight* BoneWeight = nullptr;
		Bone_index* BoneIndex = nullptr;
		Mat* InversePose = nullptr;
		unsigned int chunkSize = 0;

		//Extract
		eat2("TeddySkin.spu", CType::VERTS_TYPE, "", (unsigned char*&)Verts, chunkSize);
		chunkSize = 0;
		eat2("TeddySkin.spu", CType::TRI_TYPE, "", (unsigned char*&)TriList, chunkSize);
		chunkSize = 0;
		eat2("TeddySkin.spu", CType::BONE_TYPE, "", (unsigned char*&)BoneWeight, chunkSize);
		chunkSize = 0;
		eat2("TeddySkin.spu", CType::BONE_INDEX, "", (unsigned char*&)BoneIndex, chunkSize);
		chunkSize = 0;
		eat2("TeddySkin.spu", CType::INVERSE_TYPE, "", (unsigned char*&)InversePose, chunkSize);
		this->numVerts = 1034;
		this->numTris = 1628;
		hierData* hier = nullptr;
		
		eat("Teddy.spu", ChunkType::HIER_TYPE, "", (unsigned char*&)hier, chunkSize);

		//Get the Depth data
		//Full Hack
		hierData current;
		int* depth = new int[20];
		for (int i = 0; i < 20; i++)
		{
			depth[i] = 0;
			current = hier[i];
			while (current.parentIndex > -1)
			{
				current = hier[current.parentIndex];
				depth[i]++;
			}
		}

		//Get Hierarchy data
		//80 bones work for teddy too Wow!!!
		unsigned int hierSize = (unsigned int)(80 * 9);
		int* Hierarchy = new int[hierSize];
		for (unsigned int i = 0; i < hierSize; i++)
		{
			Hierarchy[i] = 20;
		}
		int ind = 0;
		for (int i = 0; i < 20; i++)
		{
			ind = i * 9;
			current = hier[i];
			for (int j = ind + depth[i]; j >= ind; j--)
			{
				Hierarchy[j] = current.index;
				current = hier[current.parentIndex];
			}
		}




		// Set the SBO 
		this->poInversePose_SBO->Set(this->NumBones, sizeof(Mat), InversePose);
		this->poHierarchy_SBO->Set((this->NumBones * this->HeirarchyDepth), sizeof(int), &Hierarchy[0]);

		

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);

		glBindVertexArray(this->vao);  //<---- active

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_trilist);
		assert(this->vbo_trilist != 0);

		glGenBuffers(1, &this->vbo_boneweight);
		assert(this->vbo_boneweight != 0);

		glGenBuffers(1, &this->vbo_boneindex);
		assert(this->vbo_boneindex != 0);

		// Load VERTS: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(FBX_Vertex_vsn) * this->numVerts), Verts, GL_STATIC_DRAW);

		// Vertext data in location 0
		void* offsetVert = (void*)((unsigned int)&Verts[0].x - (unsigned int)Verts);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data in location 1
		void* offsetTex = (void*)((unsigned int)&Verts[0].s - (unsigned int)Verts);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetTex);
		glEnableVertexAttribArray(1);

		// Normal data in location 2
		void* offsetNorm = (void*)((unsigned int)&Verts[0].nx - (unsigned int)Verts);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetNorm);
		glEnableVertexAttribArray(2);
		// Load BoneWeight: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneweight);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_weight) * this->numVerts), BoneWeight, GL_STATIC_DRAW);

		// BoneWeight data in location 3
		offsetVert = (void*)((unsigned int)&BoneWeight[0].a - (unsigned int)BoneWeight);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Bone_weight), offsetVert);
		glEnableVertexAttribArray(3);
		// Load BoneIndex: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneindex);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_index) * this->numVerts), BoneIndex, GL_STATIC_DRAW);

		// BoneIndex data in location 4
		offsetVert = (void*)((unsigned int)&BoneIndex[0].ia - (unsigned int)BoneIndex);
		glVertexAttribIPointer(4, 4, GL_UNSIGNED_INT, sizeof(Bone_index), offsetVert);
		glEnableVertexAttribArray(4);

		// Load TriList: ---------------------------------------------------------

		/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(VBO_Trilist) * this->numTris), TriList, GL_STATIC_DRAW);
		delete[] Verts;
		delete[] TriList;
		delete[] BoneIndex;
		delete[] BoneWeight;
		delete[] InversePose;
		delete depth;
		delete[] Hierarchy;
		delete hier;
	}

	TeddyModel::TeddyModel(const char* const modelFileName)
		: Model(),
		vbo_boneweight(0),
		vbo_boneindex(0),
		NumBones(0),
		HeirarchyDepth(0),
		poInversePose_SBO(nullptr),
		poHierarchy_SBO(nullptr)
	{
		this->NumBones = 20;
		this->HeirarchyDepth = 9;

		this->poInversePose_SBO = new SSBO();
		this->poHierarchy_SBO = new SSBO();
		this->privCreateVAO(modelFileName);
	}

	TeddyModel::~TeddyModel()
	{
		// remove anything dynamic here
		delete this->poInversePose_SBO;
		delete this->poHierarchy_SBO;
	}

}

// --- End of File ---
