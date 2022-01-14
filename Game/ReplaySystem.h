#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include "Player.h"

SDL_Surface *BackgroundSurface2 = IMG_Load("Background.png");
SDL_Surface *PlayerSurface2 = IMG_Load("Player1.png");
SDL_Surface *PlayerGroundSurface2 = IMG_Load("PlayerGround.png");

SDL_Texture *PlayerTexture2;
SDL_Texture *BackgroundTexture2;

std::vector<Player> replay;

void replaySave(int x, int y, int dir) {
	Player temp;
	temp.setX(x);
	temp.setY2(y);
	temp.setDir(dir);
	replay.push_back(temp);
}

void replayRead(SDL_Renderer *Renderer) {
	SDL_Rect tmp;
	tmp.w = 500;
	tmp.h = 500;
	for (unsigned i = 0; i < replay.size(); i++) {
		/*std::cout << replay.at(i).getX() << std::endl;
		std::cout << replay.at(i).getY() << std::endl;
		std::cout << replay.at(i).getDir() << std::endl;*/

		tmp.x = replay.at(i).getX()-200;
		tmp.y = replay.at(i).getY()-200;

		if (replay.at(i).getX() > 1450) {
			BackgroundTexture2 = SDL_CreateTextureFromSurface(Renderer, BackgroundSurface2);
			SDL_RenderCopy(Renderer, BackgroundTexture2, nullptr, nullptr);
			SDL_DestroyTexture(BackgroundTexture2);
			PlayerTexture2 = SDL_CreateTextureFromSurface(Renderer, PlayerGroundSurface2);

			switch (replay.at(i).getDir()) {
			case 0:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 180, NULL, SDL_FLIP_NONE);
				break;
			case 3:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 270, NULL, SDL_FLIP_NONE);
				break;
			case 2:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 0, NULL, SDL_FLIP_NONE);
				break;
			case 1:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 90, NULL, SDL_FLIP_NONE);
				break;
			}
			SDL_DestroyTexture(PlayerTexture2);
			SDL_RenderPresent(Renderer);
		}
		else {
			BackgroundTexture2 = SDL_CreateTextureFromSurface(Renderer, BackgroundSurface2);
			SDL_RenderCopy(Renderer, BackgroundTexture2, nullptr, nullptr);
			SDL_DestroyTexture(BackgroundTexture2);
			PlayerTexture2 = SDL_CreateTextureFromSurface(Renderer, PlayerSurface2);

			switch (replay.at(i).getDir()) {
			case 0:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 180, NULL, SDL_FLIP_NONE);
				break;
			case 3:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 270, NULL, SDL_FLIP_NONE);
				break;
			case 2:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 0, NULL, SDL_FLIP_NONE);
				break;
			case 1:
				SDL_RenderCopyEx(Renderer, PlayerTexture2, nullptr, &tmp, 90, NULL, SDL_FLIP_NONE);
				break;
			}
			SDL_DestroyTexture(PlayerTexture2);
			SDL_RenderPresent(Renderer);
		}	
		
	}
}

