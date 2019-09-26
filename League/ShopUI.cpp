#pragma once
#include "myglobal.h"
#include "ShopUI.h"
#include "Player.h"
#include <iostream>
#include "Font.h"
using namespace std;

/* Save locations for UI
	starting y for buyable items = MainBackgroundRect.y + 5*MainBackgroundRect.h/30
	ending y + height for buyable items = MainBackgroundRect.y + 20 * MainBackgroundRect.h / 29 + Item1Rect.w
	starting x for buyable items = (MainBackgroundRect.x + MainBackgroundRect.w / 20)
	ending x + width for buyable items = (MainBackgroundRect.x + 15 * MainBackgroundRect.w / 35 + Item1Rect.w)
	very bottom of buyable items square = (MainBackgroundRect.y + 64 * MainBackgroundRect.h / 77)
	distance from the bottom of last square to very bottom of buyable items = (MainBackgroundRect.y + 32 * MainBackgroundRect.h / 41)
	very top of buyable items square = MainBackgroundRect.y + 8*MainBackgroundRect.h/67
	very left of buyable items square = (MainBackgroundRect.x + 10 * MainBackgroundRect.w / 2000) * sort of
	very right of buyable items square = (MainBackgroundRect.x + 5 * MainBackgroundRect.w / 11) * sort of
	very left of requirement box = 504*MainBackgroundRect.w/1000
	very right of requirement box = MainBackgroundRect.x + 980*MainBackgroundRect.w/1000)
*/


