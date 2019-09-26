#pragma once
#include "Item.h"
#include <map>
class ItemShop
{
public:
	ItemShop();
	void Initialize();

	map<string, Item> Items;
	vector<Item> CostOrder;
private:

};