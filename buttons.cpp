#include "buttons.h"
#include <iostream>
using namespace std;

/* Constructors */
Play::Play(int pX, int pY, SDL_Texture* pTexture)
	:Entity{ pX, pY, pTexture }
{
	// 
}

Pause::Pause(int pX, int pY, SDL_Texture* pTexture)
	:Entity{ pX, pY, pTexture }
{
	//
}

Skip::Skip(int pX, int pY, SDL_Texture* pTexture)
	:Entity{ pX, pY, pTexture }
{
	//
}


void Play::OnClick()
{
	cout << "hey there! \n";
}

void Pause::OnClick()
{
	cout << "daa \n";
}

void Skip::OnClick()
{
	//
}