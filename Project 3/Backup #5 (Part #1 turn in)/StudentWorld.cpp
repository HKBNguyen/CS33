#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <list>
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
StudentWorld::~StudentWorld()
{
	cleanUp();
}
int StudentWorld::init()
{
	for (int i = 0; i < 30; i++)
	{
		Objects.push_back(new Star(randInt(0, VIEW_WIDTH - 1), randInt(0, VIEW_HEIGHT - 1), this));
	}
	Nachen.push_back(new NachenBlaster(this));
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	list<Actor*>::iterator itS; // iterator for Stars
	itS = Objects.begin();
	while (itS != Objects.end())
	{
		if (Nachen.front()->isAlive())
			Nachen.front()->doSomething();
		if ((*itS)->isAlive())
		{
			(*itS)->doSomething();
			if (!Nachen.front()->isAlive())
				return GWSTATUS_PLAYER_DIED;
		}
		itS++;
	}
	removeDeadObjects();
	if (randInt(0, 100) < 15)
		Objects.push_back(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this));
	return GWSTATUS_CONTINUE_GAME;
	//  decLives();
	//return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
	list<Actor*>::iterator it;
	it = Objects.begin();
	while (it != Objects.end())
	{
		if (*it != nullptr)
		{
			delete *it;
			*it = nullptr;
			it = Objects.erase(it);
		}
		else
			it++;
	}
	if (Nachen.front() != nullptr)
	{
		delete Nachen.front();
		Nachen.front() = nullptr;
	}
}


void StudentWorld::removeDeadObjects()
{
	list<Actor*>::iterator itS; // iterator for Stars
	itS = Objects.begin();
	while (itS != Objects.end())
	{
		if (!(*itS)->isAlive())
		{
			if (*itS != nullptr)
			{
				delete *itS;
				*itS = nullptr;
				itS = Objects.erase(itS);
			}
			else
				itS++;
		}
		else
			itS++;
	}
}




