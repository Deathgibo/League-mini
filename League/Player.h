#pragma once
#include "Polygon.h"
#include "Item.h"
#include "Map.h"

class Minion;
class Tower;
class PlayerAbility;
//can make a simple state with enums, like stunned, silenced, walking, idol, abilitycast
class Player
{
public:
	Player();
	void Initialize();
	void Move(bool originalclick = 0);
	void Move(double x, double y, bool originalclick = 0);
	void UpdatePlayer();
	void UpdateHitBox();
	void Physics();
	bool TriangleCollision(Triangle one, Triangle two);//this will go in the physics class
	inline double Det2D(Vertex p1, Vertex p2, Vertex p3);
	void CheckTriWinding(Vertex& p1, Vertex& p2, Vertex& p3, bool allowReversed);
	bool BoundaryDoesntCollideChk(Vertex p1, Vertex p2, Vertex p3, double eps);
	void Print(SDL_Renderer* grender);
	void Respawn();
	void DamagePlayer(double damage);
	void GiveItem(Item& item);
	void AddStats(Item& item);
	void SubStats(Item& item);
	vector<Polygon> GetClosePolygons();					//gets all the close polygons so the player doesnt have to check all of them with physics
	bool CollisionSeeIfPlayerCanHopOff();				//algorithm to determine if the player can hop off the polygon when hes circling it
	bool CollisionSeeIfPointCanHopOff(Vertex thepoint);	//when determining longest path need this to see when the vertex on the polygon can stop and where the player would get off
	bool CollisionWhatDirectiontogo();					//determines what direction player should go when he just reached a polygon, based on distance of both paths
	
	/*stats*/
	int maxhealth;
	double currenthealth;
	int maxmana;
	double currentmana;
	int gold;
	float AD;
	float AP;
	float MR;
	float ARMOR;
	float ATKSPEED;
	float CRIT;
	float CDR;
	float HEALTHREGEN;
	float MAGICPEN;
	float MOVESPEED = 3;
	float LIFESTEAL;
	int playerlevel;
	double RANGE; 
	double shield = 0;
	
	bool BotSide = true;
	Vertex Dimensions;
	Vertex Velocity;
	Vertex Position;
	Vertex MapPosition;
	Polygon HitBox;
	vector<Triangle> HitBoxTriangles;
	vector<Triangle> StartingHitBoxTriangles;
	SDL_Texture* Image;

	vector<Item*> items;

	PlayerAbility* player1abilities;
	Minion* targetminion;
	Tower* targettower;

	bool autoing = false;				//this boolean tells what cursor to print

	/*movement variables*/
	bool MovePath = false;				//true if your moving to where you recently clicked
	bool MoveBack = false;				//true if you hit something and need to move back (only for triangle physics though)
	Vertex destination;					//the place where the player clicked, not the algorithm
	Polygon* polygonhit;				//the polygon which you hit when doing move algorithm
	int polyindexone = 100;				//the index of the polygon line you hit
	int polyindextwo = 100;				//the  other index of the polygon line you hit
	bool circlingpolygon = false;		//means your going around the polygon trying to find a spot you can hop off
	vector<Polygon*> pastpolys;			//holds the past polygons you have been on when trying to reach destination, should clear every time you reset movement
	bool dirright = false;				//if your circling the polygon this tells you what direction to go, right it adding to index, left is subtracting index
	vector<Polygon> closepolygons;

	int attackcounter = 200;
private:

	double angle = 0;
	Vertex clickposition;
	SDL_Rect BlackHealthBar;
	SDL_Rect ColoredHealthBar;
};