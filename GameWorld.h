#ifndef GAMEWORLD
#define GAMEWORLD
#include "Hand.h"

class Game;

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
	Game* m_game;

	//helper mutators
	//void clean(); //makes sure Hand digits follow rules
public:
	//accessors
	Hand* tLeft() const;
	Hand* tRight() const;
	Hand* bLeft() const;
	Hand* bRight() const;
	bool FFOn() const;
	bool OFOn() const;
	bool PSOn() const;
	//mutators
	GameWorld(Game* game, bool friendlyFire = false, bool overflow = false, bool allowSplit = true);
	void attack(Hand *from, Hand *to); //calls clean
	bool split(int amtL2R); //pass in the # of digits to be transferred from left hand to right hand (can be negative)
	~GameWorld();
	
};
inline bool GameWorld::FFOn() const { return friendlyFireEnabled; }
inline bool GameWorld::OFOn() const { return overflowEnabled; }
inline bool GameWorld::PSOn() const { return allowPointSplits; }

#endif