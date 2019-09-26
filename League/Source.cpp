#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Polygon.h"
#include "Triangle.h"
#include "ShopUI.h"
#include "Font.h"
#include "Map.h"
#include "Player.h"
#include "PlayerUI.h"
#include "ItemShop.h"
#include "LTimer.h"
#include "Game.h"
#include <vector>
#include <chrono>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
using namespace std::chrono;
using namespace std;

bool showframetime = false;
int screenwidth = 1000;
int screenheight = 550;
int MouseState = 0;//used for map cursor movement,
int MouseStateNoClear = 0;
bool upKeyState = false;
bool downKeyState = false;
bool leftKeyState = false;
bool rightKeyState = false;
bool QKeyState = false;
bool AKeyState = false;
bool EKeyState = false;
bool RKeyState = false;
bool WKeyState = false;
bool SKeyState = false;
bool DKeyState = false;
bool IKeyState = false;//toggle store
bool XKeyState = false;//used to lock off hitboxindex
bool TKeyState = false;//used for triangulating polygon,
bool CKeyState = false;//used for creating point on map hitbox,
bool VKeyState = false;//used for creating new map hitbox,
bool BKeyState = false;//used for deleting last map hitbox,
bool NKeyState = false;//used for saving map to file
bool ButtonDown = false;//used for map hitbox clicked,
bool ButtonDownOnce = false;//used if you need to know if player clicked for a frame it turns false until you unclick and click again
bool ButtonLeftOnce = false;
bool ButtonLeftHold = false;
bool ButtonRightOnce = false;
bool buttooncehelper = true;
SDL_Window* gwindow = 0;
TTF_Font * gFont = 0;
SDL_Renderer* grender = 0;
SDL_Surface* gsurface = 0;
SDL_Texture* LeagueMap = 0;
SDL_Texture* BlitzIdle = 0;
SDL_Texture* BlitzGrab = 0;
SDL_Texture* ShopMenu = 0;
SDL_Texture* ShopeSideScroll = 0;
SDL_Texture* Infinityedgeimage = 0;
SDL_Texture* ImageBfSword = 0;
SDL_Texture* ImagePickAxe = 0;
SDL_Texture* ImageClockAgility = 0;
SDL_Texture* ImageMorrello = 0;
SDL_Texture* ImageBlastingRod = 0;
SDL_Texture* ImageOblivionOrb = 0;
SDL_Texture* ImageAmplifyingTome = 0;
SDL_Texture* ImageRubyCrystal = 0;
SDL_Texture* ImagePhantomDancer = 0;
SDL_Texture* ImageBrawlersGloves = 0;
SDL_Texture* ImageDagger = 0;
SDL_Texture* ImageZeal = 0;
SDL_Texture* ImageSpiritVisage = 0;
SDL_Texture* ImageSpectresCowl = 0;
SDL_Texture* ImageKindleGem = 0;
SDL_Texture* ImageNullMantle = 0;
SDL_Texture* ImageRanduins = 0;
SDL_Texture* ImageGiantsBelt = 0;
SDL_Texture* ImageClothArmor = 0;
SDL_Texture* ImageWardensMail = 0;
SDL_Texture* ImageWarmogs = 0;
SDL_Texture* ImageCrystallineBracer = 0;
SDL_Texture* ImageRejuveBeads = 0;
SDL_Texture* ImageBoots = 0;
SDL_Texture* ttftest = 0;
SDL_Texture* descriptionbox = 0;
SDL_Texture* goldimage = 0;
SDL_Texture* playeruibackground = 0;
SDL_Texture* ImageBloodThirster = 0;
SDL_Texture* blitzq = 0;
SDL_Texture* blitzw = 0;
SDL_Texture* blitze = 0;
SDL_Texture* blitzr = 0;
SDL_Texture* blitzpassive = 0;
SDL_Texture* blitzicon = 0;
SDL_Texture* flash = 0;
SDL_Texture* tp = 0;
SDL_Texture* wardingtotem = 0;
SDL_Texture* movespeedicon = 0;
SDL_Texture* rangeicon = 0;
SDL_Texture* cdricon = 0;
SDL_Texture* mricon = 0;
SDL_Texture* armoricon = 0;
SDL_Texture* criticon = 0;
SDL_Texture* adicon = 0;
SDL_Texture* apicon = 0;
SDL_Texture* attackspeedicon = 0;
SDL_Texture* minionranged = 0;
SDL_Texture* minionmelle = 0;
SDL_Texture* minioncannon = 0;
SDL_Texture* cursor = 0;
SDL_Texture* attackcursor = 0;
SDL_Texture* redmelle = 0;
SDL_Texture* redcannon = 0;
SDL_Texture* redranged = 0;
SDL_Texture* brokenturret = 0;
SDL_Texture* buylightup = 0;
SDL_Texture* selllightup = 0;
SDL_Texture* blitzhand = 0;
SDL_Texture* minimapbackground = 0;
SDL_Texture* redcircle = 0;
SDL_Texture* bluecircle = 0;
SDL_Texture* map11 = 0;
SDL_Texture* bluetowericon = 0;
SDL_Texture* redtowericon = 0;

