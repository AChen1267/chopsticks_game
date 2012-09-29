#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Game::Game(bool friendlyFire, bool overflow, bool allowSplit)
	:m_gameWorld(friendlyFire,overflow,allowSplit)
{
	topsTurn = true;
	topScore = bottomScore = 0;
}
void Game::display()
{
	cout << "Top: " << m_gameWorld.tLeft()->numDigits() << "  " << m_gameWorld.tRight()->numDigits() << endl;
	cout << "Bot: " << m_gameWorld.bLeft()->numDigits() << "  " << m_gameWorld.bRight()->numDigits() << endl;
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
	while ((!m_gameWorld.tLeft()->isDead() || !m_gameWorld.tRight()->isDead())
		&& (!m_gameWorld.bLeft()->isDead() || !m_gameWorld.bRight()->isDead()))
	{
		display();
		string test;
		getline(cin,test);
		clearScreen();
	}
}