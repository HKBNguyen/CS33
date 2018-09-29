#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <vector>
#include <string>
using namespace std;


class NachenBlaster : public Actor
{
public:
	NachenBlaster()
		:Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0)
	{
		m_hp = 50;
		cabbage_pts = 50;
	}
	~NachenBlaster()
	{}
	virtual void doSomething()
	{

	}
	int get_HP()
	{
		return m_hp;
	}
	virtual bool isAlive()
	{
		if (m_hp < 0)
			return false;
		else
			return true;
	}
private:
	int m_hp, cabbage_pts;
};

class Star : public Actor
{
public:
	Star()
		:Actor(IID_STAR, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1), 0, randInt(.05, .5), 3)
	{

	}
	~Star()
	{}
	virtual void moveTo()
	{
		GraphObject::moveTo(GraphObject::getX() - 1, GraphObject::getY());
	}
	virtual void doSomething()
	{
		if (GraphObject::getX() < 0)
			alive = false;
		else
			moveTo();
	}
	virtual bool isAlive()
	{
		return alive;
	}

private:
	bool alive;
};

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