int countedFrames = 0;
LTimer fpsTimer;
LTimer thetimer;

bool leave = false;

const double MS_PER_UPDATE = 20; //milliseconds

void ScreenSizeChangeTrigger(int& width, int& height, Game & thegame);
void Handlefpstimer(int& countedframe, LTimer& fpstimer);
void HandleInput();
void ResetInput();
bool init();
bool loadmedia();
SDL_Texture* loadtext(string s, SDL_Color textcolor);
SDL_Texture* loadtexture(string a);
void close();
int main(int argc, char* argv[])
{
	thetimer.start();
	srand(time(0));
	init();
	loadmedia();
	ResetInput();

	Game thegame;
	int screenwidthsave = screenwidth;
	int screenheightsave = screenheight;

	double previous = thetimer.getTicks();
	double lag = 0.0;

	while (leave == false)
	{	
		/*							MAIN LOOP							 */
		auto start = high_resolution_clock::now();

		ScreenSizeChangeTrigger(screenwidthsave, screenheightsave, thegame);

		SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
		SDL_RenderClear(grender);
		SDL_RenderDrawRect(grender, 0);
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
		
		double current = thetimer.getTicks();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;
		//cout << elapsed << endl;
		HandleInput();
		thegame.Print();
		thegame.Update();
		Handlefpstimer(countedFrames, fpsTimer);
		ResetInput();
		//cout << elapsed << endl;
		if (16.667 - elapsed > 0)
		{
			SDL_Delay(16.667 - elapsed);
		}
		/*while (lag >= MS_PER_UPDATE)
		{
			thegame.Update();
			ResetInput();
			lag -= MS_PER_UPDATE;
		}*/
		
		SDL_RenderPresent(grender);
		
		if (showframetime)
		{
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Time to finish whole run: "
				<< duration.count() << "microseconds" << endl;
		}
	}

	close();
	return 0;
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Could not initialize SDL";
		success = false;
	}
	else
	{
		gwindow = SDL_CreateWindow("League of Legends", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);//| SDL_WINDOW_BORDERLESS
		if (gwindow == 0)
		{
			cout << "could not create window";
			success = false;
		}
		else
		{
			gsurface = SDL_GetWindowSurface(gwindow);
			if (gsurface == 0)
			{
				cout << "could not upload surface";
				success = false;
			}
			else
			{
				int flags = IMG_INIT_PNG;
				if ((IMG_Init(flags) & flags) != flags)
				{
					cout << "failed to initialize png";
					success = false;
				}
				if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				{
					cout << "failed to scale quality";
				}
				grender = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawColor(grender, 255, 255, 255, 255);
				TTF_Init();
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
			
		}
	}
	SDL_ShowCursor(SDL_DISABLE);
	return success;
}
bool loadmedia()
{
	SDL_Color white = { 0,0,0 };
	gFont = TTF_OpenFont("TimesTenLTStd-Roman.otf",18);
	ttftest = loadtext("supdude", white);

	LeagueMap = loadtexture("leaguemapmiddle.JPG");
	BlitzIdle = loadtexture("blitzidle.PNG");
	BlitzGrab = loadtexture("blitzgrab.PNG");
	ShopMenu = loadtexture("shopmenu.PNG");
	ShopeSideScroll = loadtexture("sidescrollshop.PNG");
	Infinityedgeimage = loadtexture("Infinity_Edge_item.PNG");
	
	ImageBfSword = loadtexture("B._F._Sword_item.PNG");
	ImagePickAxe = loadtexture("Pickaxe_item.PNG");
	ImageClockAgility = loadtexture("Cloak_of_Agility.PNG");
	ImageMorrello = loadtexture("Morellonomicon_item.PNG");
	ImageBlastingRod = loadtexture("Blasting_Wand_item.PNG");
	ImageOblivionOrb = loadtexture("Oblivion_Orb.PNG");
	ImageAmplifyingTome = loadtexture("Amplifying_Tome_item.PNG");
	ImageRubyCrystal = loadtexture("Ruby_Crystal_item.PNG");
	ImagePhantomDancer = loadtexture("Phantom_Dancer_item.PNG");
	ImageBrawlersGloves = loadtexture("Brawler's_Gloves_item.PNG");
	ImageDagger = loadtexture("Dagger_item.PNG");
	ImageZeal = loadtexture("Zeal_item.PNG");
	ImageSpiritVisage = loadtexture("Spirit_Visage_item.PNG");
	ImageSpectresCowl = loadtexture("Spectre's_Cowl_item.PNG");
	ImageKindleGem = loadtexture("Kindlegem_item.PNG");
	ImageNullMantle = loadtexture("Null-Magic_Mantle_item.PNG");
	ImageRanduins = loadtexture("Randuin's_Omen_item.PNG");
	ImageGiantsBelt = loadtexture("Giant's_Belt_item.PNG");
	ImageClothArmor = loadtexture("Cloth_Armor_item.PNG");
	ImageWardensMail = loadtexture("Warden's_Mail_item.PNG");
	ImageWarmogs = loadtexture("Warmog's_Armor_item.PNG");
	ImageCrystallineBracer = loadtexture("Crystalline_Bracer_item.PNG");
	ImageRejuveBeads = loadtexture("Rejuvenation_Bead_item.PNG");
	ImageBoots = loadtexture("Boots_of_Speed_item.PNG");
	descriptionbox = loadtexture("descriptionbox.PNG");
	goldimage = loadtexture("Gold.PNG");
	ImageBloodThirster = loadtexture("The_Bloodthirster_item.PNG");
	playeruibackground = loadtexture("playeruibackground.PNG");
	blitzq = loadtexture("blitzq.PNG");
	blitzw = loadtexture("blitzw.PNG");
	blitze = loadtexture("blitze.PNG");
	blitzr = loadtexture("blitzr.PNG");
	blitzpassive = loadtexture("blitzpassive.PNG");
	flash = loadtexture("flash.PNG");
	tp = loadtexture("teleport.PNG");
	wardingtotem = loadtexture("wardingtotem.PNG");
	blitzicon = loadtexture("blitzcrankicon.PNG");
	movespeedicon = loadtexture("Movement_speed_icon.PNG");
	rangeicon = loadtexture("Range_icon.PNG");
	cdricon = loadtexture("Cooldown_reduction_icon.PNG");
	mricon = loadtexture("Magic_resistance_icon.PNG");
	armoricon = loadtexture("Armor_icon.PNG");
	criticon = loadtexture("Critical_strike_chance_icon.PNG");
	adicon = loadtexture("Attack_damage_icon.PNG");
	apicon = loadtexture("Ability_power_icon.PNG");
	attackspeedicon = loadtexture("Attack_speed_icon.PNG");
	minionranged = loadtexture("minionranged.PNG");
	minionmelle = loadtexture("minionmelle.PNG");
	minioncannon = loadtexture("minioncannon.PNG");
	cursor = loadtexture("cursor.PNG");
	attackcursor = loadtexture("attackcursor.PNG");
	redmelle = loadtexture("redmelle.PNG");
	redcannon = loadtexture("redcannon.PNG");
	redranged = loadtexture("redranged.PNG");
	brokenturret = loadtexture("brokenturret.PNG");
	buylightup = loadtexture("buylightup.PNG");
	selllightup = loadtexture("selllightup.PNG");
	blitzhand = loadtexture("blitzhand.PNG");
	minimapbackground = loadtexture("minimapcolor.PNG");
	redcircle = loadtexture("redcircle2.PNG");
	bluecircle = loadtexture("bluecircle2.PNG");
	map11 = loadtexture("map11.PNG");
	bluetowericon = loadtexture("bluetowericon.PNG");
	redtowericon = loadtexture("redtowericon.PNG");

	return 1;
}
SDL_Texture* loadtexture(string a)
{
	SDL_Texture* returntexture = 0;
	SDL_Surface* tempsurface = IMG_Load(a.c_str());
	//SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 255, 255, 255));
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
SDL_Texture* loadtext(string s, SDL_Color textcolor)
{

	//Render text surface
	SDL_Texture* mTexture = 0;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, s.c_str(), textcolor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(grender, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture;
}
void close()
{
	SDL_DestroyRenderer(grender);
	SDL_DestroyWindow(gwindow);
	gwindow = 0;
	SDL_FreeSurface(gsurface);
	gsurface = 0;

	SDL_Quit();
	IMG_Quit();
}
void ScreenSizeChangeTrigger(int& width, int& height, Game & thegame)
{

	if (screenheight != height || screenwidth != width)
	{
		cout << "Screen Size Changed" << endl;
		height = screenheight;
		width = screenwidth;
		thegame.ScreenSizeTrigger();
	}
}
void Handlefpstimer(int& countedframe, LTimer& fpstimer)
{
	stringstream timetext;
	SDL_Rect fpsrect = { screenwidth - 100,0,125,50 };
	if (static_cast<int>(fpstimer.getTicks() % 1000) <= 0)
	{
		countedframe = 0;
		fpstimer.start();
	}
	double avgFPS = static_cast<double>(countedframe) / (fpstimer.getTicks() / 1000.0);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	timetext.str("");
	timetext << "FPS: " << avgFPS;
	SDL_Color black = { 0,0,0 };
	Font fpstexture(timetext.str().c_str(), "black");
	fpstexture.Print(grender, fpsrect);
	fpstexture.FreeTexture();
	countedframe++;
}
void ResetInput()
{
	ButtonDownOnce = false;
	ButtonRightOnce = false;
	ButtonLeftOnce = false;
	upKeyState = 0;
	downKeyState = 0;
	leftKeyState = 0;
	rightKeyState = 0;
	QKeyState = 0;
	EKeyState = 0;
	RKeyState = 0;
	AKeyState = 0;
	WKeyState = 0;
	SKeyState = 0;
	DKeyState = 0;
	MouseState = 0;
	IKeyState = 0;
	XKeyState = 0;
	TKeyState = 0;
	CKeyState = 0;
	VKeyState = 0;
	BKeyState = 0;
	NKeyState = 0;
}
void HandleInput()
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			leave = true;
		}
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				screenwidth = e.window.data1;
				screenheight = e.window.data2;
			}
		}
		else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: upKeyState = true; break;
			case SDLK_DOWN: downKeyState = true; break;
			case SDLK_LEFT: leftKeyState = true; break;
			case SDLK_RIGHT: rightKeyState = true; break;
			case SDLK_q: QKeyState = true; break;
			case SDLK_e: EKeyState = true; break;
			case SDLK_r: RKeyState = true; break;
			case SDLK_w: WKeyState = true; break;
			case SDLK_a: AKeyState = true; break;
			case SDLK_s: SKeyState = true; break;
			case SDLK_d: DKeyState = true; break;
			case SDLK_i: IKeyState = true; break;
			case SDLK_x: XKeyState = true; break;
			case SDLK_t: TKeyState = true; break;
			case SDLK_c: CKeyState = true; break;
			case SDLK_v: VKeyState = true; break;
			case SDLK_b: BKeyState = true; break;
			case SDLK_n: NKeyState = true; break;
			case SDLK_RETURN:	break;
			case SDLK_BACKSPACE:break;
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{

		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			ButtonDown = true;
			ButtonDownOnce = true;
			if (e.button.button == SDL_BUTTON_RIGHT)
			{
				ButtonRightOnce = true;
			}
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				ButtonLeftOnce = true;
				ButtonLeftHold = true;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			ButtonDown = false;
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				ButtonLeftHold = false;
			}
		}
		if (e.type == SDL_MOUSEWHEEL)
		{
			MouseState = e.wheel.y;
			MouseStateNoClear = e.wheel.y;
		}
		if (e.type != SDL_MOUSEWHEEL)
		{
			MouseStateNoClear = 0;
		}
	}
}