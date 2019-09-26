#include "MinionWalkingState.h"
#include "AttackingMinionState.h"
#include "AttackingTowerState.h"
#include "MinionWalkToLaneState.h"
#include "AttackingPlayerState.h"
#include "Tower.h"


MinionWalkingState::MinionWalkingState()
{
	changelanerange = true;
	setdirection = true;
	directionright = true;
}
MinionState* MinionWalkingState::handleinput(Minion& minion)
{
	extern vector<Minion> minions;
	extern vector<Tower> towers;
	extern Player theplayer;

	bool enemyplayer = false;
	bool enemyminion = false;
	bool enemytower = false;

	/*if minion is outside lane limit go to walkback state*/
	if (chasing)			//if your chasing increase range limit else make it the smaller one
	{
		if (!IsMinionWithinLane(minion, minion.chasingrangelimit))
		{
			minion.playertarget = 0;
			return new MinionWalkToLaneState();
		}
	}
	else
	{
		if (!IsMinionWithinLane(minion, minion.simplerangelimit))
		{
			minion.playertarget = 0;
			return new MinionWalkToLaneState();
		}
	}

	/*see whats the closest thing in our vision and see if that thing is within attack range*/
	if (closestminionsave == 0 && closesttowersave == 0 && closestplayersave == 0)
	{
		return 0;
	}
	if (closestenemy == 0)
	{
		if (sqrt(pow(minion.MapPosition.x - closestminionsave->MapPosition.x, 2) + pow(minion.MapPosition.y - closestminionsave->MapPosition.y, 2)) < minion.AttackRange)
		{
			minion.miniontarget = closestminionsave;
			return new AttackingMinionState();
		}
	}
	if (closestenemy == 1)
	{
		if (sqrt(pow(minion.MapPosition.x - closestplayersave->MapPosition.x, 2) + pow(minion.MapPosition.y - closestplayersave->MapPosition.y, 2)) < minion.AttackRange)
		{
			minion.playertarget = closestplayersave;
			return new AttackingPlayerState();
		}
	}
	if (closestenemy == 2)
	{
		if (sqrt(pow(minion.MapPosition.x - closesttowersave->MapPosition.x, 2) + pow(minion.MapPosition.y - closesttowersave->MapPosition.y, 2)) < minion.AttackRange)
		{
			minion.towertarget = closesttowersave;
			return new AttackingTowerState();
		}
	}

	return 0;
}
void MinionWalkingState::update(Minion& minion)
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

	double closestdistance = 1000000;
	double closestminion = 2000000;
	double closesttower = 2000000;
	double closestplayer = 2000000;
	Minion* tmpminion = 0;
	Tower* tmptower = 0;


	/*find the closest, if any, minion within vision range and store that distance and minion*/
	bool chasingminion = false;
	for (int i = 0; i < minions.size(); i++)
	{
		if (minion.MapPosition != minions[i].MapPosition && minion.BotSide != minions[i].BotSide)
		{
			double d = pow(minion.MapPosition.x - minions[i].MapPosition.x, 2) + pow(minion.MapPosition.y - minions[i].MapPosition.y, 2);
			if (d < pow(minion.VisionRange, 2))
			{
				if (d < closestdistance)
				{
					closestdistance = d;
					closestminion = d;
					chasingminion = true;
					tmpminion = &minions[i];
				}
			}
		}
	}
	closestdistance = 1000000;
	
	/*find the closest, if any, tower within vision range and store that distance and tower*/
	bool chasingtower = false;
	for (int i = 0; i < towers.size(); i++)
	{
		if (minion.MapPosition != towers[i].MapPosition && minion.BotSide != towers[i].BotSide && towers[i].alive)
		{
			double d = pow(minion.MapPosition.x - towers[i].MapPosition.x, 2) + pow(minion.MapPosition.y - towers[i].MapPosition.y, 2);
			if (d < pow(minion.VisionRange, 2))
			{
				if (d < closestdistance)
				{
					chasingtower = true;
					closestdistance = d;
					closesttower = d;
					tmptower = &towers[i];
				}
			}
		}
	}
	/*find the closest, if any, player within vision range and store that distance and player*/
	bool chasingplayer = false;
	if (minion.BotSide != theplayer.BotSide)
	{
		double d = pow(minion.MapPosition.x - theplayer.MapPosition.x, 2) + pow(minion.MapPosition.y - theplayer.MapPosition.y, 2);
		if (d < pow(minion.VisionRange, 2))
		{
			chasingplayer = true;
			closestplayer = d;
		}
	}
	
	/*figure out which one was closest so you know what to follow*/
	double x = .5;
	double y = .5;
	if (closestplayer < closestminion && closestplayer < closesttower)
	{
		closestenemy = 1;
		closestplayersave = &theplayer;
		closestminionsave = 0;
		closestminionsave = 0;

		if (theplayer.MapPosition.x - minion.MapPosition.x < 0)
			x = -.5;
		if (theplayer.MapPosition.y - minion.MapPosition.y < 0)
			y = -.5;
		minion.MapPosition.x += x;
		minion.MapPosition.y += y;
	}
	else if (closestminion < closestplayer && closestminion < closesttower)
	{
		closestenemy = 0;
		closestminionsave = tmpminion;
		closestplayersave = 0;
		closesttowersave = 0;

		if (tmpminion->MapPosition.x - minion.MapPosition.x < 0)
			x = -.5;
		if (tmpminion->MapPosition.y - minion.MapPosition.y < 0)
			y = -.5;
		minion.MapPosition.x += x;
		minion.MapPosition.y += y; 
	}
	else if (closesttower < closestplayer && closesttower < closestminion)
	{
		closestenemy = 2;
		closesttowersave = tmptower;
		closestplayersave = 0;
		closestminionsave = 0;

		if (tmptower->MapPosition.x - minion.MapPosition.x < 0)
			x = -.5;
		if (tmptower->MapPosition.y - minion.MapPosition.y < 0)
			y = -.5;
		minion.MapPosition.x += x;
		minion.MapPosition.y += y; 
	}
	else
	{
		closestplayersave = 0;
		closestminionsave = 0;
		closesttowersave = 0;
		closestenemy = -1;
	}

	/*find out if chasing something so we can increase the lane range*/
	if (chasingminion || chasingplayer)
	{
		chasing = true;
	}
	else
	{
		chasing = false;
	}

	/*if you dont see any minions, towers, or players just run along the line*/
	if (!chasingminion && !chasingtower && !chasingplayer)
	{
		if (minion.BotSide)
		{
			minion.MapPosition.x++;
			minion.MapPosition.y += themap.minionmidlane.GetEdgeSlope();
		}
		else
		{
			minion.MapPosition.x--;
			minion.MapPosition.y -= themap.minionmidlane.GetEdgeSlope();
		}
	}

}