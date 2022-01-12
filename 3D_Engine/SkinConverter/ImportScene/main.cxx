/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

/////////////////////////////////////////////////////////////////////////
//
// This example illustrates how to detect if a scene is password 
// protected, import and browse the scene to access node and animation 
// information. It displays the content of the FBX file which name is 
// passed as program argument. You can try it with the various FBX files 
// output by the export examples.
//
/////////////////////////////////////////////////////////////////////////

#include "../Common/Common.h"
#include "DisplayCommon.h"
#include "DisplayHierarchy.h"
#include "DisplayAnimation.h"
#include "DisplayMarker.h"
#include "DisplaySkeleton.h"
#include "DisplayMesh.h"
#include "DisplayNurb.h"
#include "DisplayPatch.h"
#include "DisplayLodGroup.h"
#include "DisplayCamera.h"
#include "DisplayLight.h"
#include "DisplayGlobalSettings.h"
#include "DisplayPose.h"
#include "DisplayPivotsAndLimits.h"
#include "DisplayUserProperties.h"
#include "DisplayGenericInfo.h"
#include "ChunkHeader.h"
#include "PackageHeader.h"

//#include <WinBase.h>

// Local function prototypes.
void DisplayContent(FbxScene* pScene);
void DisplayContent(FbxNode* pNode);
void DisplayTarget(FbxNode* pNode);
void DisplayTransformPropagation(FbxNode* pNode);
void DisplayGeometricTransform(FbxNode* pNode);
void DisplayMetaData(FbxScene* pScene);

static bool gVerbose = true;

// Keenan(3.2.4) - STL
	#include "FBX_STL.h"
	std::vector<FBX_Vertex> FBX_vert;
	std::vector<FBX_Vertex_vsn> FBX_vert_fat;
	std::vector<FBX_Trilist> FBX_tri;

// Keenan(3.2.5) - VBO and Reduce
	#include "FBX_VBO.h"
	std::vector<VBO_Trilist> VBO_tri;
	std::vector<FBX_Vertex_vsn> VBO_vert;

// -------------------------------------------------------------------
// Keenan(2) Weights
// -------------------------------------------------------------------
		#include <vector>
		#include <algorithm>
		#include "BoneWeight.h"
//#include <handleapi.h>
//#include <fileapi.h>
//#include <WinBase.h>

//#include <fileapi.h>
//#include <handleapi.h>
//#include <WinBase.h>

		std::vector< BoneEntry > vBoneTable;
		std::vector< VertEntry > vBoneWeightTable;
		std::vector< FinalVertEntry > vFinalBoneWeightTable;
        std::vector< PoseInvBoneEntry > vFinalInvPoseTable;
		int totalNumVerts = 0;

		bool Vect_sort(BoneWeight const& v1, BoneWeight const& v2)
		{
			if (v1.fBoneWeight > v2.fBoneWeight)
			{
				return true;
			}
			else
			{
				return false;
			}
		}



