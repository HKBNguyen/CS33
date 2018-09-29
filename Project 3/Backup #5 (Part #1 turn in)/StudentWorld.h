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
	void all_doSomething();
	void removeDeadObjects();

private:
	std::list <Actor*> Objects;
	std::list <Actor*> Nachen;
	int nObjects;
	
};

#endif // STUDENTWORLD_H_
