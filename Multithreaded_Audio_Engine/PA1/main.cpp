//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "A.h"
#include "FileSlow.h"
#include "conio.h"
#include "FileThread.h"
#include "KillThread.h"
#include "ThreadCount.h"
#include "CoordinatorThread.h"
#include "SharedCV.h"
#include "WaveMan.h"
#include "WaveThread.h"
#include "Playback.h"
using namespace ThreadFramework;
using namespace std::chrono_literals;
int main()
{
	START_BANNER_MAIN("--Main--");

	// ----------------------------------------------------------------
	// setup objects
	//-----------------------------------------------------------------

	// ThreadCounter
	std::condition_variable  cv_ThreadCount;
	ThreadCount::SetCV(&cv_ThreadCount);

	// Signal Main->Kill Thread to start killing threads
	std::condition_variable  cv_KeyPress;

	// Signal Kill->All threads to self exit.. needs to be shared
	std::promise<void>	prom_Kill;
	std::shared_future<void> fut_Kill = prom_Kill.get_future();


	// Signal Kill->Main Thread all threads have ended, safe to leave main 
	std::promise<void>	prom_EndMain;
	std::future<void>	fut_EndMain = prom_EndMain.get_future();

	// Signal File-->Coordinator Thread signal when done loading 
	SharedCV  FileDataReady;

	// Initialize WaveMan
	WaveMan waveMan;


	KillThread  t_Kill("-Kill-", prom_Kill, prom_EndMain, &cv_KeyPress, &cv_ThreadCount);
	t_Kill.Launch();

	FileThread  t_File("-File-", fut_Kill, FileDataReady);
	t_File.Launch();

	CoordinatorThread t_Coordinator("-Coord-", fut_Kill, FileDataReady, t_File);
	t_Coordinator.Launch();
	
	

	
	WaveThread t_waveA("-WaveA-", fut_Kill, waveMan);
	WaveThread t_waveB("-WaveB-", fut_Kill, waveMan);
	WaveThread t_waveC("-WaveC-", fut_Kill, waveMan);
	WaveThread t_waveD("-WaveD-", fut_Kill, waveMan);
	WaveThread t_waveE("-WaveE-", fut_Kill, waveMan);
	WaveThread t_waveF("-WaveF-", fut_Kill, waveMan);
	WaveThread t_waveG("-WaveG-", fut_Kill, waveMan);
	WaveThread t_waveH("-WaveH-", fut_Kill, waveMan);
	WaveThread t_waveI("-WaveI-", fut_Kill, waveMan);
	WaveThread t_waveJ("-WaveJ-", fut_Kill, waveMan);
	WaveThread t_waveK("-WaveK-", fut_Kill, waveMan);
	WaveThread t_waveL("-WaveL-", fut_Kill, waveMan);
	WaveThread t_waveM("-WaveM-", fut_Kill, waveMan);
	WaveThread t_waveN("-WaveN-", fut_Kill, waveMan);
	WaveThread t_waveO("-WaveO-", fut_Kill, waveMan);
	WaveThread t_waveP("-WaveP-", fut_Kill, waveMan);
	WaveThread t_waveQ("-WaveQ-", fut_Kill, waveMan);
	WaveThread t_waveR("-WaveR-", fut_Kill, waveMan);
	WaveThread t_waveS("-WaveS-", fut_Kill, waveMan);
	WaveThread t_waveT("-WaveT-", fut_Kill, waveMan);
	WaveThread t_waveU("-WaveU-", fut_Kill, waveMan);
	WaveThread t_waveV("-WaveV-", fut_Kill, waveMan);
	WaveThread t_waveW("-WaveW-", fut_Kill, waveMan);

	Playback play("-Playback-", fut_Kill, t_Coordinator,t_waveA,t_waveB,t_waveC,t_waveD,t_waveE,t_waveF, t_waveG, t_waveH, t_waveI, t_waveJ, t_waveK, t_waveL, t_waveM, t_waveN, t_waveO, t_waveP, t_waveQ, t_waveR, t_waveS, t_waveT, t_waveU, t_waveV, t_waveW);
	play.Launch();
	
	
	
	AZUL_UNUSED_VAR(_getch());
	std::this_thread::sleep_for(5s);
	cv_KeyPress.notify_one();   // notify the kill thread

	// Do not leave main until kills are done
	fut_EndMain.get();

}

// --- End of File ---
