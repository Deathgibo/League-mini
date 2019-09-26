#pragma once
#include "Map.h"
#include "myglobal.h"
#include "MiniMap.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Map Info
6093 x 5090
starting bot side 400,5070-700,700,700
starting top side 5200,200,700,700
*Player camera has to match screenwidth and height, you ask the image to cut out something ur screens size it does and plops it on our screen
note that you cantbe asking something too big for your screen or it will have to shrink it, or too small it will have to stretch unless you put whiteness around
wont be able to zoom in a cost i will take
*/
Map::Map()
{
	extern int screenwidth;
	extern int screenheight;
	extern SDL_Texture* LeagueMap;

	PlayerCamera = { 1200,4570-screenheight,screenwidth,screenheight };

	MapTexture = LeagueMap;

	HitBoxes.clear();
	MapLoadHitBoxesFromFile();
	StartingHitBoxes = HitBoxes;
	/*set all the startinhitbox center points for our physics*/
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		StartingHitBoxes[i].bestfitcenter = StartingHitBoxes[i].GetBestFitCenter();
	}
	for (int i = 0; i < HitBoxes.size(); i++)
	{
		HitBoxesTriangles.push_back(HitBoxes[i].Triangulate());
	}
	StartingHitBoxesTriangles = HitBoxesTriangles;
	minionmidlane.p1.x = 1300; minionmidlane.p1.y = 4200;
	minionmidlane.p2.x = 5200; minionmidlane.p2.y = 1000;
}
void Map::Initialize()//just for image
{
	extern SDL_Texture* LeagueMap;
	MapTexture = LeagueMap;
}
void Map::MoveMap(double x, double y)//*this is most expensive but you dont need this when you run the game because you dont need to print hitboxes!
{
	//physics are on the maplocations so we only want to visually move the ones in camera box
	if (!showhitboxes)
	{
		return;
	}
	int counter = 0;
	for (int i = 0; i < HitBoxes.size(); i++)
	{
		//HitBoxes[i].Move(x, y);
		for (int j = 0; j < HitBoxes[i].Vertices.size(); j++)
		{
			HitBoxes[i].Vertices[j].x = StartingHitBoxes[i].Vertices[j].x - PlayerCamera.x;
			HitBoxes[i].Vertices[j].y = StartingHitBoxes[i].Vertices[j].y - PlayerCamera.y;
			counter++;
		}
	}
	for (int i = 0; i < HitBoxesTriangles.size(); i++)
	{
		for (int t = 0; t < HitBoxesTriangles[i].size(); t++)
		{
			for (int p = 0; p < 3; p++)
			{
				HitBoxesTriangles[i][t].points[p].x = StartingHitBoxesTriangles[i][t].points[p].x - PlayerCamera.x;
				HitBoxesTriangles[i][t].points[p].y = StartingHitBoxesTriangles[i][t].points[p].y - PlayerCamera.y;
				counter++;
			}
		}
	}
	//cout << counter << endl;
}
vector<Polygon> Map::GetHitBoxesCopy()
{
	return HitBoxes;
}
void Map::Print(SDL_Renderer* grender)
{
	SDL_RenderCopy(grender, MapTexture,&PlayerCamera , 0);
	SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	if (showhitboxes)
	{
		for (int i = 0; i < HitBoxesTriangles.size(); i++)
		{
			for (int j = 0; j < HitBoxesTriangles[i].size(); j++)
			{
				HitBoxesTriangles[i][j].Print(grender);
			}
		}
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
		for (int i = 0; i < HitBoxes.size(); i++)
		{
			HitBoxes[i].Print(grender);
		}
	}
}
SDL_Rect Map::GetPlayerCameraCopy()
{
	return PlayerCamera;
}
void Map::MovePlayerCamera(int x, int y)
{
	extern int screenwidth;
	extern int screenheight;
	PlayerCamera.x += x;
	PlayerCamera.y += y;
	if (PlayerCamera.x < 0 || PlayerCamera.x + PlayerCamera.w > MapScreenWidth)
	{
		PlayerCamera.x -= x;
	}
	if (PlayerCamera.y < 0 || PlayerCamera.y + PlayerCamera.h > MapScreenHeight)
	{
		PlayerCamera.y -= y;
	}
	MoveMap(0, 0);
}
void Map::ZoomPlayerCamera(int w, int h)
{
	PlayerCamera.w += w;
	PlayerCamera.h += h;
	if (PlayerCamera.x + PlayerCamera.w >= MapScreenWidth || PlayerCamera.w < 1)
	{
		PlayerCamera.w -= w;
		PlayerCamera.h -= h;
	}
	else if (PlayerCamera.y + PlayerCamera.h > MapScreenHeight || PlayerCamera.h < 1)
	{
		PlayerCamera.w -= w;
		PlayerCamera.h -= h;
	}

}
void Map::UpdateMap()
{
	extern int screenwidth;
	extern int screenheight;
	extern int MouseState;
	extern MiniMap theminimap;
	int x, y;
	SDL_GetMouseState(&x, &y);
	PlayerCamera.w = screenwidth;
	PlayerCamera.h = screenheight;
	int amount = 25;
	bool cameramoved = false;
	myglobal global;
	if (global.PointInsideRect(theminimap.minimaprect, x, y))
	{
	}
		if (x < amount)
		{
			MovePlayerCamera(-CameraMoveSpeed, 0);
			cameramoved = true;
		}
		if (x > screenwidth - amount)
		{
			MovePlayerCamera(CameraMoveSpeed, 0);
			cameramoved = true;
		}
		if (y < amount)
		{
			MovePlayerCamera(0, -CameraMoveSpeed);
			cameramoved = true;
		}
		if (y > screenheight - amount)
		{
			MovePlayerCamera(0, CameraMoveSpeed);
			cameramoved = true;
		}
		if (cameramoved)
		{
			//MoveMap(0, 0);//update hitboxes after camera has moved
		}

	if (mapeditormode)
	{
		MapEditor(x, y);
	}

	//moving map zoom
	/*int speed = 24;//pref an even number because these are ints
	if (MouseState == 1)
	{
		ZoomPlayerCamera(-speed, -speed);
		MovePlayerCamera(speed/2, speed/2);
	}
	if (MouseState == -1)
	{
		ZoomPlayerCamera(speed, speed);
		MovePlayerCamera(-speed/2, -speed/2);

	}*/
}
void Map::MapEditor(int x,int y)
{
	extern bool XKeyState;
	extern bool TKeyState;
	extern bool NKeyState;
	extern bool VKeyState;
	extern bool ButtonDown;
	extern bool BKeyState;
	extern bool CKeyState;
	//edit map moving polygons
	if (ButtonDown)
	{
		if (hitboxindex == -1)
		{
			for (int i = 0; i < HitBoxes.size(); i++)
			{
				if (HitBoxes[i].PointInsidePolygon(x, y))
				{
					hitboxindex = i;
				}
			}
		}
		if (hitboxindex != -1)
		{
			int pointindexsave = pointindex;
			pointindex = HitBoxes[hitboxindex].WhatPointClicked(x, y);
			if (pointindex == -1)
			{
				pointindex = pointindexsave;
			}
		}
		if (pointindex != -1 && hitboxindex != -1)
		{
			StartingHitBoxes[hitboxindex].SetVertex(x + PlayerCamera.x, y + PlayerCamera.y, pointindex);
			MoveMap(0, 0);
		}
	}
	//edit map add sides to polygons
	if (TKeyState)
	{
		if (hitboxindex == HitBoxes.size()-1)
		{
			HitBoxesTriangles.push_back(StartingHitBoxes[hitboxindex].Triangulate());
			StartingHitBoxesTriangles.push_back(StartingHitBoxes[hitboxindex].Triangulate());
		}
	}
	if (XKeyState)
	{
		hitboxindex = -1;
	}
	if (CKeyState)
	{
		if (hitboxindex != -1)
		{
			StartingHitBoxes[hitboxindex].AddVertices(1);
			HitBoxes[hitboxindex].AddVertices(1);
		}
	}
	if (VKeyState)
	{
		Polygon tmppoly;
		HitBoxes.push_back(tmppoly);
		StartingHitBoxes.push_back(tmppoly);
		StartingHitBoxes[StartingHitBoxes.size() - 1].Move(PlayerCamera.x + x - 100, PlayerCamera.y + y - 100);
	}
	if (BKeyState)
	{
		if (hitboxindex != -1)
		{
			StartingHitBoxes.erase(StartingHitBoxes.begin() + hitboxindex);
			HitBoxes.erase(HitBoxes.begin() + hitboxindex);
		}
		//StartingHitBoxes.pop_back();
		//HitBoxes.pop_back();
	}
	if (NKeyState)
	{
		MapSaveHitBoxes();
	}
}
void Map::MapSaveHitBoxes()/* save startinghitbox information */
{
	cout << "saving map..." << endl;
	string savename = "MapInformation.txt";
	fstream file;
	file.open(savename, ios::out);
	file.close();
	for (int i = 0; i < StartingHitBoxes.size(); i++)
	{
		file.open(savename, ios::app);
		for (int j = 0; j < StartingHitBoxes[i].Vertices.size(); j++)
		{
			file << StartingHitBoxes[i].Vertices[j].x << "," << StartingHitBoxes[i].Vertices[j].y << " ";
		}
		file << "!" << endl;
		file.close();
	}
	file.open(savename, ios::app);
	file << "$" << endl;
	file.close();
	cout << "map successfully saved!" << endl;
}
void Map::MapLoadHitBoxesFromFile()
{
	string holder;
	string loadname = "MapInformation.txt";
	fstream file;
	file.open(loadname);
	if (file.peek() == -1 || file.peek() == 36)
	{
		cout << "file empty..." << endl;
		file.close();
		return;
	}
	bool leave1 = false;
	while (!leave1)
	{
		Polygon tmppoly;
		HitBoxes.push_back(tmppoly);
		HitBoxes[HitBoxes.size() - 1].Vertices.clear();
		bool leave2 = false;
		while (!leave2)
		{
			getline(file, holder, ',');
			int x = stoi(holder);
			getline(file, holder, ' ');
			int y = stoi(holder);
			Vertex tmp(x, y);
			HitBoxes[HitBoxes.size() - 1].Vertices.push_back(tmp);
			if (file.peek() == 33)
			{
				getline(file, holder);
				leave2 = true;
			}
		}
		if (file.peek() == 36)
		{
			leave1 = true;
		}
	}
	file.close();
}