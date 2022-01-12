//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "GameMan.h"
#include "Keyboard.h"

namespace Azul
{
	// Use this to read keyboard
	bool Keyboard::GetKeyState(Keyboard::Key key)
	{
		bool value;

		Game *pGame = GameMan::GetGame();
		if (pGame->GetKey(key) == GLFW_PRESS)
		{
			value = true;
		}
		else
		{
			value = false;
		}

		return value;
	}
}

// --- End of File ---
