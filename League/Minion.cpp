#include "Minion.h"
#include "MinionWalkingState.h"
#include "Minionafkstate.h"
#include "MinionKnockupState.h"
#include "Tower.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;


Minion::Minion()
{
	Image = 0;
	miniontarget = 0;
	towertarget = 0;
	playertarget = 0;
	state = 0;
}
Minion::~Minion()
{
	Image = 0;
	miniontarget = 0;
	towertarget = 0;
	playertarget = 0;
	state = 0;
}
void Minion::Initialize()
{
	extern Map themap;

	state = new MinionWalkingState();				//allocated memory
	Dimensions.x = 75; Dimensions.y = 55;

}
void Minion::BotsideMidlaneMellePosition(int x)
{
	extern Map themap;
	int extramellelength = 50;
	MapPosition.x = themap.minionmidlane.p1.x + extramellelength + x; MapPosition.y = themap.minionmidlane.p1.y + (extramellelength*themap.minionmidlane.GetEdgeSlope()) + (-x / themap.minionmidlane.GetEdgeSlope());
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
}
void Minion::BotsideMidlaneRangePosition(int x)
{
	extern Map themap;
	int extrarangelength = 0;
	MapPosition.x = themap.minionmidlane.p1.x + extrarangelength + x; MapPosition.y = themap.minionmidlane.p1.y + (extrarangelength*themap.minionmidlane.GetEdgeSlope()) + (-x / themap.minionmidlane.GetEdgeSlope());
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
}
void Minion::TopsideMidlaneMellePosition(int x)
{
	extern Map themap;
	int extramellelength = -50;
	MapPosition.x = themap.minionmidlane.p2.x + extramellelength + x; MapPosition.y = themap.minionmidlane.p2.y + (extramellelength*themap.minionmidlane.GetEdgeSlope()) + (-x / themap.minionmidlane.GetEdgeSlope());
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
}
void Minion::TopsideMidlaneRangePosition(int x)
{
	extern Map themap;
	int extrarangelength = 0;
	MapPosition.x = themap.minionmidlane.p2.x + extrarangelength + x; MapPosition.y = themap.minionmidlane.p2.y + (extrarangelength*themap.minionmidlane.GetEdgeSlope()) + (-x / themap.minionmidlane.GetEdgeSlope());
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
}
void Minion::SetToMelle(bool top)//change image and stats
{
	extern SDL_Texture* minionmelle;
	extern SDL_Texture* redmelle;

	Initialize();
	if (top)
		Image = redmelle;
	else
		Image = minionmelle;
	VisionRange = 200;
	AttackRange = 50;
	damage = 12;
	maxhealth = 445;
	currenthealth = maxhealth;
}
void Minion::SetToRanged(bool top)
{
	extern SDL_Texture* minionranged;
	extern SDL_Texture* redranged;

	Initialize();
	if (top)
		Image = redranged;
	else
		Image = minionranged;
	VisionRange = 250;
	AttackRange = 200;
	damage = 25;
	maxhealth = 280;
	currenthealth = maxhealth;
}
void Minion::SetToCannon(bool top)
{
	extern SDL_Texture* minioncannon;
	extern SDL_Texture* redcannon;

	Initialize();
	if (top)
		Image = redcannon;
	else
		Image = minioncannon;
	VisionRange = 200;
	AttackRange = 150;
	damage = 40;
	maxhealth = 700;
	currenthealth = maxhealth;
}
void Minion::Update()
{
	HandleInputState();
	UpdateState();

	BlackHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x/2),static_cast<int>(MapPosition.y - Dimensions.y/2 -  10),static_cast<int>(Dimensions.x),5 };
	ColoredHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2),static_cast<int>(MapPosition.y - Dimensions.y/2 - 10),static_cast<int>(Dimensions.x),5 };
}
void Minion::HandleInputState()
{
	MinionState* tmpstate = 0;

	if (state == 0)
		cout << "minion state is zero" << endl;
	else
		tmpstate = state->handleinput(*this);

	if (tmpstate != 0)
	{
		delete state;
		state = tmpstate;
	}
}
void Minion::UpdateState()
{
	state->update(*this);
	
	if (attackcounter < 200)
		attackcounter++;
}
void Minion::PutMinionInAfkState()
{
	if (state == 0)
	{
		state = new Minionafkstate();
	}
	else
	{
		delete state;
		state = new Minionafkstate();
	}
}
void Minion::PutMinionInKnockupState(int theduration)
{
	if (state == 0)
	{
		state = new MinionKnockupState(theduration);
	}
	else
	{
		delete state;
		state = new MinionKnockupState(theduration);
	}
}
void Minion::ExitMinionAfkState()
{
	if (state == 0)
	{
		cout << "state is zero cant exit minionafk state" << endl;
	}
	else
	{
		delete state;
		state = new MinionWalkingState();
	}
}
void Minion::DamageMinion(double damage)
{
	extern vector<Minion> minions;
	extern vector<Tower> towers;
	extern Player theplayer;

	if (damage < 0)
	{
		cout << "negative damage!" << endl;
		return;
	}

	currenthealth -= damage;

	if (currenthealth <= 0)
	{
		for (int i = 0; i < minions.size(); i++)		//find its location in minions and delete it
		{
			if (MapPosition == minions[i].MapPosition && BotSide == minions[i].BotSide)
			{
				minions.erase(minions.begin() + i);
				for (int j = 0; j < minions.size(); j++)	//find minions who currently have minion targets 
				{
					if (minions[j].miniontarget != 0)
					{
						for (int k = 0; k < minions.size(); k++) //find the index of the minions target
						{
							if (minions[j].miniontarget->MapPosition == minions[k].MapPosition && minions[j].miniontarget->BotSide == minions[k].BotSide)
							{
								if (k > i) //if index is one thats shifted, this index minion is the wrong one, the right one is the index to its left
								{
									minions[j].miniontarget = &minions[k - 1];
									break;
								}
								else if (k == i)
								{
									minions[j].miniontarget = 0;
									break;
								}
							}
						}
					}
				}
				for (int j = 0; j < towers.size(); j++)	//find towers who currently have minion targets 
				{
					if (towers[j].miniontarget != 0)
					{
						for (int k = 0; k < minions.size(); k++) //find the index of the towers target
						{
							if (towers[j].miniontarget->MapPosition == minions[k].MapPosition && towers[j].miniontarget->BotSide == minions[k].BotSide)
							{
								if (k > i) //if index is one thats shifted, this index minion is the wrong one, the right one is the index to its left
								{
									towers[j].miniontarget = &minions[k - 1];
									break;
								}
								else if (k == i)
								{
									towers[j].miniontarget = 0;
									break;
								}
							}
						}
					}
				}
				if (theplayer.targetminion != 0)
				{
					for (int k = 0; k < minions.size(); k++) //find the index of the players target
					{
						if (theplayer.targetminion->MapPosition == minions[k].MapPosition && theplayer.targetminion->BotSide == minions[k].BotSide)
						{
							if (k > i) //if index is one thats shifted, this index minion is the wrong one, the right one is the index to its left
							{
								theplayer.targetminion = &minions[k - 1];
								break;
							}
							else if (k == i)
							{
								theplayer.targetminion = 0;
								break;
							}
						}
					}
				}
				return;
			}
		}
	}
}
void Minion::Print()
{
	extern SDL_Renderer* grender;
	extern Map themap;
	extern int screenwidth;
	extern int screenheight;

	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;

	/*print minion image*/
	SDL_Rect renderrect = { Position.x - (Dimensions.x / 2),Position.y - (Dimensions.y / 2),Dimensions.x,Dimensions.y };
	SDL_RenderCopy(grender, Image, 0, &renderrect);

	/*print minion health bars */
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
	if(BotSide)
		SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	else
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderFillRect(grender, &printcoloredhealthbar);
	
	/*print mid lane line*/
	Edge minionmidlaneprint;
	minionmidlaneprint.p1.x = themap.minionmidlane.p1.x - themap.PlayerCamera.x; minionmidlaneprint.p1.y = themap.minionmidlane.p1.y - themap.PlayerCamera.y;
	minionmidlaneprint.p2.x = themap.minionmidlane.p2.x - themap.PlayerCamera.x; minionmidlaneprint.p2.y = themap.minionmidlane.p2.y - themap.PlayerCamera.y;
	minionmidlaneprint.Print(grender);

	/*print minion attack speed circle*/
	double percent = static_cast<double>(attackcounter) / 200;
	double circlepercent = 365 - (365 * percent);
	for (int i = circlepercent; i < 365; i+=10)
	{
		int radius = 5;
		SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
		SDL_RenderDrawLine(grender, Position.x-50, Position.y-35, radius*cos((i*3.14)/180) + Position.x-50, radius*sin((i*3.14) / 180) + Position.y-35);
	}

	if (printminioninfo)
	{
		/*print minion vision range circle*/
		for (int i = 0; i < 360; i += 1)
		{
			SDL_RenderDrawPoint(grender, VisionRange*cos((i*3.14) / 180) + Position.x, VisionRange*sin((i*3.14) / 180) + Position.y);
			//SDL_RenderDrawLine(grender, VisionRanged*cos((i*3.14) / 180) + Position.x, VisionRanged*sin((i*3.14) / 180) + Position.y, Position.x, Position.y);
		}

		/*print mid lane line*/
		Edge minionmidlaneprint;
		minionmidlaneprint.p1.x = themap.minionmidlane.p1.x - themap.PlayerCamera.x; minionmidlaneprint.p1.y = themap.minionmidlane.p1.y - themap.PlayerCamera.y;
		minionmidlaneprint.p2.x = themap.minionmidlane.p2.x - themap.PlayerCamera.x; minionmidlaneprint.p2.y = themap.minionmidlane.p2.y - themap.PlayerCamera.y;
		minionmidlaneprint.Print(grender);
	}
}