#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

Actor::Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world)
	: GraphObject(imageID, startX, startY, startDirection, size, depth), currWorld(world)
{
	m_ID = imageID;
	alive = true;
}

bool Actor::isAlien() const
{
	return false;
}

bool Actor::isAlive()
{
	if (getX() < 0 || getX() >= VIEW_WIDTH)
	{
		setDead();
		return alive;
	}
	return alive;
	
}
/*void Actor::sufferDamage(int cause)
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
		m_hp -= 5.0;
		break;
	case IID_SNAGGLEGON:
		m_hp -= 15.0;
	default:
		break;
	}
	if (m_hp <= 0)
		setDead();
}*/
void Actor::setDead()
{
	alive = false;
}

StudentWorld* Actor::getWorld()
{
	return currWorld;
}

DamageableObject::DamageableObject(int imageID, double x, double y, int starDir, double size, int depth, StudentWorld* world, double hp)
	:Actor(imageID, x, y, starDir, size, depth, world)
{
	m_hp = hp;
}
double DamageableObject::getHP()
{
	return m_hp;
}
void DamageableObject::incHP(double amt)
{
	m_hp += amt;
}
void DamageableObject::sufferDamage(double amt, int cause)
{
	m_hp -= amt;
	if (m_hp <= 0)
		setDead();
}

Alien::Alien(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld * world, double hp, double speed, int travel_dir, double damage, unsigned int score)
	:DamageableObject(imageID, startX, startY, startDirection, size, depth, world,hp)
{
	//double alien_hp = hp;
	//incHP(alien_hp);
	travel_direction = travel_dir;
	m_speed = speed;
	m_length = 0;
	m_score = score;
	m_damage = damage;
}

bool Alien::isAlien() const
{
	return true;
}
bool Alien::checkInRange()
{
	if (getWorld()->returnNachen()->getX() > getX())
		return false;
	int upper = getY() + 4;
	int lower = getY() - 4;
	if (getWorld()->returnNachen()->getY() <= upper && getWorld()->returnNachen()->getY() >= lower)
		return true;
	return false;
}

void Alien::dropGoodie()
{
}

void Alien::setSpeed(double speed)
{
	m_speed = speed;
}

void Alien::setDir(int dir)
{
	travel_direction = dir;
}

void Alien::move()
{
	
	if (travel_direction == 2)
	{
		moveTo(getX() - m_speed, getY() + m_speed);
		
	}
	else if (travel_direction == 1)
	{
		moveTo(getX() - m_speed, getY() - m_speed);
	
	}
	else
	{
		moveTo(getX() - m_speed, getY());
		
	}
	if (m_length > 0)
	m_length--;
}

void Alien::setLength(double length)
{
	m_length = length;
}