int main(int argc, char** argv)
{
    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult;

    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);
    // Load the scene.

    // The example can take a FBX file as an argument.
	FbxString lFilePath("");
	for( int i = 1, c = argc; i < c; ++i )
	{
		if( FbxString(argv[i]) == "-test" ) gVerbose = false;
		else if( lFilePath.IsEmpty() ) lFilePath = argv[i];
	}

	if( lFilePath.IsEmpty() )
	{
        lResult = false;
        FBXSDK_printf("\n\nUsage: ImportScene <FBX file name>\n\n");
	}
	else
	{
		FBXSDK_printf("\n\nFile: %s\n\n", lFilePath.Buffer());
		lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());
	}

    if(lResult == false)
    {
        FBXSDK_printf("\n\nAn error occurred while loading the scene...");
    }
    else 
    {
        // Keenan(3.1) - Triangulate
        FbxGeometryConverter lGeomConverter(lSdkManager);
        // Replace = true
        lGeomConverter.Triangulate(lScene, true);

		// Keenan(3.2.2) - Kill the pig
        // Display the scene.
			//DisplayMetaData(lScene);
			//FBXSDK_printf("\n\n---------------------\nGlobal Light Settings\n---------------------\n\n");
			//if( gVerbose ) DisplayGlobalLightSettings(&lScene->GetGlobalSettings());
			//FBXSDK_printf("\n\n----------------------\nGlobal Camera Settings\n----------------------\n\n");
			//if( gVerbose ) DisplayGlobalCameraSettings(&lScene->GetGlobalSettings());
			//FBXSDK_printf("\n\n--------------------\nGlobal Time Settings\n--------------------\n\n");
			//if( gVerbose ) DisplayGlobalTimeSettings(&lScene->GetGlobalSettings());

        FBXSDK_printf("\n\n---------\nHierarchy\n---------\n\n");

        if( gVerbose ) DisplayHierarchy(lScene);

        FBXSDK_printf("\n\n------------\nNode Content\n------------\n\n");

        if( gVerbose ) DisplayContent(lScene);

		// Keenan(3.2.2) - Kill the pig
			//FBXSDK_printf("\n\n----\nPose\n----\n\n");
			//if( gVerbose ) DisplayPose(lScene);
			//FBXSDK_printf("\n\n---------\nAnimation\n---------\n\n");
			//if( gVerbose ) DisplayAnimation(lScene);
			////now display generic information
			//FBXSDK_printf("\n\n---------\nGeneric Information\n---------\n\n");
			//if( gVerbose ) DisplayGenericInfo(lScene);
    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);


	// Keenan(3.2.5) - VBO and Reduce

		// Sort ME -----------------------------------------------------

		// copy FBX_vert_fat into FBX_vert_fast_sort
		std::vector<FBX_Vertex_vsn> FBX_vert_fat_sort(FBX_vert_fat);

		// sort it
		// THANK YOU STL SORT!!!!!!
		std::sort(FBX_vert_fat_sort.begin(), FBX_vert_fat_sort.end());

		printf("\n\nFBX SORT\n\n");

		// dump the sort
		FBX_Vertex_vsn vTmp;
		for (int i = 0; i < (int)FBX_vert_fat_sort.size(); i++)
		{
			vTmp = FBX_vert_fat_sort[i];
			printf("FBX_sort[%d]: i:%d v: %f %f %f s: %f %f n:%f %f %f \n",
				   i, vTmp.index, vTmp.x, vTmp.y, vTmp.z, vTmp.s, vTmp.t, vTmp.nx, vTmp.ny, vTmp.nz);
		}
		printf("\n\n");

		// REDUCE ME  --------------

		// Destination size (max os the same size of the fat, probably will be smaller)
		VBO_vert.reserve(FBX_vert_fat_sort.size());

		// get the current
		FBX_Vertex_vsn currVert = FBX_vert_fat_sort[0];
		VBO_vert.push_back(currVert);

		for (int i = 0; i < (int)FBX_vert_fat_sort.size(); i++)
		{
			vTmp = FBX_vert_fat_sort[i];

			// if curr != next, then next is good so stort it into redux buffer
			if (!(vTmp == currVert))
			{
				currVert = vTmp;
				VBO_vert.push_back(currVert);
			}
		}

		// print me - BTW this the final VBO vert buffer
		for (int i = 0; i < (int)VBO_vert.size(); i++)
		{
			vTmp = VBO_vert[i];
			printf("VBO_vert[%d]: i:%d v: %f %f %f s: %f %f n:%f %f %f \n",
				   i, vTmp.index, vTmp.x, vTmp.y, vTmp.z, vTmp.s, vTmp.t, vTmp.nx, vTmp.ny, vTmp.nz);

		}
		printf("\n\n");
		assert(65536 >(int)VBO_vert.size());

		// now create an update trilist
		VBO_tri.reserve(FBX_tri.size());
		std::vector< FBX_Vertex_vsn >::iterator it;

		int new_v0;
		int new_v1;
		int new_v2;
		VBO_Trilist tmpVBOTri;

		for (int i = 0; i < (int)FBX_tri.size(); i++)
		{
			FBX_Trilist old_Tri = FBX_tri[i];
			FBX_Vertex_vsn vert;

			// -- V0 ---------
			// find the old V0 in the fat list unsorted, get the vert
			// goto the new VBO_vert, find the vert get the index

			vert = FBX_vert_fat[old_Tri.v0];

			it = std::find(VBO_vert.begin(), VBO_vert.end(), vert);

			new_v0 = std::distance(VBO_vert.begin(), it);

			// -- V1 ---------

			vert = FBX_vert_fat[old_Tri.v1];

			it = std::find(VBO_vert.begin(), VBO_vert.end(), vert);

			new_v1 = std::distance(VBO_vert.begin(), it);
			// -- V2 ---------

			vert = FBX_vert_fat[old_Tri.v2];

			it = std::find(VBO_vert.begin(), VBO_vert.end(), vert);

			new_v2 = std::distance(VBO_vert.begin(), it);

			// create the VBO_tri

			tmpVBOTri.v0 = new_v0;
			tmpVBOTri.v1 = new_v1;
			tmpVBOTri.v2 = new_v2;

			VBO_tri.push_back(tmpVBOTri);
		}


		// Done - print VBO trilist 
		printf("\n\n");
		for (int i = 0; i< (int)VBO_tri.size(); i++)
		{
			tmpVBOTri = VBO_tri[i];
			printf("VBO_tri[%d]: %d %d %d\n", i, tmpVBOTri.v0, tmpVBOTri.v1, tmpVBOTri.v2);
		}


		printf("\n\n");

		// -------------------------------------------------------------------
		// Keenan(2) Weights
		// -------------------------------------------------------------------
				printf("\n");
				printf("\n");
				printf("AAA Original Bone centric - Keenan \n");
				for (unsigned int j = 0; j < vBoneTable.size(); j++)
				{
					vBoneTable[j].PrintMe();

					for (unsigned int k = 0; k < vBoneTable[j].vVertWeight.size(); k++)
					{
						printf("      i:%d w:%f \n", vBoneTable[j].vVertWeight[k].iVertIndex, vBoneTable[j].vVertWeight[k].fBoneWeight);
					}
				}

				// Vert centric table
				vBoneWeightTable.reserve(totalNumVerts);

				for (auto j = 0; j < totalNumVerts; j++)
				{
					VertEntry v;
					vBoneWeightTable.push_back(v);
				}

				printf("\n");
				printf("\n");
				printf("\n\nBBB Vert centric - Keenan \n");

				for (unsigned int j = 0; j < vBoneTable.size(); j++)
				{
					//vBoneTable[j].PrintMe();

					for (unsigned int k = 0; k < vBoneTable[j].vVertWeight.size(); k++)
					{
						int boneIndex = j;
						int vertIndex = vBoneTable[j].vVertWeight[k].iVertIndex;
						float boneWeight = vBoneTable[j].vVertWeight[k].fBoneWeight;

						BoneWeight bw;

						bw.iBoneIndex = boneIndex;
						bw.fBoneWeight = boneWeight;

						vBoneWeightTable[vertIndex].vBoneWeight.push_back(bw);

					}
				}

				for (auto j = 0; j < totalNumVerts; j++)
				{
					printf("vert:%d\n", j);

					for (unsigned int k = 0; k < vBoneWeightTable[j].vBoneWeight.size(); k++)
					{
						printf("      bone_i:%d w:%f \n", vBoneWeightTable[j].vBoneWeight[k].iBoneIndex, vBoneWeightTable[j].vBoneWeight[k].fBoneWeight);

					}
				}

				printf("\n");
				printf("\n");
				printf("CCC SORTED by weight - Keenan\n");

				for (auto j = 0; j < totalNumVerts; j++)
				{
					//printf("vert:%d\n", j);
					std::sort(vBoneWeightTable[j].vBoneWeight.begin(), vBoneWeightTable[j].vBoneWeight.end(), Vect_sort);

				}

				for (auto j = 0; j < totalNumVerts; j++)
				{
					printf("vert:%d\n", j);

					for (unsigned int k = 0; k < vBoneWeightTable[j].vBoneWeight.size(); k++)
					{
						printf("      bone_i:%d w:%f \n", vBoneWeightTable[j].vBoneWeight[k].iBoneIndex, vBoneWeightTable[j].vBoneWeight[k].fBoneWeight);

					}
				}

				printf("\n");
				printf("\n");
				printf("DDD Final SORTED by weight Keenan\n");

				for (auto j = 0; j < totalNumVerts; j++)
				{
					BoneWeight bw;
					bw.iBoneIndex = 0;
					bw.fBoneWeight = 0.0f;

					// Add more... in case there is only one entry
					vBoneWeightTable[j].vBoneWeight.push_back(bw);
					vBoneWeightTable[j].vBoneWeight.push_back(bw);
					vBoneWeightTable[j].vBoneWeight.push_back(bw);
					vBoneWeightTable[j].vBoneWeight.push_back(bw);

					// Load it
					FinalVertEntry fbw;
					fbw.A.iBoneIndex = vBoneWeightTable[j].vBoneWeight[0].iBoneIndex;
					fbw.A.fBoneWeight = vBoneWeightTable[j].vBoneWeight[0].fBoneWeight;

					fbw.B.iBoneIndex = vBoneWeightTable[j].vBoneWeight[1].iBoneIndex;
					fbw.B.fBoneWeight = vBoneWeightTable[j].vBoneWeight[1].fBoneWeight;

					fbw.C.iBoneIndex = vBoneWeightTable[j].vBoneWeight[2].iBoneIndex;
					fbw.C.fBoneWeight = vBoneWeightTable[j].vBoneWeight[2].fBoneWeight;

					fbw.D.iBoneIndex = vBoneWeightTable[j].vBoneWeight[3].iBoneIndex;
					fbw.D.fBoneWeight = vBoneWeightTable[j].vBoneWeight[3].fBoneWeight;

					// Normalize it
					float sum = fbw.A.fBoneWeight + fbw.B.fBoneWeight + fbw.C.fBoneWeight + fbw.D.fBoneWeight;

					fbw.A.fBoneWeight /= sum;
					fbw.B.fBoneWeight /= sum;
					fbw.C.fBoneWeight /= sum;
					fbw.D.fBoneWeight /= sum;

					// push back
					vFinalBoneWeightTable.push_back(fbw);

				}

				for (auto j = 0; j < totalNumVerts; j++)
				{
					float sum = vFinalBoneWeightTable[j].A.fBoneWeight
						+ vFinalBoneWeightTable[j].B.fBoneWeight
						+ vFinalBoneWeightTable[j].C.fBoneWeight
						+ vFinalBoneWeightTable[j].D.fBoneWeight;

					printf("vert:%d                     sum:%f\n", j, sum);

					printf("      bone_i:%d w:%f \n", vFinalBoneWeightTable[j].A.iBoneIndex, vFinalBoneWeightTable[j].A.fBoneWeight);
					printf("      bone_i:%d w:%f \n", vFinalBoneWeightTable[j].B.iBoneIndex, vFinalBoneWeightTable[j].B.fBoneWeight);
					printf("      bone_i:%d w:%f \n", vFinalBoneWeightTable[j].C.iBoneIndex, vFinalBoneWeightTable[j].C.fBoneWeight);
					printf("      bone_i:%d w:%f \n", vFinalBoneWeightTable[j].D.iBoneIndex, vFinalBoneWeightTable[j].D.fBoneWeight);
				}


                printf("\n");
                printf("\n");
                printf("EEE Final InversePose Keenan\n");
                printf("\n");
                for (size_t j = 0; j < vFinalInvPoseTable.size(); j++)
                {
                    vFinalInvPoseTable[j].PrintMe();
                }
				printf("\n");
				printf("\n");
				//Bind
				PackageHeader* pH = new PackageHeader();
				strcpy_s(pH->packageName, PackageHeader::PACKAGE_NAME_SIZE, lFilePath.Left(lFilePath.Size() - 4));
				pH->numChunks = 0;
				pH->totalSize = 0;

				HANDLE fh = CreateFile(argv[2], GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				SetFilePointer(fh, sizeof(PackageHeader), nullptr, FILE_BEGIN);

				ChunkHeader* vertChunk = new ChunkHeader();
				vertChunk->type = CType::VERTS_TYPE;
				vertChunk->chunkSize = sizeof(FBX_Vertex_vsn) * VBO_vert.size();

				WriteFile(fh, (char*)vertChunk, sizeof(ChunkHeader), nullptr, nullptr);
				
				

				printf("\n // ********************************************************************");
				printf("\n // ********************************************************************");
				printf("\n");
				printf("\n");
				printf("// FFF VBO Vert_xyzuvn KeenanX\n");
				printf("\n");
			   
				printf("Vert_xyzuvn Verts[] =\n");
				printf("{ \n");
				for (int i = 0; i < (int)VBO_vert.size(); i++)
				{
					vTmp = VBO_vert[i];
					printf("\t {%0ff, %0ff, %0ff, %0ff, %0ff, %0ff, %0ff, %0ff },   // [%d] index:%d \n",
						vTmp.x, vTmp.y, vTmp.z, vTmp.s, vTmp.t, vTmp.nx, vTmp.ny, vTmp.nz, i, vTmp.index);
					WriteFile(fh, &VBO_vert[i], sizeof(FBX_Vertex_vsn), nullptr, nullptr);
				}
				printf("}; \n");
				pH->numChunks++;
				pH->totalSize += sizeof(ChunkHeader) + vertChunk->chunkSize;

				delete vertChunk;

				
				ChunkHeader* triChunk = new ChunkHeader();
				triChunk->type = CType::TRI_TYPE;
				triChunk->chunkSize = sizeof(VBO_Trilist) * VBO_tri.size();
				WriteFile(fh, (char*)triChunk, sizeof(ChunkHeader), nullptr, nullptr);
				printf("\n");
				printf("\n");
				printf("// GGG VBO Tri_List KeenanX\n");
				printf("\n");
				printf("Tri_index TriList[] =\n");
				printf("{ \n");
				for (int i = 0; i < (int)VBO_tri.size(); i++)
				{
					tmpVBOTri = VBO_tri[i];
					printf("\t { %4d, %4d, %4d},   // [%d] \n", tmpVBOTri.v0, tmpVBOTri.v1, tmpVBOTri.v2,i);
					WriteFile(fh, &VBO_tri[i], sizeof(VBO_Trilist), nullptr, nullptr);
				}
				printf("}; \n");
				
				pH->numChunks++;
				pH->totalSize += sizeof(ChunkHeader) + triChunk->chunkSize;
				delete triChunk;

				

				/// <summary>
				BoneWeightTable pBoneWeight [1605];
				printf("\n");
				printf("\n");
				assert(totalNumVerts == vFinalBoneWeightTable.size());
				ChunkHeader* boneWeight = new ChunkHeader();
				boneWeight->type = CType::BONE_TYPE;
				boneWeight->chunkSize = sizeof(BoneWeightTable) * VBO_vert.size();
				WriteFile(fh, (char*)boneWeight, sizeof(ChunkHeader), nullptr, nullptr);
				printf("// HHH VBO Bone_Weight KeenanX\n");
				printf("\n");
				printf("Bone_weight BoneWeight[] =\n");
				printf("{ \n");
				for (int i = 0; i < (int)VBO_vert.size(); i++)
				{
					vTmp = VBO_vert[i];
					int index = vTmp.index;
					
					//printf("\t {%0ff, %0ff, %0ff, %0ff}, // [%d] index:%d \n",
						pBoneWeight[index].a = vFinalBoneWeightTable[index].A.fBoneWeight;
						pBoneWeight[index].b = vFinalBoneWeightTable[index].B.fBoneWeight;
						pBoneWeight[index].c = vFinalBoneWeightTable[index].C.fBoneWeight;
						pBoneWeight[index].d = vFinalBoneWeightTable[index].D.fBoneWeight;
						//i,
						//index);
						WriteFile(fh, &pBoneWeight[index], sizeof(BoneWeightTable), nullptr, nullptr);
						
				}
				printf("}; \n");
				pH->numChunks++;
				pH->totalSize += sizeof(ChunkHeader) + boneWeight->chunkSize;
				delete boneWeight;



				printf("\n");
				printf("\n");
				assert(totalNumVerts == vFinalBoneWeightTable.size());

				BoneIndexTable pBoneIndex[1605];
				ChunkHeader* boneIndex = new ChunkHeader();
				boneIndex->type = CType::BONE_INDEX;
				boneIndex->chunkSize = sizeof(BoneIndexTable) * VBO_vert.size();
				WriteFile(fh, (char*)boneIndex, sizeof(ChunkHeader), nullptr, nullptr);
				printf("// III VBO Bone_Index KeenanX\n");
				printf("\n");
				printf("Bone_index BoneIndex[] =\n");
				printf("{ \n");
				for (int i = 0; i < (int)VBO_vert.size(); i++)
				{
					vTmp = VBO_vert[i];
					int index = vTmp.index;

					//printf("\t {%4d, %4d, %4d, %4d}, // [%d] index:%d \n",
						pBoneIndex[index].ia = vFinalBoneWeightTable[index].A.iBoneIndex;
						pBoneIndex[index].ib = vFinalBoneWeightTable[index].B.iBoneIndex;
						pBoneIndex[index].ic = vFinalBoneWeightTable[index].C.iBoneIndex;
						pBoneIndex[index].id = vFinalBoneWeightTable[index].D.iBoneIndex;
						WriteFile(fh, &pBoneIndex[index], sizeof(BoneIndexTable), nullptr, nullptr);
						
				}
				printf("}; \n");
				pH->numChunks++;
				pH->totalSize += sizeof(ChunkHeader) + boneIndex->chunkSize;
				delete boneIndex;

				//const unsigned int numBones = vFinalInvPoseTable.size();
				Mat pInverse[80];
				ChunkHeader* boneInverse = new ChunkHeader();
				boneInverse->type = CType::INVERSE_TYPE;
				boneInverse->chunkSize = sizeof(Mat) * vFinalInvPoseTable.size();
				WriteFile(fh, (char*)boneInverse, sizeof(ChunkHeader), nullptr, nullptr);
				printf("\n");
				printf("\n");
				printf("// JJJ Final InversePose KeenanX\n");
				printf("Mat InversePose[] =\n");
				printf("{ \n");
				for (size_t j = 0; j < vFinalInvPoseTable.size(); j++)
				{
					//printf("\t { %0ff, %0ff, %0ff, %0ff,   // [%d] \n",
						pInverse[j].m0 = vFinalInvPoseTable[j].m.m0;
						pInverse[j].m1 = vFinalInvPoseTable[j].m.m1;
						pInverse[j].m2 = vFinalInvPoseTable[j].m.m2;
						pInverse[j].m3 = vFinalInvPoseTable[j].m.m3;

						pInverse[j].m4 = vFinalInvPoseTable[j].m.m4;
						pInverse[j].m5 = vFinalInvPoseTable[j].m.m5;
						pInverse[j].m6 = vFinalInvPoseTable[j].m.m6;
						pInverse[j].m7 = vFinalInvPoseTable[j].m.m7;
							
						pInverse[j].m8 = vFinalInvPoseTable[j].m.m8;
						pInverse[j].m9 = vFinalInvPoseTable[j].m.m9;
						pInverse[j].m10 = vFinalInvPoseTable[j].m.m10;
						pInverse[j].m11 = vFinalInvPoseTable[j].m.m11;
							
						pInverse[j].m12 = vFinalInvPoseTable[j].m.m12;
						pInverse[j].m13 = vFinalInvPoseTable[j].m.m13;
						pInverse[j].m14 = vFinalInvPoseTable[j].m.m14;
						pInverse[j].m15 =vFinalInvPoseTable[j].m.m15;
						WriteFile(fh, &pInverse[j], sizeof(Mat), nullptr, nullptr);

				}
				printf("};\n");
				printf("\n");
				pH->numChunks++;
				pH->totalSize += sizeof(ChunkHeader) + boneInverse->chunkSize;
				delete boneInverse;

				

				
				SetFilePointer(fh, 0, nullptr, FILE_BEGIN);
				WriteFile(fh, (char*)pH, sizeof(PackageHeader), nullptr, nullptr);
			
				
				delete pH;
				CloseHandle(fh);

    return 0;
}

