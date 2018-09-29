#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor: public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world, double hp);
	virtual void doSomething() = 0;
	virtual bool isAlive();
	void setDead();
	void incHP(double amt);
	void sufferDamage(int cause);
	int ID() { return m_ID; }
	double getHP();
	StudentWorld * getWorld();
private:
	StudentWorld * currWorld;
	int m_ID;
	double m_hp;
	bool alive;

};

class Alien : public Actor
{
public:
	Alien(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world, double hp);
	void doSomething();
	bool checkInRange();
private:
	double plan_length, flight_speed;
	int travel_direction;
	//travel_directions: 0 is left, 1 is down and left, 2 is up and left
};
/*class Ship : public Actor
{
public:
	Ship(int x, int y, StudentWorld* world);
	virtual ~Ship();
	virtual bool isAlive();
	int get_HP();
	virtual void sufferDamage() = 0;
private:
	int m_hp;

};*/

class NachenBlaster : public Actor
{
public:
	NachenBlaster(StudentWorld* world);
	~NachenBlaster();
	virtual void doSomething();
	virtual void moveTo(double x, double y);
	int curr_cab();
	int curr_tor();
private:
	int cabbage_pts, torCount;
//	Cabbage m_count[];
};

class Star : public Actor
{
public:
	Star(int x, int y, StudentWorld* world);
	virtual void doSomething();

private:

};
class Explosion : public Actor
{
public:
	Explosion(double x, double y, StudentWorld* world);
	void doSomething();
private:
};
class Cabbage :public Actor
{
public:
	Cabbage(double x, double y, StudentWorld* world);
	void doSomething();
private:
};
class Turnip : public Actor
{
public:
	Turnip(double x, double y, StudentWorld* world);
	void doSomething();
private:

};
class Flatulence_Torpedo : public Actor
{
public:
	Flatulence_Torpedo(double x, double y, StudentWorld* world);
	void doSomething();
private:

};
class Extra_Life_Goodie: public Actor
{
public:
	Extra_Life_Goodie(double x, double y, StudentWorld* world);
	void doSomething();
private:
};
class Repair_Goodie : public Actor
{

};
class Flatulence_Torpedo_Goodie : public Actor
{

};
class Smallgon :public Alien
{
public:
	Smallgon(double x, double y, StudentWorld* world);
private:
	//travel_directions: 0 is left, 1 is down and left, 2 is up and left

};
class Smoregon : public Alien
{
public:
	Smoregon(double x, double y, StudentWorld* world);

};
class Snagglegon : public Actor
{

};
#endif // ACTOR_H_
