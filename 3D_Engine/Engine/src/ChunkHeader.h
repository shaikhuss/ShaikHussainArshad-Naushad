//-----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef CHUNK_HEADER_H
#define CHUNK_HEADER_H

enum class ChunkType : uint32_t
{
	HIER_TYPE = 0xA0000000u,
	NORMS_TYPE,
	BONE_TYPE,
	ANIM_TYPE





};
struct hierData
{
	int index;
	int parentIndex;
	char name[50];
};

struct animData
{
	int frameCount;
	int boneCount;
	char name[20];

};


struct boneData
{
	float tx;
	float ty;
	float tz;
	float qx;
	float qy;
	float qz;
	float qw;
	float sx;
	float sy;
	float sz;

};
struct ChunkHeader
{
	static const unsigned int CHUNK_NAME_SIZE = 20;

	// data:
	ChunkType      type;
	char           chunkName[CHUNK_NAME_SIZE];
	unsigned int   chunkSize;
	unsigned int   hashNum;
};

#endif