void DisplayContent(FbxScene* pScene)
{
    int i;
    FbxNode* lNode = pScene->GetRootNode();

    if(lNode)
    {
        for(i = 0; i < lNode->GetChildCount(); i++)
        {
            DisplayContent(lNode->GetChild(i));
        }
    }
}

void DisplayContent(FbxNode* pNode)
{
    FbxNodeAttribute::EType lAttributeType;
    int i;

    if(pNode->GetNodeAttribute() == NULL)
    {
        FBXSDK_printf("NULL Node Attribute\n\n");
    }
    else
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
	    default:
	        break;
        case FbxNodeAttribute::eMarker:  
            DisplayMarker(pNode);
            break;

        case FbxNodeAttribute::eSkeleton:  
            DisplaySkeleton(pNode);
            break;

        case FbxNodeAttribute::eMesh:      
            DisplayMesh(pNode);
            break;

        case FbxNodeAttribute::eNurbs:      
            DisplayNurb(pNode);
            break;

        case FbxNodeAttribute::ePatch:     
            DisplayPatch(pNode);
            break;

        case FbxNodeAttribute::eCamera:    
            DisplayCamera(pNode);
            break;

        case FbxNodeAttribute::eLight:     
            DisplayLight(pNode);
            break;

        case FbxNodeAttribute::eLODGroup:
            DisplayLodGroup(pNode);
            break;
        }   
    }

    DisplayUserProperties(pNode);
    DisplayTarget(pNode);

	// Keenan(3.2.2) - Kill the pig
		//DisplayPivotsAndLimits(pNode);

    DisplayTransformPropagation(pNode);
    DisplayGeometricTransform(pNode);

    for(i = 0; i < pNode->GetChildCount(); i++)
    {
        DisplayContent(pNode->GetChild(i));
    }
}


