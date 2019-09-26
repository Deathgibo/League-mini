#pragma once
#include "Polygon.h"
#include "Triangle.h"
struct TextureHolder
{
	SDL_Texture* Texture;
	SDL_Rect Texturerectangle;
};
class Map
{
public:
	Map();
	void Initialize();
	void MoveMap(double x, double y);
	vector<Polygon> GetHitBoxesCopy();
	SDL_Rect GetPlayerCameraCopy();
	void Print(SDL_Renderer* grender);
	void UpdateMap();
	void MovePlayerCamera(int x, int y);
	void ZoomPlayerCamera(int w, int h);
	void MapEditor(int x, int y);
	void MapSaveHitBoxes();
	void MapLoadHitBoxesFromFile();

	SDL_Rect PlayerCamera;
	int CameraMoveSpeed = 8;
	SDL_Texture* MapTexture;
	const int MapScreenWidth = 6093;
	const int MapScreenHeight = 5090;
	vector<Polygon> HitBoxes;
	vector<Polygon> StartingHitBoxes;
	vector<vector<Triangle>> HitBoxesTriangles;
	vector<vector<Triangle>> StartingHitBoxesTriangles;
	Edge minionmidlane; //the midlane line

private:
	//map editor stuff
	bool mapeditormode = false;
	bool showhitboxes = false;
	int pointindex = -1;
	int hitboxindex = -1;
};