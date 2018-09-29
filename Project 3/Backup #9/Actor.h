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
	void changeHP(int cause);
	virtual bool collided() = 0;
	int ID() { return m_ID; }
	virtual ~Actor();
//	virtual void sufferDamage() = 0;
	double getHP();
	StudentWorld * getWorld();
private:
	StudentWorld * currWorld;
	int m_ID;
	double m_hp;
	bool alive;

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
	bool collided();
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
	~Star();
	virtual void doSomething();
	bool collided();

private:

};
class Explosion : public Actor
{
public:
	Explosion(double x, double y, StudentWorld* world);
	~Explosion();
	bool collided();
	void doSomething();
private:
};
class Cabbage :public Actor
{
public:
	Cabbage(double x, double y, StudentWorld* world);
	void doSomething();
	bool collided();
private:
	

};
class Turnip : public Actor
{
public:
	Turnip(double x, double y, StudentWorld* world);
	void doSomething();
	bool collided();
private:

};
class Flatulence_Torpedo : public Actor
{
public:
	Flatulence_Torpedo(double x, double y, StudentWorld* world);
	void doSomething();
	bool collided();
private:

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
public:
	Smallgon(double x, double y, StudentWorld* world, NachenBlaster* ship);
	void doSomething();
	bool collided();
	bool checkInRange();
private:
	int plan_length, flight_speed, travel_direction;
	//travel_directions: 0 is left, 1 is down and left, 2 is up and left
	NachenBlaster* m_Nachen;

};
class Smoregon : public Actor
{

};
class Snagglegon : public Actor
{

};
#endif // ACTOR_H_
