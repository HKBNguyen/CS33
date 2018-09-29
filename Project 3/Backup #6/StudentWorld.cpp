#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
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
		Objects.push_back(new Star(randInt(0,VIEW_WIDTH-1),randInt(0,VIEW_HEIGHT-1),this));
	}
	Nachen = (new NachenBlaster(this));
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addObjects(Actor* obj)
{
	Objects.push_back(obj);
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	int lives = getLives();
	int health = Nachen->get_HP();
	int score = getScore();
	int level = getLevel();
	double cab_energy = Nachen->curr_cab();
	int tor_amt = 0;
	ostringstream oss;
	oss << "Lives:  " << lives << "  "
		<< "Health:  " << (health / 50) * 100 << "%" << "  "
		<< "Score:  " << score << "  "
		<< "Level:  " << level << "  ";
	oss.setf(ios::fixed);
	oss.precision(2);
	 oss << "Cabbages:  " << (cab_energy / 30)*100 << "%" << "  "
		<< "Torpedos:  " << tor_amt;
	string s = oss.str();
	setGameStatText(s);
	list<Actor*>::iterator itS; // iterator for Stars
	itS = Objects.begin();
	if (Nachen->isAlive())
		Nachen->doSomething();
	while (itS != Objects.end())
	{
		if ((*itS)->isAlive())
		{
			(*itS)->doSomething();
			if (!Nachen->isAlive())
				return GWSTATUS_PLAYER_DIED;
		}
		++itS;
	}
	removeDeadObjects();
	if (randInt(0, 100) < 15)
	{
		Objects.push_back(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this));
	}
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
			++it;
	}
	if (Nachen != nullptr)
	{
		delete Nachen;
		Nachen = nullptr;
	}
}


void StudentWorld::removeDeadObjects()
{
	list<Actor*>::iterator t; 
	t = Objects.begin();
	while (t != Objects.end())
	{
		if (!((*t)->isAlive()))
		{
			if (*t != nullptr)
			{
				delete *t;
				*t = nullptr;
				t = Objects.erase(t);
			}
			else
				++t;
		}
		else
			++t;
	}
}




