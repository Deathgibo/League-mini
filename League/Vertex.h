#pragma once
#include <SDL.h>

class Vertex
{
public:
	Vertex();
	Vertex(double xx, double yy);
	double GetXCopy();
	double GetYCopy();
	void Move(double xx, double yy);
	void Print(SDL_Renderer* grender);
	void PrintCircle(SDL_Renderer* grender);
	bool operator!=(const Vertex& thevert);
	bool operator==(const Vertex& thevert);
	double x;
	double y;
private:

};