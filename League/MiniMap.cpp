#include "MiniMap.h"
#include "Map.h"
#include "Player.h"
#include "Minion.h"
#include "Tower.h"
#include "myglobal.h"
#include <iostream>
#include <vector>
using namespace std;


MiniMap::MiniMap()
{
	extern int screenwidth;
	extern int screenheight;
	extern SDL_Texture* LeagueMap;
	extern Map themap;

	image = LeagueMap;

	minimaprect.w = 100 * screenwidth / 1000;
	minimaprect.h = (.839344*minimaprect.w); //keeping resolution of map
	minimaprect.x = screenwidth - minimaprect.w;
	minimaprect.y = screenheight - minimaprect.h;
	
	StartingHitBoxes = themap.StartingHitBoxes;
	ZoomShapes();
	Updateminimapposition();
}
void MiniMap::Initialize()
{
	extern int screenwidth;
	extern int screenheight;
	extern SDL_Texture* LeagueMap;

	image = LeagueMap;

	Updateminimapposition();
}
void MiniMap::Updateminimapposition()
{
	/*if i want to do this so it fits whatever thing, find ratio of width and height of shapes by getting leftmost,rightmost and subtracting
	then just lock bottomleft right to the x,y of the minimaprect, then just scan increasing the zoom until the rightmost minus leftmost is equal to minimap width*/

	extern int screenwidth;
	extern int screenheight;
	extern Map themap;

	minimaprect.w = 180 * screenwidth / 1000;
	minimaprect.h = (.78*minimaprect.w); //keeping resolution of map
	minimaprect.x = screenwidth - minimaprect.w;
	minimaprect.y = screenheight - minimaprect.h;

	//update shapes again
	StartingHitBoxes = themap.StartingHitBoxes;
	ZoomShapes();
	double xamount = 0;
	double yamount = 0;
	//find lowesty out of all the points
	//find the lowest x out of all the points
	double lowesty = 100000;
	Vertex lowestyindex;
	double lowestx = 100000;
	Vertex lowestxindex;
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		for (int j = 0; j < StartingHitBoxes[i].Vertices.size(); j++)
		{
			if (StartingHitBoxes[i].Vertices[j].y < lowesty)
			{
				lowesty = StartingHitBoxes[i].Vertices[j].y;
				lowestyindex.x = i;
				lowestyindex.y = j;
			}
			if (StartingHitBoxes[i].Vertices[j].x < lowestx)
			{
				lowestx = StartingHitBoxes[i].Vertices[j].x;
				lowestxindex.x = i;
				lowestxindex.y = j;
			}
		}
	}
	xamount = StartingHitBoxes[lowestxindex.x].Vertices[lowestxindex.y].x;
	yamount = StartingHitBoxes[lowestyindex.x].Vertices[lowestyindex.y].y;;
	//xamount + z = therect.x
	MoveShapes(minimaprect.x - xamount, minimaprect.y - yamount);
}
void MiniMap::Print()
{
	extern vector<Minion> minions;
	extern vector<Tower> towers;
	extern Map themap;
	extern SDL_Renderer* grender;
	extern SDL_Texture* minimapbackground;
	extern SDL_Texture* map11;
	extern SDL_Texture* blitzicon;
	extern SDL_Texture* redcircle;
	extern SDL_Texture* bluecircle;
	extern SDL_Texture* bluetowericon;
	extern SDL_Texture* redtowericon;


	/*print background*/
	SDL_RenderCopy(grender, minimapbackground, 0, &minimaprect);

	/*print shapes*/
	SDL_SetRenderDrawColor(grender, 0, 51, 0, 0);
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		StartingHitBoxes[i].Print(grender);
	}
	//StartingHitBoxes[0].PrintVerticesInfo();

	/*print minion dots*/
	for (int i = 0; i < minions.size(); i++)
	{
		Vertex minionratio = MinionRatioWithMap(minions[i]);
		SDL_Rect minionrect = { 0,0,0,0 };
		minionrect.w = 4 * minimaprect.x / 1000;
		minionrect.h = 6 * minimaprect.y / 1000;
		minionrect.x = minimaprect.x + (minionratio.x*minimaprect.w) - (minionrect.w / 2);
		minionrect.y = minimaprect.y + (minionratio.y*minimaprect.h) - (minionrect.h / 2);
		if (minions[i].BotSide)
			SDL_RenderCopy(grender, bluecircle, 0, &minionrect);
		else
			SDL_RenderCopy(grender, redcircle, 0, &minionrect);
	}

	/*print tower icon*/
	for (int i = 0; i < towers.size(); i++)
	{
		Vertex towerratio = TowerRatioWithMap(towers[i]);
		SDL_Rect towerrect = { 0,0,0,0 };
		towerrect.w = 10 * minimaprect.x / 1000;
		towerrect.h = 35 * minimaprect.y / 1000;
		towerrect.x = minimaprect.x + (towerratio.x*minimaprect.w) - (towerrect.w / 2);
		towerrect.y = minimaprect.y + (towerratio.y*minimaprect.h) - (towerrect.h / 2);
		if (towers[i].alive)
		{
			if (towers[i].BotSide)
				SDL_RenderCopy(grender, bluetowericon, 0, &towerrect);
			else
				SDL_RenderCopy(grender, redtowericon, 0, &towerrect);
		}
	}
	/* print player icon */
	Vertex playerratio = PlayerRatioWithMap();
	SDL_Rect playerrect = { 0,0,0,0 };
	playerrect.w = 15 * minimaprect.x / 1000;
	playerrect.h = 25 * minimaprect.y / 1000;
	playerrect.x = minimaprect.x + (playerratio.x*minimaprect.w) - (playerrect.w/2);
	playerrect.y = minimaprect.y + (playerratio.y*minimaprect.h) - (playerrect.h/2);
	//cout << playerratio.x << " " << playerratio.y << endl;
	SDL_RenderCopy(grender, blitzicon, 0, &playerrect);
}
void MiniMap::Update()
{
	extern bool ButtonRightOnce;
	extern bool ButtonLeftOnce;
	extern bool ButtonLeftHold;
	extern Player theplayer;
	extern Map themap;
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	/*move player from mini map*/
	myglobal global;
	if (ButtonRightOnce && global.PointInsideRect(minimaprect, x, y))
	{
		Vertex mouseratio = MouseRatioWithMap();
		theplayer.Move(mouseratio.x - themap.PlayerCamera.x, mouseratio.y - themap.PlayerCamera.y,1);
	}
	/*move camera from mini map*/
	if (ButtonLeftHold && global.PointInsideRect(minimaprect, x, y))
	{
		Vertex mouseratio = MouseRatioWithMap();
		//cout << mouseratio.x << " " << mouseratio.y << endl;
		themap.MovePlayerCamera(mouseratio.x - themap.PlayerCamera.x - (themap.PlayerCamera.w/2), mouseratio.y - themap.PlayerCamera.y - (themap.PlayerCamera.h / 2));
	}

}
void MiniMap::ZoomShapes()
{
	extern int screenwidth;
	extern int screenheight;
	//33000

	double x = 33000.0 / screenwidth;

	mat2x2 rotatematrix;
	rotatematrix.column1x = 1.0/x;
	rotatematrix.column1y = 0;
	rotatematrix.column2x = 0;
	rotatematrix.column2y = 1.0/x;

	//league map dimensions 12200 x 10240
	/*center point to zoom to */
	int mx = 12200/2;
	int my = 10240/2;
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		for (int j = 0; j < StartingHitBoxes[i].Vertices.size(); j++)
		{
			StartingHitBoxes[i].Vertices[j] = rotatematrix.matrixvectorMult(StartingHitBoxes[i].Vertices[j], mx, my);
		}
	}
	//StartingHitBoxes[0].PrintVerticesInfo();
}
void MiniMap::MoveShapes(double x, double y)
{
	extern Map themap;
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		for (int j = 0; j < StartingHitBoxes[i].Vertices.size(); j++)
		{
			StartingHitBoxes[i].Vertices[j].x +=x;
			StartingHitBoxes[i].Vertices[j].y += y;
		}
	}
}
Vertex MiniMap::PlayerRatioWithMap()
{
	extern Map themap;
	extern Player theplayer;

	//league map dimensions 12200 x 10240
	//6093 x 5090

	//our minimap dimensions x : 5884  y:  4623    xleft 187 xright 6071 ybottom 5088 ytop 465

	Vertex ratios;
	int xamount = -550;
	int yamount = 1300;
	//ratios.x = (theplayer.MapPosition.x + xamount) / (6093 + xamount);
	//ratios.y = (theplayer.MapPosition.y + yamount) / (5090 + yamount);
	ratios.x = (theplayer.MapPosition.x - 187) / 5884;
	ratios.y = (theplayer.MapPosition.y - 465) / 4623;
	return ratios;
}
Vertex MiniMap::MinionRatioWithMap(Minion minion)
{
	extern Map themap;

	//league map dimensions 12200 x 10240
	//6093 x 5090

	//our minimap dimensions x : 5884  y:  4623    xleft 187 xright 6071 ybottom 5088 ytop 465

	Vertex ratios;
	//ratios.x = (minion.MapPosition.x - 300) / 6093;
	//ratios.y = (minion.MapPosition.y) / 5090;
	ratios.x = (minion.MapPosition.x - 187) / 5884;
	ratios.y = (minion.MapPosition.y - 465) / 4623;
	return ratios;
}
Vertex MiniMap::TowerRatioWithMap(Tower tower)
{
	extern Map themap;

	//league map dimensions 12200 x 10240
	//6093 x 5090

	//our minimap dimensions x : 5884  y:  4623    xleft 187 xright 6071 ybottom 5088 ytop 465

	Vertex ratios;
	//ratios.x = (minion.MapPosition.x - 300) / 6093;
	//ratios.y = (minion.MapPosition.y) / 5090;
	ratios.x = (tower.MapPosition.x - 187) / 5884;
	ratios.y = (tower.MapPosition.y - 465) / 4623;
	return ratios;
}
Vertex MiniMap::MouseRatioWithMap()
{
	extern Map themap;

	int x, y;
	SDL_GetMouseState(&x, &y);
	//league map dimensions 12200 x 10240
	//6093 x 5090

	//our minimap dimensions x : 5884  y:  4623    xleft 187 xright 6071 ybottom 5088 ytop 465


	//move all points on minimapover

	Vertex ratios;
	//ratios.x = (minion.MapPosition.x - 300) / 6093;
	//ratios.y = (minion.MapPosition.y) / 5090;
	//towerrect.x = minimaprect.x + (towerratio.x*minimaprect.w) - (towerrect.w / 2);
	//towerrect.y = minimaprect.y + (towerratio.y*minimaprect.h) - (towerrect.h / 2);
	
	//find ratio 
	double ratiox = static_cast<double>(x - minimaprect.x) / static_cast<double>(minimaprect.w);
	ratiox = ratiox * 5884 + 187;
	double ratioy = static_cast<double>(y - minimaprect.y) / static_cast<double>(minimaprect.h);
	ratioy = ratioy * 4623 + 465;
	ratios.x = ratiox;
	ratios.y = ratioy;
	return ratios;
}