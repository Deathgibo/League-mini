#pragma once
#include <SDL.h>
#include <vector>

class Item;

class PlayerUI
{
public:
	PlayerUI();
	void UpdateRects(bool overrideshowshopui = 0);
	void UpdatePlayerStats();
	void PrintSmallDescription(SDL_Rect therect, Item theitem);
	void PrintAbilityDescription(SDL_Rect therect, char ability);
	void Update();
	void Print(SDL_Renderer* grender);
	SDL_Texture* MainBackground;
	SDL_Texture* Item1;
	SDL_Texture* Item2;
	SDL_Texture* Item3;
	SDL_Texture* Item4;
	SDL_Texture* Item5;
	SDL_Texture* Item6;
	SDL_Texture* VisionItem;
	SDL_Texture* Summoner1;
	SDL_Texture* Summoner2;
	SDL_Texture* Ability1;
	SDL_Texture* Ability2;
	SDL_Texture* Ability3;
	SDL_Texture* Ability4;
	SDL_Texture* AbilityPassive;
	SDL_Texture* HealthBar;
	SDL_Texture* ManaBar;
	SDL_Texture* ChampionIcon;
	
	SDL_Rect MainBackgroundRect;
	SDL_Rect Item1Rect;
	SDL_Rect Item2Rect;
	SDL_Rect Item3Rect;
	SDL_Rect Item4Rect;
	SDL_Rect Item5Rect;
	SDL_Rect Item6Rect;
	vector<SDL_Rect> ItemRects;
	SDL_Rect VisionItemRect;
	SDL_Rect Summoner1Rect;
	SDL_Rect Summoner2Rect;
	SDL_Rect Ability1Rect;
	SDL_Rect Ability2Rect;
	SDL_Rect Ability3Rect;
	SDL_Rect Ability4Rect;
	SDL_Rect AbilityPassiveRect;
	SDL_Rect HealthBarRect;
	SDL_Rect ManaBarRect;
	SDL_Rect ChampionIconRect;
	SDL_Rect GoldRect;
	SDL_Rect GoldAmountRect;
	SDL_Rect HealthAmountRect;
	SDL_Rect ManaAmountRect;
	SDL_Rect PlayerLevelRect;
	//player stat pictures and number rects
	SDL_Rect ADRect;
	SDL_Rect ADAmountRect;
	SDL_Rect APRect;
	SDL_Rect APAmountRect;
	SDL_Rect ArmorRect;
	SDL_Rect ArmorAmountRect;
	SDL_Rect MrRect;
	SDL_Rect MrAmountRect;
	SDL_Rect AttackspeedRect;
	SDL_Rect AttackSpeedAmountRect;
	SDL_Rect CDRRect;
	SDL_Rect CDRAmountRect;
	SDL_Rect MoveSpeedRect;
	SDL_Rect MoveSpeedAmountRect;
	SDL_Rect RangeRect;
	SDL_Rect RangeAmountRect;

private:
	bool guihelpergetxy = false;
};