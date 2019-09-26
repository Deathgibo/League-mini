#include "Vertex.h"
#include <iostream>
using namespace std;

Vertex::Vertex()
{
	x = 0;
	y = 0;
}
Vertex::Vertex(double xx, double yy)
{
	x = xx;
	y = yy;
}
double Vertex::GetXCopy()
{
	return x;
}
double Vertex::GetYCopy()
{
	return y;
}
void Vertex::Move(double xx, double yy)
{
	x += xx;
	y += yy;
}
void Vertex::Print(SDL_Renderer* grender)
{
	SDL_RenderDrawPoint(grender, x, y);
}
void Vertex::PrintCircle(SDL_Renderer* grender)
{
	int radius = 5;
	SDL_RenderDrawPoint(grender, x, y);
	for (int i = 0; i < 360; i++)
	{
		SDL_RenderDrawPoint(grender, radius*cos((i * 180) / 3.14) + x, radius*sin((i * 180) / 3.14) + y);
	}
}
bool Vertex::operator!=(const Vertex& thevert)
{
	if (x != thevert.x || y != thevert.y)
		return true;
	return false;
}
bool Vertex::operator==(const Vertex& thevert)
{
	if (thevert.x == x && thevert.y == y)
		return true;
	return false;
}