void Alien::doDifferent()
{
	if (checkInRange()) //#5 prototype
	{
		double chance = 1 / ((20 / (getWorld()->getLevel())) + 5); // ugly formula from spec
		if (randInt(0, 100) / 1.0 < chance * 100)
		{
			Turnip* turPtr = new Turnip(getX() - 14, getY(), getWorld());
			getWorld()->addObjects(turPtr);
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
	}
}
void Alien::sufferDamage(double amt, int cause)
{
	DamageableObject::sufferDamage(amt, cause);
	if (!isAlive())
	{
		getWorld()->increaseScore(m_score);
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->addObjects(new Explosion(getX(), getY(), getWorld()));
	}
}
void Alien::newPlan()
{
	if (getY() >= VIEW_HEIGHT - 1 || getY() <= 0 || m_length == 0)
	{
		if (getY() >= VIEW_HEIGHT - 1)
			travel_direction = 1;
		else if (getY() <= 0)
			travel_direction = 2;
		else if (m_length == 0)
		{
			int dirNum = randInt(0, 2);
			travel_direction = dirNum;
		}
		if (m_length >= 0)
		setLength(randInt(1, 32));
	}
}

void Alien::doSomething()
{
	if (!isAlive())
		return;
	newPlan();
	doDifferent();
	move();
}

Projectile::Projectile(int imageID, double startX, double startY, double damageAmt, StudentWorld * world, double deltaX, bool rotates, int imageDir)
	:DamageableObject(imageID, startX, startY,0,.5,1,world,1)
{
	m_damage = damageAmt;
	m_move = deltaX;
	m_rotates = rotates;
}
void Projectile::doSomething()
{
	if (!isAlive())
		return;
	Actor* aH = getWorld()->getCollidingAlien(this);
	if (aH != nullptr)
	{
		Alien* alienHit = static_cast<Alien*>(aH);
		alienHit->sufferDamage(m_damage, 1);
		setDead();
		return;
	}
	moveTo(getX() + m_move, getY());
	if(m_rotates)
	setDirection(20);
	Actor* aH2 = getWorld()->getCollidingAlien(this);
	if (aH2 != nullptr)
	{
		Alien* alienHit = static_cast<Alien*>(aH2);
		alienHit->sufferDamage(m_damage, 1);
		setDead();
		return;
	}

}
NachenBlaster::NachenBlaster(StudentWorld* world)
:DamageableObject(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world, 50)
	{
	cabbage_pts = 30;
	torCount = 5;
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
	:Actor(IID_STAR, x, y, 0, (randInt(5,50)/100.0), 3, world)
	{

	}
void Star::doSomething()
	{
	if (!isAlive())
		return;
		else
			moveTo(getX() -1, getY());
	}
Explosion::Explosion(double x, double y, StudentWorld* world)
	: Actor(IID_EXPLOSION, x, y, 0, 1, 0, world)
{

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
	: Projectile(IID_CABBAGE, x,y,2,world,7,true,0)
{

}


Flatulence_Torpedo::Flatulence_Torpedo(double x, double y, StudentWorld * world)
	:DamageableObject(IID_TORPEDO, x, y, 0, .5, 1, world,1)
{

}

void Flatulence_Torpedo::doSomething()
{
	if (!isAlive())
		return;
//	if (getWorld()->collideAllPossible(this))
	//	return;
	moveTo(getX() + 8, getY());
}


Turnip::Turnip(double x, double y, StudentWorld * world)
	:DamageableObject(IID_TURNIP, x, y, 0, .5, 1, world,1)
{

}

void Turnip::doSomething()
{
	if (!isAlive())
		return;
	//if (getWorld()->collideAllPossible(this))
	//	return;
	moveTo(getX() - 6, getY());
	setDirection(20);
}

Extra_Life_Goodie::Extra_Life_Goodie(double x, double y, StudentWorld * world)
	: Actor(IID_LIFE_GOODIE, x, y, 0, .5, 1, world)
{

}

void Extra_Life_Goodie::doSomething()
{
	if (!isAlive())
		return;
	/*if (getWorld()->collideAllPossible(this))
	{
		getWorld()->increaseScore(100);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->incLives();
		return;
	}*/
	moveTo(getX() - .75, getY() - .75);
}


Smallgon::Smallgon(double x,double y, StudentWorld* world)
	:Alien(IID_SMALLGON,x,y,0,1.5,1,world, 5 * (1 + (world->getLevel() - 1)*.1),2, 0, 5, 250)
{
}


Smoregon::Smoregon(double x, double y, StudentWorld * world)
	:Alien(IID_SMOREGON, x, y, 0, 1.5, 1, world, 5 * (1 + (world->getLevel() - 1)*.1),2, 0,5 ,250)
{

}

void Smoregon::doDifferent()
{
	Alien::doDifferent();
	if (checkInRange()) //#5 prototype
	{
		double chance = 1 / ((20 / (getWorld()->getLevel())) + 5);
		if (randInt(0, 100) < 30)
		{
			setSpeed(5);
			setLength(VIEW_WIDTH);
			setDir(0);
		}
	}
}

Snagglegon::Snagglegon(double x, double y, StudentWorld * world)
	:Alien(IID_SNAGGLEGON, x, y, 0, 1.5, 1, world, 10*(1+((world->getLevel()-1)*.1)), 1.75, 2, 15, 1000)
{
	setLength(-1);
}

void Snagglegon::doDifferent()
{
	if (checkInRange()) //#5 prototype
	{
		double chance = 1 / ((15 / (getWorld()->getLevel())) + 10); // ugly formula from spec
		if (randInt(0, 100) < 30)
		{
			Actor *torPtr = new Flatulence_Torpedo(getX() -14, getY(), getWorld());
			getWorld()->addObjects(torPtr);
			getWorld()->playSound(SOUND_TORPEDO);
			return;
		}
	}
}
