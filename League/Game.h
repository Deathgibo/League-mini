#pragma once
#include "ShopUI.h"
#include "Map.h"
#include "Player.h"
#include "PlayerUI.h"
#include "ItemShop.h"
#include "Tower.h"
#include "Minion.h"
#include "MiniMap.h"
#include <SDL.h>

 
class Game
{
public:
	Game();
	~Game();
	void Initialize();
	void Update();
	void Print();
	void ScreenSizeTrigger();
	void SpawnMinions();
	void SpawnTowers();
	void PrintCursor();
	void GivePlayerGold();
private:
	vector<Minion>* minionsptr;
	Map* themapptr;
	ItemShop* itemshopptr;
	Player* theplayerptr;

	//ShopUI shopmenu;
	PlayerUI playerui;

	int spawnminioncounter;

	bool attacking = false;
};