#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL_image.h>

SDL_Window *Window = SDL_CreateWindow("Dol s plastiko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1024, 0);
SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

SDL_Surface *StartScreenSurface = IMG_Load("startScreen.png");
SDL_Surface *InfoSurface = IMG_Load("info.png");
SDL_Surface *PlayerSurface = IMG_Load("Player1.png");
SDL_Surface *PlayerGroundSurface = IMG_Load("PlayerGround.png");
SDL_Surface *EnemySurface = IMG_Load("Enemy.png");
SDL_Surface *BackgroundSurface = IMG_Load("Background.png");
SDL_Surface *TrashSurface = IMG_Load("Trash.png");
SDL_Surface *AllySurface = IMG_Load("Ally.png");
SDL_Surface *AllyGroundSurface = IMG_Load("AllyGround.png");
SDL_Surface *HeartSurface = IMG_Load("Heart.png");

SDL_Texture *PlayerTexture = SDL_CreateTextureFromSurface(Renderer, PlayerSurface);
SDL_Texture *BackgroundTexture = SDL_CreateTextureFromSurface(Renderer, BackgroundSurface);
SDL_Texture *TrashTexture = SDL_CreateTextureFromSurface(Renderer, TrashSurface);
SDL_Texture *EnemyTexture = SDL_CreateTextureFromSurface(Renderer, EnemySurface);
SDL_Texture *StartScreenTexture = SDL_CreateTextureFromSurface(Renderer, StartScreenSurface);
SDL_Texture *InfoTexture = SDL_CreateTextureFromSurface(Renderer, InfoSurface);
SDL_Texture *AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllySurface);
SDL_Texture *HeartTexture = SDL_CreateTextureFromSurface(Renderer, HeartSurface);

