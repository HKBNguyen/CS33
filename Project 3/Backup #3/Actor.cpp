#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int startDirection, double size, int depth)
	: GraphObject(imageID, startX, startY, startDirection, size, depth)
{
	
}

/*StudentWorld* Actor::getWorld()
{
	return currWorld;
}*/


NachenBlaster::NachenBlaster()
		:Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0)
	{
		m_hp = 50;
		cabbage_pts = 50;
	}
NachenBlaster::~NachenBlaster()
	{

	}
void NachenBlaster::doSomething()
	{

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



Star::Star()
	:Actor(IID_STAR, randInt(0, VIEW_WIDTH - 1), randInt(0, VIEW_HEIGHT - 1), 0, randInt(.05, .5), 3)
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
		if (GraphObject::getX() < 0)
			alive = false;
		else
			moveTo();
	}
bool Star::isAlive()
	{
		return alive;
	}
