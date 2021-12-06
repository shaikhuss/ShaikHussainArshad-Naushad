//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO2_0_H
#define DEMO2_0_H

#include "Command.h"
#include "SndMan.h"
#include "VoiceCallback.h"

class Demo2_0 : public Command
{
public:
	Demo2_0() = default;
	~Demo2_0() = default;
	Demo2_0(const Demo2_0&) = delete;
	Demo2_0& operator = (const Demo2_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo2 part: 0s \n");

		// Play A

		Snd* pSndA = nullptr;
		
		pSndA = SndMan::Add(SndID::Intro);
		assert(pSndA);
		
		//pCallback_A->SetASnd(pSndA);
		
		// Vol & Pan
		assert(pSndA->Vol(0.8f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		
		//Snd* pSndB = nullptr;
		//VoiceCallback* pCallback_B = new VoiceCallback();

		Snd* pSndB = SndMan::Add(SndID::A);
		assert(pSndB);



		// Vol & Pan
		assert(pSndB->Vol(0.80f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(1.0f) == Handle::Status::SUCCESS);

		

		Snd* pSndC = SndMan::Add(SndID::AtoB);
		assert(pSndC);



		// Vol & Pan
		assert(pSndC->Vol(0.80f) == Handle::Status::SUCCESS);
		assert(pSndC->Pan(-1.0f) == Handle::Status::SUCCESS);


		Snd* pSndD = SndMan::Add(SndID::B);
		assert(pSndD);



		// Vol & Pan
		assert(pSndD->Vol(0.50f) == Handle::Status::SUCCESS);
		assert(pSndD->Pan(1.0f) == Handle::Status::SUCCESS);

		

		Snd* pSndE = SndMan::Add(SndID::BtoC);
		assert(pSndE);



		// Vol & Pan
		assert(pSndE->Vol(0.50f) == Handle::Status::SUCCESS);
		assert(pSndE->Pan(1.0f) == Handle::Status::SUCCESS);

		

		Snd* pSndF = SndMan::Add(SndID::C);
		assert(pSndF);



		// Vol & Pan
		assert(pSndF->Vol(0.50f) == Handle::Status::SUCCESS);
		assert(pSndF->Pan(-1.0f) == Handle::Status::SUCCESS);

		Snd* pSndG = SndMan::Add(SndID::CtoA);
		assert(pSndG);



		// Vol & Pan
		assert(pSndG->Vol(0.50f) == Handle::Status::SUCCESS);
		assert(pSndG->Pan(1.0f) == Handle::Status::SUCCESS);


		//Snd* pSndH = SndMan::Add(SndID::End);
		//assert(pSndH);
		//
		//
		//
		//// Vol & Pan
		//assert(pSndH->Vol(0.50f) == Handle::Status::SUCCESS);
		//assert(pSndH->Pan(1.0f) == Handle::Status::SUCCESS);

	}
};
#endif