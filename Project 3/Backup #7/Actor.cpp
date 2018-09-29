#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world)
	: GraphObject(imageID, startX, startY, startDirection, size, depth), currWorld(world)
{
	
}

bool Actor::collided()
{
	return false;
}
Actor::~Actor()
{

}

StudentWorld* Actor::getWorld()
{
	return currWorld;
}

NachenBlaster::NachenBlaster(StudentWorld* world)
		:Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world)
	{
	m_hp = 50;
	cabbage_pts = 30;
	torCount = 5;
	}
NachenBlaster::~NachenBlaster()
	{

	}
void NachenBlaster::moveTo(double x, double y)
{
	if (x < 0 || x >= VIEW_WIDTH || y < 0 || y >= VIEW_HEIGHT)
		return;
	else
		GraphObject::moveTo(x, y);
}
bool NachenBlaster::collided()
{
	return false;
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
		if (m_hp < 0)
			return false;
		else
			return true;
	}


Star::Star(int x, int y, StudentWorld* world) 
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

bool Star::collided()
{
	return false;
}

/*Explosion::Explosion()

{

}*/
Cabbage::Cabbage(int x, int y, StudentWorld* world)
	: Actor(IID_CABBAGE, x, y, 0, .5, 1, world)
{

}

bool Cabbage :: isAlive()
{
	if (getX() >= VIEW_WIDTH)
		return false;
	else if (collided())
		return false;
	else
		return true;
}
void Cabbage::doSomething()
{
	if (!isAlive())
		return;
	if (collided() && !isAlive())
		return;
	GraphObject::moveTo(getX() + 8, getY());
	GraphObject::setDirection(20);
}

bool Cabbage::collided()
{
	return false;
}

Flatulence_Torpedo::Flatulence_Torpedo(int x, int y, StudentWorld * world)
	:Actor(IID_TORPEDO, x, y, 0, .5, 1, getWorld())
{

}

bool Flatulence_Torpedo::isAlive()
{
	if (getX() < 0 || getX() >= VIEW_WIDTH)
		return false;
	else
		return true;
}

void Flatulence_Torpedo::doSomething()
{
	moveTo(getX() + 8, getY());
}

bool Flatulence_Torpedo::collided()
{
	return false;
}

Smallgon::Smallgon(int x,int y, StudentWorld* world)
	:Actor(IID_SMALLGON,x,y,0,1.5,1,world)
{
	m_hp = 5 * (1 + (getWorld()->getLevel()-1)*.1);
	plan_length = 0;
	flight_speed = 2;
}

bool Smallgon::isAlive()
{
	if (getX() < 0 || m_hp <= 0)
		return false;
	else
		return true;
}

void Smallgon::doSomething()
{
	if (!isAlive())
		return;
	if ((plan_length == 0 || getY() == VIEW_HEIGHT - 1 || getY() == 0))
	{
		if (getY() >= VIEW_HEIGHT - 1)
			setDirection(225);
		else if (getY() <= 0)
			setDirection(135);
		else if (plan_length == 0)
		{
			int dir[3] = { 0, 135, 225 };
			int dirNum = randInt(0, 2);
			setDirection(dir[dirNum]);
		}
		int newlen = randInt(1, 32);
		plan_length = newlen;
	}
	// implement #5 on page 34
	if (getDirection() == 135)
		moveTo(getX() - flight_speed, getY() + flight_speed);
	else if (getDirection() == 225)
		moveTo(getX() - flight_speed, getY() - flight_speed);
	else
		moveTo(getX() - flight_speed, getY());
}

bool Smallgon::collided()
{
	return false;
}