ShopUI::ShopUI()//*need a global command when screen size changes
{
	extern SDL_Texture* ShopMenu;
	extern SDL_Texture* ShopeSideScroll;

	UIX = 100;
	UIY = 50;
	clickeditem.ItemReset();
	MainBackground = ShopMenu;
	Sidescroll = ShopeSideScroll;
	Item1 = 0;
	Item2 = 0;
	Item3 = 0;
	Item4 = 0;
	Item5 = 0;
	Item6 = 0;
	VisionItem = 0;
	Sell = 0;
	Undo = 0;
	Buy = 0;
	UpdateRects(1);
}
void ShopUI::Initialize()
{
	extern SDL_Texture* ShopMenu;
	extern SDL_Texture* ShopeSideScroll;

	UIX = 100;
	UIY = 50;
	clickeditem.ItemReset();
	MainBackground = ShopMenu;
	Sidescroll = ShopeSideScroll;
	Item1 = 0;
	Item2 = 0;
	Item3 = 0;
	Item4 = 0;
	Item5 = 0;
	Item6 = 0;
	VisionItem = 0;
	Sell = 0;
	Undo = 0;
	Buy = 0;
	UpdateRects(1);

}
void ShopUI::UpdateRects(bool overrideshowshopui)
{
	if (!overrideshowshopui)
	{
		if (!ShowShopUI)
		{
			return;
		}
	}
	extern int screenwidth;
	extern int screenheight;

	MainBackgroundRect = { UIX,UIY,screenwidth - screenwidth / 4,screenheight - screenheight / 5 };
	int itemwidth = screenwidth / 26;
	int itemheight = screenheight / 21;
	int item1x = MainBackgroundRect.x + MainBackgroundRect.w / 29;
	int item2x = MainBackgroundRect.x + 3 * MainBackgroundRect.w / 34;
	int item3x = MainBackgroundRect.x + 3 * MainBackgroundRect.w / 21;
	int itemtopy = MainBackgroundRect.y + MainBackgroundRect.h - MainBackgroundRect.h / 7;
	int itembottomy = MainBackgroundRect.y + MainBackgroundRect.h - 3 * MainBackgroundRect.h / 38;
	int currenty = MainBackgroundRect.y + 5 * MainBackgroundRect.h / 30;
	
	Item1Rect = { item1x,itemtopy,itemwidth,itemheight };
	Item2Rect = { item2x,itemtopy,itemwidth,itemheight };
	Item3Rect = { item3x,itemtopy,itemwidth,itemheight };
	Item4Rect = { item1x,itembottomy,itemwidth,itemheight };
	Item5Rect = { item2x,itembottomy,itemwidth,itemheight };
	Item6Rect = { item3x,itembottomy,itemwidth,itemheight };
	ItemRects.clear();
	ItemRects.push_back(Item1Rect); ItemRects.push_back(Item2Rect); ItemRects.push_back(Item3Rect);
	ItemRects.push_back(Item4Rect); ItemRects.push_back(Item5Rect); ItemRects.push_back(Item6Rect);
	
	VisionItemRect = { (MainBackgroundRect.x + 80 * MainBackgroundRect.w / 405), (MainBackgroundRect.y + MainBackgroundRect.h - MainBackgroundRect.h / 9), itemwidth,itemheight };
	DiscriptionRect = { (MainBackgroundRect.x + 100* MainBackgroundRect.w / 198),(MainBackgroundRect.y + 580 * MainBackgroundRect.h / 1000) + 1,5*screenwidth / 14,10*screenheight / 40 };
	SellRect = { (MainBackgroundRect.x + 40 * MainBackgroundRect.w / 139),(MainBackgroundRect.y + MainBackgroundRect.h - 2*MainBackgroundRect.h / 29),2*screenwidth / 27,screenheight / 34 };
	UndoRect = { (MainBackgroundRect.x + 80 * MainBackgroundRect.w / 205),(MainBackgroundRect.y + MainBackgroundRect.h - 2 * MainBackgroundRect.h / 29),2 * screenwidth / 27,screenheight / 34 };
	BuyRect = { (MainBackgroundRect.x + 720 * MainBackgroundRect.w / 865),(MainBackgroundRect.y + MainBackgroundRect.h - 1440 * MainBackgroundRect.h / 3662),8 * screenwidth / 79,screenheight / 28 };
	goldamountRect = { MainBackgroundRect.x + 402 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 880 * MainBackgroundRect.h / 1000,39*MainBackgroundRect.w / 1000,33*MainBackgroundRect.h / 1000 };

	scrollstartingy = MainBackgroundRect.y + 8 * MainBackgroundRect.h / 65;
	scrollendingy = MainBackgroundRect.y + 64 * MainBackgroundRect.h / 91;
	sidescrollRect = { (MainBackgroundRect.x + 20 * MainBackgroundRect.w / 43),scrollstartingy,screenwidth / 105,screenheight / 10 };
	
	itemsscrollyoffset = 0;
	
}
void ShopUI::Print(SDL_Renderer* grender)
{
	extern Player theplayer;
	extern SDL_Texture* buylightup;
	extern SDL_Texture* selllightup;
	extern ItemShop itemshop;

	if (!ShowShopUI)
	{
		return;
	}


	SDL_RenderCopy(grender, MainBackground, 0, &MainBackgroundRect);
	for (int i = 0; i < theplayer.items.size(); i++)
	{
		SDL_RenderCopy(grender, theplayer.items[i]->image, 0, &ItemRects[i]);
	}
	SDL_RenderCopy(grender, VisionItem, 0, &VisionItemRect);

	bool notsame = true;
	for (int i = 0; i < theplayer.items.size(); i++)
	{
		if (clickeditem.name == theplayer.items[i]->name && clickeditem.name != "N/A")
		{
			SDL_RenderCopy(grender, selllightup, 0, &SellRect);
			notsame = false;
			break;
		}
	}
	if (notsame)
	{
		SDL_RenderCopy(grender, Sell, 0, &SellRect);
	}
	SDL_RenderCopy(grender, Undo, 0, &UndoRect);
	if(clickeditem.COST <= theplayer.gold && clickeditem.name != "N/A")
		SDL_RenderCopy(grender, buylightup, 0, &BuyRect);
	else
		SDL_RenderCopy(grender, Buy, 0, &BuyRect);
	SDL_RenderCopy(grender, Sidescroll, 0, &sidescrollRect);

	int widthpernumber = 10 * MainBackgroundRect.w / 1000;
	int digits = to_string(theplayer.gold).size();
	goldamountRect = { MainBackgroundRect.x + 422 * MainBackgroundRect.w / 1000 - ((widthpernumber*digits)/2), MainBackgroundRect.y + 880 * MainBackgroundRect.h / 1000,widthpernumber * digits,33 * MainBackgroundRect.h / 1000 };
	Font gfont(to_string(theplayer.gold), "yellow");
	gfont.Print(grender, goldamountRect);



	itemrects.clear();//every time you print you could reset the itemrects position so clear it
	for (int i = 0; i < theplayer.items.size(); i++)
	{
		itemrect tmp1; 
		tmp1.therect = ItemRects[i];
		tmp1.theitem = *theplayer.items[i];
		itemrects.push_back(tmp1);
	}
	PrintItems(grender);
    PrintRequirements(grender, clickeditem, MainBackgroundRect.x + 504 * MainBackgroundRect.w / 1000, MainBackgroundRect.x + 980 * MainBackgroundRect.w / 1000, MainBackgroundRect.y + 225 * MainBackgroundRect.h / 1000);
	PrintBuildsInto(grender, clickeditem);
	for (int i = 0; i < itemshop.CostOrder.size(); i++)
	{
		SDL_SetTextureColorMod(itemshop.CostOrder[i].image, 255, 255, 255);
	}
	PrintLargeDescription(grender, clickeditem);
	if (printsmalldescription)
	{
		PrintSmallDescription(grender, smalldescriptionitem);
	}
}
void ShopUI::PrintItems(SDL_Renderer* grender)
{
	extern ItemShop itemshop;
	extern Player theplayer;

	SDL_Rect therect = { 0,0,0,0 };
	int rowcounter = 0;

	int itemsquarelength = Item1Rect.w;
	int ItemsStartingY = MainBackgroundRect.y + 5*MainBackgroundRect.h/30 - itemsscrollyoffset;
	int BottomVisibleYandH = (MainBackgroundRect.y + 690 * MainBackgroundRect.h / 1000 + itemsquarelength);
	int YIncrementDistance = BottomVisibleYandH - (ItemsStartingY + itemsscrollyoffset) - (numberinrow * itemsquarelength);
	YIncrementDistance = YIncrementDistance / (numberinrow-1);

	int xvalues[4];
	int ItemStartingX = (MainBackgroundRect.x + 50 * MainBackgroundRect.w / 1000);
	int ItemRightMostXandW = (MainBackgroundRect.x + 428 * MainBackgroundRect.w / 1000 + itemsquarelength);
	int XIncrementDistance = ItemRightMostXandW - ItemStartingX - (numberinrow*itemsquarelength);
	XIncrementDistance = XIncrementDistance / numberinrow;
	xvalues[0] = ItemStartingX;
	xvalues[1] = ItemStartingX + XIncrementDistance + itemsquarelength;
	xvalues[2] = ItemStartingX + 2*(XIncrementDistance + itemsquarelength);
	xvalues[3] = ItemStartingX + 3 * (XIncrementDistance + itemsquarelength);

	int theheight = itemsquarelength;
	int widthpernumber = 200 * itemsquarelength / 1000;

	int TopYofSelectBox = (MainBackgroundRect.y + 119 * MainBackgroundRect.h / 1000);
	int BottomYofSelectBox = (MainBackgroundRect.y + 831 * MainBackgroundRect.h / 1000);

	Font thefont;
	for (int i = 0; i < itemshop.CostOrder.size(); i++)
	{
		SDL_Rect goldrect = { xvalues[rowcounter] + (itemsquarelength /2) - (widthpernumber * to_string(itemshop.CostOrder[i].COST).size()) / 2, ItemsStartingY + itemsquarelength + theheight/7,widthpernumber * to_string(itemshop.CostOrder[i].COST).size(),theheight / 2 };
		thefont.Initialize(to_string(itemshop.CostOrder[i].COST), "white");
		
		int actualyh = goldrect.h - 2 * itemsquarelength / 12;

		if (goldrect.y + actualyh >= TopYofSelectBox && goldrect.y <= BottomYofSelectBox)
		{
			if (goldrect.y < TopYofSelectBox)
			{
				int distance = goldrect.y + goldrect.h - TopYofSelectBox;
				double width = theheight / 2;
				double percentage = distance / width;
				SDL_Rect croprect = { 0,actualyh * (1 - percentage),1000,1000 };
				goldrect.y = TopYofSelectBox;
				goldrect.h = distance;
				SDL_RenderCopy(grender, thefont.image, &croprect, &goldrect);
			}
			else if (goldrect.y + actualyh > BottomYofSelectBox)
			{
				int distance = BottomYofSelectBox - goldrect.y;
				double width = theheight / 2;
				double percentage = distance / width;
				SDL_Rect croprect = { 0,0,1000,actualyh * percentage };
				goldrect.y = BottomYofSelectBox - distance;
				goldrect.h = distance;
				SDL_RenderCopy(grender, thefont.image, &croprect, &goldrect);
			}
			else
			{
				thefont.Initialize(to_string(itemshop.CostOrder[i].COST), "white");
				thefont.Print(grender, goldrect);
			}
		}
		if (itemshop.CostOrder[i].COST > theplayer.gold)
		{
			SDL_SetTextureColorMod(itemshop.CostOrder[i].image, 100, 100, 100);
		}
		else
		{
			SDL_SetTextureColorMod(itemshop.CostOrder[i].image, 255, 255, 255);
		}
		if (ItemsStartingY + itemsquarelength >= TopYofSelectBox && ItemsStartingY <= BottomYofSelectBox)
		{
			if (ItemsStartingY < TopYofSelectBox)
			{
				int distance = ItemsStartingY + itemsquarelength - TopYofSelectBox;
				double width = itemsquarelength;
				double percentage = distance / width;
				SDL_Rect croprect = { 0,ItemImageDimension * (1-percentage),1000,1000 };
				therect = { xvalues[rowcounter],TopYofSelectBox,itemsquarelength,distance };
				SDL_RenderCopy(grender, itemshop.CostOrder[i].image, &croprect, &therect);
				/*adding to array of itemrects*/
				itemrect tmpitemrect; tmpitemrect.therect = therect; tmpitemrect.theitem = itemshop.CostOrder[i];
				itemrects.push_back(tmpitemrect);
			}
			else if (ItemsStartingY + itemsquarelength > BottomYofSelectBox)
			{
				int distance = BottomYofSelectBox - ItemsStartingY;
				double width = itemsquarelength;
				double percentage = distance / width;
				SDL_Rect croprect = { 0,0,1000,ItemImageDimension * percentage };
				therect = { xvalues[rowcounter],ItemsStartingY,itemsquarelength,distance };
				SDL_RenderCopy(grender, itemshop.CostOrder[i].image, &croprect, &therect);
				/*adding to array of itemrects*/
				itemrect tmpitemrect; tmpitemrect.therect = therect; tmpitemrect.theitem = itemshop.CostOrder[i];
				itemrects.push_back(tmpitemrect);
			}
			else
			{
				therect = { xvalues[rowcounter],ItemsStartingY,itemsquarelength,theheight };
				SDL_RenderCopy(grender, itemshop.CostOrder[i].image, 0, &therect);
				/*adding to array of itemrects*/
				itemrect tmpitemrect; tmpitemrect.therect = therect; tmpitemrect.theitem = itemshop.CostOrder[i];
				itemrects.push_back(tmpitemrect);
			}
		}
		
		rowcounter = (rowcounter + 1) % numberinrow;
		if (rowcounter == 0)
		{
			ItemsStartingY += (YIncrementDistance + itemsquarelength);
		}
		//SDL_SetTextureColorMod(itemshop.CostOrder[i].image, 255, 255, 255);
	}
	thefont.FreeTexture();

}
void ShopUI::PrintRequirements(SDL_Renderer* grender, Item item, int leftboundary, int rightboundary,int startingheight)
{
	extern int screenwidth;
	extern int screenheight;

	if (item.name == "N/A")
	{
		return;
	}
	extern ItemShop itemshop;
	
	int itemwidth = screenwidth / 26;
	int itemheight = screenheight / 21;
	int YIncrement = startingheight + 110 * MainBackgroundRect.h / 1000;
	int boundarycenterx = leftboundary + ((rightboundary - leftboundary) / 2);
	int boundarywidth = rightboundary - leftboundary;
	
	SDL_Rect ItemRect = { boundarycenterx - (itemwidth / 2), startingheight, itemwidth, itemheight };
	
	SDL_RenderCopy(grender, item.image, 0, &ItemRect);

	/*adding to array of itemrects*/
	itemrect tmpitemrect; tmpitemrect.therect = ItemRect; tmpitemrect.theitem = item;
	itemrects.push_back(tmpitemrect);

	int widthpernumber = 200 * itemwidth / 1000;
	SDL_Rect goldrect = { 0,0,0,0 };
	goldrect.x = ItemRect.x + (ItemRect.w / 2) - (widthpernumber * to_string(item.COST).size()) / 2;
	goldrect.y = ItemRect.y + ItemRect.w - 350 * ItemRect.w / 1000;
	goldrect.w = widthpernumber * to_string(item.COST).size();
	goldrect.h = ItemRect.h / 2;
	Font gfont(to_string(item.COST), "yellow");
	gfont.Print(grender, goldrect);
	gfont.FreeTexture();

	int middleyposition = ItemRect.y + ItemRect.h + 110 * MainBackgroundRect.h / 4000;
	SDL_SetRenderDrawColor(grender, 233, 206, 27, 200);
	switch (item.childrenitems.size())
	{
	case 0: return;	break;
	case 1:  
		SDL_RenderDrawLine(grender, boundarycenterx, ItemRect.y + ItemRect.h, boundarycenterx, ItemRect.y + ItemRect.h + 110 * MainBackgroundRect.h / 2000);
		PrintRequirements(grender,itemshop.Items.at(item.childrenitems[0]),leftboundary, rightboundary, YIncrement);
		break;
	case 2: 
		SDL_RenderDrawLine(grender, boundarycenterx, ItemRect.y + ItemRect.h, boundarycenterx, middleyposition);
		SDL_RenderDrawLine(grender, leftboundary + ((boundarycenterx - leftboundary) / 2), middleyposition, boundarycenterx + ((rightboundary - boundarycenterx) / 2), middleyposition);
		SDL_RenderDrawLine(grender, leftboundary + ((boundarycenterx - leftboundary) / 2), middleyposition, leftboundary + ((boundarycenterx - leftboundary) / 2), YIncrement);
		SDL_RenderDrawLine(grender, boundarycenterx + ((rightboundary - boundarycenterx) / 2), middleyposition, boundarycenterx + ((rightboundary - boundarycenterx) / 2), YIncrement);
		
		PrintRequirements(grender, itemshop.Items.at(item.childrenitems[0]), leftboundary, boundarycenterx, YIncrement);
		PrintRequirements(grender, itemshop.Items.at(item.childrenitems[1]), boundarycenterx, rightboundary, YIncrement);
		break;
	case 3:
		SDL_RenderDrawLine(grender, boundarycenterx, ItemRect.y + ItemRect.h, boundarycenterx, ItemRect.y + ItemRect.h + 110 * MainBackgroundRect.h / 2000);
		SDL_RenderDrawLine(grender, leftboundary + ((leftboundary + .33* boundarywidth - leftboundary) / 2), middleyposition, (leftboundary + .66 * boundarywidth) + ((rightboundary - (leftboundary + .66 * boundarywidth)) / 2), middleyposition);
		SDL_RenderDrawLine(grender, leftboundary + ((leftboundary + .33* boundarywidth - leftboundary) / 2), middleyposition, leftboundary + ((leftboundary + .33* boundarywidth - leftboundary) / 2), YIncrement);
		SDL_RenderDrawLine(grender, (leftboundary + .66 * boundarywidth) + ((rightboundary - (leftboundary + .66 * boundarywidth)) / 2), middleyposition, (leftboundary + .66 * boundarywidth) + ((rightboundary - (leftboundary + .66 * boundarywidth)) / 2), YIncrement);

		PrintRequirements(grender, itemshop.Items.at(item.childrenitems[0]), leftboundary, leftboundary + .33* boundarywidth, YIncrement);
		PrintRequirements(grender, itemshop.Items.at(item.childrenitems[1]), leftboundary + .33 * boundarywidth, leftboundary + .66 * boundarywidth, YIncrement);
		PrintRequirements(grender, itemshop.Items.at(item.childrenitems[2]), leftboundary + .66 * boundarywidth, rightboundary, YIncrement);
		break;
	}
}
void ShopUI::PrintSmallDescription(SDL_Renderer* grender, itemrect itemrectz)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	extern SDL_Texture* descriptionbox;
	extern SDL_Texture* goldimage;

	int basic = itemrectz.theitem.descriptionstring.size();
	int passives = itemrectz.theitem.descriptionuniquestring.size();

	SDL_Rect DescriptionRect = { 0,0,0,0 };
	DescriptionRect.x = x + 40 * MainBackgroundRect.w / 1000;
	DescriptionRect.y = y - 40 * MainBackgroundRect.h / 1000;
	DescriptionRect.w = 333 * MainBackgroundRect.w / 1000;
	int YIncrement = 20 * DescriptionRect.w / 1000;
	int extraamount = (passives == 0) ? 0 : 2 * YIncrement;
	DescriptionRect.h = (200 * DescriptionRect.w / 1000) + (3* YIncrement*basic) + (2.5*YIncrement* passives) + extraamount;
	SDL_RenderCopy(grender, descriptionbox, 0, &DescriptionRect);

	SDL_Rect ItemImageRect = { 0,0,0,0 };
	ItemImageRect.x = DescriptionRect.x + 30 * DescriptionRect.w / 1000;
	ItemImageRect.y = DescriptionRect.y + 30 * DescriptionRect.w / 1000;
	ItemImageRect.w = 150 * DescriptionRect.w / 1000;
	ItemImageRect.h = 150 * DescriptionRect.w / 1000;
	SDL_RenderCopy(grender, itemrectz.theitem.image, 0, &ItemImageRect);

	SDL_Rect ItemNameRect = { 0,0,0,0 };
	ItemNameRect.x = ItemImageRect.x + ItemImageRect.w + 30 * DescriptionRect.w / 1000;
	ItemNameRect.y = ItemImageRect.y + 30* DescriptionRect.w / 1000;
	int widthperletter = 25 * DescriptionRect.w / 1000;
	ItemNameRect.w = widthperletter * itemrectz.theitem.name.size();
	ItemNameRect.h = 50 * DescriptionRect.w / 1000;
	Font tmpfont(itemrectz.theitem.name, "yellow");
	tmpfont.Print(grender, ItemNameRect);

	SDL_Rect GoldIconRect = { 0,0,0,0 };
	GoldIconRect.x = ItemImageRect.x + ItemImageRect.w + 30 * DescriptionRect.w / 1000;
	GoldIconRect.y = DescriptionRect.y + 120 * DescriptionRect.w / 1000;
	GoldIconRect.w = widthperletter * 4;
	GoldIconRect.h = ItemImageRect.y + ItemImageRect.h - GoldIconRect.y;
	SDL_RenderCopy(grender, goldimage, 0, &GoldIconRect);

	SDL_Rect GoldTextRect = { 0,0,0,0 };
	GoldTextRect.x = ItemImageRect.x + ItemImageRect.w + 150 * DescriptionRect.w / 1000;
	GoldTextRect.y = DescriptionRect.y + 130 * DescriptionRect.w / 1000;
	int widthpernumber = 17 * DescriptionRect.w / 1000;
	GoldTextRect.w = widthpernumber * 6;
	GoldTextRect.h = ItemImageRect.y + ItemImageRect.h - GoldIconRect.y;
	tmpfont.Initialize(to_string(itemrectz.theitem.COST), "yellow");
	tmpfont.Print(grender, GoldTextRect);

	string thestring;
	SDL_Rect statrect = { 0,0,0,0 };
	statrect.x = ItemImageRect.x + 10 * DescriptionRect.w / 1000;
	statrect.y = ItemImageRect.y + ItemImageRect.h + YIncrement;
	statrect.w = 2 * YIncrement;
	statrect.h = 2 * YIncrement;
	
	for (int i = 0; i < itemrectz.theitem.descriptionstring.size(); i++)
	{
		thestring = itemrectz.theitem.descriptionstring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect); 
		statrect.y += statrect.h + YIncrement;
	}

	statrect.y += 2 * YIncrement;

	for (int i = 0; i < itemrectz.theitem.descriptionuniquestring.size(); i++)
	{
		thestring = itemrectz.theitem.descriptionuniquestring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect); statrect.y += statrect.h + YIncrement / 2;
	}

	tmpfont.FreeTexture();
}
void ShopUI::PrintLargeDescription(SDL_Renderer* grender, Item item)
{
	if (item.name == "N/A")
	{
		return;
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	extern SDL_Texture* descriptionbox;
	extern SDL_Texture* goldimage;

	int YIncrement = 20 * DiscriptionRect.w / 1000;

	SDL_Rect ItemImageRect = { 0,0,0,0 };
	ItemImageRect.x = DiscriptionRect.x + 26 * DiscriptionRect.w / 1000;
	ItemImageRect.y = DiscriptionRect.y + 15 * DiscriptionRect.w / 1000;
	ItemImageRect.w = 70 * DiscriptionRect.w / 1000;
	ItemImageRect.h = 70 * DiscriptionRect.w / 1000;
	SDL_RenderCopy(grender, item.image, 0, &ItemImageRect);

	SDL_Rect ItemNameRect = { 0,0,0,0 };
	ItemNameRect.x = ItemImageRect.x + ItemImageRect.w + 20 * DiscriptionRect.w / 1000;
	ItemNameRect.y = ItemImageRect.y + 11 * DiscriptionRect.w / 1000;
	int widthperletter = 15 * DiscriptionRect.w / 1000;
	ItemNameRect.w = widthperletter * item.name.size();
	ItemNameRect.h = 24 * DiscriptionRect.w / 1000;
	Font tmpfont(item.name, "yellow");
	tmpfont.Print(grender, ItemNameRect);

	SDL_Rect GoldIconRect = { 0,0,0,0 };
	GoldIconRect.x = ItemImageRect.x + ItemImageRect.w + 20 * DiscriptionRect.w / 1000;
	GoldIconRect.y = DiscriptionRect.y + 55 * DiscriptionRect.w / 1000;
	GoldIconRect.w = widthperletter * 4;
	GoldIconRect.h = ItemImageRect.y + ItemImageRect.h - GoldIconRect.y;
	SDL_RenderCopy(grender, goldimage, 0, &GoldIconRect);

	SDL_Rect GoldTextRect = { 0,0,0,0 };
	GoldTextRect.x = ItemImageRect.x + ItemImageRect.w + 92 * DiscriptionRect.w / 1000;
	GoldTextRect.y = DiscriptionRect.y + 61 * DiscriptionRect.w / 1000;
	int widthpernumber = 17 * DiscriptionRect.w / 1000;
	GoldTextRect.w = widthpernumber * to_string(item.COST).size();
	GoldTextRect.h = ItemImageRect.y + ItemImageRect.h - GoldIconRect.y;
	tmpfont.Initialize(to_string(item.COST), "yellow");
	tmpfont.Print(grender, GoldTextRect);


	string thestring;
	SDL_Rect statrect = { 0,0,0,0 };
	statrect.x = ItemImageRect.x + 10 * DiscriptionRect.w / 1000;
	statrect.y = ItemImageRect.y + ItemImageRect.h + YIncrement;
	statrect.w = 3 * widthperletter;
	statrect.h = 5* YIncrement /3;
	widthperletter = 15 * DiscriptionRect.w / 1000;

	for (int i = 0; i < item.descriptionstring.size(); i++)
	{
		thestring = item.descriptionstring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect);
		statrect.y += statrect.h + YIncrement / 2;
	}

	statrect.y += YIncrement;

	for (int i = 0; i < item.descriptionuniquestring.size(); i++)
	{
		thestring = item.descriptionuniquestring[i];
		statrect.w = widthperletter * thestring.size(); tmpfont.Initialize(thestring, "white"); tmpfont.Print(grender, statrect); 
		statrect.y += statrect.h + YIncrement / 2;
	}

	tmpfont.FreeTexture();
}
void ShopUI::PrintBuildsInto(SDL_Renderer* grender, Item item)
{
	extern ItemShop itemshop;

	SDL_Rect therect = { 0,0,0,0 };
	int startingx = (MainBackgroundRect.x + 540 * MainBackgroundRect.w / 1000);
	int startingy = (MainBackgroundRect.y + 130 * MainBackgroundRect.h / 1000);
	int xdiff = 59*MainBackgroundRect.w/1000;
	int width = Item1Rect.w;
	int height = Item1Rect.h;
	for (int i = 0; i < item.buildsinto.size(); i++)
	{
		therect = { startingx,startingy,width,height };
		SDL_RenderCopy(grender, itemshop.Items.at(item.buildsinto[i]).image, 0, &therect);
		startingx += xdiff;
		/*adding to array of itemrects*/
		itemrect tmpitemrect; tmpitemrect.therect = therect; tmpitemrect.theitem = itemshop.Items.at(item.buildsinto[i]);
		itemrects.push_back(tmpitemrect);
	}
}

