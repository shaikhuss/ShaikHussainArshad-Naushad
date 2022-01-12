//-----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef EAT2_H
#define EAT2_H

#include "CHeader.h"
#include <File.h>
#include <PackageHeader.h>

bool eat2(const char* const inName,
	CType type,
	const char* const chunkName,
	unsigned char*& chunkBuff,
	unsigned int& chunkSize)
{
	CHeader	chunkHdr;
	static Azul::File::Handle fh;
	bool status = false;
	Azul::File::Open(fh, inName, Azul::File::Mode::READ);
	Azul::File::Seek(fh, Azul::File::Location::CURRENT, sizeof(PackageHeader));
	//AZUL_UNUSED_VAR(type);

	Azul::File::Read(fh, &chunkHdr, sizeof(CHeader));
	//chunkBuff = new unsigned char[chunkHdr.chunkSize];
	while (status != true)
	{
		if ((strcmp(chunkHdr.chunkName, chunkName) == 0) && chunkHdr.type == type)
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
		Azul::File::Read(fh, &chunkHdr, sizeof(CHeader));
	}

	Azul::File::Close(fh);
	return true;


}

#endif

// End of File
