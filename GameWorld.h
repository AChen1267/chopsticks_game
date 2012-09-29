#ifndef GAMEWORLD
#define GAMEWORLD
#include "Hand.h"

class GameWorld
{
private:
	Hand *topsLeft, *topsRight, *bottomsLeft, *bottomsRight; //to be consistent with app code; no player class but uses private int m_player
																//tL tR
																//bL bR only matters for display
	bool topLeftsDead, topRightsDead, bottomLeftsDead, bottomRightsDead;
	bool friendlyFireEnabled;
	bool overflowEnabled;
	bool allowPointSplits;

	//helper mutators
	void clean(); //makes sure Hand digits follow rules
public:
	//accessors
	Hand* tLeft() const;
	Hand* tRight() const;
	Hand* bLeft() const;
	Hand* bRight() const;
	//mutators
	GameWorld(bool friendlyFire = false, bool overflow = false, bool allowSplit = true);
	void attack(Hand *from, Hand *to); //calls clean
	void split(int leftNum);
	~GameWorld();
	
};

#endif