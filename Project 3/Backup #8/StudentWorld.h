#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>
#include "Actor.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	void removeDeadObjects();
	void addObjects(Actor* obj);
	int compareMin(int n1, int n2)
	{
		if (n1 < n2)
			return n1;
		else
			return n2;
	}

private:
	void addNewShip();
	std::list <Actor*> Objects;
	NachenBlaster* Nachen;
	int aliensDead, totalToKill, maxAliens, currAliens;
	
	
};

#endif // STUDENTWORLD_H_
