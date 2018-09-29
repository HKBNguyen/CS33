#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
class Actor: public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world);
	virtual void doSomething() = 0;
	virtual bool isAlive();
	virtual bool isAlien() const;
	void setDead();
	//void sufferDamage(int cause);
	int ID() { return m_ID; }
	StudentWorld * getWorld();
private:
	StudentWorld * currWorld;
	int m_ID;
	bool alive;

};

class DamageableObject : public Actor
{
public: 
	DamageableObject(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld* world, double hp);
	double getHP();
	void incHP(double amt);
	virtual void sufferDamage(double amt, int cause);
private:
	double m_hp;
};

class Alien : public DamageableObject
{
public:
	Alien(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world, double hp, double speed, int travel_dir, double damage, unsigned int score);
	virtual bool isAlien() const;
	bool checkInRange();
	virtual void dropGoodie();
	void setSpeed(double speed);
	void setDir(int dir);
	void move();
	void setLength(double length);
	void doSomething();
	virtual void doDifferent();
	virtual void sufferDamage(double amt, int cause);
private:
	double m_speed, m_damage, m_length;
	int travel_direction;
	unsigned int m_score;
	
	void newPlan();
		//travel_directions: 0 is left, 1 is down and left, 2 is up and left
};
class Projectile: public DamageableObject
{
public:
	Projectile(int imageID, double startX, double startY, double damageAmt,StudentWorld* world, double deltaX, bool rotates, int imageDir);
	virtual void doSomething();
private:
	double m_damage, m_move;
	bool m_rotates;
	int m_dirChange;
};

class NachenBlaster : public DamageableObject
{
public:
	NachenBlaster(StudentWorld* world);
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
class Cabbage :public Projectile
{
public:
	Cabbage(double x, double y, StudentWorld* world);
	
private:
};
class Turnip : public DamageableObject
{
public:
	Turnip(double x, double y, StudentWorld* world);
	void doSomething();
private:

};
class Flatulence_Torpedo : public DamageableObject
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
	virtual void doDifferent();
private:

};
class Snagglegon : public Alien
{
public:
	Snagglegon(double x, double y, StudentWorld* world);
	virtual void doDifferent();
private:
//	virtual void doDifferent();
};
#endif // ACTOR_H_
