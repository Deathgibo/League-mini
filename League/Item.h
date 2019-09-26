#pragma once
#include <SDL.h>
#include <vector>
#include <string>
using namespace std;

class Item
{
public:
	Item();
	void ItemReset();
	void BuildInfinityEdge();
	void BuildBfSword();
	void BuildPickAxe();
	void BuildClockAgility();
	void BuildMorrello();
	void BuildBlastingRod();
	void BuildOblivionOrb();
	void BuildAmplifyingTome();
	void BuildRubyCrystal();
	void BuildPhantomDancer();
	void BuildBrawlersGloves();
	void BuildDagger();
	void BuildZeal();
	void BuildSpiritVisage();
	void BuildSpectresCowl();
	void BuildKindleGem();
	void BuildNullMantle();
	void BuildRanduins();
	void BuildGiantsBelt();
	void BuildClothArmor();
	void BuildWardensMail();
	void BuildWarmogs();
	void BuildCrystallineBracer();
	void BuildRejuveBeads();
	void BuildBoots();
	void BuildBloodThirster();

	string name;
	vector<string> descriptionstring;
	vector<string> descriptionuniquestring;
	vector<string> buildsinto;
	vector<string> childrenitems;
	SDL_Texture* image;
	SDL_Texture* descriptionimage;
	SDL_Texture* buyimage;
	float AD;
	float AP;
	float MR;
	float ARMOR;
	float ATKSPEED;
	float CRIT;
	float CDR;
	float HEALTHREGEN;
	float HEALTH;
	float MAGICPEN;
	float MOVESPEED;
	float LIFESTEAL;
	bool GREVIOUSWOUNDS;
	bool UNIQUEPASSIVEBT;
	bool UNIQUEPASSIVEPD;
	bool UNIQUEPASSIVEIF;
	bool UNIQUEPASSIVERO;
	bool UNIQUEPASSIVEWA;
	int COST;
	int SELLCOST;
private:


};