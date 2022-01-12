//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "WaveThread.h"
#include "WaveMan.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

WaveMan::WaveMan()
	: wfx{ 0 },
	hWaveOut(nullptr)
{
	wfx.nSamplesPerSec = 22050; // sample rate 
	wfx.wBitsPerSample = 16;    // number of bits per sample of mono data 
	wfx.nChannels = 2;          // number of channels (i.e. mono, stereo...) 
	wfx.wFormatTag = WAVE_FORMAT_PCM;								// format type 
	wfx.nBlockAlign = (DWORD)((wfx.wBitsPerSample >> 3) * wfx.nChannels);	// block size of data 
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;		// for buffer estimation 
	wfx.cbSize = 0;

	UserWavePlayer wavePlayer;

	MMRESULT result;   // for waveOut return values 

	result = waveOutOpen(	&hWaveOut, 
							WAVE_MAPPER, 
							&wfx, 
							(DWORD_PTR)waveOutProc, 
							(DWORD_PTR)&wavePlayer, 
							CALLBACK_FUNCTION);

	if (result != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "unable to open WAVE_MAPPER device\n");
		ExitProcess(1);
	}
}

WaveMan::~WaveMan()
{
	assert(hWaveOut);
	waveOutClose(hWaveOut);
}

void CALLBACK WaveMan::waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	AZUL_UNUSED_VAR(hWaveOut);
	AZUL_UNUSED_VAR(dwParam2);

	UserWavePlayer *pWavePlayer = (UserWavePlayer *)dwInstance;
	WAVEHDR *waveHdr = nullptr;

	switch (uMsg)
	{
	case WOM_DONE:
		// with this case, dwParam1 is the wavehdr
		waveHdr = (WAVEHDR *)dwParam1;
		pWavePlayer->numWaves--;

		if (pWavePlayer->numWaves == 0)
		{
			pWavePlayer->donePlaying = true;
		}

		Trace::out("WOM_DONE: %s remain:%d \n", waveHdr->dwUser, pWavePlayer->numWaves);
		break;

	case WOM_CLOSE:
		pWavePlayer->closed = true;
		Trace::out("WOM_CLOSE:\n");
		break;

	case WOM_OPEN:
		Trace::out("WOM_OPEN:\n");
		break;

	default:
		assert(false);
	}

}

HWAVEOUT WaveMan::GetHandle()
{
	return hWaveOut;
}


// -- End of File --

