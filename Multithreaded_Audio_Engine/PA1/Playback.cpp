//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "ThreadCountProxy.h"
#include "Playback.h"
#include "PlayCmd.h"
#include "SendDataCmd.h"
using namespace ThreadFramework;
using namespace std::chrono_literals;

Playback::~Playback()
{
	if (mThread.joinable())
	{
		mThread.join();
	}
}

Playback::Playback(const char* const pName, std::shared_future<void>& fut_Kill, CoordinatorThread& Coord, WaveThread& Waat, WaveThread& Wat, WaveThread&wt3, WaveThread& wt4, WaveThread& wt5, WaveThread& wt6,WaveThread& wt7, WaveThread& wt8, WaveThread& wt9, WaveThread& wt10, WaveThread& wt11, WaveThread& wt12, WaveThread& wt13, WaveThread& wt14, WaveThread& wt15, WaveThread& wt16, WaveThread& wt17, WaveThread& wt18, WaveThread& wt19, WaveThread& wt20, WaveThread& wt21, WaveThread& wt22, WaveThread& wt23)
	:BannerBase(pName),
	mThread(),
	mFutureKill(fut_Kill),
	ct(Coord),
	Wt(Waat),
	Wt2(Wat),
	Wt3(wt3),
	Wt4(wt4),
	Wt5(wt5),
	Wt6(wt6),
	Wt7(wt7),
	Wt8(wt8),
	Wt9(wt9),
	Wt10(wt10),
	Wt11(wt11),
	Wt12(wt12),
	Wt13(wt13),
	Wt14(wt14),
	Wt15(wt15),
	Wt16(wt16),
	Wt17(wt17),
	Wt18(wt18),
	Wt19(wt19),
	Wt20(wt20),
	Wt21(wt21),
	Wt22(wt22),
	Wt23(wt23),
	
	mStatus(status::Empty),
	mtx()
{
}

void Playback::Launch()
{
	// make sure the thread wasn't started
	if (mThread.joinable() == false)
	{
		mThread = std::thread(std::ref(*this));
	}
	else
	{
		// Lock up
		assert(false);
	}
}

