#include "Game.hpp"

namespace Green
{
	GameVariables::GameVariables()
	{
		//auto wndStr = skCrypt("TankWindowClass");
		auto wndStr = skCrypt("PokerStars Lobby");
		m_GameWindow = FindWindowA(NULL, wndStr);
		wndStr.clear();
	}

	GameFunctions::GameFunctions()
	{
	}
}