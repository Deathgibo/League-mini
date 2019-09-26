#pragma once
#include "Minion.h"
#include "myglobal.h"
#include <iostream>
using namespace std;

class MinionState
{
public:
	virtual ~MinionState()
	{

	}
	virtual MinionState* handleinput(Minion& minion)//handles the input for the other states that state can go to
	{
		return 0;
	}
	virtual void update(Minion& minion)
	{

	}
	bool IsMinionWithinLane(Minion& minion, int range)
	{
		extern SDL_Renderer* grender;
		extern Map themap;

		Edge minionedge;
		myglobal global;
		int amount = 1000;

		/*see if were in the lane by finding collision point and extending it*/
		minionedge.p1.x = minion.MapPosition.x - amount;
		minionedge.p1.y = minion.MapPosition.y - -amount / themap.minionmidlane.GetEdgeSlope();
		minionedge.p2.x = minion.MapPosition.x + amount;
		minionedge.p2.y = minion.MapPosition.y + -amount / themap.minionmidlane.GetEdgeSlope();
	
		Vertex collisionpoint = global.gettwolinecollisionpoint(themap.minionmidlane.p1, themap.minionmidlane.p2, minionedge.p1, minionedge.p2);
		double distance;

		distance = sqrt(pow(collisionpoint.x - minion.MapPosition.x, 2) + pow(collisionpoint.y - minion.MapPosition.y, 2));
		
		if (distance <= range)
			return true;
		else
			return false;
	}
	void PlayersInRange()
	{

	}
	void TowersInRange()
	{

	}
	void MinionsInRange()
	{

	}
protected:
	bool changelanerange = true;	//trigger to give minion a random range when first walkingback to lane
	bool setdirection = true;		//sets the direction minion goes to when in walkingtolanestate
	bool directionright = true;		//determines what the direction is in walkingtolanestate
	bool chasing = false;			//to know if the minion is chasing in minionwalkingstate to see if we need to increase the lane range or not
	
	/*these are used to help keep trap of the closest minion so you dont have to refind closest*/
	int closestenemy = -1;			//0 is minion, 1 is player, 2 is tower
	Minion* closestminionsave = 0;
	Player* closestplayersave = 0;
	Tower* closesttowersave = 0;

	bool isnowinlane = false;
private:

};
