#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include <string>
#include <math.h>
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
	aliensDead = currAliens = 0;
	totalToKill = 6 + (4 * getLevel());
	maxAliens = 4 + (.5 * getLevel());
    return GWSTATUS_CONTINUE_GAME;
}
void StudentWorld::addObjects(Actor* obj)
{
	Objects.push_back(obj);
}


bool StudentWorld::canCollide(Actor* mainObject, Actor* otherObject)
{
	int ID = mainObject->ID();
	int otherID = otherObject->ID();
	switch (ID)
	{
	case IID_NACHENBLASTER:
		if (otherID == IID_STAR || otherID == IID_CABBAGE || otherID == IID_EXPLOSION)
			return false;
		return true;
	case IID_CABBAGE:
		if (otherID != IID_SMALLGON && otherID != IID_SMOREGON && otherID != IID_SNAGGLEGON)
			return false;
		return true;
	case IID_TORPEDO:
		if (otherID != IID_NACHENBLASTER && otherID != IID_SMALLGON && otherID != IID_SMOREGON && otherID != IID_SNAGGLEGON )
			return false;
		return true;
	case IID_TURNIP:
	case IID_LIFE_GOODIE:
	case IID_REPAIR_GOODIE:
	case IID_TORPEDO_GOODIE:
		if (otherID != IID_NACHENBLASTER)
			return false;
		return true;
	case IID_SMALLGON:
	case IID_SMOREGON:
	case IID_SNAGGLEGON:
		if (otherID != IID_NACHENBLASTER && otherID != IID_CABBAGE && otherID != IID_TORPEDO)
			return false;
		return true;
	}
}

bool StudentWorld::doesCollide(Actor* obj1, Actor* obj2)
{
	if ((eucl_dist(obj1->getX(), obj1->getY(), obj2->getX(), obj2->getY())) < .75 * (obj1->getRadius() + obj2->getRadius()))
		return true;
}

bool StudentWorld::collideAllPossible(Actor* mainObject)
{
	list<Actor*>::iterator T;
	for (T = Objects.begin(); T != Objects.end(); T++)
	{
		if (canCollide(mainObject, *T) && doesCollide(mainObject, *T))
			mainObject->
	}
}

int StudentWorld::eucl_dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void StudentWorld::addNewShip()
{
	int remainingShips = totalToKill - aliensDead;
	if (currAliens < compareMin(maxAliens, remainingShips))
	{
		int s1 = 60;
		int s2 = 20 + getLevel() * 5;
		int s3 = 5 + getLevel() * 10;
		double s = s1 + s2 + s3;
		if (randInt(0, 100) < ((s1/s)*100))
		{
			Objects.push_back(new Smallgon(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this, Nachen));
			//currAliens++;
		}
	}
	
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
	int tor_amt = Nachen->curr_tor();
	ostringstream oss;
	oss << "Lives:  " << lives << "  "
		<< "Health:  " << (health / 50) * 100 << "%" << "  "
		<< "Score:  " << score << "  "
		<< "Level:  " << level << "  ";
	oss.setf(ios::fixed);
	oss.precision(0);
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
	addNewShip();
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






