//-----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef C_HEADER_H
#define C_HEADER_H

enum class CType : uint32_t
{
	VERTS_TYPE = 0xA0000000u,
	TRI_TYPE,
	BONE_TYPE,
	BONE_INDEX,
	INVERSE_TYPE
};

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

struct CHeader
{
	static const unsigned int CHUNK_NAME_SIZE = 20;

	// data:
	CType      type;
	char           chunkName[CHUNK_NAME_SIZE];
	unsigned int   chunkSize;
	unsigned int   hashNum;
};

#endif