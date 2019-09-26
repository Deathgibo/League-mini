#include "MinionWalkToLaneState.h"
#include "MinionWalkingState.h"
#include <iostream>
using namespace std;

MinionWalkToLaneState::MinionWalkToLaneState()
{

}
MinionState* MinionWalkToLaneState::handleinput(Minion& minion)
{
	/*once your back to lane go to walking state*/
	if (isnowinlane)
	{
		minion.lanerangelimit = minion.startinglanerrangelimit;
		return new MinionWalkingState();
	}
	return 0;
}
void MinionWalkToLaneState::update(Minion& minion)
{
	extern vector<Minion> minions;
	extern vector<Tower> towers;
	extern Player theplayer;
	extern SDL_Renderer* grender;
	extern Map themap;

	bool withinrange = false;
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
	Vertex newcollisionpoint;
	int theamount = 75;
	if (directionright == false)
	{
		newcollisionpoint.x = collisionpoint.x + theamount;
		newcollisionpoint.y = collisionpoint.y - theamount / themap.minionmidlane.GetEdgeSlope();
	}
	else
	{
		newcollisionpoint.x = collisionpoint.x - theamount;
		newcollisionpoint.y = collisionpoint.y + theamount / themap.minionmidlane.GetEdgeSlope();
	}
	distance = sqrt(pow(newcollisionpoint.x - minion.MapPosition.x, 2) + pow(newcollisionpoint.y - minion.MapPosition.y, 2));
	if (distance <= minion.lanerangelimit)
	{
		changelanerange = true;
		setdirection = true;
		withinrange = true;
		isnowinlane = true;
	}
	else
	{
		if (changelanerange)
		{
			minion.lanerangelimit = rand() % minion.startinglanerrangelimit + 10;//**minions might walk too fast past the thing and distance will never be 0 for example
			changelanerange = false;
		}
		if (setdirection)
		{
			if (minion.MapPosition.x - collisionpoint.x < 0)
				directionright = false;
			else
				directionright = true;
			setdirection = false;
		}
		withinrange = false;
		isnowinlane = false;
	}

	if (!withinrange)
	{
		if (minion.MapPosition.x - newcollisionpoint.x < 0)
		{
			minion.MapPosition.x++;
			minion.MapPosition.y += -1 / themap.minionmidlane.GetEdgeSlope();
		}
		else
		{
			minion.MapPosition.x--;
			minion.MapPosition.y -= -1 / themap.minionmidlane.GetEdgeSlope();
		}
	}
}