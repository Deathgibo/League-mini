#pragma once
#include "Vertex.h"
#include "Minion.h"
#include "Player.h"

class TowerState;

class Tower
{
public:
	Tower();
	void Update();
	void Print();
	void UpdateState();
	void HandleInputState();
	void DamageTower(double x);

	int attackcounter = 200;
	bool BotSide = false;
	double maxhealth;
	double currenthealth;
	double damage;
	double Range;
	Vertex Position;
	Vertex MapPosition;
	bool alive = true;
	SDL_Rect towerrect;

	Minion* miniontarget;
	Player* playertarget;
private:
	TowerState* state;
	SDL_Rect BlackHealthBar;
	SDL_Rect ColoredHealthBar;

};