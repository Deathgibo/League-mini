#pragma once
#include "Player.h"
#include "ItemShop.h"
#include "MiniMap.h"
#include <iostream>
#include <chrono>
#include "BlitzcrankAbilities.h"
using namespace std;
using namespace std::chrono;


Player::Player()
{
	extern Map themap;
	extern int screenheight;
	extern SDL_Texture* BlitzIdle;
	extern ItemShop itemshop;

	targetminion = 0;
	targettower = 0;
	player1abilities = new BlitzcrankAbilities(this);
	/*stats*/
	maxhealth = 2000;
	currenthealth = maxhealth;
	maxmana = 1000;
	currentmana = maxmana;
	AD = 68;
	gold = 500;
	AP = 10;
	MR = 50;
	ARMOR = 50;
	ATKSPEED = 1;
	CRIT = 0;
	CDR = 0;
	HEALTHREGEN = 0;
	MAGICPEN = 0;
	MOVESPEED = 3;
	LIFESTEAL = 0;
	playerlevel = 1;
	RANGE = 50;

	Dimensions.x = 100;
	Dimensions.y = 100;
	Velocity.x = 0;
	Velocity.y = 0;
	MapPosition.x = 600;
	MapPosition.y = 4800;
	clickposition.x = 0; clickposition.y = 0;
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
	HitBox.AddVertices(3);
	Image = BlitzIdle;
	HitBox.Vertices[0].x = MapPosition.x - 10; HitBox.Vertices[0].y = MapPosition.y + 15;
	HitBox.Vertices[1].x = MapPosition.x + 30; HitBox.Vertices[1].y = MapPosition.y + 15;
	HitBox.Vertices[2].x = MapPosition.x + 40; HitBox.Vertices[2].y = MapPosition.y + 35;
	HitBox.Vertices[3].x = MapPosition.x + 30; HitBox.Vertices[3].y = MapPosition.y + 45;
	HitBox.Vertices[4].x = MapPosition.x - 10; HitBox.Vertices[4].y = MapPosition.y + 45;
	HitBox.Vertices[5].x = MapPosition.x - 20; HitBox.Vertices[5].y = MapPosition.y + 35;
	StartingHitBoxTriangles = HitBox.Triangulate();
	for (int i = 0; i < StartingHitBoxTriangles.size(); i++)
	{
		StartingHitBoxTriangles[i].Move(-themap.PlayerCamera.x, -themap.PlayerCamera.y);
		HitBoxTriangles.push_back(StartingHitBoxTriangles[i]);
		StartingHitBoxTriangles[i].Move(themap.PlayerCamera.x, themap.PlayerCamera.y);
	}
	BlackHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };
	ColoredHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };

}
void Player::Initialize()
{
	extern Map themap;
	extern int screenheight;
	extern SDL_Texture* BlitzIdle;
	/*stats*/

	Dimensions.x = 100;
	Dimensions.y = 100;
	Velocity.x = 0;
	Velocity.y = 0;
	MapPosition.x = 600;
	MapPosition.y = 4800;
	clickposition.x = 0; clickposition.y = 0;
	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
	Image = BlitzIdle;
	BlackHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };
	ColoredHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };
}
void Player::UpdatePlayer()
{
	extern bool SKeyState;

	Move(1);
	if (SKeyState)
	{
		MovePath = false;
	}

	//auto start = high_resolution_clock::now();
	Physics();
	/*auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time to finish whole run: "
		<< duration.count() << "microseconds" << endl;*/

	player1abilities->AutoAttack(this);
	player1abilities->activateabilities(this);
	if (attackcounter < 200)
		attackcounter++;

	BlackHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };
	ColoredHealthBar = { static_cast<int>(MapPosition.x - Dimensions.x / 2 + 15),static_cast<int>(MapPosition.y - Dimensions.y / 2 - 10),static_cast<int>(Dimensions.x),5 };
}
void Player::UpdateHitBox()
{
	HitBox.Vertices[0].x = MapPosition.x - 10; HitBox.Vertices[0].y = MapPosition.y + 15;
	HitBox.Vertices[1].x = MapPosition.x + 30; HitBox.Vertices[1].y = MapPosition.y + 15;
	HitBox.Vertices[2].x = MapPosition.x + 40; HitBox.Vertices[2].y = MapPosition.y + 35;
	HitBox.Vertices[3].x = MapPosition.x + 30; HitBox.Vertices[3].y = MapPosition.y + 45;
	HitBox.Vertices[4].x = MapPosition.x - 10; HitBox.Vertices[4].y = MapPosition.y + 45;
	HitBox.Vertices[5].x = MapPosition.x - 20; HitBox.Vertices[5].y = MapPosition.y + 35;
}
bool Player::CollisionSeeIfPointCanHopOff(Vertex thepoint)
{
	extern SDL_Renderer* grender;

	myglobal global;

	/*make the line which is the vertex and destination*/
	Vertex p1(thepoint.x, thepoint.y);
	Vertex p2(destination.x, destination.y);



	/*if the made line is hitting any lines of the polygon (except for the ones that contain its own vertex) then player cannot hop off because he would go through wall*/
	for (int j = 0; j < polygonhit->Vertices.size(); j++)
	{
		int index2 = (j + 1) % polygonhit->Vertices.size();
		if (global.checktwolinecollision(p1, p2, polygonhit->Vertices[j], polygonhit->Vertices[index2]))
		{
			if (thepoint != polygonhit->Vertices[j] && thepoint != polygonhit->Vertices[index2])
			{
				return false;
			}
		}
	}
	return true;
}
bool Player::CollisionSeeIfPlayerCanHopOff()
{
	extern SDL_Renderer* grender;

	myglobal global;

	/*make the line which is the player position and destination*/
	Vertex p1(MapPosition.x, MapPosition.y + (3 * Dimensions.y / 10));
	Vertex p2(destination.x, destination.y);

	int theindex = polyindexone;
	if (sqrt(pow(p2.x - polygonhit->Vertices[polyindextwo].x,2) + pow(p2.y - polygonhit->Vertices[polyindextwo].y,2)) > 
		sqrt(pow(p2.x - polygonhit->Vertices[polyindexone].x, 2) + pow(p2.y - polygonhit->Vertices[polyindexone].y, 2)))
	{
		theindex = polyindextwo;
	}
	/*if the made line is hitting any lines of the polygon (except for the ones that contain its own vertex) then player cannot hop off because he would go through wall*/
	for (int j = 0; j < polygonhit->Vertices.size(); j++)
	{
		int index2 = (j + 1) % polygonhit->Vertices.size();
		if (global.checktwolinecollision(p1, p2, polygonhit->Vertices[j], polygonhit->Vertices[index2]))
		{
			if (j != theindex && index2 != theindex)
			{
				return false;
			}
		}
	}
	return true;
}
vector<Polygon>  Player::GetClosePolygons()
{
	extern Map themap;

	vector<Polygon> closepolys;
	double distance = 1000;//1000
	Vertex playercenter = HitBox.GetBestFitCenter();
	for (int i = 0; i < themap.StartingHitBoxes.size(); i++)
	{
		if (pow(themap.StartingHitBoxes[i].bestfitcenter.x - playercenter.x, 2) + pow(themap.StartingHitBoxes[i].bestfitcenter.y - playercenter.y, 2) < pow(distance,2))
		{
			closepolys.push_back(themap.StartingHitBoxes[i]);
		}
	}
	return closepolys;
}
bool Player::CollisionWhatDirectiontogo()//false left, true right
{
	/*    algorithm overview
	we make two partitions of the vertices on the polygon. We start with the two vertices the player is hitting one is always going to be decreasing
	and two is always going to be increasing to keep rotations uniform. For each partition we start with the first vertex then see if it is visible to our destination
	if it is then we are good else add the next vertex and repeat until we hit the halfway point. Once we have both partitions find the distance of both. The distance
	is the player to the first vertex, all the distances of the vertices in the partition, then the last vertex with destination. The one with lowest distance gets chosen
	*/
	vector<Vertex> partitionone;
	vector<Vertex> partitiontwo;
	
	/*calculate the middle point for the maximum the partitions can have each*/
	int number;
	if (polygonhit->Vertices.size() % 2 == 0)
	{
		number = (polygonhit->Vertices.size() / 2) - 1;
	}
	else
	{
		number = (polygonhit->Vertices.size() / 2);
	}

	/*to keep order one is always lowest out of the two and vice versa*/
	int therealpolyindexone = polyindexone;
	int therealpolyindextwo = polyindextwo;
	if (polyindexone - polyindextwo > 0)
	{
		therealpolyindexone = polyindextwo;
		therealpolyindextwo = polyindexone;
	}

	/*make partition one checking if its visible to destination each vertex*/
	partitionone.push_back(polygonhit->Vertices[therealpolyindexone]);
	for (int i = 1; i < number+1; i++)
	{
		int theindex = (4*polygonhit->Vertices.size() + therealpolyindexone - i) % polygonhit->Vertices.size();
		if (!CollisionSeeIfPointCanHopOff(polygonhit->Vertices[theindex]))
		{
			partitionone.push_back(polygonhit->Vertices[theindex]);
		}
		else
		{
			partitionone.push_back(polygonhit->Vertices[theindex]);
			break;
		}
	}

	/*make partition two checking if its visible to destination each vertex*/
	partitiontwo.push_back(polygonhit->Vertices[therealpolyindextwo]);
	for (int i = 1; i < number+1; i++)
	{
		int theindex = (therealpolyindextwo + i) % polygonhit->Vertices.size();
		if (!CollisionSeeIfPointCanHopOff(polygonhit->Vertices[theindex]))
		{
			partitiontwo.push_back(polygonhit->Vertices[theindex]);
		}
		else
		{
			partitiontwo.push_back(polygonhit->Vertices[theindex]);
			break;
		}
	}

	double distance1 = 0;
	double distance2 = 0;

	/*calculate distance 1*/
	distance1 += sqrt(pow(MapPosition.x - partitionone[0].x, 2) + pow(MapPosition.y + (3 * Dimensions.y / 10) - partitionone[0].y, 2));
	for (int i = 0; i < partitionone.size() - 1; i++)
	{
		distance1 += sqrt(pow(partitionone[i].x - partitionone[i+1].x, 2) + pow(partitionone[i].y - partitionone[i+1].y, 2));
	}
	distance1 += sqrt(pow(partitionone[partitionone.size() - 1].x - destination.x, 2) + pow(partitionone[partitionone.size() - 1].y - destination.y, 2));

	/*calculate distance 2*/
	distance2 += sqrt(pow(MapPosition.x - partitiontwo[0].x, 2) + pow(MapPosition.y + (3 * Dimensions.y / 10) - partitiontwo[0].y, 2));
	for (int i = 0; i < partitiontwo.size() - 1; i++)
	{
		distance2 += sqrt(pow(partitiontwo[i].x - partitiontwo[i + 1].x, 2) + pow(partitiontwo[i].y - partitiontwo[i + 1].y, 2));
	}
	distance2 += sqrt(pow(partitiontwo[partitiontwo.size() - 1].x - destination.x, 2) + pow(partitiontwo[partitiontwo.size() - 1].y - destination.y, 2));

	/*return lowest distance*/
	if (distance1 <= distance2)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Player::Physics()
{
	extern SDL_Renderer* grender;
	extern Map themap;

	myglobal global;


	/*if your circling the polygon see if we've stopped moving then see if the destination is visible if it is go there, else go to the next vertex on the polygon*/
	if (circlingpolygon)
	{
		if (!MovePath)
		{	
			if (CollisionSeeIfPlayerCanHopOff())
			{
				Move(destination.x - themap.PlayerCamera.x, destination.y - themap.PlayerCamera.y);
				pastpolys.push_back(polygonhit);
				circlingpolygon = false;
			}
			else
			{
				/*picks which direction to go if right add index, left subtract index*/
				if (dirright)
				{
					polyindexone = (polyindexone + 1) % polygonhit->Vertices.size();
					polyindextwo = (polyindextwo + 1) % polygonhit->Vertices.size();
					Move(polygonhit->Vertices[polyindextwo].x - themap.PlayerCamera.x, polygonhit->Vertices[polyindextwo].y - themap.PlayerCamera.y);
				}
				else
				{
					if (polyindexone == 0)
						polyindexone = polygonhit->Vertices.size() - 1;
					else
						polyindexone = (polyindexone - 1) % polygonhit->Vertices.size();
					if (polyindextwo == 0)
						polyindextwo = polygonhit->Vertices.size() - 1;
					else
						polyindextwo = (polyindextwo - 1) % polygonhit->Vertices.size();
					Move(polygonhit->Vertices[polyindexone].x - themap.PlayerCamera.x, polygonhit->Vertices[polyindexone].y - themap.PlayerCamera.y);
				}
			}
		}
	}
	/*if were not circling check to see if were hitting any polygons so we can circle around it once hit*/
	else
	{
		if (!MovePath)//if your not moving no need to check physics
		{
			return;
		}

		/*for optomization get close polygons*/
		closepolygons = GetClosePolygons();
		//cout << closepolygons.size() << endl;

		/*for all the hitbox vertices check with each of the player vertice and see if any lines hit*/
		for (int i = 0; i < closepolygons.size(); i++)
		{
			for (int j = 0; j < closepolygons[i].Vertices.size(); j++)
			{
				int index2 = (j + 1) % closepolygons[i].Vertices.size();
				for (int k = 0; k < HitBox.Vertices.size(); k++)
				{
					int playerindex2 = (k + 1) % HitBox.Vertices.size();
					if (global.checktwolinecollision(HitBox.Vertices[k], HitBox.Vertices[playerindex2], closepolygons[i].Vertices[j], closepolygons[i].Vertices[index2]))
					{
						
						/*see if we hit any past poly*/
						bool samepolyhit = false;
						for (int x = 0; x < pastpolys.size(); x++)
						{
							if (pastpolys[x]->Equals(closepolygons[i]))
							{
								samepolyhit = true;
								
							}
						}
						if (!samepolyhit)
						{
							//themap.StartingHitBoxes[i].Vertices[j]

							polygonhit = &closepolygons[i];
							polyindexone = j;
							polyindextwo = index2;
							
							/*if destination is inside this polygon change destination*/
							if (polygonhit->PointInsidePolygon(destination.x, destination.y))
							{
								
								/*move point to most reasonable point outside it*/
								//create a line between destination and player, increment that line in the opposite slope then check every 5 or so until its not inside poly
								//then relocate our destination to that

								//slope1 = (one2.y - one.y) / (one2.x - one.x);
								//b1 = one2.y - slope1 * one2.x;
								double slope = (MapPosition.y - destination.y) / (MapPosition.x - destination.x);
								double b1 = MapPosition.y - slope * MapPosition.x;

								Vertex p1(destination.x, destination.y);
								Vertex p2(MapPosition.x, MapPosition.y);

								bool leave = false;
								bool dirright = true;
								if (MapPosition.x - p1.x < 0)
								{
									dirright = false;
								}
								bool dirup = true;
								if (MapPosition.y - p1.y < 0)
								{
									dirup = false;
								}
								while (!leave)
								{
									if (abs(slope) > 1)
									{
										if (dirup)
											p1.y -= 30;
										else
											p1.y += 30;
										p1.x = (p1.y - b1)/slope;
									}
									else
									{
										if (dirright)
											p1.x -= 30;
										else
											p1.x += 30;
										p1.y = p1.x*slope + b1;
									}
									if (!polygonhit->PointInsidePolygon(p1.x, p1.y))
									{
										if (abs(slope) > 1)
										{
											if (dirup)
												p1.y -= 30;
											else
												p1.y += 30;
											p1.x = (p1.y - b1) / slope;
										}
										else
										{
											if (dirright)
												p1.x -= 30;
											else
												p1.x += 30;
											p1.y = p1.x*slope + b1;
										}
										if (!polygonhit->PointInsidePolygon(p1.x, p1.y))
										{
											leave = true;
										}
									}
									//SDL_RenderDrawLine(grender, p1.x - themap.PlayerCamera.x, p1.y - themap.PlayerCamera.y, p2.x - themap.PlayerCamera.x, p2.y - themap.PlayerCamera.y);
									//SDL_RenderPresent(grender);
									//SDL_Delay(500);
								}						
								//SDL_RenderDrawLine(grender, p1.x - themap.PlayerCamera.x, p1.y - themap.PlayerCamera.y, p2.x - themap.PlayerCamera.x, p2.y - themap.PlayerCamera.y);
								//SDL_RenderPresent(grender);
								//SDL_Delay(500);
								destination.x = p1.x;
								destination.y = p1.y;
								//MapPosition.x = (-MOVESPEED) * cos((angle*3.14) / 180) + MapPosition.x;
								//MapPosition.y = (-MOVESPEED) * -sin((angle*3.14) / 180) + MapPosition.y;
								//circlingpolygon = false;
								//pastpolys.clear();
								//return; 
							}
							/*see if player cannot hop off at this point*/
							if (!CollisionSeeIfPlayerCanHopOff())//*only function making really clean would stop some small bugs 
							{
								
								/*determine direction to go (false left, true right)*/
								if (CollisionWhatDirectiontogo())
								{
									dirright = true;
									Move(polygonhit->Vertices[polyindextwo].x - themap.PlayerCamera.x, polygonhit->Vertices[polyindextwo].y - themap.PlayerCamera.y);
								}
								else
								{
									dirright = false;
									Move(polygonhit->Vertices[polyindexone].x - themap.PlayerCamera.x, polygonhit->Vertices[polyindexone].y - themap.PlayerCamera.y);
								}
								circlingpolygon = true;
								
								/*important to move back so you cant eventually go through wall if repeatively clicking*/
								MapPosition.x = (-MOVESPEED) * cos((angle*3.14) / 180) + MapPosition.x;
								MapPosition.y = (-MOVESPEED) * -sin((angle*3.14) / 180) + MapPosition.y;
								return;
							}
						}
					}
				}
			}
		}
	}
}
void Player::Move(bool originalclick)
{
	extern bool ButtonDown;
	extern bool ButtonDownOnce;
	extern bool ButtonRightOnce;
	extern MiniMap theminimap;
	extern Map themap;
	int x, y;
	SDL_GetMouseState(&x, &y);
	myglobal global;

	double originalx = MapPosition.x;
	double originaly = MapPosition.y;
	if (ButtonRightOnce)
	{
		/*reset everything for our moving algorithm*/
		circlingpolygon = false;
		pastpolys.clear();
		destination.x = x + themap.PlayerCamera.x; destination.y = y + themap.PlayerCamera.y;

		if (global.PointInsideRect(theminimap.minimaprect, x, y))
		{
			return;
		}
		double distance = sqrt(pow(MapPosition.x - (themap.PlayerCamera.x + x), 2) + pow(MapPosition.y + (3*Dimensions.y / 10) - (themap.PlayerCamera.y + y), 2));
		if (distance == 0)
		{
			cout << "distance 0" << endl;
			return;
		}
		angle = acos((themap.PlayerCamera.x + x - MapPosition.x) / distance);
		angle = (angle * 180) / 3.14;
		if (themap.PlayerCamera.y + y > MapPosition.y + (3 * Dimensions.y / 10))//if point is under center switch angle
		{
			angle = 360 - angle;
		}
		clickposition.x = themap.PlayerCamera.x + x;
		clickposition.y = themap.PlayerCamera.y + y;

		MovePath = true;
	}
	if (MoveBack)
	{
		MapPosition.x = -MOVESPEED * cos((angle*3.14) / 180) + MapPosition.x;
		MapPosition.y = -MOVESPEED * -sin((angle*3.14) / 180) + MapPosition.y;
		MoveBack = false;
		MovePath = false;
	}
	if (MovePath == true)
	{
		MapPosition.x = MOVESPEED * cos((angle*3.14) / 180) + MapPosition.x;
		MapPosition.y = MOVESPEED * -sin((angle*3.14) / 180) + MapPosition.y;
		double distance = sqrt(pow(MapPosition.x - clickposition.x, 2) + pow(MapPosition.y + (3 * Dimensions.y / 10) - clickposition.y, 2));
		if (distance < 2)
		{
			MovePath = false;
		}
	}
	for (int i = 0; i < StartingHitBoxTriangles.size(); i++)
	{
		StartingHitBoxTriangles[i].Move((MapPosition.x - originalx), (MapPosition.y - originaly));
	}
	for (int i = 0; i < HitBox.Vertices.size(); i++)
	{
		HitBox.Vertices[i].Move((MapPosition.x - originalx), (MapPosition.y - originaly));
	}
}
void Player::Move(double x, double y, bool originalclick)//this does no moving it just sets the path for the original move to do it
{
	extern bool ButtonDown;
	extern bool ButtonDownOnce;
	extern bool ButtonRightOnce;
	extern Map themap;
	
	double originalx = MapPosition.x;
	double originaly = MapPosition.y;

	if (originalclick)
	{
		circlingpolygon = false;
		pastpolys.clear();
		destination.x = x + themap.PlayerCamera.x; destination.y = y + themap.PlayerCamera.y;
	}

	double distance = sqrt(pow(MapPosition.x - (themap.PlayerCamera.x + x), 2) + pow(MapPosition.y + (3 * Dimensions.y / 10) - (themap.PlayerCamera.y + y), 2));
	if (distance == 0)
	{
		cout << "distance 0" << endl;
		return;
	}
	angle = acos((themap.PlayerCamera.x + x - MapPosition.x) / distance);
	angle = (angle * 180) / 3.14;
	if (themap.PlayerCamera.y + y > MapPosition.y + (3 * Dimensions.y / 10))//if point is under center switch angle
	{
		angle = 360 - angle;
	}
	clickposition.x = themap.PlayerCamera.x + x;
	clickposition.y = themap.PlayerCamera.y + y;

	MovePath = true;
}
void Player::Print(SDL_Renderer* grender)
{
	extern Map themap;
	extern int screenwidth;
	extern int screenheight;

	Position.x = MapPosition.x - themap.PlayerCamera.x;
	Position.y = MapPosition.y - themap.PlayerCamera.y;
	SDL_Rect renderrect = { Position.x - (Dimensions.x/2),Position.y - (Dimensions.y/2),Dimensions.x,Dimensions.y };
	SDL_RenderCopy(grender, Image, 0, &renderrect);
	
	UpdateHitBox();
	for (int i = 0; i < HitBox.Vertices.size(); i++)
	{
		HitBox.Vertices[i].Move(-themap.PlayerCamera.x, -themap.PlayerCamera.y);
	}
	HitBox.Print(grender);
	for (int i = 0; i < HitBox.Vertices.size(); i++)
	{
		HitBox.Vertices[i].Move(themap.PlayerCamera.x, themap.PlayerCamera.y);
	}
	/*for (int i = 0; i < StartingHitBoxTriangles.size(); i++)
	{
		//StartingHitBoxTriangles[i].Move(-themap.PlayerCamera.x, -themap.PlayerCamera.y);
		//HitBoxTriangles[i] = StartingHitBoxTriangles[i];
		//StartingHitBoxTriangles[i].Move(themap.PlayerCamera.x, themap.PlayerCamera.y);
		//HitBoxTriangles[i].Print(grender);
	}*/

	SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
	SDL_Rect printblackhealthbar = { BlackHealthBar.x - themap.PlayerCamera.x,BlackHealthBar.y - themap.PlayerCamera.y,BlackHealthBar.w,BlackHealthBar.h };
	SDL_Rect printcoloredhealthbar{ ColoredHealthBar.x - themap.PlayerCamera.x,ColoredHealthBar.y - themap.PlayerCamera.y,ColoredHealthBar.w,ColoredHealthBar.h };
	double healthperctent = (currenthealth / maxhealth)*printcoloredhealthbar.w;
	printcoloredhealthbar.w = healthperctent;
	if (currenthealth <= 0)
	{
		printcoloredhealthbar.w = 0;
	}
	SDL_RenderFillRect(grender, &printblackhealthbar);
	if (BotSide)
		SDL_SetRenderDrawColor(grender, 0, 0, 255, 0);
	else
		SDL_SetRenderDrawColor(grender, 255, 0, 0, 0);
	SDL_RenderFillRect(grender, &printcoloredhealthbar);
	SDL_SetRenderDrawColor(grender, 255, 255, 255, 0);
	SDL_Rect shieldbarrect = { printcoloredhealthbar.x + printcoloredhealthbar.w,printcoloredhealthbar.y,(shield / maxhealth)*printblackhealthbar.w,printcoloredhealthbar.h };
	SDL_RenderFillRect(grender, &shieldbarrect);

	double percent = static_cast<double>(attackcounter) / 200;
	double circlepercent = 365 - (365 * percent);
	for (int i = circlepercent; i < 365; i += 10)
	{
		int radius = 5;
		SDL_SetRenderDrawColor(grender, 0, 255, 0, 0);
		SDL_RenderDrawLine(grender, Position.x - 50, printblackhealthbar.y + (printblackhealthbar.h/2), radius*cos((i*3.14) / 180) + Position.x - 50, radius*sin((i*3.14) / 180) + printblackhealthbar.y + (printblackhealthbar.h / 2));
	}
}
bool Player::TriangleCollision(Triangle t1, Triangle t2)//borders dont collide *from rosettacode.org*
{
	bool allowReversed = true;
	double eps = 0.0;

	//Trangles must be expressed anti-clockwise
	CheckTriWinding(t1.points[0], t1.points[1], t1.points[2], allowReversed);
	CheckTriWinding(t2.points[0], t2.points[1], t2.points[2], allowReversed);

	//For edge E of trangle 1,
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;

		//Check all points of trangle 2 lay on the external side of the edge E. If
		//they do, the triangles do not collide.
		if (BoundaryDoesntCollideChk(t1.points[i], t1.points[j], t2.points[0], eps) &&
			BoundaryDoesntCollideChk(t1.points[i], t1.points[j], t2.points[1], eps) &&
			BoundaryDoesntCollideChk(t1.points[i], t1.points[j], t2.points[2], eps))
			return false;
	}

	//For edge E of trangle 2,
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;

		//Check all points of trangle 1 lay on the external side of the edge E. If
		//they do, the triangles do not collide.
		if (BoundaryDoesntCollideChk(t2.points[i], t2.points[j], t1.points[0], eps) &&
			BoundaryDoesntCollideChk(t2.points[i], t2.points[j], t1.points[1], eps) &&
			BoundaryDoesntCollideChk(t2.points[i], t2.points[j], t1.points[2], eps))
			return false;
	}

	//The triangles collide
	return true;
}
inline double Player::Det2D(Vertex p1, Vertex p2, Vertex p3)
{
	return +p1.x*(p2.y - p3.y)
		+ p2.x*(p3.y - p1.y)
		+ p3.x*(p1.y - p2.y);
}
void Player::CheckTriWinding(Vertex& p1, Vertex& p2, Vertex& p3, bool allowReversed)
{
	double detTri = Det2D(p1, p2, p3);
	if (detTri < 0.0)
	{
		if (allowReversed)
		{
			Vertex a = p3;
			p3 = p2;
			p2 = a;
		}
		else throw std::runtime_error("triangle has wrong winding direction");
	}
}
bool Player::BoundaryDoesntCollideChk(Vertex p1, Vertex p2, Vertex p3, double eps)
{
	return Det2D(p1, p2, p3) <= eps;
}
void Player::DamagePlayer(double damage)
{
	if (damage < 0)
	{
		cout << "negative damage!" << endl;
		return;
	}
	double originalshield = shield;
	shield -= damage;
	damage -= originalshield;
	if (shield < 0)
		shield = 0;
	if (damage < 0)
		damage = 0;
	currenthealth -= damage;
	if (currenthealth <= 0)
	{
		Respawn();
	}
}
void Player::Respawn()
{
	MovePath = false;
	currenthealth = maxhealth;
	double originalx = MapPosition.x;
	double originaly = MapPosition.y;
	if (BotSide)
	{
		MapPosition.x = 600;
		MapPosition.y = 4800;
	}
	else
	{
		MapPosition.x = 600;
		MapPosition.y = 4800;
	}
	for (int i = 0; i < StartingHitBoxTriangles.size(); i++)
	{
		StartingHitBoxTriangles[i].Move((MapPosition.x - originalx), (MapPosition.y - originaly));
	}
	for (int i = 0; i < HitBox.Vertices.size(); i++)
	{
		HitBox.Vertices[i].Move((MapPosition.x - originalx), (MapPosition.y - originaly));
	}
}
void Player::GiveItem(Item& item)
{
	if (items.size() < 6)
	{
		items.push_back(&item);
		gold -= item.COST;
	}
	AddStats(item);
}
void Player::AddStats(Item& item)
{
	maxhealth +=item.HEALTH;
	AD += item.AD;
	AP += item.AP;
	MR += item.MR;
	ARMOR += item.ARMOR;
	ATKSPEED += item.ATKSPEED;
	CRIT += item.CRIT;
	CDR += item.CDR;
	HEALTHREGEN += item.HEALTHREGEN;
	MAGICPEN += item.MAGICPEN;
	MOVESPEED += item.MOVESPEED;
	LIFESTEAL += item.LIFESTEAL;
}
void Player::SubStats(Item& item)
{
	maxhealth -= item.HEALTH;
	AD -= item.AD;
	AP -= item.AP;
	MR -= item.MR;
	ARMOR -= item.ARMOR;
	ATKSPEED -= item.ATKSPEED;
	CRIT -= item.CRIT;
	CDR -= item.CDR;
	HEALTHREGEN -= item.HEALTHREGEN;
	MAGICPEN -= item.MAGICPEN;
	MOVESPEED -= item.MOVESPEED;
	LIFESTEAL -= item.LIFESTEAL;
}