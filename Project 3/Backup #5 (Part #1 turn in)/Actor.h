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
//	Cabbage m_count[];
};

class Star : public Actor
{
public:
	Star(int x, int y, StudentWorld* world);
	~Star();
	virtual void moveTo();
	virtual void doSomething();
	virtual bool isAlive();

private:
	
};
class Explosion : public Actor
{
public:
	Explosion();
};
class Cabbage :public Actor
{
public:
	Cabbage(int x, int y, StudentWorld* world);
	bool isAlive();
	void doSomething();
private:
	bool alive;

};
class Turnip : public Actor
{

};
class Flatulence_Torpedo : public Actor
{

};
class Extra_Life_Goodie: public Actor
{

};
class Repair_Goodie : public Actor
{

};
class Flatulence_Torpedo_Goodie : public Actor
{

};
class Smallgon :public Actor
{

};
class Smoregon : public Actor
{

};
class Snagglegon : public Actor
{

};
#endif // ACTOR_H_
