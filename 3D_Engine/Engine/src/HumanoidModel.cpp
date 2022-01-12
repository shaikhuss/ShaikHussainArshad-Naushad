//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "HumanoidModel.h"

#include <CHeader.h>
#include <eat3.h>
#include <ChunkHeader.h>
#include <eat.h>
#include <vector>

namespace Azul
{
	//Initialize structs
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
	/*int HumanoidHierarchy[]
	{
	  0,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  5,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  5,	  6,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  5,	  6,	  7,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 8,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	 11,	80,	 80,	 80,   80,	 80,	 80,	 80,	80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	80,	 80,	 80,	   80,	 80,	 80,	80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	80,	 80,	 80,	  80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	 14,      80,		80,	 80,	 80,	  80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 80,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 16,	  80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 16,	 17,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 16,	 17,	 18,	80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 16,	 17,	 18,	 19,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	20,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  20,	 21,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	20,	 21,	 22,	80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	20,	 21,	 22,	 23,
	  0,	  1,	  2,	  3,	  4,	   8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	24,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  24,	 25,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  24,	 25,	 26,	80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	24,	 25,	 26,	 27,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 28,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  28,	 29, 	80,	  80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 28,	 29,	30,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  28,	 29,	 30,	 31,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	  32,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 32,	 33,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	32,	 33,	 34,	 80,
	  0,	  1,	  2,	  3,	  4,	  8,	  9,	 10,	 11,	 12,	 13,	 14,	 15,	 32,	 33,	 34,	 35,
	  0,	  1,	  2,	  3,	  4,	 36,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37, 	38,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	80,	 80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,   80,	 80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	80,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	 44,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	 44,	 45,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	 44,	 45,	 46,	80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	 44,	 45,	 46,	 47,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	48,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	48,	 49,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	48,	 49,	 50,	80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	48,	 49,	 50,	 51,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	52,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	52,	 53,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	52,	 53,	 54,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	52,	 53,	 54,	 55,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	56,	80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	56,	 57,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	  56,	 57,	 58,	80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	56,	 57,	 58,	 59,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	   60,	 80,	 80,	 80,
	  0,	  1,	  2,	  3,	  4,	 36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	  60,	 61,	80,	 80,
	  0,	  1,	  2,	  3,	  4,	  36,	 37,	 38,	 39,	 40,	 41,	 42,	 43,	60,	 61,	 62,	80,
	  0,	  1,	  2,	  3,	  4,	36,	 37,	 38,	 39,	 40,	 41,	 42,	 43, 	60,	 61,	 62,	 63,
	  0,	 64,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	80,
	  0,	64,	 65,	 66, 	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	 66,	 67,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	 66,	 67,	 68,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	 66,	 67,	 68,	 69,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	 66,	 67,	 68,	 69,	 70,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 64,	 65,	 66,	 67,	 68,	 69,	 70,	 71,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	 74,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	 74,	 75,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	 74,	 75,	 76,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	72,	 73,	 74,	 75,	 76,	 77, 	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	 74,	 75,	 76,	 77,	 78,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,
	  0,	 72,	 73,	 74,	 75,	 76,	 77,	 78,	 79,	80,	 80,	 80,	 80,	 80,	 80,	 80,	 80,

	};*/

	
	void HumanoidModel::privCreateVAO(const char* const modelFileName)
	{
		// Set the SBO 
		
		// future proofing it for a file
		AZUL_UNUSED_VAR(modelFileName);

		//Initalize
		FBX_Vertex_vsn* Vert = nullptr;
		VBO_Trilist* Tri = nullptr;
		Bone_weight* B_Weight = nullptr;
		Bone_index* B_Index = nullptr;
		Mat* Inverse = nullptr;
		unsigned int chunkSize = 0;

		//extract
		eat3("humanoidSkin.spu", CType::VERTS_TYPE, "", (unsigned char*&)Vert, chunkSize);
		chunkSize = 0;
		eat3("humanoidSkin.spu", CType::TRI_TYPE, "", (unsigned char*&)Tri, chunkSize);
		chunkSize = 0;
		eat3("humanoidSkin.spu", CType::BONE_TYPE, "", (unsigned char*&)B_Weight, chunkSize);
		chunkSize = 0;
		eat3("humanoidSkin.spu", CType::BONE_INDEX, "", (unsigned char*&)B_Index, chunkSize);
		chunkSize = 0;
		eat3("humanoidSkin.spu", CType::INVERSE_TYPE, "", (unsigned char*&)Inverse, chunkSize);

		hierData* hier = nullptr;
		//chunkSize = 0;
		eat("Humanoid.spu", ChunkType::HIER_TYPE, "", (unsigned char*&)hier, chunkSize);


		//Bone hierarchy
		hierData current;
		int* depth = new int[80];
		for (int i = 0; i < 80; i++)
		{
			depth[i] = 0;
			current = hier[i];
			while (current.parentIndex > -1)
			{
				current = hier[current.parentIndex];
				depth[i]++;
			}
		}

		unsigned int hierSize = (unsigned int)(80 * 17);
		int* HumanoidHier = new int[hierSize];
		for (unsigned int i = 0; i < hierSize; i++)
		{
			HumanoidHier[i] = 80;
		}
		int ind = 0;
		for (int i = 0; i < 80; i++)
		{
			ind = i * 17;
			current = hier[i];
			for (int j = ind + depth[i]; j >= ind; j--)
			{
				HumanoidHier[j] = current.index;
				current = hier[current.parentIndex];
			}
		}
		

		this->poInversePose_SBO->Set(this->NumBones, sizeof(Mat), Inverse);
		this->poHierarchy_SBO->Set((this->NumBones * this->HeirarchyDepth), sizeof(int), &HumanoidHier[0]);

		delete depth;
		delete [] HumanoidHier;
		//Matrix matIdentity(Matrix::Special::Identity);
		//for (unsigned int i = 0; i < this->NumBones; i++)
		//{
		//	this->poInversePose_SBO[i] = &Inverse[i];
		//	this->poBone[i] = matIdentity;
		//}
		this->numVerts = 1605;
		this->numTris = 3206;


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
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(FBX_Vertex_vsn) * this->numVerts), Vert, GL_STATIC_DRAW);

		// Vertext data in location 0
		void* offsetVert = (void*)((unsigned int)&Vert[0].x - (unsigned int)Vert);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetVert);
		glEnableVertexAttribArray(0);

		// Texture data in location 1
		void* offsetTex = (void*)((unsigned int)&Vert[0].s - (unsigned int)Vert);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetTex);
		glEnableVertexAttribArray(1);

		// Normal data in location 2
		void* offsetNorm = (void*)((unsigned int)&Vert[0].nx - (unsigned int)Vert);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FBX_Vertex_vsn), offsetNorm);
		glEnableVertexAttribArray(2);

		// Load BoneWeight: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneweight);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_weight) * this->numVerts), B_Weight, GL_STATIC_DRAW);

		// BoneWeight data in location 3
		offsetVert = (void*)((unsigned int)&B_Weight[0].a - (unsigned int)B_Weight);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Bone_weight), offsetVert);
		glEnableVertexAttribArray(3);

		// Load BoneIndex: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_boneindex);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Bone_index) * this->numVerts), B_Index, GL_STATIC_DRAW);

		// BoneIndex data in location 4
		offsetVert = (void*)((unsigned int)&B_Index[0].ia - (unsigned int)B_Index);
		glVertexAttribIPointer(4, 4, GL_UNSIGNED_INT, sizeof(Bone_index), offsetVert);
		glEnableVertexAttribArray(4);

		// Load TriList: ---------------------------------------------------------

		/* Bind our 2nd VBO as being the active buffer and storing index ) */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_trilist);

		/* Copy the index data to our buffer */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(VBO_Trilist) * this->numTris), Tri, GL_STATIC_DRAW);
		delete[] Vert;
		delete[] Tri;
		delete[] B_Index;
		delete[] B_Weight;
		delete[] Inverse;
		delete hier;
	}

	HumanoidModel::HumanoidModel(const char* const modelFileName)
		: Model(),
		vbo_boneweight(0),
		vbo_boneindex(0),
		NumBones(0),
		HeirarchyDepth(0),
		poInversePose_SBO(nullptr),
		poHierarchy_SBO(nullptr)
	{
		this->NumBones = 80;
		this->HeirarchyDepth = 17;

		this->poInversePose_SBO = new SSBO();
		this->poHierarchy_SBO = new SSBO();
		this->privCreateVAO(modelFileName);
	}

	HumanoidModel::~HumanoidModel()
	{
		// remove anything dynamic here
		delete this->poInversePose_SBO;
		delete this->poHierarchy_SBO;
	}

}

// --- End of File ---
