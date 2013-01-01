//#include <cstdlib>
#include <iostream>
#include <string>
#include "Hand.h"
#include "Game.h"
#include "GameWorld.h"

using namespace std;

int main()
{
	string options[3];
	cout << "Friendly fire on? (Y or N): ";
	getline(cin,options[0]);
	cout << "Overflow on? (Y or N): ";
	getline(cin,options[1]);
	cout << "Splitting on? (Y or N): ";
	getline(cin,options[2]);
	bool params[3];
	for(int i=0; i<3; i++)
		if (!options[i].compare("Y"))
			params[i] = true;
		else
			params[i] = false;
	Game chopsticks(params[0],params[1],params[2]);
	chopsticks.play();
}