void DisplayTarget(FbxNode* pNode)
{
    if(pNode->GetTarget() != NULL)
    {
        DisplayString("    Target Name: ", (char *) pNode->GetTarget()->GetName());
    }
}

void DisplayTransformPropagation(FbxNode* pNode)
{
    FBXSDK_printf("    Transformation Propagation\n");

    // 
    // Rotation Space
    //
    EFbxRotationOrder lRotationOrder;
    pNode->GetRotationOrder(FbxNode::eSourcePivot, lRotationOrder);

    FBXSDK_printf("        Rotation Space: ");

    switch (lRotationOrder)
    {
    case eEulerXYZ: 
        FBXSDK_printf("Euler XYZ\n");
        break;
    case eEulerXZY:
        FBXSDK_printf("Euler XZY\n");
        break;
    case eEulerYZX:
        FBXSDK_printf("Euler YZX\n");
        break;
    case eEulerYXZ:
        FBXSDK_printf("Euler YXZ\n");
        break;
    case eEulerZXY:
        FBXSDK_printf("Euler ZXY\n");
        break;
    case eEulerZYX:
        FBXSDK_printf("Euler ZYX\n");
        break;
    case eSphericXYZ:
        FBXSDK_printf("Spheric XYZ\n");
        break;
    }

    //
    // Use the Rotation space only for the limits
    // (keep using eEulerXYZ for the rest)
    //
    FBXSDK_printf("        Use the Rotation Space for Limit specification only: %s\n",
        pNode->GetUseRotationSpaceForLimitOnly(FbxNode::eSourcePivot) ? "Yes" : "No");


    //
    // Inherit Type
    //
    FbxTransform::EInheritType lInheritType;
    pNode->GetTransformationInheritType(lInheritType);

    FBXSDK_printf("        Transformation Inheritance: ");

    switch (lInheritType)
    {
    case FbxTransform::eInheritRrSs:
        FBXSDK_printf("RrSs\n");
        break;
    case FbxTransform::eInheritRSrs:
        FBXSDK_printf("RSrs\n");
        break;
    case FbxTransform::eInheritRrs:
        FBXSDK_printf("Rrs\n");
        break;
    }
}

