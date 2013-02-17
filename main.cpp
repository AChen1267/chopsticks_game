//#include <cstdlib>
#include <iostream>
#include <string>
#include "Hand.h"
#include "Game.h"
#include "GameWorld.h"

using namespace std;

int main()
{
	string options[4];
	cout << "Friendly fire on? (Y or N): ";
	getline(cin,options[0]);
	cout << "Overflow on? (Y or N): ";
	getline(cin,options[1]);
	cout << "Splitting on? (Y or N): ";
	getline(cin,options[2]);
	cout << "AI on? (Y or N): ";
	getline(cin,options[3]);
	bool params[4];
	for(int i=0; i<4; i++)
		if (!options[i].compare("Y"))
			params[i] = true;
		else
			params[i] = false;
	Game chopsticks(params[0],params[1],params[2],params[3]);
	chopsticks.play();
}