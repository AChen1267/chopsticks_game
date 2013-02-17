#ifndef GAME
#define GAME

class GameWorld;

class Game
{
private:
	bool topsTurn;
	bool aiOn;
	int topScore, bottomScore;
	GameWorld* m_gameWorld;
	void AI();
	//helper functions
	void clearScreen();
	void display();
public:
	//accessors
	bool isTopsTurn() const;
	//mutators
	Game(bool friendlyFire = false, bool overflow = false, bool allowSplit = true, bool ai = false);
	void play();
};

inline bool Game::isTopsTurn() const { return topsTurn; }
#endif