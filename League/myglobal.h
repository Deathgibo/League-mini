#pragma once
#include <SDL.h>
#include "Vertex.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;


class myglobal
{
public:
	myglobal()
	{

	}
	void UILocation(SDL_Rect background, SDL_Rect& placement)
	{
		extern bool ButtonDown;
		extern bool upKeyState;
		extern bool downKeyState;
		extern bool leftKeyState;
		extern bool rightKeyState;
		extern bool AKeyState;
		extern bool WKeyState;
		extern bool SKeyState;
		extern bool DKeyState;
		int speed = 1;
		if (ButtonDown)
		{
			speed = 15;
		}
		if (upKeyState)
			placement.h-=speed;
		if (downKeyState)
			placement.h+= speed;
		if (leftKeyState)
			placement.w-= speed;
		if (rightKeyState)
			placement.w+= speed;
		if (AKeyState)
			placement.x-= speed;
		if (DKeyState)
			placement.x+= speed;
		if (WKeyState)
			placement.y-= speed;
		if (SKeyState)
			placement.y+= speed;
		if (upKeyState || downKeyState || leftKeyState || rightKeyState || AKeyState || DKeyState || WKeyState || SKeyState)
		{
			double x = UIWidthRatio(background.x, background.w, placement.x);
			bool leave = false;
			int counter = 0;
			int value = 0;
			while (!leave)
			{
				int answer = background.x + (static_cast<int>(x* 1000 + value)*background.w) / 1000;
				if (answer == placement.x)
				{
					cout << "x: " << static_cast<int>(x * 1000 + value);
					leave = true;
				}
				counter++;
				if (counter % 2 == 0)
				{
					value = -(counter / 2);
				}
				else
				{
					value = counter / 2;
				}
			}
			double y = UIHeightRatio(background.y, background.h, placement.y);
			leave = false;
			counter = 0;
			value = 0;
			while (!leave)
			{
				int answer = background.y + (static_cast<int>(y * 1000 + value)*background.h) / 1000;
				if (answer == placement.y)
				{
					cout << " y: " << static_cast<int>(y * 1000 + value);
					leave = true;
				}
				counter++;
				if (counter % 2 == 0)
				{
					value = -(counter / 2);
				}
				else
				{
					value = counter / 2;
				}
			}
			double w = UIWidthRatio(background.x, background.w, placement.x + placement.w) - UIWidthRatio(background.x, background.w, placement.x);
			leave = false;
			counter = 0;
			value = 0;
			while (!leave)
			{
				int answer = (static_cast<int>(w * 1000 + value)*background.w) / 1000;
				if (answer == placement.w)
				{
					cout << " w: " << static_cast<int>(w * 1000 + value);
					leave = true;
				}
				counter++;
				if (counter % 2 == 0)
				{
					value = -(counter / 2);
				}
				else
				{
					value = counter / 2;
				}
			}
			double h = UIHeightRatio(background.y, background.h, placement.y + placement.h) - UIHeightRatio(background.y, background.h, placement.y);
			leave = false;
			counter = 0;
			value = 0;
			while (!leave)
			{
				int answer = ((static_cast<int>(h * 1000 + value))*background.h) / 1000;
				if (answer == placement.h)
				{
					cout << " h: " << static_cast<int>(h * 1000 + value) << endl;
					leave = true;
				}
				counter++;
				if (counter % 2 == 0)
				{
					value = -(counter / 2);
				}
				else
				{
					value = counter / 2;
				}
			}
		}
	}
	double UIWidthRatio(double uistartingx, double uiwidth, double mousex)
	{
		return (mousex - uistartingx) / uiwidth;
	}
	double UIHeightRatio(double uistartingy, double uiheight, double mousey)
	{
		return (mousey - uistartingy) / uiheight;
	}
	bool PointInsideRect(SDL_Rect rect, int x, int y)
	{
		if (x < rect.x + rect.w && x > rect.x && y > rect.y && y < rect.y + rect.h)
		{
			return true;
		}
		return false;
	}
	Vertex gettwolinecollisionpoint(Vertex one, Vertex one2, Vertex two, Vertex two2)
	{
		Vertex returnpoint(0,0);
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
		if (zero1 == 1 && zero2 == 1)
		{
			cout << "both zero";
			return returnpoint;
		}
		else if (undefined1 == 1 && undefined2 == 1)
		{
			cout << "both vertical";
			return returnpoint;
		}
		else if (undefined1 || undefined2 == 1)
		{
			double y = 0;
			double x = 0;
			int amount = 0;


			y = slope1 * b2 + b1;
			x = b2;
			returnpoint.x = x;
			returnpoint.y = y;
			return returnpoint;
		}
		else
		{
			//glitch if its a slope thats super super small
			//if slopes are same there is no solution unless they are the same
			if (slope1 - slope2 == 0)
			{
				cout << "problem";
				return returnpoint;
			}

			double x = (b2 - b1) / (slope1 - slope2);
			double y = x * slope1 + b1;
			returnpoint.x = x;
			returnpoint.y = y;
			return returnpoint;
		}
	}
	bool checktwolinecollision(Vertex one, Vertex one2, Vertex two, Vertex two2)
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
private:

};
