#ifndef GAME
#define GAME
#include "GameWorld.h"

class Game
{
private:
	bool topsTurn;
	int topScore, bottomScore;
	GameWorld m_gameWorld;
	
	//helper functions
	void clearScreen();
	void display();
public:
	//mutators
	Game(bool friendlyFire = false, bool overflow = false, bool allowSplit = true);
	void play();
};

#endif