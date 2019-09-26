#include "Game.h"
#include <iostream>
#include <ctime>
#include <iostream>
using namespace std;

Map themap;
ItemShop itemshop;
Player theplayer;
vector<Minion> minions;
vector<Tower> towers;
ShopUI shopmenu;
MiniMap theminimap;

Game::Game()
{

	themap.Initialize();
	itemshop.Initialize();
	shopmenu.Initialize();
	theplayer.Initialize();
	theminimap.Initialize();
	SpawnTowers();
	SpawnMinions();
	for (int i = 0; i < minions.size(); i++)
	{
		minions[i].Initialize();
	}
	themapptr = &themap;
	itemshopptr = &itemshop;
	theplayerptr = &theplayer;
	spawnminioncounter = 0;
}
Game::~Game()
{
	themapptr = 0;
	itemshopptr = 0;
	theplayerptr = 0;
	minions.clear();
	towers.clear();
}
void Game::Initialize()
{
	themap.Initialize();
	itemshop.Initialize();
	theplayer.Initialize();
	theminimap.Initialize();
	SpawnTowers();
	SpawnMinions();
	for (int i = 0; i < minions.size(); i++)
	{
		minions[i].Initialize();
	}
	themapptr = &themap;
	itemshopptr = &itemshop;
	theplayerptr = &theplayer;
}
void Game::Update()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	//cout << "x " << x + themap.PlayerCamera.x << " y " << y + themap.PlayerCamera.y << endl;
	//cout << theplayer.MapPosition.x << endl;
	GivePlayerGold();

	spawnminioncounter++;
	themapptr->UpdateMap();
	theplayerptr->UpdatePlayer();
	playerui.Update();
	shopmenu.Update();
	theminimap.Update();
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i].Update();
	}
	for (int i = 0; i < minions.size(); i++)
	{
		minions[i].Update();
	}
	if (spawnminioncounter % 3000 == 0)
	{
		SpawnMinions();
	}
}
void Game::Print()
{
	extern SDL_Renderer* grender;
	
	themapptr->Print(grender); 
	for (int i = 0; i < minions.size(); i++)
	{
		minions[i].Print();
	}
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i].Print();
	}
	theplayerptr->Print(grender);
	theminimap.Print();
	playerui.Print(grender);
	shopmenu.Print(grender);
	PrintCursor();
}
void Game::ScreenSizeTrigger()
{
	shopmenu.UpdateRects(1);
	playerui.UpdateRects(1);
	theminimap.Updateminimapposition();
}
void Game::PrintCursor()
{
	extern Map themap;
	extern SDL_Renderer* grender;
	extern SDL_Texture* cursor;
	extern SDL_Texture* attackcursor;
	extern bool AKeyState;

	int x, y;
	SDL_GetMouseState(&x, &y);


	SDL_Rect mouserect = { x-5,y-5,35,35 };
	SDL_Rect attackrect = { x-(35/2),y-(35/2),35,35 };
	if (theplayer.autoing)
	{
		SDL_RenderCopy(grender, attackcursor, 0, &attackrect);
	}
	else
	{
		SDL_RenderCopy(grender, cursor, 0, &mouserect);
	}

}
void Game::SpawnMinions()
{
	//spawn middle lane top and bottom side
	int counter = -30;
	int distanceapart = 20;
	for (int i = 0; i < 4; i++)
	{
		Minion tmpminion;
		tmpminion.SetToMelle();
		tmpminion.BotSide = true;
		tmpminion.BotsideMidlaneMellePosition(counter + i* distanceapart);
		minions.push_back(tmpminion);
	}
	for (int i = 0; i < 4; i++)
	{
		Minion tmpminion;
		tmpminion.SetToRanged();
		tmpminion.BotSide = true;
		tmpminion.BotsideMidlaneRangePosition(counter + i * distanceapart);
		minions.push_back(tmpminion);
	}
	for (int i = 0; i < 1; i++)
	{
		Minion tmpminion;
		tmpminion.SetToCannon();
		tmpminion.BotSide = true;
		tmpminion.BotsideMidlaneRangePosition(counter + i * distanceapart);
		minions.push_back(tmpminion);
	}
	for (int i = 0; i < 4; i++)
	{
		Minion tmpminion;
		tmpminion.SetToMelle(1);
		tmpminion.BotSide = false;
		tmpminion.TopsideMidlaneMellePosition(counter + i * distanceapart);
		minions.push_back(tmpminion);
	}
	for (int i = 0; i < 4; i++)
	{
		Minion tmpminion;
		tmpminion.SetToRanged(1);
		tmpminion.BotSide = false;
		tmpminion.TopsideMidlaneRangePosition(counter + i * distanceapart);
		minions.push_back(tmpminion);
	}
	for (int i = 0; i < 1; i++)
	{
		Minion tmpminion;
		tmpminion.SetToCannon(1);
		tmpminion.TopsideMidlaneRangePosition(counter + i * distanceapart);
		minions.push_back(tmpminion);
	}
}
void Game::SpawnTowers()
{
	//spawn 6 midlane towers
	Tower botsidemid3;
	botsidemid3.BotSide = true;
	botsidemid3.MapPosition.x = 1881; botsidemid3.MapPosition.y = 3752;
	towers.push_back(botsidemid3);

	Tower botsidemid2;
	botsidemid2.BotSide = true;
	botsidemid2.MapPosition.x = 2398; botsidemid2.MapPosition.y = 3418;
	towers.push_back(botsidemid2);

	Tower botsidemid1;
	botsidemid1.BotSide = true;
	botsidemid1.MapPosition.x = 2698; botsidemid1.MapPosition.y = 2929;
	towers.push_back(botsidemid1);

	Tower topsidemid3;
	topsidemid3.MapPosition.x = 3812; topsidemid3.MapPosition.y = 2307;
	towers.push_back(topsidemid3);

	Tower topsidemid2;
	topsidemid2.MapPosition.x = 4093; topsidemid2.MapPosition.y = 1834;
	towers.push_back(topsidemid2);

	Tower topsidemid1;
	topsidemid1.MapPosition.x = 4562; topsidemid1.MapPosition.y = 1517;
	towers.push_back(topsidemid1);
}
void Game::GivePlayerGold()
{
	extern bool BKeyState;
	if (BKeyState)
	{
		theplayer.gold += 500;
	}
}