#include "GameWorld.h"
#include "Game.h"
#include "Hand.h"
#include "extras.h"
#include <cstdlib>
using namespace std;

GameWorld::GameWorld(Game* game, bool friendlyFire, bool overflow, bool allowSplit)
{	
	topsLeft = new Hand(this,TOP);
	topsRight = new Hand(this,TOP);
	bottomsLeft = new Hand(this,BOT);
	bottomsRight = new Hand(this,BOT);
	topLeftsDead = topRightsDead = bottomLeftsDead = bottomRightsDead = false;
	friendlyFireEnabled = friendlyFire;
	overflowEnabled = overflow;
	allowPointSplits = allowSplit;
	m_game = game;
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
bool GameWorld::split(int amtL2R)
{
	if (m_game->isTopsTurn())
	{
		int right = topsRight->numDigits();
		int newLeft = topsLeft->numDigits() - amtL2R;
		int newRight = right + amtL2R;

		if (newLeft < 1 || newLeft > 4 || newLeft == right || amtL2R == 0 || newRight < 1 || newRight > 4)
			return false;
		else
		{
			topsLeft->addDigits(-amtL2R);
			topsRight->addDigits(amtL2R);
			if (topsLeft->isDead()) topsLeft->setDead(false);
			if (topsRight->isDead()) topsRight->setDead(false);
		}
	}
	else
	{
		int right = bottomsRight->numDigits();
		int newLeft = bottomsLeft->numDigits() - amtL2R;
		int newRight = right + amtL2R;

		if (newLeft < 1 || newLeft > 4 || newLeft == right || amtL2R == 0 || newRight < 1 || newRight > 4)
			return false;
		else
		{
			bottomsLeft->addDigits(-amtL2R);
			bottomsRight->addDigits(amtL2R);
			if (bottomsLeft->isDead()) bottomsLeft->setDead(false);
			if (bottomsRight->isDead()) bottomsRight->setDead(false);
		}
	}
	return true;
}
GameWorld::~GameWorld()
{
	delete topsLeft, topsRight, bottomsLeft, bottomsRight;
}