void DisplayGeometricTransform(FbxNode* pNode)
{
    FbxVector4 lTmpVector;

    FBXSDK_printf("    Geometric Transformations\n");

    //
    // Translation
    //
    lTmpVector = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FBXSDK_printf("        Translation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

    //
    // Rotation
    //
    lTmpVector = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FBXSDK_printf("        Rotation:    %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

    //
    // Scaling
    //
    lTmpVector = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    FBXSDK_printf("        Scaling:     %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
}


void DisplayMetaData(FbxScene* pScene)
{
    FbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
    if (sceneInfo)
    {
        FBXSDK_printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
        FBXSDK_printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
        FBXSDK_printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
        FBXSDK_printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
        FBXSDK_printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
        FBXSDK_printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
        FBXSDK_printf("    Comment: %s\n", sceneInfo->mComment.Buffer());

        FbxThumbnail* thumbnail = sceneInfo->GetSceneThumbnail();
        if (thumbnail)
        {
            FBXSDK_printf("    Thumbnail:\n");

            switch (thumbnail->GetDataFormat())
            {
            case FbxThumbnail::eRGB_24:
                FBXSDK_printf("        Format: RGB\n");
                break;
            case FbxThumbnail::eRGBA_32:
                FBXSDK_printf("        Format: RGBA\n");
                break;
            }

            switch (thumbnail->GetSize())
            {
	        default:
	            break;
            case FbxThumbnail::eNotSet:
                FBXSDK_printf("        Size: no dimensions specified (%ld bytes)\n", thumbnail->GetSizeInBytes());
                break;
            case FbxThumbnail::e64x64:
                FBXSDK_printf("        Size: 64 x 64 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
                break;
            case FbxThumbnail::e128x128:
                FBXSDK_printf("        Size: 128 x 128 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
            }
        }
    }
}

