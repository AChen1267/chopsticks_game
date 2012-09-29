#include "Hand.h"
#include "GameWorld.h"
#include <cstdlib>
using namespace std;

Hand::Hand(GameWorld *world, int player)
{
	m_isDead = false;
	m_digits = 1;
	m_myTurn = false;
	m_player = player;
	m_world = world;
}
void Hand::setDead(bool isDead)
{
	m_isDead = isDead;
	m_digits = 0;
}
void Hand::addDigits(int increment)
{
	m_digits += increment;
}