//-----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 


#ifndef CHUNK_HEADER_H
#define CHUNK_HEADER_H

enum class CType : unsigned int
{
	VERTS_TYPE = 0xA0000000u,
	TRI_TYPE,
	BONE_TYPE,
	BONE_INDEX,
	INVERSE_TYPE

};


struct ChunkHeader
{
	static const unsigned int CHUNK_NAME_SIZE = 20;

	// data:
	CType      type;
	char           chunkName[CHUNK_NAME_SIZE];
	unsigned int   chunkSize;
	unsigned int   hashNum;
};

#endif