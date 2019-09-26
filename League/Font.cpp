#include "Font.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

Font::Font()
{
	currentcolor = textcolorblack;
	image = 0;
}
Font::~Font()
{
	if (image != 0)
	{
		SDL_DestroyTexture(image);
		image = 0;
	}
}
Font::Font(string s, string color)
{
	currentcolor = textcolorblack;
	if (color == "blue")
		currentcolor = textcolorblue;
	if (color == "white")
		currentcolor = textcolorwhite;
	if(color == "yellow")
		currentcolor = textcoloryellow;
	if(color == "black")
		currentcolor = textcolorblack;
	image = loadtext(s, currentcolor);
}
void Font::Initialize(string s, string color)
{
	currentcolor = textcolorblack;
	if (color == "blue")
		currentcolor = textcolorblue;
	if (color == "white")
		currentcolor = textcolorwhite;
	if (color == "yellow")
		currentcolor = textcoloryellow;
	if (color == "black")
		currentcolor = textcolorblack;
	image = loadtext(s, currentcolor);
}
void Font::Print(SDL_Renderer* grender,SDL_Rect therect)
{
	SDL_RenderCopy(grender, image, 0, &therect);
}
SDL_Texture* Font::loadtext(string s, SDL_Color textcolor)
{
	if (image != 0)
	{
		FreeTexture();
	}
	extern int screenwidth;
	extern TTF_Font* gFont;
	extern SDL_Renderer* grender;
	SDL_Surface* tempsurface = TTF_RenderText_Blended_Wrapped(gFont, s.c_str(), textcolor, screenwidth);
	SDL_Texture* returntexture;
	returntexture = SDL_CreateTextureFromSurface(grender, tempsurface);
	SDL_FreeSurface(tempsurface);
	return returntexture;
}
void Font::FreeTexture()
{
	SDL_DestroyTexture(image);
	image = 0;
}