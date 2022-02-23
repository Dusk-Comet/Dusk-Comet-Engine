// RPG Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <DuskComet/Game.hpp>

#include "DuskComet/System/Event.hpp"

void gameWindow_OnFocusGained(dc::EventArgs e)
{

}

void gameWindow_OnFocusLost(dc::EventArgs e)
{

}

int main()
{

	dc::Game::instance().initialize();

	dc::EventArgs temp;



	if (!dc::Game::instance().getInitializeResult())
	{
		return -1;
	}

	sf::Texture::getMaximumSize();

	dc::Game::instance().gameWindow().onFocusGained += gameWindow_OnFocusGained;
	dc::Game::instance().gameWindow().onFocusLost += gameWindow_OnFocusLost;

	dc::Game::instance().gameWindow().initialize();

	dc::Game::instance().gameWindow().createGameWindow("GameWindow", dc::Size(424, 240), true, false, true);

	dc::Game::instance().gameWindow().setWindowSize(dc::Size(424 * 2, 240 * 2));
	dc::Game::instance().gameWindow().run();


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
