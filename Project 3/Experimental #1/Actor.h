#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor: public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world);
	virtual void doSomething() = 0;
	virtual bool isAlive();
	void setDead();
	int ID();
	virtual ~Actor();
	StudentWorld * getWorld() const;
private:
	StudentWorld * currWorld;
	int m_ID;
	bool alive;

};

class Damageable : public Actor
{
public:
	Damageable(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld* world, double hp);
	virtual ~Damageable ();
	virtual void sufferDamage(double amt);
	virtual void changeHP(double amt);
	double getHP() const;
private:
	double m_hp;

};
class Projectile : public Damageable
{
public:
	Projectile(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld* world, double hp = 1);
	~Projectile();
	virtual void sufferDamage(double amt);
private:
};

class NachenBlaster : public Damageable
{
public:
	NachenBlaster(StudentWorld* world);
	~NachenBlaster();
	virtual void doSomething();
	virtual void sufferDamage(double amt);
	int get_HP();
	virtual bool isAlive();
	virtual void moveTo(double x, double y);
	int curr_cab();
	int curr_tor();
private:
	int m_hp, cabbage_pts, torCount;

};

class Star : public Actor
{
public:
	Star(double x, double y, StudentWorld* world);
	~Star();
	virtual void moveTo();
	virtual void doSomething();
	virtual bool isAlive();
private:

};
class Explosion : public Actor
{
public:
	//Explosion();
};
class Cabbage :public Projectile
{
public:
	Cabbage(int x, int y, StudentWorld* world);
	void doSomething();
private:
	

};
class Turnip : public Projectile
{
public:
	Turnip(int x, int y, StudentWorld* world);
	void doSomething();
private:

};
class Flatulence_Torpedo : public Projectile
{
public:
	Flatulence_Torpedo(int x, int y, StudentWorld* world);
	void doSomething();
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
	Smallgon(int x, int y, StudentWorld* world, NachenBlaster* ship);
	bool isAlive();
	void doSomething();
	bool collided();
	bool checkInRange();
private:
	int m_hp, plan_length, flight_speed, travel_direction;
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
