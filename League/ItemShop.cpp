#pragma once
#include "ItemShop.h"
#include <algorithm>
#include <iostream>
ItemShop::ItemShop()
{
	CostOrder.clear();
	Item IF; 
	IF.BuildInfinityEdge();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBfSword();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildPickAxe();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildClockAgility();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildMorrello();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBlastingRod();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildOblivionOrb();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildAmplifyingTome();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRubyCrystal();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildPhantomDancer();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBrawlersGloves();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildDagger();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildZeal();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildSpiritVisage();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildSpectresCowl();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildKindleGem();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildNullMantle();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRanduins();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildGiantsBelt();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildClothArmor();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildWardensMail();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildWarmogs();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildCrystallineBracer();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRejuveBeads();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBoots();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));

	for (int i = 0; i < CostOrder.size() - 1; i++)
	{
		for (int j = 0; j < CostOrder.size() - i - 1; j++)
		{
			if (CostOrder[j].COST > CostOrder[j + 1].COST)
			{
				swap(CostOrder[j], CostOrder[j + 1]);
			}
		}
	}
}
void ItemShop::Initialize()
{
	CostOrder.clear();
	Items.clear();
	Item IF;
	IF.BuildInfinityEdge();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBfSword();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildPickAxe();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildClockAgility();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildMorrello();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBlastingRod();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildOblivionOrb();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildAmplifyingTome();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRubyCrystal();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildPhantomDancer();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBrawlersGloves();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildDagger();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildZeal();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildSpiritVisage();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildSpectresCowl();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildKindleGem();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildNullMantle();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRanduins();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildGiantsBelt();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildClothArmor();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildWardensMail();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildWarmogs();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildCrystallineBracer();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildRejuveBeads();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBoots();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));
	IF.BuildBloodThirster();
	CostOrder.push_back(IF);
	Items.insert(pair<string, Item>(IF.name, IF));

	for (int i = 0; i < CostOrder.size() - 1; i++)
	{
		for (int j = 0; j < CostOrder.size() - i - 1; j++)
		{
			if (CostOrder[j].COST > CostOrder[j + 1].COST)
			{
				swap(CostOrder[j], CostOrder[j + 1]);
			}
		}
	}
}