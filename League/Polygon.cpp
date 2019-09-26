#include "Polygon.h"
#include <iostream>
using namespace std;

Polygon::Polygon()
{
	Vertex one(100, 100);
	Vertex two(200, 100);
	Vertex three(150, 200);
	Vertices.push_back(one); 
	Vertices.push_back(two); 
	Vertices.push_back(three);

	bestfitcenter = GetBestFitCenter();
}
Polygon::Polygon(Vertex one, Vertex two, Vertex three)
{
	Vertices.push_back(one);
	Vertices.push_back(two);
	Vertices.push_back(three);
	bestfitcenter = GetBestFitCenter();
}
Polygon::Polygon(int amount)
{
	Polygon();
	AddVertices(amount);
	bestfitcenter = GetBestFitCenter();
}
vector<Edge> Polygon::GetEdgesCopy()
{
	vector<Edge> Edges;
	for (int i = 0; i < Vertices.size(); i++)
	{
		if (i == Vertices.size() - 1)
		{
			Edge tmp(Vertices[i], Vertices[0]);
			Edges.push_back(tmp);
		}
		else
		{
			Edge tmp(Vertices[i], Vertices[i + 1]);
			Edges.push_back(tmp);
		}
	}
	return Edges;
}
bool Polygon::Equals(Polygon p1)
{
	if (p1.Vertices.size() != Vertices.size())
	{
		return false;
	}
	for (int i = 0; i < Vertices.size(); i++)
	{
		bool matched = false;
		for (int j = 0; j < p1.Vertices.size(); j++)
		{
			if (p1.Vertices[j] == Vertices[i])
			{
				matched = true;
			}
		}
		if (matched == false)
		{
			return false;
		}
	}
	return true;
}
void Polygon::Move(double x, double y)
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		Vertices[i].Move(x, y);
	}
	bestfitcenter = GetBestFitCenter();
}
void Polygon::AddVertices(int amount)
{
	if (Vertices.size() == 0)
	{
		Vertex tmp(0, 0);
		Vertices.push_back(tmp);
		return;
	}
	while (amount != 0)
	{
		Vertex tmp(Vertices[0].x, Vertices[0].y);
		Vertices.push_back(tmp);
		amount--;
	}
	bestfitcenter = GetBestFitCenter();
}
vector<Vertex> Polygon::GetVerticesCopy()
{
	return Vertices;
}
void Polygon::Print(SDL_Renderer* grender)
{
	for(int i = 0; i < Vertices.size(); i++)
	{
		if (i == Vertices.size() - 1)
			SDL_RenderDrawLine(grender, Vertices[i].x, Vertices[i].y, Vertices[0].x, Vertices[0].y);
		else
			SDL_RenderDrawLine(grender, Vertices[i].x, Vertices[i].y, Vertices[i + 1].x, Vertices[i + 1].y);
	}
}
void Polygon::PrintVerticesInfo()
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		cout << "vertice " << i << ": " << "(" << Vertices[i].x << ", " << Vertices[i].y << ")" << endl;
	}
}
void Polygon::SetVertex(int x, int y, int index)
{
	if (index >= Vertices.size() || index < 0)
	{
		cout << "wrong index (Polygon::SetVertex)" << endl;
		return;
	}
	Vertices[index].x = x;
	Vertices[index].y = y;

	bestfitcenter = GetBestFitCenter();
}
Vertex Polygon::GetBestFitCenter()
{
	//get very left very right very top very bottom and get center of them all

	double lowestx = 100000;
	int lowestxindex = -1;
	double highestx = 0;
	int highestxindex = -1;
	double lowesty = 100000;
	int lowestyindex = -1;
	double highesty = 0;
	int highestyindex = -1;
	for (int i = 0; i < Vertices.size(); i++)
	{
		if (Vertices[i].x < lowestx)
		{
			lowestx = Vertices[i].x;
			lowestxindex = i;
		}
		if (Vertices[i].x > highestx)
		{
			highestx = Vertices[i].x;
			highestxindex = i;
		}
		if (Vertices[i].y < lowesty)
		{
			lowesty = Vertices[i].y;
			lowestyindex = i;
		}
		if (Vertices[i].y > highesty)
		{
			highesty = Vertices[i].y;
			highestyindex = i;
		}
	}
	Vertex center;
	center.x = (Vertices[lowestxindex].x + Vertices[highestxindex].x) / 2.0;
	center.y = (Vertices[lowestyindex].y + Vertices[highestyindex].y) / 2.0;
	return center;
}
int Polygon::WhatPointClicked(double x, double y)
{
	int radius = 20;
	for (int i = 0; i < Vertices.size(); i++)
	{
		//create circle around point and see if distance clicked is less than radius
		double distance = sqrt(pow(x - Vertices[i].x, 2) + pow(y - Vertices[i].y, 2));
		if (distance <= radius)
		{
			return i;
		}
	}
	return -1;
}
bool Polygon::PointInsidePolygon(double x, double y)
{
	extern int screenwidth;
	extern int screenheight;
	vector<Edge> Edges = GetEdgesCopy();
	int counter = 0;
	double slope = 0;
	bool slopepicked = false;
	while (!slopepicked)
	{
		bool similar = false;
		for (int i = 0; i < Edges.size(); i++)
		{
			if (Edges[i].GetEdgeSlope() == slope)
			{
				similar = true;
			}
		}
		if (similar == true)
		{
			slope += .1;
		}
		else
		{
			slopepicked = true;
		}
	}
	Vertex mouseone(x, y);
	double mousex = x + 10000;
	double mousey = y - (slope * x);
	Vertex mousetwo(mousex, mousey);
	Edge mouseline; mouseline.p1 = mouseone; mouseline.p2 = mousetwo;
	vector<Edge> repeatchecker;
	for (int i = 0; i < Edges.size(); i++)
	{
		if (checktwolinecollision(mouseline.p1, mouseline.p2, Edges[i].p1, Edges[i].p2))
		{
			counter++;
			repeatchecker.push_back(Edges[i]);
		}
	}
	/*for (int i = 0; i < repeatchecker.size(); i++)
	{
		for (int j = i+1; j < repeatchecker.size(); j++)
		{
			if (repeatchecker[i].p1 == repeatchecker[j].p1 || repeatchecker[i].p1 == repeatchecker[j].p2 || repeatchecker[i].p2 == repeatchecker[j].p1 ||
				repeatchecker[i].p2 == repeatchecker[j].p2)
			{
				counter--;
			}
		}
	}*/
	if (counter % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Polygon::checktwolinecollision(Vertex one, Vertex one2, Vertex two, Vertex two2)
{
	double larger1y = one.y;
	double smaller1y = one2.y;
	double larger1x = one.x;
	double smaller1x = one2.x;
	double larger2x = two.x;
	double smaller2x = two2.x;
	double larger2y = two.y;
	double smaller2y = two2.y;
	if (two2.x > two.x)
	{
		larger2x = two2.x;
		smaller2x = two.x;
	}
	if (two2.y > two.y)
	{
		larger2y = two2.y;
		smaller2y = two.y;
	}
	if (one2.x > one.x)
	{
		larger1x = one2.x;
		smaller1x = one.x;
	}
	if (one2.y > one.y)
	{
		larger1y = one2.y;
		smaller1y = one.y;
	}

	double slope1 = 0;
	double b1 = 0;//is the b intercept if horizontal line its the y if vertical its the x
	bool undefined1 = false;
	bool zero1 = false;
	if (one2.x == one.x)
	{
		undefined1 = true;
		b1 = one.x;
	}
	else if (one2.y == one.y)
	{
		zero1 = true;
		b1 = one.y;
	}
	else
	{
		slope1 = (one2.y - one.y) / (one2.x - one.x);
		b1 = one2.y - slope1 * one2.x;
	}

	double slope2 = 0;
	double b2 = 0;
	bool undefined2 = false;
	bool zero2 = false;
	if (two2.x == two.x)
	{
		undefined2 = true;
		b2 = two.x;
	}
	else if (two2.y == two.y)//two2.y == two.y
	{
		zero2 = true;
		b2 = two.y;
	}
	else
	{
		slope2 = (two2.y - two.y) / (two2.x - two.x);
		b2 = two2.y - slope2 * two2.x;
		if (abs(slope2) <= .005)
		{
			zero2 = true;
			b2 = two.y;
			slope2 = 0;
		}
		if (abs(slope2) >= 5000)
		{
			undefined2 = true;
			b2 = two.x;
			slope2 = 0;
		}
	}
	if (zero1 && zero2 == 1)
	{
		if (static_cast<int>(one.y) == static_cast<int>(b2))//static_cast<int>(one.y) == static_cast<int>(two.y)
		{
			double largestx = larger2x;
			if (larger1x > larger2x)
			{
				if (larger1x - smaller1x >= larger1x - larger2x)
				{
					return true;
				}
			}
			else
			{
				if (larger2x - smaller2x >= larger2x - larger1x)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 && undefined2 == 1)
	{
		if (static_cast<int>(one.x) == static_cast<int>(two.x))//static_cast<int>(one.x) == static_cast<int>(two.x)
		{

			double largesty = larger2y;
			if (larger1y > larger2y)
			{
				if (larger1y - smaller1y >= larger1y - larger2y)
				{
					return true;
				}
			}
			else
			{
				if (larger2y - smaller2y >= larger2y - larger1y)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (undefined1 || undefined2 == 1)
	{
		double y = 0;
		double x = 0;
		int amount = 0;
	

		y = slope1 * b2 + b1;
		x = b2;

		amount = 0;
		if ((y <= larger1y + amount && y >= smaller1y - amount) && (y <= larger2y + amount && y >= smaller2y - amount))//safe check with x?
		{
			if ((x <= larger1x + amount && x >= smaller1x - amount) && (x <= larger2x + amount && x >= smaller2x - amount))
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		//glitch if its a slope thats super super small
		//if slopes are same there is no solution unless they are the same
		if (slope1 - slope2 == 0)
		{
			if (b2 == b1)
			{
				return true;
			}
			return false;
		}
		
		double x = (b2 - b1) / (slope1 - slope2);
		double y = x * slope1 + b1;
		if ((y <= larger1y && y >= smaller1y) && (y <= larger2y && y >= smaller2y))
		{
			if ((x <= larger1x && x >= smaller1x) && (x <= larger2x && x >= smaller2x))//safe check with y?
			{
				return true;
			}
		}
		return false;
	}
}
vector<Triangle> Polygon::Triangulate()
{
	vector<Triangle> triangles;
	Triangulation(triangles, *this);
	return triangles;
}
void Polygon::Triangulation(vector<Triangle>& originaltriangles, Polygon tmppoly)
{
	//recursive once we get to triangle can either make vector of triangles and push it or update our vertices with the vertices of the triangles state
	if (tmppoly.Vertices.size() == 3)
	{
		//just make a triangle and push back on our vector
		Triangle tmp(tmppoly.Vertices[0], tmppoly.Vertices[1], tmppoly.Vertices[2]);
		originaltriangles.push_back(tmp);
		return;
	}
	if (tmppoly.Vertices.size() < 3)
	{
		cout << "error poly less than 3 points" << endl;
		return;
	}
	int highestyindex = -1;
	int highestyvalue = -1;
	int highestyrepeat = 0;
	int highestxindex;
	int highestxvalue = -1;
	bool right = false;
	for (int i = 0; i < tmppoly.Vertices.size(); i++)
	{
		if (tmppoly.Vertices[i].y > highestyvalue)
		{
			highestyindex = i;
			highestyvalue = tmppoly.Vertices[i].y;
			highestyrepeat = 0;
		}
		else if (tmppoly.Vertices[i].y == highestyvalue)
		{
			highestyrepeat++;
		}
	}
	if (highestyrepeat >= 1)
	{
		for (int i = 0; i < tmppoly.Vertices.size(); i++)
		{
			if (tmppoly.Vertices[i].x > highestxvalue)
			{
				highestyindex = i;
				highestxvalue = tmppoly.Vertices[i].x;
			}
		}
	}
	if (highestyindex == -1)
	{
		cout << "highestyindex not found..." << endl;
		return;
	}
	Vertex neighborone;
	Vertex neighbortwo;
	if (highestyindex == 0)
		neighborone = tmppoly.Vertices[tmppoly.Vertices.size()-1];
	else
		neighborone = tmppoly.Vertices[highestyindex - 1];
	if(highestyindex == tmppoly.Vertices.size()-1)
		neighbortwo = tmppoly.Vertices[0];
	else
		neighbortwo = tmppoly.Vertices[highestyindex + 1];

	int middleindex = -1;
	bool leave = false;
	bool ear = true;
	//create triangle
	Vertex onelol(neighborone.x, neighborone.y);
	Vertex twolol(neighbortwo.x, neighbortwo.y);
	Vertex threelol(tmppoly.Vertices[highestyindex].x, tmppoly.Vertices[highestyindex].y);
	Polygon polyear(onelol, twolol, threelol);
	while (!leave)
	{
		for (int x = 0; x < tmppoly.Vertices.size(); x++)//**why scan line just see if any point is in the triangle formed
		{
			if (polyear.PointInsidePolygon(tmppoly.Vertices[x].x, tmppoly.Vertices[x].y))
			{
				if (tmppoly.Vertices[x] != neighborone && tmppoly.Vertices[x] != neighbortwo && tmppoly.Vertices[x] != tmppoly.Vertices[highestyindex])
				{
					if (middleindex == -1)
					{
						ear = false;
						middleindex = x;
					}
					else
					{
						double distanceold = sqrt(pow(tmppoly.Vertices[highestyindex].x - tmppoly.Vertices[middleindex].x, 2) + pow(tmppoly.Vertices[highestyindex].y - tmppoly.Vertices[middleindex].y, 2));
						double distancenew = sqrt(pow(tmppoly.Vertices[highestyindex].x - tmppoly.Vertices[middleindex].x, 2) + pow(tmppoly.Vertices[highestyindex].y - tmppoly.Vertices[middleindex].y, 2));
						if (distancenew < distanceold)
						{
							ear = false;
							middleindex = x;
						}
					}
				}
			}
		}
		leave = true;
	}
	if (ear)
	{
		//normal poly without one point
		Polygon poly1;
		poly1 = tmppoly;
		poly1.Vertices.erase(poly1.Vertices.begin() + highestyindex);
		//the triangle (ear) we broke off garunteed to be an ear
		Polygon poly2(neighborone, neighbortwo, tmppoly.Vertices[highestyindex]);

		Triangulation(originaltriangles, poly1);
		Triangulation(originaltriangles, poly2);
	}
	else
	{
		if (middleindex == -1)
		{
			cout << "middle index not found";
		}
		//do algorithm where you keep deleting its left neighbor until it gets to middleindex then same with right
		Polygon poly1;
		poly1.Vertices.clear();
		bool leave1 = false;
		int index = highestyindex;
		int middleindexstart = middleindex;
		while (!leave1)
		{
			if (index < 0)
			{
				index = tmppoly.Vertices.size() - 1;
			}
			if (tmppoly.Vertices[index] == tmppoly.Vertices[middleindex])
			{
				poly1.AddVertices(1);
				poly1.Vertices[poly1.Vertices.size() - 1].x = tmppoly.Vertices[index].x;
				poly1.Vertices[poly1.Vertices.size() - 1].y = tmppoly.Vertices[index].y;
				leave1 = true;
			}
			if (leave1 != true)
			{
				poly1.AddVertices(1);
				poly1.Vertices[poly1.Vertices.size() - 1].x = tmppoly.Vertices[index].x; 
				poly1.Vertices[poly1.Vertices.size() - 1].y = tmppoly.Vertices[index].y;
				index--;
			}
			/*if (index < 0)
			{
				index = poly1.Vertices.size() - 1;
			}
			if (poly1.Vertices[index] == poly1.Vertices[middleindex])
			{
				leave1 = true;
			}
			if (leave1 != true)
			{
				poly1.Vertices.erase(poly1.Vertices.begin() + (index));
				if (index < middleindex)
				{
					middleindex--;
				}
				index--;
			}*/
		}
		Polygon poly2;
		poly2.Vertices.clear();
		leave1 = false;
		index = highestyindex;
		middleindex = middleindexstart;
		while (!leave1)
		{
			if (index >= tmppoly.Vertices.size())
			{
				index = 0;
			}
			if (tmppoly.Vertices[index] == tmppoly.Vertices[middleindex])
			{
				poly2.AddVertices(1);
				poly2.Vertices[poly2.Vertices.size() - 1].x = tmppoly.Vertices[index].x;
				poly2.Vertices[poly2.Vertices.size() - 1].y = tmppoly.Vertices[index].y;
				leave1 = true;
			}
			if (leave1 != true)
			{
				poly2.AddVertices(1);
				poly2.Vertices[poly2.Vertices.size() - 1].x = tmppoly.Vertices[index].x;
				poly2.Vertices[poly2.Vertices.size() - 1].y = tmppoly.Vertices[index].y;
				index++;
			}
			/*cout << "size " << poly2.Vertices.size() << " " << index << " " << middleindex << endl;
			if (index >= poly2.Vertices.size())
			{
				index = 0;
			}
			if (poly2.Vertices[index] == poly2.Vertices[middleindex])
			{
				leave1 = true;
			}
			if (leave1 != true)
			{
				poly2.Vertices.erase(poly2.Vertices.begin() + (index));
				if (index < middleindex)
				{
					middleindex--;
				}
				index++;
			}*/
		}
		Triangulation(originaltriangles, poly1);
		Triangulation(originaltriangles, poly2);
	}
}