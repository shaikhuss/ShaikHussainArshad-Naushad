//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_ID_H
#define SND_ID_H

enum class SndID
{
	Fiddle = 101,
	Bassoon = 102,
	Oboe = 103,
	SongA = 104,
	SongB = 105,
	Calliope = 106,
	Intro = 201,
	A = 202,
	AtoB = 203,
	B = 204,
	BtoC = 205,
	C = 206,
	CtoA = 207,
	End = 208,
	Coma = 301,
	Beethoven = 503,
	Electro = 501,
	Alarm = 502,
	Dial = 401,
	MoonPatrol = 402,
	Sequence = 403,
	Donkey = 404,

	Quit,
	Uninitialized = 0x7FFF0000
};

#endif

// --- End of File ---
