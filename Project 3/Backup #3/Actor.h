#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int startDirection, double size, int depth);
	virtual void doSomething() = 0;
	virtual bool isAlive() = 0;
	//StudentWorld * getWorld();
private:
	//StudentWorld * currWorld;
};

class NachenBlaster : public Actor
{
public:
	NachenBlaster();
	~NachenBlaster();
	virtual void doSomething();
	int get_HP();
	virtual bool isAlive();
private:
	int m_hp, cabbage_pts;
};

class Star : public Actor
{
public:
	Star();
	~Star();
	virtual void moveTo();
	virtual void doSomething();
	virtual bool isAlive();

private:
	bool alive;
};
#endif // ACTOR_H_
