#include <iostream>
#include <SDL_image.h>

#include "renderWindow.h";
#include "defs.h"

using namespace std;

RenderWindow::RenderWindow(const char* p_title, int pW, int pH)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(
		"My App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		pW, pH, SDL_WINDOW_SHOWN
	);

	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_SOFTWARE
	);
}

void RenderWindow::Display()
{
	SDL_SetRenderDrawColor(renderer, 64, 68, 88, 255);
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::LoadTexture(const char* pFilePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, pFilePath);

	if (texture == NULL)
	{
		cout << "Error loading " << pFilePath << "\n";
	}

	return texture;
}

void RenderWindow::RenderSquare(int pX, int pY, int pW, int pH, int pR, int pG, int pB, int pA)
{
	SDL_Rect renderRect;
	renderRect.x = pX;
	renderRect.y = pY;
	renderRect.w = pW;
	renderRect.h = pH;

	SDL_SetRenderDrawColor(renderer, pR, pG, pB, pA);
	SDL_RenderFillRect(renderer, &renderRect);

}

void RenderWindow::Blit(SDL_Texture* pTexture, int pX, int pY, int pW, int pH)
{
	SDL_Rect dst;
	dst.x = pX;
	dst.y = pY;
	dst.w = pW;
	dst.h = pH;

	SDL_RenderCopy(renderer, pTexture, NULL, &dst);
}

void RenderWindow::RenderEntity(Entity& pEntity)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = pEntity.GetRect().w;
	src.h = pEntity.GetRect().h;

	SDL_Rect dst;
	dst.x = pEntity.GetX();
	dst.y = pEntity.GetY();
	dst.w = pEntity.GetRect().w;
	dst.h = pEntity.GetRect().h;

	SDL_Point pnt;
	SDL_RenderCopyEx(renderer, pEntity.GetTexture(), &src, &dst, 0.0, &pnt, SDL_FLIP_NONE);
}

void RenderWindow::GetTextAndRect( int pX, int pY, const char* pText, TTF_Font* pFont, SDL_Texture** pTexture, SDL_Rect* pRect) 
{
	int text_width;
	int text_height;
	SDL_Surface* surface;
	SDL_Color textColor = { 255, 255, 255, 0 };

	surface			= TTF_RenderText_Solid(pFont, pText, textColor);
	*pTexture		= SDL_CreateTextureFromSurface(renderer, surface);
	string _text	= pText;
	text_width		= _text.size()*24;
	text_height		= 48;

	SDL_FreeSurface(surface);

	pRect->x	= pX;
	pRect->y	= pY;
	pRect->w	= text_width;
	pRect->h	= text_height;
}

void RenderWindow::RenderText(SDL_Texture* pTexture, SDL_Rect pRect)
{
	SDL_RenderCopy(renderer, pTexture, NULL, &pRect);
}

/*
void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w * p_entity.getScale()) / 2;
	dst.y = p_entity.getY() + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h * p_entity.getScale()) / 2;
	dst.w = p_entity.getCurrentFrame().w * p_entity.getScale();
	dst.h = p_entity.getCurrentFrame().h * p_entity.getScale();

	SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}
*/


void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Destroy()
{
	SDL_DestroyWindow(window);
}