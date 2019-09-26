#pragma once
#include <SDL.h>
#include <vector>
#include "ItemShop.h"

struct itemrect
{
	Item theitem;
	SDL_Rect therect;
};

class ShopUI//**TEXT are glitching and freezing do i need to free up memory?
{
public:
	ShopUI();
	void Initialize();
	void Print(SDL_Renderer* grender);
	void PrintItems(SDL_Renderer* grender);
	void PrintRequirements(SDL_Renderer* grender, Item item, int leftboundary, int rightboundary, int startingheight);
	void PrintBuildsInto(SDL_Renderer* grender, Item item);
	void PrintLargeDescription(SDL_Renderer* grender, Item item);
	void PrintSmallDescription(SDL_Renderer* grender, itemrect itemrectz);
	void HandleScrollBarMovement();
	void HandleMouseWheelScrollBarInput(int x, int y);
	void HandleMouseHoveringorClickingItemsInput(int x, int y);
	void HandleMouseDraggingScrollBarInput(int x, int y);
	void CheckIfDraggingScrollBar(int x, int y);
	void UpdateRects(bool overrideshowshopui = 0);
	void Update();
	void HandlePlayerBuy();
	
	SDL_Texture* MainBackground;
	SDL_Texture* Item1;
	SDL_Texture* Item2;
	SDL_Texture* Item3;
	SDL_Texture* Item4;
	SDL_Texture* Item5;
	SDL_Texture* Item6;
	SDL_Texture* VisionItem;
	SDL_Texture* Sell;
	SDL_Texture* Undo;
	SDL_Texture* Buy;
	SDL_Texture* Sidescroll;
	SDL_Rect MainBackgroundRect;
	SDL_Rect Item1Rect;
	SDL_Rect Item2Rect;
	SDL_Rect Item3Rect;
	SDL_Rect Item4Rect;
	SDL_Rect Item5Rect;
	SDL_Rect Item6Rect;
	vector<SDL_Rect> ItemRects;
	SDL_Rect VisionItemRect;
	SDL_Rect DiscriptionRect;
	SDL_Rect SellRect;
	SDL_Rect UndoRect;
	SDL_Rect BuyRect;
	SDL_Rect sidescrollRect;
	SDL_Rect goldamountRect;
	int UIX;							//ui starting x
	int UIY;							//ui starting y
	bool ShowShopUI = false;				//boolean to see if we should show map
private:
	Item clickeditem;					//current item being selected for view
	vector<itemrect> itemrects;			//these hold all the rectangles and items in them being printed by the item selection, build into, required, and description
	
	/*scroll bar variables*/
	bool scrollbarclicked = false;		//boolean if we click and hold onto scroll bar
	int scrollstartingy;				//starting y of scrollbar in menu
	int scrollendingy;					//ending y of scrollbar in menu
	int itemsscrollyoffset = 0;			//offset of the scrollbar from original y (the items yposition - itemscrollyoffset is how we use it)
	int ItemImageDimension = 64;		//the png of the items are 64 by 64 this helps us with the itemlist scroll algorithm
	
	/*select item location*/
	int numberinrow = 4;

	/*small description*/
	bool printsmalldescription = false;	//true if we hover over any item image else false
	itemrect smalldescriptionitem;		//is the item we are hovering over with our mouse

	/*gui helper*/
	bool guihelpergetxy = true;

};