#pragma once
#include "Vertex.h"
#include <vector>
using namespace std;

class Triangle
{
public:
	Triangle();
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	Triangle(Vertex one, Vertex two, Vertex three);
	void Move(double x, double y);
	void Print(SDL_Renderer* grender);
	void VerticeInfo();
	double Det();

	vector<Vertex> points;
private:
};