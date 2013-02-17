#include "Game.h"
#include "GameWorld.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Game::Game(bool friendlyFire, bool overflow, bool allowSplit, bool ai)
{
	topsTurn = true;
	topScore = bottomScore = 0;
	aiOn = ai;
	m_gameWorld = new GameWorld(this,friendlyFire,overflow,allowSplit);
}
void Game::display()
{
	cout << "Top: " << m_gameWorld->tLeft()->numDigits() << "  " << m_gameWorld->tRight()->numDigits() << endl;
	cout << "Bot: " << m_gameWorld->bLeft()->numDigits() << "  " << m_gameWorld->bRight()->numDigits() << endl;
}

#include <windows.h>

void Game::clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
							&dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

void Game::play()
{
	while ((!m_gameWorld->tLeft()->isDead() || !m_gameWorld->tRight()->isDead())
		&& (!m_gameWorld->bLeft()->isDead() || !m_gameWorld->bRight()->isDead()))
	{
		display();

		string option;
		bool tld = m_gameWorld->tLeft()->isDead();
		bool trd = m_gameWorld->tRight()->isDead();
		bool bld = m_gameWorld->bLeft()->isDead();
		bool brd = m_gameWorld->bRight()->isDead();
		bool tAlive = !(tld || trd); //both hands are alive
		bool bAlive = !(bld || brd);
		bool splitValid = false;

		if (topsTurn && !aiOn)
		{
			cout << "It is top's turn. ";
			if (m_gameWorld->PSOn())
			{
				cout << "Will you (A)ttack";
				//the condition below checks for nonsplitting configurations: equal digits per hand, (0,1) or (1,0), (1,2) or (2,1), and (3,4) or (4,3)
				if (m_gameWorld->tLeft()->numDigits() != m_gameWorld->tRight()->numDigits() &&
					!((m_gameWorld->tLeft()->numDigits() == 1 && m_gameWorld->tRight()->numDigits() == 0) ||
						(m_gameWorld->tLeft()->numDigits() == 0 && m_gameWorld->tRight()->numDigits() == 1)) &&
					!((m_gameWorld->tLeft()->numDigits() == 2 && m_gameWorld->tRight()->numDigits() == 1) ||
						(m_gameWorld->tLeft()->numDigits() == 1 && m_gameWorld->tRight()->numDigits() == 2)) &&
					!((m_gameWorld->tLeft()->numDigits() == 3 && m_gameWorld->tRight()->numDigits() == 4) ||
						(m_gameWorld->tLeft()->numDigits() == 4 && m_gameWorld->tRight()->numDigits() == 3)))
				{
					cout << " or (S)plit";
					splitValid = true;
				}
				cout << "?" << endl;
				getline(cin,option);
				while (option.compare("A") != 0 && ((splitValid && option.compare("S") != 0) || (!splitValid && option.compare("S") == 0)))
				{
					cout << "That is not a valid option. Will you (A)ttack";
					if (m_gameWorld->tLeft()->numDigits() != m_gameWorld->tRight()->numDigits())
						" or (S)plit";
					cout << "?" << endl;
					getline(cin,option);
				}
			}
			if (!option.compare("S"))
			{
				string LtoRamt;
				cout << "State the amount to be transferred from left to right. Negative indicates right to left. " << endl;
				getline(cin,LtoRamt);
				int amt = atoi(LtoRamt.c_str());
				while (amt == 0 || !m_gameWorld->split(amt))
				{
					cout << "Argument invalid. State the amount to be transferred from left to right. " << endl;
					getline(cin,LtoRamt);
					amt = atoi(LtoRamt.c_str());
				}
			}
			else
			{
				string useHand, targetHand;
				cout << "Will you attack with your: ";
				if (!tld)	cout << "(L)eft hand ";
				if (!trd)	cout << "(R)ight hand";
				cout << endl;
				getline(cin,useHand);
				while (useHand.compare("L") != 0 && useHand.compare("R") != 0 
					|| (useHand.compare("L") == 0 && tld) || (useHand.compare("R") == 0 && trd))
				{
					cout << "That is not a valid option. Will you attack with your: ";
					if (!tld)	cout << "(L)eft hand ";
					if (!trd)	cout << "(R)ight hand";
					cout << endl;
					getline(cin,useHand);
				}
				cout << "Which hand will you attack? ";
				if (!bld)	cout << "(BL)Bottom left ";
				if (!brd)	cout << "(BR)Bottom right ";
				if (m_gameWorld->FFOn())
				{
					if (!tld && useHand.compare("L"))	cout << "(ML)My left "; //can't attack own hand
					if (!trd && useHand.compare("R"))	cout << "(MR)My right";
				}
				cout << endl;
				getline(cin,targetHand);
				while (targetHand.compare("BL") != 0 && targetHand.compare("BR") != 0
					&& targetHand.compare("ML") != 0 && targetHand.compare("MR") != 0
					|| (targetHand.compare("BL") == 0 && bld) || (targetHand.compare("BR") == 0 && brd)
					|| (targetHand.compare("ML") == 0 && (tld || useHand.compare("L") == 0))
					|| (targetHand.compare("MR") == 0 && (trd || useHand.compare("R") == 0)))
				{
					cout << "That is not a valid option. Which hand will you attack? ";
					if (!bld)	cout << "(BL)Bottom left ";
					if (!brd)	cout << "(BR)Bottom right ";
					if (m_gameWorld->FFOn())
					{
						if (!tld && useHand.compare("L"))	cout << "(ML)My left ";
						if (!trd && useHand.compare("R"))	cout << "(MR)My right";
					}
					cout << endl;
					getline(cin,targetHand);
				}
				Hand *usePtr, *tarPtr;
				if (!useHand.compare("L"))
					usePtr = m_gameWorld->tLeft();
				else
					usePtr = m_gameWorld->tRight();
			
				if (!targetHand.compare("ML"))
					tarPtr = m_gameWorld->tLeft();
				else if (!targetHand.compare("MR"))
					tarPtr = m_gameWorld->tRight();
				else if (!targetHand.compare("BL"))
					tarPtr = m_gameWorld->bLeft();
				else
					tarPtr = m_gameWorld->bRight();
				m_gameWorld->attack(usePtr,tarPtr);
			}
		}
		else if (topsTurn && aiOn)
		{
			AI();
		}
		else
		{
			cout << "It is bottom's turn. ";
			if (m_gameWorld->PSOn())
			{
				cout << "Will you (A)ttack";
				//the condition below checks for nonsplitting configurations: equal digits per hand, (0,1) or (1,0), (1,2) or (2,1), and (3,4) or (4,3)
				if (m_gameWorld->bLeft()->numDigits() != m_gameWorld->bRight()->numDigits() &&
					!((m_gameWorld->bLeft()->numDigits() == 1 && m_gameWorld->bRight()->numDigits() == 0) ||
						(m_gameWorld->bLeft()->numDigits() == 0 && m_gameWorld->bRight()->numDigits() == 1)) &&
					!((m_gameWorld->bLeft()->numDigits() == 2 && m_gameWorld->bRight()->numDigits() == 1) ||
						(m_gameWorld->bLeft()->numDigits() == 1 && m_gameWorld->bRight()->numDigits() == 2)) &&
					!((m_gameWorld->bLeft()->numDigits() == 3 && m_gameWorld->bRight()->numDigits() == 4) ||
						(m_gameWorld->bLeft()->numDigits() == 4 && m_gameWorld->bRight()->numDigits() == 3)))
				{
					cout << " or (S)plit";
					splitValid = true;
				}
				cout << "?" << endl;
				getline(cin,option);
				while (option.compare("A") != 0 && ((splitValid && option.compare("S") != 0)||(!splitValid && option.compare("S") == 0)))
				{
					cout << "That is not a valid option. Will you (A)ttack";
					if (m_gameWorld->bLeft()->numDigits() != m_gameWorld->bRight()->numDigits())
						" or (S)plit";
					cout << "?" << endl;
					getline(cin,option);
				}
			}
			if (!option.compare("S"))
			{
				string LtoRamt;
				cout << "State the amount to be transferred from left to right. Negative indicates right to left. " << endl;
				getline(cin, LtoRamt);
				int amt = atoi(LtoRamt.c_str());
				while (amt == 0 || !m_gameWorld->split(amt))
				{
					cout << "Argument invalid. State the amount to be transferred from left to right. " << endl;
					getline(cin,LtoRamt);
					amt = atoi(LtoRamt.c_str());
				}
			}
			else
			{
				string useHand, targetHand;
				cout << "Will you attack with your: ";
				if (!bld)	cout << "(L)eft hand ";
				if (!brd)	cout << "(R)ight hand";
				cout << endl;
				getline(cin,useHand);
				while (useHand.compare("L") != 0 && useHand.compare("R") != 0 
					|| (useHand.compare("L") == 0 && bld) || (useHand.compare("R") == 0 && brd))
				{
					cout << "That is not a valid option. Will you attack with your: ";
					if (!bld)	cout << "(L)eft hand ";
					if (!brd)	cout << "(R)ight hand";
					cout << endl;
					getline(cin,useHand);
				}
				cout << "Which hand will you attack? ";
				if (!tld)	cout << "(TL)Top left ";
				if (!trd)	cout << "(TR)Top right ";
				if (m_gameWorld->FFOn())
				{
					if (!bld && useHand.compare("L"))	cout << "(ML)My left ";
					if (!brd && useHand.compare("R"))	cout << "(MR)My right";
				}
				cout << endl;
				getline(cin,targetHand);
				while (targetHand.compare("TL") != 0 && targetHand.compare("TR") != 0
					&& targetHand.compare("ML") != 0 && targetHand.compare("MR") != 0
					|| (targetHand.compare("TL") == 0 && tld) || (targetHand.compare("TR") == 0 && trd)
					|| (targetHand.compare("ML") == 0 && (bld || useHand.compare("L") == 0))
					|| (targetHand.compare("MR") == 0 && (brd || useHand.compare("R") == 0)))
				{
					cout << "That is not a valid option. Which hand will you attack? ";
					if (!tld)	cout << "(TL)Top left ";
					if (!trd)	cout << "(TR)Top right ";
					if (m_gameWorld->FFOn())
					{
						if (!bld && useHand.compare("L"))	cout << "(ML)My left ";
						if (!brd && useHand.compare("R"))	cout << "(MR)My right";
					}
					cout << endl;
					getline(cin,targetHand);
				}
				Hand *usePtr, *tarPtr;
				if (!useHand.compare("R"))
					usePtr = m_gameWorld->bRight();
				else
					usePtr = m_gameWorld->bLeft();
				
				if (!targetHand.compare("ML"))
					tarPtr = m_gameWorld->bLeft();
				else if (!targetHand.compare("MR"))
					tarPtr = m_gameWorld->bRight();
				else if (!targetHand.compare("TL"))
					tarPtr = m_gameWorld->tLeft();
				else
					tarPtr = m_gameWorld->tRight();
				m_gameWorld->attack(usePtr,tarPtr);
			}
		}
		topsTurn = !topsTurn;
		clearScreen();
	}
}

