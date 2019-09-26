#pragma once
#include <SDL.h>
#include <vector>
#include "Vertex.h"
#include "Polygon.h"
#include "Minion.h"

struct mat2x2
{
	double column1x;
	double column1y;
	double column2x;
	double column2y;

	Vertex matrixvectorMult(Vertex vector, int xoffset, int yoffset)
	{
		double ychange;
		Vertex temp;
		temp.x = column1x * (vector.x - xoffset) + column2x * (yoffset - vector.y) + xoffset;
		ychange = column1y * (vector.x - xoffset) + column2y * (yoffset - vector.y);
		ychange = ychange * -1;
		temp.y = ychange + yoffset;
		return temp;
	}
};


class MiniMap
{
public:
	MiniMap();
	void Initialize();
	void Print();
	void Update();
	void Updateminimapposition();
	void ZoomShapes();
	void MoveShapes(double x, double y);
	Vertex PlayerRatioWithMap();
	Vertex MinionRatioWithMap(Minion minion);
	Vertex TowerRatioWithMap(Tower tower);
	Vertex MouseRatioWithMap();


	SDL_Texture* image;
	SDL_Rect minimaprect;
	vector<Polygon> StartingHitBoxes;

private:

};