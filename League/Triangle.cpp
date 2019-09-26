#include "Triangle.h"
#include <iostream>

Triangle::Triangle()
{
	points.clear();
}
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	Vertex one(x1, y1);
	Vertex two(x2, y2);
	Vertex three(x3, y3);

	points.push_back(one);
	points.push_back(two);
	points.push_back(three);
}
Triangle::Triangle(Vertex one, Vertex two, Vertex three)
{
	points.push_back(one);
	points.push_back(two);
	points.push_back(three);
}
void Triangle::Move(double x, double y)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i].Move(x, y);
	}
}
void Triangle::Print(SDL_Renderer* grender)
{
	for (int i = 0; i < points.size(); i++)
	{
		SDL_RenderDrawLine(grender, points[i].x, points[i].y, points[(i + 1) % 3].x, points[(i + 1) % 3].y);
	}
}
void Triangle::VerticeInfo()
{
	for (int i = 0; i < points.size(); i++)
	{
		cout << "point " << i << ": (" << points[i].x << ", " << points[i].y << ")" << endl;
	}
}
double Triangle::Det()
{
	if (points.size() == 3)
	{
		return +points[0].x*(points[1].y - points[2].y)
			+ points[1].x*(points[2].y - points[0].y)
			+ points[2].x*(points[0].y - points[1].y);
	}
}