#pragma once
#include "PlayerAbility.h"
#include "Vertex.h"
#include "myglobal.h"
#include "Minion.h"
#include <string>

class BlitzcrankAbilities : public PlayerAbility
{
public:
	BlitzcrankAbilities(Player* player) : PlayerAbility(player)
	{
		qname = "Rocket Grab";
		qmana = 100;
		qstring.push_back("Blitzcrank fires his right hand to grab an opponent");
		qstring.push_back("on its path, dealing damage and dragging it back to him.");


		wname = "Overdrive";
		wmana = 75;
		wstring.push_back("Blitzcrank super charges himself to get dramatically");
		wstring.push_back("increased Movement and Attack Speed. He is temporarily");
		wstring.push_back("slowed after the effect ends.");

		ename = "Power Fist";
		emana = 25;
		estring.push_back("Blitzcrank charges up his fist to make his next attack");
		estring.push_back("sloweddouble damage and pop his target up in the air.");
		
		rname = "Static Field";
		rmana = 100;
		rstring.push_back("Enemies attacked by Blitzcrank are marked and take");
		rstring.push_back("lightning damage after 3 damage. Additionally,");
		rstring.push_back("Blitzcrank can activate this ability to damage");
		rstring.push_back("nearby enemies and silence them sfor 0.5 seconds.");


		pname = "Passive";
		pmana = 0;
		pstring.push_back("When Blitzcrank's life is brought below 20% health, he");
		pstring.push_back("activates Mana Barrier. This creates a mana shield equal");
		pstring.push_back("to 30% of his mana for 10 seconds. Mana Barrier can only");
		pstring.push_back("occur once every 90 seconds.");
	}
private:
	bool handgrab = false;
	virtual void activate(Player* player)
	{
		Q(player);
		W(player);
		E(player);
		R(player);
		P(player);
	}
	void Q(Player* player)
	{
		extern SDL_Texture* blitzhand;
		extern Map themap;
		extern bool QKeyState;
		extern bool ButtonDownOnce;
		extern bool ButtonLeftOnce;
		extern SDL_Renderer* grender;
		extern vector<Minion> minions;

		bool quickcastshown = showquickcast;

		showline(blitzgrabradius);

		if (ButtonLeftOnce && !qactivated && quickcastshown) //if we have the quickcast out and press down initialize the hook grab
		{
			SDL_GetMouseState(&xtarget, &ytarget);

			/*set booleans*/
			qactivated = true;
			handgrab = true;

			/*set hand starting position*/
			handrect = { static_cast<int>(player->MapPosition.x),static_cast<int>(player->MapPosition.y),60,60 };
			startinghookposition = player->MapPosition;

			/*find angle between place you clicked and playercenter*/
			double distance = sqrt(pow(xtarget - theplayer->Position.x, 2) + pow(ytarget - theplayer->Position.y, 2));
			hookangle = acos((xtarget - theplayer->Position.x) / distance);
			hookangle = (hookangle * 180) / 3.14;
			if (ytarget + themap.PlayerCamera.y  > startinghookposition.y)//if point is under center switch angle
			{
				hookangle = 360 - hookangle;
			}

			/*set precision so the hook doesnt round down*/
			xprecise = handrect.x;
			yprecise = handrect.y;
		}
		if (handgrab == true)
		{
			/*print hand  (the handrect is in the center, but when we render we substract so the image is actually the center) */
			SDL_Rect printrect = handrect;
			printrect.x = handrect.x - (handrect.w/2) - themap.PlayerCamera.x;
			printrect.y = handrect.y - (handrect.h / 2) - themap.PlayerCamera.y;
			SDL_RenderCopy(grender, blitzhand, 0, &printrect);

			if (!hookback)
			{
				/*move hand by the angle we set and print the string*/
				xprecise = UnitsPerFrame * cos((hookangle*3.14) / 180.0) + xprecise;
				yprecise = UnitsPerFrame * -sin((hookangle*3.14) / 180.0) + yprecise;
				handrect.x = xprecise;
				handrect.y = yprecise;
				
				SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
				SDL_RenderDrawLine(grender, handrect.x - themap.PlayerCamera.x, handrect.y - themap.PlayerCamera.y, theplayer->Position.x, theplayer->Position.y);

				/*see if hook hit any players or enemies if so put them in drag state where they just get dragged to this referenced position*/
				myglobal global;
				double closest = 5000;
				for (int i = 0; i < minions.size(); i++)
				{
					SDL_Rect minionrect = { minions[i].Position.x - (minions[i].Dimensions.x/2),minions[i].Position.y - (minions[i].Dimensions.y / 2),minions[i].Dimensions.x,minions[i].Dimensions.y };
					if (global.PointInsideRect(minionrect, handrect.x - themap.PlayerCamera.x, handrect.y - themap.PlayerCamera.y) && minions[i].BotSide != player->BotSide)
					{
						if (sqrt(pow(minionrect.x - handrect.x, 2) + pow(minionrect.y - handrect.y, 2)) < closest)
						{
							player->targetminion = &minions[i];
							hookback = true;
							hitsomething = true;
						}
					}
				}
				if (hitsomething && player->targetminion != 0)
				{
					player->targetminion->PutMinionInAfkState();
					player->targetminion->DamageMinion(hookdamage);//**could kill minion and destroy memory
				}

				/*see if hook has reached the distance needed fromt he initial center and its current center*/
				if (sqrt(pow(startinghookposition.x - handrect.x, 2) + pow(startinghookposition.y - handrect.y, 2)) > blitzgrabradius)
				{
					hookback = true;
					hitsomething = false;
				}
			}
			else
			{
				/*the hand needs to move back to player so find circle between hand and player and move it back and print the string*/
				double distance = sqrt(pow(theplayer->MapPosition.x - handrect.x, 2) + pow(theplayer->MapPosition.y - handrect.y, 2));
				hookangle = acos((theplayer->MapPosition.x - handrect.x) / distance);
				hookangle = (hookangle * 180) / 3.14;
				if (theplayer->MapPosition.y > handrect.y)
				{
					hookangle = 360 - hookangle;
				}
				xprecise = UnitsPerFrame * cos((hookangle*3.14) / 180) + handrect.x;
				yprecise = UnitsPerFrame * -sin((hookangle*3.14) / 180) + handrect.y;
				handrect.x = xprecise;
				handrect.y = yprecise;
				if (hitsomething && player->targetminion != 0)
				{
					player->targetminion->MapPosition.x = handrect.x;
					player->targetminion->MapPosition.y = handrect.y;
				}
				SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
				SDL_RenderDrawLine(grender, handrect.x - themap.PlayerCamera.x, handrect.y - themap.PlayerCamera.y, theplayer->Position.x, theplayer->Position.y);
				
				/*if the hook is back to the player end*/
				if (sqrt(pow(theplayer->MapPosition.x - handrect.x, 2) + pow(theplayer->MapPosition.y - handrect.y, 2)) < 20)//hook is coming back in
				{
					handgrab = false;
					qactivated = false;
					hookback = false;
					if (hitsomething && player->targetminion != 0)
					{
						player->targetminion->ExitMinionAfkState();
						hitsomething = false;
					}
				}
			}

		}

	}
	void W(Player* player)
	{
		extern bool WKeyState;
		if (WKeyState && !wactivated)
		{
			wactivated = true;
			player->MOVESPEED += speedincrease;
		}
		if (wactivated)
		{
			wcounter++;
			if (wcounter > speedduration)
			{
				wactivated = false;
				player->MOVESPEED -= speedincrease;
				wcounter = 0;
			}
		}
	}
	void E(Player* player)
	{
		extern bool RKeyState;
		
		if (RKeyState && !eactivate)
		{
			eactivate = true;
		}
		if (eactivate)
		{
			if (justautod && player->targetminion != 0)
			{
				player->targetminion->PutMinionInKnockupState(100);
				ecounter = eduration;
			}
			ecounter++;
			if (ecounter > eduration)
			{
				ecounter = 0;
				eactivate = false;
			}
		}
		//player sound
		//show hand animation
		//if he hits someone put them in stun state and knock up
		//else once time expires end
	}
	void R(Player* player)
	{
		extern vector<Minion> minions;
		extern bool TKeyState;

		if (TKeyState && !ractivated)
		{
			for (int i = 0; i < minions.size(); i++)
			{
				if (sqrt(pow(minions[i].MapPosition.x - player->MapPosition.x, 2) + pow(minions[i].MapPosition.y - player->MapPosition.y, 2)) <= ultradius
					&& minions[i].BotSide != player->BotSide)
				{
					minions[i].DamageMinion(ultdamage);
				}
			}
		}
		//play sound
		//show animation
		//do x damage to everyone in its radius and put silence effect on
	}
	void P(Player* player)
	{
		if (player->currenthealth < (.30*player->maxhealth) && !pactivated)
		{
			player->shield += player->maxhealth*shieldpercentage;
			pactivated = true;
		}
		if (pactivated)
		{
			shieldcounter++;
			if (shieldcounter > shieldduration)
			{
				shieldcounter = 0;
				player->shield = 0;
			}
		}
	}


private:
	
	/*blitz q variables*/
	double blitzgrabradius = 400;
	SDL_Rect handrect;
	int xtarget;						//the x where the hook is going to go
	int ytarget;						//the y where the hook is going to go
	Vertex startinghookposition;		//saved position of where you first spawned the hook
	double hookangle; 
	bool hookback = false;
	double UnitsPerFrame = 8;
	double xprecise;
	double yprecise;
	bool hitsomething = false;
	double hookdamage = 50;

	/*w variables*/
	int speedduration = 100;
	int wcounter = 0;
	int speedincrease = 2;

	/*eabilities*/
	int ecounter = 0;
	int eduration = 200;

	/*r variables*/
	int ultradius = 300;
	double ultdamage = 200;

	/*p variables*/
	int shieldduration = 500;
	int shieldcounter = 0;
	double shieldpercentage = .30;

	
};
