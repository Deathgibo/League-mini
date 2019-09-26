#pragma once
#include "myglobal.h"
#include "PlayerUI.h"
#include "Font.h"
#include "Item.h"
#include "PlayerAbility.h"
#include "BlitzcrankAbilities.h"
#include "Player.h"
#include <iostream>
using namespace std;


PlayerUI::PlayerUI()
{
	extern SDL_Texture* playeruibackground;
	extern SDL_Texture* blitzq;
	extern SDL_Texture* blitzw;
	extern SDL_Texture* blitze;
	extern SDL_Texture* blitzr;
	extern SDL_Texture* blitzpassive;
	extern SDL_Texture* flash;
	extern SDL_Texture* tp;
	extern SDL_Texture* wardingtotem;
	extern SDL_Texture* blitzicon;


	MainBackground = playeruibackground;
	Item1 = 0;
	Item2 = 0;
	Item3 = 0;
	Item4 = 0;
	Item5 = 0;
	Item6 = 0;
	VisionItem = wardingtotem;
	Summoner1 = tp;
	Summoner2 = flash;
	Ability1 = blitzq;
	Ability2 = blitzw;
	Ability3 = blitze;
	Ability4 = blitzr;
	AbilityPassive = blitzpassive;
	HealthBar = 0;
	ManaBar = 0;
	ChampionIcon = blitzicon;
	UpdateRects(1);
}

