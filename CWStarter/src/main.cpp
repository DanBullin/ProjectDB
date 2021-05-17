/*!
\file main.cpp
\brief Contains the entry point for the application
*/

/*! \mainpage ProjectDB - IMAT2906 Coursework
*
* This is the doxygen report from my IMAT2906 Coursework of a 2D Platformer\n
* By Dan Bullin
*/

#include "Game.h" 

int main() /** Entry point for the application */
{
	// Create new game
	// Start update loop
	Game game;
	game.update();
	return 0;
}