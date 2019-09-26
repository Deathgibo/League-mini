#include "PlayerAbility.h"
#include "myglobal.h"
#include "Minion.h"
#include "Tower.h"
#include <iostream>
using namespace std;

PlayerAbility::PlayerAbility(Player* player)
{
	theplayer = player;
	justautod = false;
}
PlayerAbility::~PlayerAbility()
{

}
void PlayerAbility::activateabilities(Player* player)
{
	activate(player);
}
void PlayerAbility::activate(Player* player)
{

}
void PlayerAbility::SetStrings()
{

}
void PlayerAbility::AutoAttack(Player* player)
{
	extern bool AKeyState;
	extern vector<Minion> minions;
	extern vector<Tower> towers;
	extern bool ButtonRightOnce;
	extern bool ButtonLeftOnce;
	
	int x, y;
	SDL_GetMouseState(&x, &y);

	justautod = false;

	if (AKeyState)
	{
		autoselected = !autoselected;
	}
	if (autoselected)
	{
		player->autoing = true;
		//cursor is this
		if (ButtonLeftOnce)
		{
			automoving = true;
			autoselected = false;
			
			myglobal global;
			double closest = 5000;
			chasingminion = false;
			for (int i = 0; i < minions.size(); i++)
			{
				SDL_Rect minionrect = { minions[i].Position.x - (minions[i].Dimensions.x / 2),minions[i].Position.y - (minions[i].Dimensions.y / 2),minions[i].Dimensions.x,minions[i].Dimensions.y };
				if (global.PointInsideRect(minionrect, x, y) && minions[i].BotSide != player->BotSide)
				{
					if (sqrt(pow(minionrect.x - x, 2) + pow(minionrect.y - y, 2)) < closest)
					{
						player->targetminion = &minions[i];
						chasingminion = true;
						chasingtower = false;
					}
				}
			}
			for (int i = 0; i < towers.size(); i++)
			{
				if (global.PointInsideRect(towers[i].towerrect, x, y) && towers[i].BotSide != player->BotSide)
				{
						player->targettower = &towers[i];
						chasingtower = true;
						chasingminion = false;
						player->Move(towers[i].Position.x, towers[i].Position.y,1);
				}
			}
			if (!chasingminion && !chasingtower)
			{
				player->Move(x, y,1);
				automoving = false;
				player->targetminion = 0;
				player->targettower = 0;
			}
		}
		if (ButtonRightOnce)
		{
			autoselected = false;
		}
	}
	else
	{
		player->autoing = false;
	}
	if (automoving)
	{
		if (ButtonRightOnce)
		{
			automoving = false;
		}
		else
		{
			if (chasingtower && player->targettower != 0)
			{
				if (sqrt(pow(player->MapPosition.x - player->targettower->MapPosition.x, 2) + pow(player->MapPosition.y - player->targettower->MapPosition.y, 2)) < player->RANGE)
				{
					if (player->attackcounter >= 200)
					{
						//justautod = true;
						player->targettower->DamageTower(player->AD);
						player->attackcounter = 0;
					}
				}
			}
			else if (chasingminion && player->targetminion != 0)
			{
				//if minion isnt within your auto range move else stay still
				if (sqrt(pow(player->MapPosition.x - player->targetminion->MapPosition.x, 2) + pow(player->MapPosition.y - player->targetminion->MapPosition.y, 2)) > player->RANGE)
				{
					player->Move(player->targetminion->Position.x, player->targetminion->Position.y,1);
				}

				if (sqrt(pow(player->MapPosition.x - player->targetminion->MapPosition.x, 2) + pow(player->MapPosition.y - player->targetminion->MapPosition.y, 2)) < player->RANGE)
				{
					if (player->attackcounter >= 200)
					{
						justautod = true;
						player->targetminion->DamageMinion(player->AD);
						player->attackcounter = 0;
					}
				}
			}
		}
		//if your within range damage minion and quit
		if (!player->MovePath)
		{
			//automoving = false;
		}
	}

}
double PlayerAbility::getplayerx()
{
	return 0;
}
double PlayerAbility::getplayery()
{
	return 0;
}
Vertex PlayerAbility::getplayermiddle()
{
	Vertex lol(0, 0);
	return lol;
}
void PlayerAbility::showline(int radius)
{
	extern bool QKeyState;
	extern bool ButtonDownOnce;
	extern SDL_Renderer* grender;

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (quickcasted && QKeyState)
	{
		showquickcast = !showquickcast;
	}
	if (ButtonDownOnce)
	{
		showquickcast = false;
	}
	if (showquickcast)
	{
		double rad = sqrt(pow(x - theplayer->Position.x, 2) + pow(y - theplayer->Position.y, 2));
		if (rad == 0)
		{
			cout << "radius is 0";
			return;
		}
		double angle = acos((x - theplayer->Position.x) / rad);
		angle = (angle * 180) / 3.14;
		if (theplayer->Position.y < y)
		{
			angle = 360 - angle;
		}
		double thex = radius * cos((angle*3.14) / 180) + theplayer->Position.x;
		double they = radius * -sin((angle*3.14) / 180) + theplayer->Position.y;
		SDL_RenderDrawLine(grender, theplayer->Position.x, theplayer->Position.y, thex, they);
	}
}