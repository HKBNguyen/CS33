#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world)
	: GraphObject(imageID, startX, startY, startDirection, size, depth), currWorld(world)
{
	m_ID = imageID;
	alive = true;
}

Actor::~Actor()
{

}
bool Actor::isAlive()
{
	if (getX() >= VIEW_WIDTH || getX() < 0)
	{
		setDead();
		return alive;
	}
	else
		return alive;
}

void Actor::setDead()
{
	alive = false;
}

StudentWorld* Actor::getWorld() const
{
	return currWorld;
}

int Actor::ID()
{
	return m_ID;
}

Damageable::Damageable(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld* world, double hp)
	:Actor(imageID, x, y, starDir, size, depth, world)
{
	m_hp = hp;
}

Damageable::~Damageable()
{
}
double Damageable::getHP() const
{
	return m_hp;
}

void Damageable::sufferDamage(double amt)
{
	changeHP(amt);
}

void Damageable::changeHP(double amt)
{
	m_hp + amt;
}

Projectile::Projectile(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld * world, double hp = 1)
	: Damageable(imageID, x, y, starDir, size, depth, world, hp)
{

}

Projectile::~Projectile()
{
}

void Projectile::sufferDamage(double amt)
{
	setDead();
}


NachenBlaster::NachenBlaster(StudentWorld* world)
		:Damageable(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world, 50)
	{
	m_hp = 50;
	cabbage_pts = 30;
	torCount = 5;
	}
NachenBlaster::~NachenBlaster()
	{

	}

void NachenBlaster::sufferDamage(double amt)
{
	changeHP(amt);
}
void NachenBlaster::moveTo(double x, double y)
{
	if (x < 0 || x >= VIEW_WIDTH || y < 0 || y >= VIEW_HEIGHT)
		return;
	else
		GraphObject::moveTo(x, y);
}

int NachenBlaster::curr_cab()
{
	return cabbage_pts;
}
int NachenBlaster::curr_tor()
{
	return torCount;
}
void NachenBlaster::doSomething()
{
	if (m_hp < 0)
		return;
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			moveTo(getX() - 6, getY());
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 6, getY());
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() + 6);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 6);
			break;
		case KEY_PRESS_SPACE:
			if (curr_cab() >= 5)
			{
				Actor* cabPtr = new Cabbage(getX() + 12, getY(), getWorld());
				getWorld()->addObjects(cabPtr);
				getWorld()->playSound(SOUND_PLAYER_SHOOT);
				cabbage_pts -= 5;
			}
			break;
		case KEY_PRESS_TAB:
			if (curr_tor() > 0)
		{
			Actor *torPtr = new Flatulence_Torpedo(getX() + 12, getY(), getWorld());
			getWorld()->addObjects(torPtr);
			getWorld()->playSound(SOUND_TORPEDO);
			torCount--;
			break;
		}
		}
	}
	if (curr_cab() < 30)
		cabbage_pts++;
}
int NachenBlaster::get_HP()
	{
		return m_hp;
	}
bool NachenBlaster::isAlive()
	{
		if (m_hp <= 0)
			return false;
		else
			return true;
	}

Star::Star(double x, double y, StudentWorld* world) 
	:Actor(IID_STAR, x, y, 0, (randInt(5,50)/100.0), 3, world)
	{

	}
Star::~Star()
	{

	}
void Star::moveTo()
	{
		GraphObject::moveTo(GraphObject::getX() - 1, GraphObject::getY());
	}
void Star::doSomething()
	{
	if (!isAlive())
		return;
		else
			moveTo();
	}
bool Star::isAlive()
	{
	return (GraphObject::getX() >= 0);
	}



/*Explosion::Explosion()

{

}*/
Cabbage::Cabbage(int x, int y, StudentWorld* world)
	: Projectile(IID_CABBAGE, x, y, 0, .5, 1, world)
{

}

void Cabbage::doSomething()
{
	if (!isAlive())
		return;
	else if (getWorld()->collideAllPossible(this))
	{

	}

	GraphObject::moveTo(getX() + 8, getY());
	GraphObject::setDirection(20);
}



Flatulence_Torpedo::Flatulence_Torpedo(int x, int y, StudentWorld * world)
	:Projectile(IID_TORPEDO, x, y, 0, .5, 1, world)
{

}

void Flatulence_Torpedo::doSomething()
{
	moveTo(getX() + 8, getY());
}



Turnip::Turnip(int x, int y, StudentWorld * world)
	:Projectile(IID_TURNIP, x, y, 0, .5, 1, world)
{

}

void Turnip::doSomething()
{
	if (!isAlive())
		return;
	moveTo(getX() - 6, getY());
	setDirection(20);
}



Smallgon::Smallgon(int x,int y, StudentWorld* world, NachenBlaster* ship)
	:Actor(IID_SMALLGON,x,y,0,1.5,1,world)
{
	m_hp = 5 * (1 + (getWorld()->getLevel()-1)*.1);
	plan_length = 0;
	flight_speed = 2;
	m_Nachen = ship;
}

bool Smallgon::isAlive()
{
	if (getX() < 0 || m_hp <= 0)
	{
		setDead();
		return false;
	}
	else
		return true;
}
bool Smallgon :: checkInRange()
{
	if (m_Nachen->getX() > getX())
		return false;
	int upper = getY() + 4;
	int lower = getY() - 4;
	if (m_Nachen->getY() <= upper && m_Nachen->getY() >= lower)
		return true;
	return false;
}

void Smallgon::doSomething()
{
	if (!isAlive())
		return;
	//implement #3 on page 34
	if ((plan_length == 0 || (getY() == VIEW_HEIGHT - 1 || getY() == 0)))
	{
		if (getY() >= VIEW_HEIGHT - 1)
			travel_direction = 1;
		else if (getY() <= 0)
			travel_direction = 2;
		else if (plan_length == 0)
		{
			int dir[3] = { 0, 1, 2};
			int dirNum = randInt(0, 2);
			travel_direction = dir[dirNum];
		}
		int newlen = randInt(1, 32);
		plan_length = newlen;
	}
	// implement #5 on page 34
	if (checkInRange()) //#5 prototype
	{
		double chance = 1 / ((20 / (getWorld()->getLevel())) + 5); // ugly formula from spec
		if (randInt(0, 100) < chance*100)
		{
			Turnip* turPtr = new Turnip(getX(), getY() + 14, getWorld());
			getWorld()->addObjects(turPtr);
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
	}
	if (travel_direction == 2)
	{
		moveTo(getX() - flight_speed, getY() + flight_speed);
		plan_length--;
	}
	else if (travel_direction == 1)
	{
		moveTo(getX() - flight_speed, getY() - flight_speed);
		plan_length--;
	}
	else
	{
		moveTo(getX() - flight_speed, getY());
		plan_length--;
	}
}

bool Smallgon::collided()
{
	return false;
}

