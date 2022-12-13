///////////////////////////////////////////////////
/*

	My goal is to make a music player with
	a queue that allows you to add songs and
	remove them, play them in the order selected
	by the user. I still need to import the 
	Mixer Library.

*/
///////////////////////////////////////////////////
#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <dirent.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <fstream>

#include "renderWindow.h"
#include "buttons.h"
#include "entity.h"
#include "defs.h"

using namespace std;

/* SDL Initializations */
RenderWindow app		= RenderWindow("Music Player", WINDOW_WIDTH, WINDOW_HEIGHT);

SDL_Texture* tex_play	= app.LoadTexture("Image/play.png");
SDL_Texture* tex_pause	= app.LoadTexture("Image/pause.png");
SDL_Texture* tex_skip	= app.LoadTexture("Image/skip.png");

Play btn_play			= Play(WINDOW_WIDTH - 64 - 4, 0, tex_play);
Pause btn_pause			= Pause(WINDOW_WIDTH - 128 - 4, 0, tex_pause);
Skip btn_skip			= Skip(WINDOW_WIDTH - 192 - 4, 0, tex_skip);

unordered_map<int, Mix_Music*> songList;
vector<string> songNameList;

const char* path = "Music";

void InitializeSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
}

void AddSongs()
{
	/* Check If The Folder "path" Exist */
	DIR* d = opendir(path);
	if (!d)
	{
		cout << "error!";
	}
	/* Initialize and check amount of files in folder "path" */
	struct dirent** namelist;
	int n;
	n = scandir(path, &namelist, NULL, alphasort);

	/* 
		Add Every Song while there's existing files
		that havent been checked
	*/
	while (n > 0)
	{
		/* Convert const char to string to sum them */
		string _s		= namelist[n - 1]->d_name;
		string _ss		= path;
		string _sOut	= _ss + "/" + _s;

		/* 
			Check if the file is valid, and add it to the playlist 
			"songList"
		*/
		if (_s != "." && _s != ".." && (_s.find(".mp3") != -1 || _s.find(".MP3") != -1))
		{
			string _str = _s;
			Mix_Music* _song = Mix_LoadMUS(_sOut.c_str());
			cout << _sOut << endl;

			songList.emplace(songList.size() + 1, _song);
			_str.erase(_str.end()-4, _str.end());
			songNameList.emplace_back(_str);
		}

		delete namelist[n - 1];
		n--;
	}

	delete namelist;
}

/* Collision */
bool Collision(SDL_Rect rectA, SDL_Rect rectB)
{
	if (rectA.x >= rectB.x && rectA.y >= rectB.y && rectA.x < (rectB.x + rectB.w) && rectA.y < (rectB.y + rectB.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Main App */
int xMouse, yMouse;
bool done		= false;
short songIndex = 1;

int main(int argc, char* args[])
{
	SDL_Texture* tex_text1;
	SDL_Rect rect_text1;
	SDL_Surface* icon = IMG_Load("icon.png");
	SDL_SetWindowIcon(app.GetWindow(), icon);

	/* Initialize SDL */
	InitializeSDL();
	AddSongs();
	TTF_Font* font		= TTF_OpenFont("arial.ttf", 64);
	Mix_Music* song		= songList.at(1);
	Mix_Chunk* sound	= Mix_LoadWAV("click.mp3");
	
	while (!done)
	{
		string _currentSong = songNameList.at(songIndex-1);
		app.GetTextAndRect(8, 8, _currentSong.c_str(), font, &tex_text1, &rect_text1);

		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					done = true;
				break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&xMouse, &yMouse);
					SDL_Rect rectMouse;
					rectMouse.x = xMouse;
					rectMouse.y = yMouse;
					rectMouse.w = 1;
					rectMouse.h = 1;
					
					if (Collision(rectMouse, btn_play.GetRect()))
					{
						btn_play.OnClick();

						if (!Mix_PlayingMusic() && song != NULL)
						{
							Mix_PlayChannel(2, sound, 0);
							Mix_PlayMusic(song, false);
						}
						else
						{
							Mix_ResumeMusic();
						}
					}
					if (Collision(rectMouse, btn_pause.GetRect()))
					{
						btn_pause.OnClick();

						Mix_PlayChannel(2, sound, 0);
						Mix_PauseMusic();
					}
					if (Collision(rectMouse, btn_skip.GetRect()))
					{
						btn_pause.OnClick();
						Mix_PlayChannel(2, sound, 0);

						Mix_HaltMusic();
						songIndex = SDL_clamp(songIndex, 1, songList.size());

						if (songIndex == songList.size())
						{
							songIndex = 1;
							song  = songList.at(songIndex);

						}
						else
						{
							songIndex++;
							song = songList.at(songIndex);
						}
					}
				break;
			}
		}

		app.RenderSquare(0, 0, WINDOW_WIDTH, 64, 107, 114, 142, 255);
		app.RenderSquare(64, 64, WINDOW_WIDTH-128, WINDOW_HEIGHT, 71, 78, 104, 255);

		app.RenderText(tex_text1, rect_text1);
		app.RenderEntity(btn_play);
		app.RenderEntity(btn_pause);
		app.RenderEntity(btn_skip);

		app.Display();
		app.Clear();
	}

	app.Destroy();
	SDL_Quit();

	return 0;
}

/* 
	// COLOR PALETTE //
	rgb(64, 66, 88)
	rgb(71, 78, 104)
	rgb(80, 87, 122)
	rgb(107, 114, 142)
*/