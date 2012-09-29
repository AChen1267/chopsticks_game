#ifndef HAND
#define HAND

class GameWorld;

class Hand
{
private:
	bool m_isDead;
	int m_digits;
	bool m_myTurn;
	int m_player; //TOP or BOTTOM
	GameWorld* m_world;
public:
	//accessors
	bool isDead() const;
	int numDigits() const;
	bool myTurn() const;
	int player() const;

	//mutators
	Hand(GameWorld *world, int player);
	void setDead(bool isDead);
	void addDigits(int increment);
};

inline bool Hand::isDead() const { return m_isDead; }
inline int Hand::numDigits() const { return m_digits; }
inline bool Hand::myTurn() const {return m_myTurn; }
inline int Hand::player() const {return m_player; }

#endif
