#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world, double hp = 1)
	: GraphObject(imageID, startX, startY, startDirection, size, depth), currWorld(world)
{
	m_ID = imageID;
	m_hp = hp;
	alive = true;
}

bool Actor::collided()
{
	return false;
}

double Actor::getHP()
{
	return m_hp;
}

bool Actor::isAlive()
{
	if (getX() < 0 || getX() >= VIEW_WIDTH || m_hp <= 0)
	{
		setDead();
		return alive;
	}
	return alive;
}

void Actor::changeHP(int cause)
{

	switch (cause)
	{
	case IID_NACHENBLASTER:
		m_hp = 0;
		break;
	case IID_CABBAGE:
		m_hp -= 2.0;
		break;
	case IID_TORPEDO:
		m_hp -= 8.0;
		break;
	case IID_TURNIP:
		m_hp -= 2.0;
		break;
	case IID_LIFE_GOODIE:
	case IID_REPAIR_GOODIE:
	case IID_TORPEDO_GOODIE:
	case IID_SMALLGON:
		m_hp -= 5.0;
		break;
	case IID_SMOREGON:
	case IID_SNAGGLEGON:
	default:
		break;
	}
	if (m_hp <= 0)
		setDead();
}
void Actor::setDead()
{
	alive = false;
}
Actor::~Actor()
{

}

StudentWorld* Actor::getWorld()
{
	return currWorld;
}

NachenBlaster::NachenBlaster(StudentWorld* world)
		:Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world, 50)
	{
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
	if (getHP() < 0)
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


Star::Star(int x, int y, StudentWorld* world) 
	:Actor(IID_STAR, x, y, 0, (randInt(5,50)/100.0), 3, world, 1)
	{

	}
Star::~Star()
	{

	}

void Star::doSomething()
	{
	if (!isAlive())
		return;
		else
			moveTo(getX() -1, getY());
	}

bool Star::collided()
{
	return false;
}

Explosion::Explosion(double x, double y, StudentWorld* world)
	: Actor(IID_EXPLOSION, x, y, 0, 1, 0, world)
{

}
Explosion::~Explosion()
{
}
bool Explosion::collided()
{
	return false;
}
void Explosion::doSomething()
{
	if(getSize() < 3.375)
	setSize(getSize()*1.5);
	else
	{
		setDead();
	}
}
Cabbage::Cabbage(double x, double y, StudentWorld* world)
	: Actor(IID_CABBAGE, x, y, 0, .5, 1, world)
{

}

void Cabbage::doSomething()
{
	if (!isAlive())
		return;
	if (getWorld()->collideAllPossible(this))
		return;
	moveTo(getX() + 8, getY());
	setDirection(20);
	
}

bool Cabbage::collided()
{
	return false;
}

Flatulence_Torpedo::Flatulence_Torpedo(double x, double y, StudentWorld * world)
	:Actor(IID_TORPEDO, x, y, 0, .5, 1, world)
{

}



void Flatulence_Torpedo::doSomething()
{
	if (!isAlive())
		return;
	if (getWorld()->collideAllPossible(this))
		return;
	moveTo(getX() + 8, getY());
	
	
}

bool Flatulence_Torpedo::collided()
{
	return false;
}

Turnip::Turnip(double x, double y, StudentWorld * world)
	:Actor(IID_TURNIP, x, y, 0, .5, 1, world)
{

}

void Turnip::doSomething()
{
	if (!isAlive())
		return;
	if (getWorld()->collideAllPossible(this))
	{
		return;
	}
	moveTo(getX() - 6, getY());
	setDirection(20);
}

bool Turnip::collided()
{
	return false;
}


Smallgon::Smallgon(double x,double y, StudentWorld* world, NachenBlaster* ship)
	:Actor(IID_SMALLGON,x,y,0,1.5,1,world, 5)
{
	//m_hp = 5 * (1 + (getWorld()->getLevel()-1)*.1);
	plan_length = 0;
	flight_speed = 2;
	m_Nachen = ship;
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
	if (getWorld()->collideAllPossible(this))
	{
		if (getHP() <= 0)
		{
			getWorld()->increaseScore(250);
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObjects(new Explosion(getX(), getY(), getWorld()));
			return;
		}
		else
			getWorld()->playSound(SOUND_BLAST);
	}
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
		if (randInt(0, 100) < 50)
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
	if (getWorld()->collideAllPossible(this))
	{
		if (getHP() <= 0)
		{
			getWorld()->increaseScore(250);
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObjects(new Explosion(getX(), getY(), getWorld()));
			return;
		}
		else
			getWorld()->playSound(SOUND_BLAST);
	}
}

bool Smallgon::collided()
{
	return false;
}


