#include "Edge.h"
#include <iostream>
using namespace std;

Edge::Edge()
{
	Vertex tmpone(0, 0);
	Vertex tmptwo(0, 0);
	p1 = tmpone;
	p2 = tmptwo;
}
Edge::Edge(double x1, double y1, double x2, double y2)
{
	p1.x = x1; p1.y = y1;
	p2.x = x2; p2.y = y2;
}
Edge::Edge(Vertex one, Vertex two)
{
	p1 = one;
	p2 = two;
}
void Edge::Move(double x, double y)
{
	p1.x += x; p1.y += y;
	p2.x += x; p2.y += y;
}
Vertex Edge::GetP1Copy()
{
	return p1;
}
Vertex Edge::GetP2Copy()
{
	return p2;
}
double Edge::EdgeLength()
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
double Edge::GetEdgeSlope()
{
	Vertex one = p1;
	Vertex two = p2;
	if (one.x - two.x == 0)
	{
		return -1;
	}
	else
	{
		return (one.y - two.y) / (one.x - two.x);
	}
}
void Edge::Print(SDL_Renderer* grender)
{
	SDL_RenderDrawLine(grender, p1.x, p1.y, p2.x, p2.y);
}