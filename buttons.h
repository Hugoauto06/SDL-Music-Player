#pragma once
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "entity.h"

class Play : public Entity
{
public:
	void OnClick();
	Play(int pX, int pY, SDL_Texture* pTexture);
private:
	int x;
	int y;
	SDL_Texture* Texture;
	SDL_Rect rect;
};

class Pause : public Entity
{
public:
	void OnClick();
	Pause(int pX, int pY, SDL_Texture* pTexture);
private:
	int x;
	int y;
	SDL_Texture* Texture;
	SDL_Rect Rect;
};

class Skip : public Entity
{
public:
	void OnClick();
	Skip(int pX, int pY, SDL_Texture* pTexture);
private:
	int x;
	int y;
	SDL_Texture* Texture;
	SDL_Rect Rect;
};