//-----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "eat.h"
#include "ChunkHeader.h"
#include "PackageHeader.h"
#include "File.h"
#include <PackageHeader.h>


//---------------------------------------------------------------------------
// Leave this signature - do your EAT magic here
// Feel free to add files and methods to this project
//---------------------------------------------------------------------------

bool eat(const char* const inFileName,
	ChunkType type,
	const char* const chunkName,
	unsigned char*& chunkBuff,
	unsigned int& chunkSize)
{
	AZUL_UNUSED_VAR(type);
	ChunkHeader	chunkHdr;
	static Azul::File::Handle fh;
	bool status = false;
	Azul::File::Open(fh, inFileName, Azul::File::Mode::READ);
	Azul::File::Seek(fh, Azul::File::Location::CURRENT, sizeof(PackageHeader));


	Azul::File::Read(fh, &chunkHdr, sizeof(ChunkHeader));
	//chunkBuff = new unsigned char[chunkHdr.chunkSize];
	while (status != true)
	{
		if (strcmp(chunkHdr.chunkName, chunkName) == 0 && chunkHdr.type == type)
		{

			chunkSize = chunkHdr.chunkSize;
			chunkBuff = new unsigned char[chunkHdr.chunkSize];
			Azul::File::Read(fh, chunkBuff, chunkSize);
			status = true;
			break;
		}
		else {
			status = false;
		}
		Azul::File::Seek(fh, Azul::File::Location::CURRENT, (int)chunkHdr.chunkSize);
		Azul::File::Read(fh, &chunkHdr, sizeof(ChunkHeader));
	}

	Azul::File::Close(fh);
	return true;



}

// End of File
