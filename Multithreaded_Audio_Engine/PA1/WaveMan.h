//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef WAVE_MAN_H
#define WAVE_MAN_H

#include "Buff.h"

using namespace ThreadFramework;

class WaveMan
{
public:
	struct UserWavePlayer
	{
		UserWavePlayer()
		{
			this->donePlaying = false;
			this->closed = false;
			this->numWaves = 4;
		}

		bool donePlaying;
		bool closed;
		int  numWaves;
	};

public:
	//WaveMan() = delete;
	WaveMan(const WaveMan &) = delete;
	WaveMan &operator = (const WaveMan &) = delete;
	~WaveMan();

	WaveMan();


	static void CALLBACK waveOutProc(HWAVEOUT hWaveOut,
		UINT uMsg,
		DWORD dwInstance,
		DWORD dwParam1,
		DWORD dwParam2);

	HWAVEOUT GetHandle();

private:
	WAVEFORMATEX   wfx;
	HWAVEOUT       hWaveOut;

};

#endif

// -- End of File --
