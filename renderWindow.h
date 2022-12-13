#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int pW, int pH);


	void Destroy();
	void Clear();
	void Display();

	SDL_Texture* LoadTexture(const char* pFilePath);
	SDL_Window* GetWindow() { return window; }
	SDL_Renderer* GetRenderer() { return renderer; }

	void Blit(SDL_Texture* pTexture, int pX, int pY, int pW, int pH);
	void RenderEntity(Entity& pEntity);
	void RenderText(SDL_Texture* pTexture, SDL_Rect pRect);
	void GetTextAndRect(int pX, int pY, const char* pText, TTF_Font* pFont, SDL_Texture** pTexture, SDL_Rect* pRect);
	void RenderSquare(int pX, int pY, int pW, int pH, int pR, int pG, int pB, int pA);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};