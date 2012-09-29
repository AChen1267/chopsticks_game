#include "GameWorld.h"
#include "Hand.h"
#include "extras.h"
#include <cstdlib>
using namespace std;

GameWorld::GameWorld(bool friendlyFire, bool overflow, bool allowSplit)
{	
	topsLeft = new Hand(this,TOP);
	topsRight = new Hand(this,TOP);
	bottomsLeft = new Hand(this,BOT);
	bottomsRight = new Hand(this,BOT);
	topLeftsDead = topRightsDead = bottomLeftsDead = bottomRightsDead = false;
	friendlyFireEnabled = friendlyFire;
	overflowEnabled = overflow;
	allowPointSplits = allowSplit;
}
Hand* GameWorld::tLeft() const { return topsLeft; }
Hand* GameWorld::tRight() const { return topsRight; }
Hand* GameWorld::bLeft() const { return bottomsLeft; }
Hand* GameWorld::bRight() const { return bottomsRight; }
void GameWorld::attack(Hand* from, Hand* to)
{
	to->addDigits(from->numDigits());
	if (to->numDigits() >= 5)
		if (overflowEnabled)
			to->addDigits(-5);
		else
		{
			to->setDead(true);
			return;
		}
	if (to->numDigits() == 0)
		to->setDead(true);
	return;
}
void GameWorld::split(int leftNum)
{
	return;
}
GameWorld::~GameWorld()
{
	delete topsLeft, topsRight, bottomsLeft, bottomsRight;
}