#include <SDL_image.h>
#include "entity.h";

/* Constructor */
Entity::Entity(int pX, int pY, SDL_Texture* pTexture)
	:x(pX), y(pY), Texture(pTexture)
{
	rect.x = pX;
	rect.y = pY;
	rect.w = 64;
	rect.h = 64;
}

/* Propities */
SDL_Texture* Entity::GetTexture()
{
	return Texture;
}

SDL_Rect Entity::GetRect()
{
	return rect;
}

int Entity::GetX()
{
	return x;
}

int Entity::GetY()
{
	return y;
}

void Entity::SetX(int pX)
{
	x = pX;
}

void Entity::SetY(int pY)
{
	y = pY;
}