void PlayerUI::UpdateRects(bool overrideshowshopui)
{
	extern int screenwidth;
	extern int screenheight;
	extern Player theplayer;

	MainBackgroundRect = { 200 * screenwidth / 1000,833*screenheight/1000 ,500 * screenwidth / 1000,(1000-833) * screenheight / 1000 };
	Item1Rect = {MainBackgroundRect.x + 793*MainBackgroundRect.w/1000, MainBackgroundRect.y + 142* MainBackgroundRect.h/1000,42* MainBackgroundRect.w /1000,256* MainBackgroundRect.h/1000 };
	Item2Rect = { MainBackgroundRect.x + 844 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 142 * MainBackgroundRect.h / 1000,42 * MainBackgroundRect.w / 1000,256 * MainBackgroundRect.h / 1000 };
	Item3Rect = { MainBackgroundRect.x + 893 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 142 * MainBackgroundRect.h / 1000,42 * MainBackgroundRect.w / 1000,256 * MainBackgroundRect.h / 1000 };
	Item4Rect = { MainBackgroundRect.x + 793 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 437 * MainBackgroundRect.h / 1000,42 * MainBackgroundRect.w / 1000,256 * MainBackgroundRect.h / 1000 };
	Item5Rect = { MainBackgroundRect.x + 844 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 437 * MainBackgroundRect.h / 1000,42 * MainBackgroundRect.w / 1000,256 * MainBackgroundRect.h / 1000 };
	Item6Rect = { MainBackgroundRect.x + 893 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 437 * MainBackgroundRect.h / 1000,42 * MainBackgroundRect.w / 1000,256 * MainBackgroundRect.h / 1000 };
	ItemRects.clear();
	ItemRects.push_back(Item1Rect); ItemRects.push_back(Item2Rect); ItemRects.push_back(Item3Rect);
	ItemRects.push_back(Item4Rect); ItemRects.push_back(Item5Rect); ItemRects.push_back(Item6Rect);
	
	VisionItemRect = { MainBackgroundRect.x + 947 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 165 * MainBackgroundRect.h / 1000,35 * MainBackgroundRect.w / 1000,234 * MainBackgroundRect.h / 1000 };
	Summoner1Rect = { MainBackgroundRect.x + 720 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 128 * MainBackgroundRect.h / 1000,36 * MainBackgroundRect.w / 1000,218 * MainBackgroundRect.h / 1000 };
	Summoner2Rect = { MainBackgroundRect.x + 680 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 128 * MainBackgroundRect.h / 1000,36 * MainBackgroundRect.w / 1000,218 * MainBackgroundRect.h / 1000 };
	Ability4Rect = { MainBackgroundRect.x + 603 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 135 * MainBackgroundRect.h / 1000,58 * MainBackgroundRect.w / 1000,346 * MainBackgroundRect.h / 1000 };
	Ability3Rect = { MainBackgroundRect.x + 533 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 135 * MainBackgroundRect.h / 1000,58 * MainBackgroundRect.w / 1000,346 * MainBackgroundRect.h / 1000 };
	Ability2Rect = { MainBackgroundRect.x + 463 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 135 * MainBackgroundRect.h / 1000,58 * MainBackgroundRect.w / 1000,346 * MainBackgroundRect.h / 1000 };
	Ability1Rect = { MainBackgroundRect.x + 393 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 135 * MainBackgroundRect.h / 1000,58 * MainBackgroundRect.w / 1000,346 * MainBackgroundRect.h / 1000 };
	AbilityPassiveRect = { MainBackgroundRect.x + 340 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 128 * MainBackgroundRect.h / 1000,36 * MainBackgroundRect.w / 1000,218 * MainBackgroundRect.h / 1000 };
	HealthBarRect = { MainBackgroundRect.x + 340 * MainBackgroundRect.w / 1000,MainBackgroundRect.y + 644 * MainBackgroundRect.h / 1000, 416 * MainBackgroundRect.w / 1000,120 * MainBackgroundRect.h / 1000 };
	ManaBarRect = { MainBackgroundRect.x + 340 * MainBackgroundRect.w / 1000,MainBackgroundRect.y + 780 * MainBackgroundRect.h / 1000, 416 * MainBackgroundRect.w / 1000,120 * MainBackgroundRect.h / 1000 };
	int widthpernumber = 10 * MainBackgroundRect.w / 1000;
	HealthAmountRect = { HealthBarRect.x + (HealthBarRect.w/2) - widthpernumber*(11/2), MainBackgroundRect.y + 654 * MainBackgroundRect.h / 1000, widthpernumber * 11, 120 * MainBackgroundRect.h / 1000 };
	ManaAmountRect = { ManaBarRect.x + (ManaBarRect.w / 2) - widthpernumber * (10 / 2) , MainBackgroundRect.y + 790 * MainBackgroundRect.h / 1000, widthpernumber * 10, 120 * MainBackgroundRect.h / 1000 };
	ChampionIconRect = { MainBackgroundRect.x + 197 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 173 * MainBackgroundRect.h / 1000,102 * MainBackgroundRect.w / 1000,617 * MainBackgroundRect.h / 1000 };

	GoldRect = { MainBackgroundRect.x + 825 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 776 * MainBackgroundRect.h / 1000,41 * MainBackgroundRect.w / 1000,155 * MainBackgroundRect.h / 1000 };
	GoldAmountRect = { MainBackgroundRect.x + 875 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 795 * MainBackgroundRect.h / 1000,48 * MainBackgroundRect.w / 1000,155 * MainBackgroundRect.h / 1000 };
	PlayerLevelRect = { MainBackgroundRect.x + 269 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 770 * MainBackgroundRect.h / 1000,20 * MainBackgroundRect.w / 1000,115 * MainBackgroundRect.h / 1000 };

	//stats
	UpdatePlayerStats();
}
void PlayerUI::UpdatePlayerStats()
{
	extern int screenwidth;
	extern int screenheight;
	extern Player theplayer;

	//stats
	int width = 20;
	int height = 143;
	int amountheight = 165;
	int widthpernumber2 = 15 * MainBackgroundRect.w / 1000;
	
	ADRect = { MainBackgroundRect.x + 17 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 173 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	ADAmountRect = { MainBackgroundRect.x + 44 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 183 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.AD)).size()),amountheight * MainBackgroundRect.h / 1000 };

	APRect = { MainBackgroundRect.x + 105 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 173 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	APAmountRect = { MainBackgroundRect.x + 134 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 183 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.AP)).size()),amountheight * MainBackgroundRect.h / 1000 };

	ArmorRect = { MainBackgroundRect.x + 17 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 376 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	ArmorAmountRect = { MainBackgroundRect.x + 44 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 386 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.ARMOR)).size()),amountheight * MainBackgroundRect.h / 1000 };

	MrRect = { MainBackgroundRect.x + 105 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 376 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	MrAmountRect = { MainBackgroundRect.x + 134 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 386 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.MR)).size()),amountheight * MainBackgroundRect.h / 1000 };

	AttackspeedRect = { MainBackgroundRect.x + 17 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 576 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	AttackSpeedAmountRect = { MainBackgroundRect.x + 44 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 586 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.ATKSPEED)).size()),amountheight * MainBackgroundRect.h / 1000 };

	CDRRect = { MainBackgroundRect.x + 105 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 576 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	CDRAmountRect = { MainBackgroundRect.x + 134 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 586 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.CDR)).size()),amountheight * MainBackgroundRect.h / 1000 };

	MoveSpeedRect = { MainBackgroundRect.x + 105 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 776 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000,height * MainBackgroundRect.h / 1000 };
	MoveSpeedAmountRect = { MainBackgroundRect.x + 134 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 786 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.MOVESPEED)).size()),amountheight * MainBackgroundRect.h / 1000 };

	RangeRect = { MainBackgroundRect.x + 17 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 776 * MainBackgroundRect.h / 1000,width * MainBackgroundRect.w / 1000, height * MainBackgroundRect.h / 1000 };
	RangeAmountRect = { MainBackgroundRect.x + 44 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 786 * MainBackgroundRect.h / 1000,widthpernumber2 * static_cast<int>(to_string(static_cast<int>(theplayer.RANGE)).size()), amountheight * MainBackgroundRect.h / 1000 };
}
void PlayerUI::Print(SDL_Renderer* grender)
{
	extern SDL_Texture* ImagePickAxe;
	extern SDL_Texture* goldimage;
	extern SDL_Texture* movespeedicon;
	extern SDL_Texture* rangeicon;
	extern SDL_Texture* cdricon;
	extern SDL_Texture* mricon;
	extern SDL_Texture* armoricon;
	extern SDL_Texture* attackspeedicon;
	extern SDL_Texture* adicon;
	extern SDL_Texture* apicon;
	extern Player theplayer;
	
	int x, y;
	SDL_GetMouseState(&x, &y);

	UpdatePlayerStats();

	SDL_RenderCopy(grender, ChampionIcon, 0, &ChampionIconRect);
	SDL_RenderCopy(grender, MainBackground, 0, &MainBackgroundRect);
	for (int i = 0; i < theplayer.items.size(); i++)
	{
		SDL_RenderCopy(grender, theplayer.items[i]->image, 0, &ItemRects[i]);
	}

	SDL_RenderCopy(grender, VisionItem, 0, &VisionItemRect);

	int widthpernumber = 15 * MainBackgroundRect.w / 1000;
	int digits = to_string(theplayer.gold).size();
	GoldAmountRect = { MainBackgroundRect.x + 905 * MainBackgroundRect.w / 1000 - ((widthpernumber*digits)/2), MainBackgroundRect.y + 795 * MainBackgroundRect.h / 1000, widthpernumber*digits ,155 * MainBackgroundRect.h / 1000 };
	Font gfont(to_string(theplayer.gold), "yellow");
	gfont.Print(grender, GoldAmountRect);

	SDL_RenderCopy(grender, goldimage, 0, &GoldRect);
	SDL_RenderCopy(grender, Summoner1, 0, &Summoner1Rect);
	SDL_RenderCopy(grender, Summoner2, 0, &Summoner2Rect);
	SDL_RenderCopy(grender, Ability1, 0, &Ability1Rect);
	SDL_RenderCopy(grender, Ability2, 0, &Ability2Rect);
	SDL_RenderCopy(grender, Ability3, 0, &Ability3Rect);
	SDL_RenderCopy(grender, Ability4, 0, &Ability4Rect);
	SDL_RenderCopy(grender, AbilityPassive, 0, &AbilityPassiveRect);

	SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
	double percent = theplayer.currenthealth / theplayer.maxhealth;
	SDL_Rect printhealthbarrect = HealthBarRect;
	printhealthbarrect.w = percent * HealthBarRect.w;
	SDL_RenderFillRect(grender, &printhealthbarrect);
	SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
	SDL_Rect shieldbarrect = { printhealthbarrect.x + printhealthbarrect.w,printhealthbarrect.y,(theplayer.shield/theplayer.maxhealth)*HealthBarRect.w,printhealthbarrect.h };
	SDL_RenderFillRect(grender, &shieldbarrect);
	SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	SDL_RenderFillRect(grender, &ManaBarRect);
	/*health*/
	string health = to_string(static_cast<int>(theplayer.currenthealth));
	string maxhealth = to_string(static_cast<int>(theplayer.maxhealth));
	health.append(" / ");
	health.append(maxhealth);
	gfont.Initialize(health, "white");
	gfont.Print(grender, HealthAmountRect);
	/*mana*/
	string mana = to_string(static_cast<int>(theplayer.currentmana));
	string maxmana = to_string(static_cast<int>(theplayer.maxmana));
	mana.append(" / "); mana.append(maxmana);
	gfont.Initialize(mana, "white");
	gfont.Print(grender, ManaAmountRect);
	/*player level*/
	gfont.Initialize(to_string(theplayer.playerlevel), "white");
	gfont.Print(grender, PlayerLevelRect);

	//stats
	SDL_RenderCopy(grender, adicon, 0, &ADRect);
	SDL_RenderCopy(grender, apicon, 0, &APRect);
	SDL_RenderCopy(grender, armoricon, 0, &ArmorRect);
	SDL_RenderCopy(grender, mricon, 0, &MrRect);
	SDL_RenderCopy(grender, attackspeedicon, 0, &AttackspeedRect);
	SDL_RenderCopy(grender, cdricon, 0, &CDRRect);
	SDL_RenderCopy(grender, rangeicon, 0, &RangeRect);
	SDL_RenderCopy(grender, movespeedicon, 0, &MoveSpeedRect);

	gfont.Initialize(to_string(static_cast<int>(theplayer.AD)), "white");
	gfont.Print(grender, ADAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.AP)), "white");
	gfont.Print(grender, APAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.ARMOR)), "white");
	gfont.Print(grender, ArmorAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.MR)), "white");
	gfont.Print(grender, MrAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.ATKSPEED)), "white");
	gfont.Print(grender, AttackSpeedAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.CDR)), "white");
	gfont.Print(grender, CDRAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.RANGE)), "white");
	gfont.Print(grender, RangeAmountRect);
	gfont.Initialize(to_string(static_cast<int>(theplayer.MOVESPEED)), "white");
	gfont.Print(grender, MoveSpeedAmountRect);

	myglobal global;
	for (int i = 0; i < ItemRects.size(); i++)
	{
		if (global.PointInsideRect(ItemRects[i], x, y) && theplayer.items.size() > i)
		{
			if (theplayer.items[i]->image != 0)
			{
				PrintSmallDescription(ItemRects[i], *theplayer.items[i]);
			}
		}
	}
	/*ability descriptions*/
	if (global.PointInsideRect(Ability1Rect, x, y))
	{
		PrintAbilityDescription(Ability1Rect,'q');
	}
	if (global.PointInsideRect(Ability2Rect, x, y))
	{
		PrintAbilityDescription(Ability2Rect, 'w');
	}
	if (global.PointInsideRect(Ability3Rect, x, y))
	{
		PrintAbilityDescription(Ability3Rect, 'e');
	}
	if (global.PointInsideRect(Ability4Rect, x, y))
	{
		PrintAbilityDescription(Ability4Rect, 'r');
	}
	if (global.PointInsideRect(AbilityPassiveRect, x, y))
	{
		PrintAbilityDescription(AbilityPassiveRect, 'p');
	}
}
void PlayerUI::Update()
{
	extern Player theplayer;
	extern SDL_Renderer* grender;
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (guihelpergetxy)
	{
		extern SDL_Texture* Infinityedgeimage;
		extern SDL_Renderer* grender;
		SDL_RenderCopy(grender, Infinityedgeimage, 0, &Item1Rect);

		myglobal g1;
		g1.UILocation(MainBackgroundRect, Item1Rect);
	}
}
void PlayerUI::PrintSmallDescription(SDL_Rect therect, Item theitem)
{
	extern SDL_Renderer* grender;
	int x, y;
	SDL_GetMouseState(&x, &y);
	extern SDL_Texture* descriptionbox;
	extern SDL_Texture* goldimage;

	int basic = theitem.descriptionstring.size();
	int passives = theitem.descriptionuniquestring.size();

	SDL_Rect DescriptionRect = { 0,0,0,0 };
	DescriptionRect.x = 1150 * MainBackgroundRect.w / 1000;
	DescriptionRect.w = 400 * MainBackgroundRect.w / 1000;
	int YIncrement = 20 * DescriptionRect.w / 1000;
	int extraamount = (passives == 0) ? 0 : 4 * YIncrement;
	//DescriptionRect.h = (200 * DescriptionRect.w / 1000) + (2 * YIncrement*basic) + (2.5*YIncrement* passives) + extraamount;
	int amount = (DescriptionRect.y) + (40 * DescriptionRect.w / 1000) + (50 * DescriptionRect.w / 1000) + YIncrement + (100 * DescriptionRect.h / 1000);
	DescriptionRect.h = amount + (3 * YIncrement*basic) + extraamount + (2.5*YIncrement* passives);
	DescriptionRect.y = (5000 * MainBackgroundRect.h / 1000) - DescriptionRect.h;
	SDL_RenderCopy(grender, descriptionbox, 0, &DescriptionRect);

	SDL_Rect ItemImageRect = { 0,0,0,0 };
	ItemImageRect.x = DescriptionRect.x + 30 * DescriptionRect.w / 1000;
	ItemImageRect.y = DescriptionRect.y + 30 * DescriptionRect.w / 1000;
	ItemImageRect.w = 150 * DescriptionRect.w / 1000;
	ItemImageRect.h = 150 * DescriptionRect.w / 1000;
	//SDL_RenderCopy(grender, theitem.image, 0, &ItemImageRect);

	SDL_Rect ItemNameRect = { 0,0,0,0 };
	ItemNameRect.x = DescriptionRect.x + 30 * DescriptionRect.w / 1000;
	ItemNameRect.y = DescriptionRect.y + 30 * DescriptionRect.w / 1000;
	int widthperletter = 25 * DescriptionRect.w / 1000;
	ItemNameRect.w = widthperletter * theitem.name.size();
	ItemNameRect.h = 50 * DescriptionRect.w / 1000;
	Font tmpfont(theitem.name, "yellow");
	tmpfont.Print(grender, ItemNameRect);

	SDL_Rect GoldIconRect = { 0,0,0,0 };
	GoldIconRect.x = ItemNameRect.x + ItemImageRect.w + 550 * DescriptionRect.w / 1000;
	GoldIconRect.y = ItemNameRect.y;
	GoldIconRect.w = widthperletter * 4;
	GoldIconRect.h = ItemNameRect.h;
	SDL_RenderCopy(grender, goldimage, 0, &GoldIconRect);

	SDL_Rect GoldTextRect = { 0,0,0,0 };
	GoldTextRect.x = ItemNameRect.x + ItemImageRect.w + 680 * DescriptionRect.w / 1000;
	GoldTextRect.y = ItemNameRect.y;
	int widthpernumber = 17 * DescriptionRect.w / 1000;
	GoldTextRect.w = widthpernumber * 6;
	GoldTextRect.h = ItemNameRect.h;
	tmpfont.Initialize(to_string(theitem.SELLCOST), "yellow");
	tmpfont.Print(grender, GoldTextRect);

	string thestring;
	SDL_Rect statrect = { 0,0,0,0 };
	statrect.x = ItemNameRect.x + 10 * DescriptionRect.w / 1000;
	statrect.y = ItemNameRect.y + ItemNameRect.h + YIncrement + 100*DescriptionRect.h/1000;
	statrect.w = 2 * YIncrement;
	statrect.h = 2 * YIncrement;

	for (int i = 0; i < theitem.descriptionstring.size(); i++)
	{
		thestring = theitem.descriptionstring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
		statrect.y += statrect.h + YIncrement;
	}
	
	statrect.y += 2 * YIncrement;



	for (int i = 0; i < theitem.descriptionuniquestring.size(); i++)
	{
		thestring = theitem.descriptionuniquestring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect); statrect.y += statrect.h + YIncrement / 2;
	}

	tmpfont.FreeTexture();
}
void PlayerUI::PrintAbilityDescription(SDL_Rect therect, char ability)
{
	extern SDL_Renderer* grender;
	int x, y;
	SDL_GetMouseState(&x, &y);
	extern SDL_Texture* descriptionbox;
	extern SDL_Texture* goldimage;
	extern Player theplayer;
	
	int basic;
	switch (ability)
	{
	case 'q': 	basic = theplayer.player1abilities->qstring.size(); break;
	case 'w':	basic = theplayer.player1abilities->wstring.size(); break;
	case 'e': 	basic = theplayer.player1abilities->estring.size(); break;
	case 'r': 	basic = theplayer.player1abilities->rstring.size(); break;
	case 'p': 	basic = theplayer.player1abilities->pstring.size(); break;
	}

	SDL_Rect DescriptionRect = { 0,0,0,0 };
	DescriptionRect.x = 670 * MainBackgroundRect.w / 1000;
	DescriptionRect.w = 550 * MainBackgroundRect.w / 1000;
	int YIncrement = 20 * DescriptionRect.w / 1000;
	int amount = ((DescriptionRect.y + 30 * DescriptionRect.w / 1000) + (50 * DescriptionRect.w / 1000)) + (50 * DescriptionRect.w / 1000) + (YIncrement)+(10 * DescriptionRect.w / 1000);
	DescriptionRect.h = amount + (2.5 * YIncrement*basic);
	DescriptionRect.y = (4700 * MainBackgroundRect.h / 1000) - DescriptionRect.h;
	SDL_RenderCopy(grender, descriptionbox, 0, &DescriptionRect);


	SDL_Rect ItemNameRect = { 0,0,0,0 };
	ItemNameRect.x = DescriptionRect.x + 30 * DescriptionRect.w / 1000;
	ItemNameRect.y = DescriptionRect.y + 30 * DescriptionRect.w / 1000;
	int widthperletter = 25 * DescriptionRect.w / 1000;
	switch (ability)
	{
	case 'q': ItemNameRect.w = widthperletter * theplayer.player1abilities->qname.size(); break;
	case 'w': ItemNameRect.w = widthperletter * theplayer.player1abilities->wname.size(); break;
	case 'e': ItemNameRect.w = widthperletter * theplayer.player1abilities->ename.size(); break;
	case 'r': ItemNameRect.w = widthperletter * theplayer.player1abilities->rname.size(); break;
	case 'p': ItemNameRect.w = widthperletter * theplayer.player1abilities->pname.size(); break;
	}
	ItemNameRect.h = 50 * DescriptionRect.w / 1000;
	string name;
	switch (ability)
	{
	case 'q': name = theplayer.player1abilities->qname; break;
	case 'w': name = theplayer.player1abilities->wname; break;
	case 'e': name = theplayer.player1abilities->ename; break;
	case 'r': name = theplayer.player1abilities->rname; break;
	case 'p': name = theplayer.player1abilities->pname; break;
	}
	Font tmpfont(name, "yellow");
	tmpfont.Print(grender, ItemNameRect);

	SDL_Rect ManaCostRect = { 0,0,0,0 };
	ManaCostRect.x = ItemNameRect.x;
	ManaCostRect.y = ItemNameRect.y + 50 * DescriptionRect.w / 1000;
	ManaCostRect.h = ItemNameRect.h;
	string manastring = "Mana Cost: ";
	switch (ability)
	{
	case 'q': manastring.append(to_string(theplayer.player1abilities->qmana)); break;
	case 'w': manastring.append(to_string(theplayer.player1abilities->wmana)); break;
	case 'e': manastring.append(to_string(theplayer.player1abilities->emana)); break;
	case 'r': manastring.append(to_string(theplayer.player1abilities->rmana)); break;
	case 'p': manastring.append(to_string(theplayer.player1abilities->pmana)); break;
	}
	widthperletter = 18 * DescriptionRect.w / 1000;
	ManaCostRect.w = widthperletter * manastring.size();
	tmpfont.Initialize(manastring, "white");
	tmpfont.Print(grender, ManaCostRect);
	

	string thestring;
	SDL_Rect statrect = { 0,0,0,0 };
	statrect.x = ItemNameRect.x + 10 * DescriptionRect.w / 1000;
	statrect.y = ManaCostRect.y + ManaCostRect.h + YIncrement + 10 * DescriptionRect.w / 1000;
	statrect.w = 2 * YIncrement;
	statrect.h = 2 * YIncrement;

	switch (ability)
	{
	case 'q': 
		for (int i = 0; i < theplayer.player1abilities->qstring.size(); i++)
		{
			thestring = theplayer.player1abilities->qstring[i];
			statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
			statrect.y += statrect.h + YIncrement / 2;
		}
		break;
	case 'w':
		for (int i = 0; i < theplayer.player1abilities->wstring.size(); i++)
		{
			thestring = theplayer.player1abilities->wstring[i];
			statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
			statrect.y += statrect.h + YIncrement / 2;
		}
		break;
	case 'e': 
		for (int i = 0; i < theplayer.player1abilities->estring.size(); i++)
		{
			thestring = theplayer.player1abilities->estring[i];
			statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
			statrect.y += statrect.h + YIncrement / 2;
		}
		break;
	case 'r': 
		for (int i = 0; i < theplayer.player1abilities->rstring.size(); i++)
		{
			thestring = theplayer.player1abilities->rstring[i];
			statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
			statrect.y += statrect.h + YIncrement / 2;
		}
		break;
	case 'p': 
		for (int i = 0; i < theplayer.player1abilities->pstring.size(); i++)
		{
			thestring = theplayer.player1abilities->pstring[i];
			statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
			statrect.y += statrect.h + YIncrement / 2;

		}
		break;
	}

	tmpfont.FreeTexture();
}