#pragma once
#include <SDL_image.h>

class Entity
{
public:
	Entity(int pX, int pY, SDL_Texture* pTexture);
	SDL_Texture* GetTexture();
	SDL_Rect GetRect();

	void SetX(int pX);
	void SetY(int pY);
	int GetX();
	int GetY();
private:
	int x;
	int y;
	SDL_Texture* Texture;
	SDL_Rect rect;
};

