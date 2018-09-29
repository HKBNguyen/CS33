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

private:
	std::list <Actor*> Objects;
	NachenBlaster* Nachen;
	
	
};

#endif // STUDENTWORLD_H_
