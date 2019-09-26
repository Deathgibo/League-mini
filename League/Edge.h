#pragma once
#include "Vertex.h"

class Edge
{
public:
	Edge();
	Edge(double x1, double y1, double x2, double y2);
	Edge(Vertex one, Vertex two);
	void Move(double x, double y);
	Vertex GetP1Copy();
	Vertex GetP2Copy();
	double EdgeLength();
	double GetEdgeSlope();
	void Print(SDL_Renderer* grender);

	Vertex p1;
	Vertex p2;
private:

};