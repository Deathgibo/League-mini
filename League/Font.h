#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

class Font
{
public:
	Font();
	~Font();
	Font(string s, string color);
	void Initialize(string s, string color);
	void Print(SDL_Renderer* grender, SDL_Rect therect);
	void FreeTexture();
	
	SDL_Texture* image;
	SDL_Color currentcolor;
private:
	SDL_Color textcolorblack = { 0,0,0 };
	SDL_Color textcolorwhite = { 255,255,255 };
	SDL_Color textcoloryellow = { 255,255,0 };
	SDL_Color textcolorblue = { 0,0,255 };
	SDL_Texture* loadtext(string s, SDL_Color textcolor);
};