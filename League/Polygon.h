#pragma once
#include "Vertex.h"
#include "Triangle.h"
#include "Edge.h"
#include <vector>
using namespace std;
//just a vector of points and I have a method that can order them clockwise or counterclock-wise
//can make a vector of lines thats good
//best is to make vector of points but you have a function to order them and a function to get lines if you want
//* polygon justa vector of points that get ordered automatically when we create and add vertices to them, then getting lines is easy with a function
class Polygon
{
public:
	Polygon();
	Polygon(int amount);
	Polygon(Vertex one, Vertex two, Vertex three);
	vector<Edge> GetEdgesCopy();
	void Move(double x, double y);
	void AddVertices(int amount);
	vector<Vertex> GetVerticesCopy();
	void Print(SDL_Renderer* grender);
	void PrintVerticesInfo();
	void SetVertex(int x, int y, int index);
	Vertex GetBestFitCenter();
	int WhatPointClicked(double x, double y);
	bool PointInsidePolygon(double x, double y);
	vector<Triangle> Triangulate();
	bool Equals(Polygon p1);

	vector<Vertex> Vertices;
	Vertex bestfitcenter;
private:
	bool checktwolinecollision(Vertex one, Vertex one2, Vertex two, Vertex two2);
	void Triangulation(vector<Triangle>& originaltriangles, Polygon tmppoly);
};