//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class Game: public Engine
{
public:
	// constructor
	Game() noexcept;
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator = (const Game&) = delete;
	Game& operator = (Game&&) = delete;
	~Game() = default;


	// Methods Users need to overloade in their game
    void Initialize() override;
    void LoadContent() override;
	void Update() override;
    void Draw() override;
    void UnLoadContent() override;

	void QuitCheck();
	void ProcessInQueue();

private:	
	// legacy
	Game( const char* windowName, const int Width,const int Height);


};

#endif

// End of File 
 