void Game::AI()
{
	//AI works by:
	//1. using a killing move (if any)
	//2. giving the largest number of digits/points to opponent
	Hand *usePtr = m_gameWorld->tLeft();
	Hand *tarPtr = m_gameWorld->bLeft();
	int largestSum = 0;
	if (m_gameWorld->OFOn())
	{
		int sum = 0;
		if (!usePtr->isDead())
		{
			if (!tarPtr->isDead())
			{
				largestSum = m_gameWorld->tLeft()->numDigits() + m_gameWorld->bLeft()->numDigits() % 5;
				if (largestSum == 0) 
				{
					m_gameWorld->attack(usePtr,tarPtr); return;
				}
			}
			if (!m_gameWorld->bRight()->isDead())
			{
				sum = m_gameWorld->tLeft()->numDigits() + m_gameWorld->bRight()->numDigits() % 5;
				if (sum == 0) 
				{
					m_gameWorld->attack(usePtr,m_gameWorld->bRight()); return;
				}
				if (sum > largestSum)
				{
					largestSum = sum;
					tarPtr = m_gameWorld->bRight();
				}
			}
		}
		if (!m_gameWorld->tRight()->isDead())
		{
			if (!m_gameWorld->bLeft()->isDead())
			{
				sum = m_gameWorld->tRight()->numDigits() + m_gameWorld->bLeft()->numDigits() % 5;
				if (sum == 0) 
				{
					m_gameWorld->attack(m_gameWorld->tRight(),m_gameWorld->bLeft()); return;
				}
				if (sum > largestSum)
				{
					largestSum = sum; 
					usePtr = m_gameWorld->tRight();
					tarPtr = m_gameWorld->bLeft();
				}
			}
			if (!m_gameWorld->bRight()->isDead())
			{
				sum = m_gameWorld->tRight()->numDigits() + m_gameWorld->bRight()->numDigits() % 5;
				if (sum == 0) 
				{
					m_gameWorld->attack(m_gameWorld->tRight(),m_gameWorld->bRight()); return;
				}
				if (sum > largestSum)
				{
					largestSum = sum;
					usePtr = m_gameWorld->tRight();
					tarPtr = m_gameWorld->bRight();
				}
			}
		}
	}
	else
	{
		int sum = 0;
		if (!usePtr->isDead())
		{
			if (!tarPtr->isDead())
				largestSum = m_gameWorld->tLeft()->numDigits() + m_gameWorld->bLeft()->numDigits();
			if (!m_gameWorld->bRight()->isDead())
			{
				sum = m_gameWorld->tLeft()->numDigits() + m_gameWorld->bRight()->numDigits();
				if (sum > largestSum)
				{
					largestSum = sum;
					tarPtr = m_gameWorld->bRight();
				}
			}
		}
		if (!m_gameWorld->tRight()->isDead())
		{
			if (!m_gameWorld->bLeft()->isDead())
			{
				sum = m_gameWorld->tRight()->numDigits() + m_gameWorld->bLeft()->numDigits();
				if (sum > largestSum)
				{
					largestSum = sum; 
					usePtr = m_gameWorld->tRight();
					tarPtr = m_gameWorld->bLeft();
				}
			}
			if (!m_gameWorld->bRight()->isDead())
			{
				sum = m_gameWorld->tRight()->numDigits() + m_gameWorld->bRight()->numDigits();
				if (sum > largestSum)
				{
					largestSum = sum;
					usePtr = m_gameWorld->tRight();
					tarPtr = m_gameWorld->bRight();
				}
			}
		}
	}
	m_gameWorld->attack(usePtr,tarPtr);
	cout << "AI has decided. Press 'enter' to continue.\n";
	cin.ignore(1000,'\n');
}