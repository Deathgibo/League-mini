#pragma once
#include "Vertex.h"
//#include "MinionWalkingState.h"
#include "Map.h"

class Player;
class MinionState;
class Tower;

class Minion
{
public:
	Minion();
	~Minion();
	void Initialize();
	void SetToMelle(bool top = 0);
	void SetToRanged(bool top = 0);
	void SetToCannon(bool top = 0);
	void BotsideMidlaneMellePosition(int x);
	void BotsideMidlaneRangePosition(int x);
	void TopsideMidlaneMellePosition(int x);
	void TopsideMidlaneRangePosition(int x);
	void Update();
	void UpdateState();
	void HandleInputState();
	void DamageMinion(double damage);
	void Print();
	void PutMinionInAfkState();
	void ExitMinionAfkState();
	void PutMinionInKnockupState(int theduration);


	double currenthealth;			
	double maxhealth;				
	int damage;						
	
	double VisionRange;					//the range at which they lock on to the player, minion, or tower
	double AttackRange;				
	int attackcounter = 200;			//stored int to know when to attack, every frame attackcounter goes up once it reaches 200 minion attacks
	int lanerangelimit = 200;			//the range limit that the minion can walk away from its lane
	int chasingrangelimit = 400;		//the range at which minion can chase you
	int simplerangelimit = 175;			//the range the minion needs to be to stay within actual lane, the limit is with the actuall middle of the lane unlike lanerangelimit
	int startinglanerrangelimit = 200; //just helps when you need to reset this you have a constant int

	Vertex Dimensions;				
	Vertex Position;				
	Vertex MapPosition;				
	SDL_Texture* Image;				

	bool BotSide = false;

	Minion* miniontarget;
	Tower* towertarget;
	Player* playertarget;
private:
	bool printminioninfo = false;

	MinionState* state;
	SDL_Rect BlackHealthBar;
	SDL_Rect ColoredHealthBar;

};
