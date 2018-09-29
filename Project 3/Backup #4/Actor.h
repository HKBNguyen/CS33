#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor: public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world);
	virtual void doSomething() = 0;
	virtual bool isAlive() = 0;
	StudentWorld * getWorld();
private:
	StudentWorld * currWorld;
};

class NachenBlaster : public Actor
{
public:
	NachenBlaster(StudentWorld* world);
	~NachenBlaster();
	virtual void doSomething();
	int get_HP();
	virtual bool isAlive();
	virtual void moveTo(double x, double y);
private:
	int m_hp, cabbage_pts;
};

class Star : public Actor
{
public:
	Star(StudentWorld* world);
	~Star();
	virtual void moveTo();
	virtual void doSomething();
	virtual bool isAlive();

private:
	bool alive;
};
#endif // ACTOR_H_