void Playback::operator()()
{
	START_BANNER_DERIVED

	KILL_THREAD_ENABLE

	
	CircularData* pQueueToMain = new CircularData();
	while (!mFutureKill._Is_ready())
	{
		
		PlayCmd* pPrintCmd1=nullptr;
		PlayCmd* pPrintCmd = nullptr;
		PlayCmd* pPrintCmd2 = nullptr;
		PlayCmd* pPrintCmd3 = nullptr;
		PlayCmd* pPrintCmd4 = nullptr;
		PlayCmd* pPrintCmd5 = nullptr;
		PlayCmd* pPrintCmd6 = nullptr;
		PlayCmd* pPrintCmd7 = nullptr;
		PlayCmd* pPrintCmd8 = nullptr;
		PlayCmd* pPrintCmd9 = nullptr;
		PlayCmd* pPrintCmd10 = nullptr;
		PlayCmd* pPrintCmd11 = nullptr;
		PlayCmd* pPrintCmd12 = nullptr;
		PlayCmd* pPrintCmd13 = nullptr;
		PlayCmd* pPrintCmd16 = nullptr;
		PlayCmd* pPrintCmd17 = nullptr;
		PlayCmd* pPrintCmd14 = nullptr;
		PlayCmd* pPrintCmd15 = nullptr;
		PlayCmd* pPrintCmd18 = nullptr;
		PlayCmd* pPrintCmd19 = nullptr;
		PlayCmd* pPrintCmd20 = nullptr;
		PlayCmd* pPrintCmd21 = nullptr;
		PlayCmd* pPrintCmd22 = nullptr;
		
		
		Command* pCmd = nullptr;
		
		

		if (mStatus == status::Empty)
		{
			
			//Debug::out("File: Playback loading\n");
			
			Buff* pBuff = ct.getbuff();
			
			if(pBuff!=nullptr)
			{ 
				if (Wt22.wdflag == true && Wt23.wdflag == false)
				{
					Wt23.Launch();
					pPrintCmd22 = new PlayCmd(Wt23, pBuff);

					pQueueToMain->PushBack(pPrintCmd22);
					Wt23.wdflag = true;
					
				}
				if (Wt21.wdflag == true && Wt22.wdflag == false)
				{
					//PlayCmd* pPrintCmd7 = nullptr;
					Wt22.Launch();
					pPrintCmd21 = new PlayCmd(Wt22, pBuff);

					pQueueToMain->PushBack(pPrintCmd21);
					Wt22.wdflag = true;
					//delete pPrintCmd7;
					ct.Fill();
				}
				if (Wt20.wdflag == true && Wt21.wdflag == false)
				{
					//PlayCmd* pPrintCmd7 = nullptr;
					Wt21.Launch();
					pPrintCmd20 = new PlayCmd(Wt21, pBuff);

					pQueueToMain->PushBack(pPrintCmd20);
					Wt21.wdflag = true;
					//delete pPrintCmd7;
					ct.End();
				}
				if (Wt19.wdflag == true && Wt20.wdflag == false)
				{
					//PlayCmd* pPrintCmd7 = nullptr;
					Wt20.Launch();
					pPrintCmd19 = new PlayCmd(Wt20, pBuff);

					pQueueToMain->PushBack(pPrintCmd19);
					Wt20.wdflag = true;
					//delete pPrintCmd7;
					ct.End();
				}
				if (Wt18.wdflag == true && Wt19.wdflag == false)
				{
					//PlayCmd* pPrintCmd6 = nullptr;
					Wt19.Launch();
					pPrintCmd18 = new PlayCmd(Wt19, pBuff);

					pQueueToMain->PushBack(pPrintCmd18);
					Wt19.wdflag = true;
					//delete pPrintCmd6;
					ct.End();
				}
				if (Wt17.wdflag == true && Wt18.wdflag == false)
				{
					Wt18.Launch();
					pPrintCmd17 = new PlayCmd(Wt18, pBuff);

					pQueueToMain->PushBack(pPrintCmd17);
					Wt18.wdflag = true;
					ct.End();
				}
				if (Wt16.wdflag == true && Wt17.wdflag == false)
				{
					Wt17.Launch();
					pPrintCmd16 = new PlayCmd(Wt17, pBuff);

					pQueueToMain->PushBack(pPrintCmd16);
					Wt17.wdflag = true;
					ct.End();
				}
				if (Wt15.wdflag == true && Wt16.wdflag == false)
				{
					Wt16.Launch();
					pPrintCmd15 = new PlayCmd(Wt16, pBuff);

					pQueueToMain->PushBack(pPrintCmd15);
					Wt16.wdflag = true;
					ct.End();
				}
				if (Wt14.wdflag == true && Wt15.wdflag == false)
				{
					//PlayCmd* pPrintCmd7 = nullptr;
					Wt15.Launch();
					pPrintCmd14 = new PlayCmd(Wt15, pBuff);

					pQueueToMain->PushBack(pPrintCmd14);
					Wt15.wdflag = true;
					//delete pPrintCmd7;
					ct.End();
				}
				if (Wt13.wdflag == true && Wt14.wdflag == false)
				{
					//PlayCmd* pPrintCmd6 = nullptr;
					Wt14.Launch();
					pPrintCmd13 = new PlayCmd(Wt14, pBuff);

					pQueueToMain->PushBack(pPrintCmd13);
					Wt14.wdflag = true;
					//delete pPrintCmd6;
					ct.End();
				}
				if (Wt12.wdflag == true && Wt13.wdflag == false)
				{
					Wt13.Launch();
					pPrintCmd12 = new PlayCmd(Wt13, pBuff);

					pQueueToMain->PushBack(pPrintCmd12);
					Wt13.wdflag = true;
					ct.End();
				}
				if (Wt11.wdflag == true && Wt12.wdflag == false)
				{
					Wt12.Launch();
					pPrintCmd11 = new PlayCmd(Wt12, pBuff);

					pQueueToMain->PushBack(pPrintCmd11);
					Wt12.wdflag = true;
					ct.End();
				}
				if (Wt10.wdflag == true && Wt11.wdflag == false)
				{
					Wt11.Launch();
					pPrintCmd10 = new PlayCmd(Wt11, pBuff);

					pQueueToMain->PushBack(pPrintCmd10);
					Wt11.wdflag = true;
					ct.End();
				}
				if (Wt9.wdflag == true && Wt10.wdflag == false)
				{
					Wt10.Launch();
					pPrintCmd9 = new PlayCmd(Wt10, pBuff);

					pQueueToMain->PushBack(pPrintCmd9);
					Wt10.wdflag = true;
					ct.End();
				}

				if (Wt8.wdflag == true && Wt9.wdflag == false)
				{
					Wt9.Launch();
					pPrintCmd8 = new PlayCmd(Wt9, pBuff);

					pQueueToMain->PushBack(pPrintCmd8);
					Wt9.wdflag = true;
					ct.End();
				}
				if (Wt7.wdflag == true && Wt8.wdflag == false)
				{
					//PlayCmd* pPrintCmd7 = nullptr;
					Wt8.Launch();
					pPrintCmd7 = new PlayCmd(Wt8, pBuff);

					pQueueToMain->PushBack(pPrintCmd7);
					Wt8.wdflag = true;
					//delete pPrintCmd7;
					ct.End();
				}
				if (Wt6.wdflag == true && Wt7.wdflag == false)
				{
					//PlayCmd* pPrintCmd6 = nullptr;
					Wt7.Launch();
					pPrintCmd6 = new PlayCmd(Wt7, pBuff);

					pQueueToMain->PushBack(pPrintCmd6);
					Wt7.wdflag = true;
					//delete pPrintCmd6;
					ct.End();
				}
				if (Wt5.wdflag == true && Wt6.wdflag == false)
				{
					Wt6.Launch();
					pPrintCmd5 = new PlayCmd(Wt6, pBuff);

					pQueueToMain->PushBack(pPrintCmd5);
					Wt6.wdflag = true;
					ct.End();
				}
				if (Wt4.wdflag == true && Wt5.wdflag == false)
				{
					Wt5.Launch();
					pPrintCmd4 = new PlayCmd(Wt5, pBuff);

					pQueueToMain->PushBack(pPrintCmd4);
					Wt5.wdflag = true;
					ct.End();
				}
				if (Wt3.wdflag == true && Wt4.wdflag == false)
				{
					Wt4.Launch();
					pPrintCmd3 = new PlayCmd(Wt4, pBuff);

					pQueueToMain->PushBack(pPrintCmd3);
					Wt4.wdflag = true;
					ct.End();
				}
				if (Wt2.wdflag == true && Wt3.wdflag == false)
				{
					Wt3.Launch();
					pPrintCmd2 = new PlayCmd(Wt3, pBuff);

					pQueueToMain->PushBack(pPrintCmd2);
					Wt3.wdflag = true;
					ct.End();
				}
				
				if (Wt.wdflag == true && Wt2.wdflag == false)
				{
					Wt2.Launch();
					pPrintCmd1 = new PlayCmd(Wt2, pBuff);

					pQueueToMain->PushBack(pPrintCmd1);
					Wt2.wdflag = true;
					ct.End();
				}
				if (Wt.wdflag == false)
				{
					Wt.Launch();
					pPrintCmd = new PlayCmd(Wt, pBuff);

					pQueueToMain->PushBack(pPrintCmd);
					Wt.wdflag = true;
					Debug::out("--- not ---\n");
					ct.End();
				}
					
			}


			while (pQueueToMain->PopFront(pCmd))
			{
				pCmd->Execute();
			}
			mStatus = status::Empty;
			
		}
		delete pPrintCmd6;
		delete pPrintCmd7;
		delete pPrintCmd5;
		delete pPrintCmd2;
		delete pPrintCmd4;
		delete pPrintCmd3;
		delete pPrintCmd;
		delete pPrintCmd1;
		delete pPrintCmd8;
		delete pPrintCmd9;
		delete pPrintCmd10;
		delete pPrintCmd11;
		delete pPrintCmd12;
		delete pPrintCmd13;
		delete pPrintCmd14;
		delete pPrintCmd15;
		delete pPrintCmd16;
		delete pPrintCmd17;
		delete pPrintCmd18;
		delete pPrintCmd19;	
		delete pPrintCmd20;
		delete pPrintCmd21;
		delete pPrintCmd22;
		// sleep that is interruptable
		//Debug::out("--- nothing %d ---\n", i++);
		mFutureKill.wait_for(500ms);
	}
	
	delete pQueueToMain;
}