void ShopUI::Update()
{
	extern bool IKeyState;
	extern ItemShop itemshop;
	extern Player theplayer;
	extern bool ButtonDownOnce;

	myglobal global;

	if (IKeyState)						//toggles our shope ui
	{
		ShowShopUI = !ShowShopUI;
	}

	if (!ShowShopUI)
	{
		return;
	}

	int x, y;
	SDL_GetMouseState(&x, &y);

	/*handle buying input*/
	if (global.PointInsideRect(BuyRect, x, y) && ButtonDownOnce)
	{
		if (clickeditem.name != "N/A" && clickeditem.COST <= theplayer.gold) 
		{
			theplayer.GiveItem(itemshop.Items.at(clickeditem.name));
		}
	}
	/*handle selling input*/
	if (global.PointInsideRect(SellRect, x, y) && ButtonDownOnce)
	{
		for (int i = 0; i < theplayer.items.size(); i++)
		{
			if (clickeditem.name == theplayer.items[i]->name && clickeditem.name != "N/A")
			{
				theplayer.items.erase(theplayer.items.begin() + i);
				theplayer.gold += clickeditem.SELLCOST;
				theplayer.SubStats(clickeditem);
				break;
			}
		}
	}
	if (guihelpergetxy)
	{
		myglobal m1;
		m1.UILocation(MainBackgroundRect, goldamountRect);
		//cout << "x: " << m1.UIWidthRatio(MainBackgroundRect.x, MainBackgroundRect.w, x);
		//cout << "y: " << m1.UIHeightRatio(MainBackgroundRect.y, MainBackgroundRect.h, y) << endl;
	}
	
	CheckIfDraggingScrollBar(x, y);
	HandleMouseDraggingScrollBarInput(x, y);

	HandleMouseHoveringorClickingItemsInput(x, y);

	HandleMouseWheelScrollBarInput(x, y);
	
}
void ShopUI::HandleScrollBarMovement()
{
	extern int screenwidth;
	extern int screenheight;
	extern ItemShop itemshop;

	int startingitemselectyposition = MainBackgroundRect.y + 5 * MainBackgroundRect.h / 30;

	double distance = scrollendingy - scrollstartingy;//substract highest the y scroll can go by lowest the y scroll can go
	double percent = (sidescrollRect.y - scrollstartingy) / distance;//take current y and subtract by starting and see how much distance that covers over its whole range
	int currenty = startingitemselectyposition; //starting y position for items being printed
	int spacelefty = (MainBackgroundRect.y + 20 * MainBackgroundRect.h / 29 + Item1Rect.w) - (MainBackgroundRect.y + 5 * MainBackgroundRect.h / 30) - (numberinrow * Item1Rect.w);
	spacelefty = spacelefty / 3;//is the space between the top and bottom y items visible on select menu
	int highestybox = currenty + ((itemshop.CostOrder.size() / numberinrow) * (spacelefty + (screenwidth / 26))) + (screenwidth / 26);//very lowest y position of the bottom item;
	double amounttomove = percent * (highestybox - (MainBackgroundRect.y + 32 * MainBackgroundRect.h / 41));//bottom of lowest item with top of where itcuts off at bottom percent of that
	
	itemsscrollyoffset = amounttomove;//we set the offset we can give all our ys in the item select box
}
void ShopUI::HandleMouseWheelScrollBarInput(int x, int y)
{
	extern int MouseState;
	myglobal m1;
	if (m1.PointInsideRect(MainBackgroundRect, x, y))
	{
		int scrollspeed = sidescrollRect.h / 2;

		if (MouseState == -1)
			sidescrollRect.y += scrollspeed;
		else if (MouseState == 1)
			sidescrollRect.y -= scrollspeed;

		if (sidescrollRect.y < scrollstartingy)
			sidescrollRect.y = scrollstartingy;
		else if (sidescrollRect.y > scrollendingy)
			sidescrollRect.y = scrollendingy;
		HandleScrollBarMovement();
	}
}
void ShopUI::HandleMouseHoveringorClickingItemsInput(int x, int y)
{
	extern bool ButtonDownOnce;
	myglobal m1;
	bool NoRectsInPoint = true;
	for (int i = 0; i < itemrects.size(); i++)
	{
		if (m1.PointInsideRect(itemrects[i].therect, x, y))
		{
			printsmalldescription = true;
			smalldescriptionitem = itemrects[i];
			NoRectsInPoint = false;
			if (ButtonDownOnce)
			{
				clickeditem = itemrects[i].theitem;
			}
		}
	}
	if (NoRectsInPoint)
	{
		printsmalldescription = false;
		smalldescriptionitem.theitem.ItemReset();
	}
}
void ShopUI::CheckIfDraggingScrollBar(int x, int y)
{
	extern bool ButtonDown;
	myglobal m1;
	if (ButtonDown && m1.PointInsideRect(sidescrollRect, x, y))
	{
		scrollbarclicked = true;
	}
	if (!ButtonDown)
	{
		scrollbarclicked = false;
	}
}
void ShopUI::HandleMouseDraggingScrollBarInput(int x,int y)
{
	if (scrollbarclicked)
	{
		sidescrollRect.y = y - sidescrollRect.h / 2;
		if (sidescrollRect.y < scrollstartingy)
		{
			sidescrollRect.y = scrollstartingy;
		}
		else if (sidescrollRect.y > scrollendingy)
		{
			sidescrollRect.y = scrollendingy;
		}
		HandleScrollBarMovement();
	}
}
void ShopUI::HandlePlayerBuy()
{

}