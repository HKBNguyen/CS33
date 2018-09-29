#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <vector>
#include <string>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
	
}

int StudentWorld::init()
{
	for (int i = 0; i < 30; i++)
	{
		Objects.push_back(new Star);
	}
	Nachen.push_back(new NachenBlaster);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

	vector<Actor*>::iterator itS; // iterator for Stars
	itS = Objects.begin();
	while (itS != Objects.end())
	{
		(*itS)->doSomething();
		if (!(*itS)->isAlive())
		{
			delete *itS;
			itS = Objects.erase(itS);
			Objects.push_back(new Star);
			itS = Objects.begin();
		}
		else 
		itS++;
	}
	vector<Actor*>::iterator itN; // iterator for NachenBlaster
	itN = Nachen.begin();
	return GWSTATUS_CONTINUE_GAME;
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
	for (int i = 0; i < 30; i++)
	{
		delete Objects[i];
	}
	
}

/*StudentWorld* StudentWorld::giveWorld()
{
	return world;
}*/