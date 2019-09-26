#include "Tower.h"
#include "Map.h"
#include "TowerIdleState.h"
#include "TowerState.h"
#include <iostream>
using namespace std;

Tower::Tower()
{
	extern Map themap;

	state = new TowerIdleState();
	maxhealth = 10000;
	currenthealth = maxhealth;
	damage = 200;
	Range = 250;
	MapPosition.x = 0; MapPosition.y = 0;
	Position.x = MapPosition.x - themap.PlayerCamera.x; Position.y = MapPosition.y - themap.PlayerCamera.y;
	miniontarget = 0;
	playertarget = 0;

}
void Tower::Update()
{
	if (alive)
	{
		HandleInputState();
		UpdateState();
	}
	towerrect = { static_cast<int>(Position.x) - 55,static_cast<int>(Position.y) - 150,100,200 };

}
void Tower::Print()
{
	extern SDL_Renderer* grender;
	extern Map themap;
	extern SDL_Texture* brokenturret;

	Position.x = MapPosition.x - themap.PlayerCamera.x; Position.y = MapPosition.y - themap.PlayerCamera.y;
	int numberx = 55;
	int numbery = 100;
	BlackHealthBar = { static_cast<int>(MapPosition.x - numberx),static_cast<int>(MapPosition.y - numbery),static_cast<int>(100),5 };
	ColoredHealthBar = { static_cast<int>(MapPosition.x - numberx),static_cast<int>(MapPosition.y - numbery),static_cast<int>(100),5 };

	/*print vision*/
	for (int i = 0; i < 360; i += 1)
	{
		SDL_RenderDrawPoint(grender, Range*cos((i*3.14) / 180) + Position.x, Range*sin((i*3.14) / 180) + Position.y);
	}
	
	/*print health bar*/
	SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	SDL_Rect printblackhealthbar = { BlackHealthBar.x - themap.PlayerCamera.x,BlackHealthBar.y - themap.PlayerCamera.y,BlackHealthBar.w,BlackHealthBar.h };
	SDL_Rect printcoloredhealthbar{ ColoredHealthBar.x - themap.PlayerCamera.x,ColoredHealthBar.y - themap.PlayerCamera.y,ColoredHealthBar.w,ColoredHealthBar.h };
	double healthperctent = (currenthealth / maxhealth)*printcoloredhealthbar.w;
	printcoloredhealthbar.w = healthperctent;
	if (currenthealth <= 0)
	{
		printcoloredhealthbar.w = 0;
	}
	SDL_RenderFillRect(grender, &printblackhealthbar);
	if (BotSide)
		SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	else
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderFillRect(grender, &printcoloredhealthbar);

	/*print attack speed*/
	double percent = static_cast<double>(attackcounter) / 200;
	double circlepercent = 365 - (365 * percent);
	for (int i = circlepercent; i < 365; i += 10)
	{
		int radius = 5;
		SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
		SDL_RenderDrawLine(grender, Position.x - 70, printblackhealthbar.y + (printblackhealthbar.h/2), radius*cos((i*3.14) / 180) + Position.x - 70, radius*sin((i*3.14) / 180) + printblackhealthbar.y + (printblackhealthbar.h / 2));
	}
	if (!alive)
	{
		towerrect = { static_cast<int>(Position.x) - 55,static_cast<int>(Position.y) - 150,100,200 };
		SDL_RenderCopy(grender, brokenturret, 0, &towerrect);
	}
}
void Tower::HandleInputState()
{
	TowerState* tmpstate = 0;
	if (state == 0)
	{
		cout << "state is zero";
	}
	else
	{
		tmpstate = state->handleinput(*this);
	}
	if (tmpstate != 0)
	{
		delete state;
		state = tmpstate;
	}
}
void Tower::UpdateState()
{
	state->update(*this);
	if (attackcounter < 200)
		attackcounter++;
}
void Tower::DamageTower(double x)
{
	extern vector<Minion> minions;
	extern vector<Tower> towers;

	if (damage < 0)
	{
		cout << "negative damage!" << endl;
		return;
	}
	currenthealth -= damage;
	if (currenthealth <= 0)
	{
		alive = false;
	}
	/*if (currenthealth <= 0)
	{
		for (int i = 0; i < towers.size(); i++)		//find its location in minions and delete it
		{
			if (MapPosition == towers[i].MapPosition && BotSide == towers[i].BotSide)
			{
				towers.erase(towers.begin() + i);
				for (int j = 0; j < minions.size(); j++)	//find minions who currently have turret targets 
				{
					if (minions[j].towertarget != 0)
					{
						for (int k = 0; k < towers.size(); k++) //find the index of the minions target
						{
							if (minions[j].towertarget->MapPosition == towers[k].MapPosition && minions[j].towertarget->BotSide == towers[k].BotSide)
							{
								if (k > i) //if index is one thats shifted, this index minion is the wrong one, the right one is the index to its left
								{
									minions[j].towertarget = &towers[k - 1];
									break;
								}
								else if (k == i)
								{
									minions[j].towertarget = 0;
									break;
								}
							}
						}
					}
				}
				return;
			}
		}
	}*/
}