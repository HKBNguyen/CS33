#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include "Actor.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	//StudentWorld* giveWorld();

private:
	std::vector <Actor*> Objects;
	std::vector <Actor*> Nachen;
	//StudentWorld * world;
};

#endif // STUDENTWORLD_H_
