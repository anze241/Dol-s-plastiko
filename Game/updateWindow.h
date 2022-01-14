#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include "ReplaySystem.h"
#include "Player.h"
#include "savingSystem.h"

SDL_Surface *Level2ScreenSurface = IMG_Load("level2Screen.png");
SDL_Surface *WinScreenSurface = IMG_Load("winScreen.png");
SDL_Surface *LoseScreenSurface = IMG_Load("loseScreen.png");
SDL_Surface *StartScreenSurface = IMG_Load("startScreen.png");
SDL_Surface *StartScreen2Surface = IMG_Load("startScreen2.png");
SDL_Surface *PauseScreenSurface = IMG_Load("pauseScreen.png");
SDL_Surface *InfoSurface = IMG_Load("info.png");
SDL_Surface *PlayerSurface = IMG_Load("Player1.png");
SDL_Surface *PlayerGroundSurface = IMG_Load("PlayerGround.png");
SDL_Surface *EnemySurface = IMG_Load("Enemy.png");
SDL_Surface *BackgroundSurface = IMG_Load("Background.png");
SDL_Surface *TrashSurface = IMG_Load("Trash.png");
SDL_Surface *AllySurface = IMG_Load("Ally.png");
SDL_Surface *AllyGroundSurface = IMG_Load("AllyGround.png");
SDL_Surface *HeartSurface = IMG_Load("Heart.png");

SDL_Texture *Level2ScreenTexture;
SDL_Texture *LoseScreenTexture;
SDL_Texture *WinScreenTexture;
SDL_Texture *PauseScreenTexture;
SDL_Texture *StartScreen2Texture;
SDL_Texture *PlayerTexture;
SDL_Texture *BackgroundTexture;
SDL_Texture *TrashTexture;
SDL_Texture *EnemyTexture;
SDL_Texture *StartScreenTexture;
SDL_Texture *InfoTexture;
SDL_Texture *AllyTexture;
SDL_Texture *HeartTexture;
TTF_Font *font;

SDL_Rect ShipRect{
		1200,
		0,
		512,
		512
	};

void displayScore(SDL_Renderer *Renderer, int score) {
	int i = 0, temp = abs(score);
	while (temp >= 10) {
		temp /= 10;
		i++;
	}
	i = i * 15 + 115;
	//std::cout << i << std::endl;
	TTF_Init();
	SDL_Rect scoreRect = { 400, 6, i, 40 };
	std::string scoreText = "Score: " + std::to_string(score);
	SDL_Color textColor = {0, 0, 0, 0};

	font = TTF_OpenFont("font.ttf", 28);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Texture *text = SDL_CreateTextureFromSurface(Renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Renderer, text, NULL, &scoreRect);
	SDL_DestroyTexture(text);
	TTF_CloseFont(font);
}

void updateWindow(SDL_Window *Window, SDL_Renderer *Renderer, Player &player, int &gameState, int &score, bool &spawn, bool &spawn2, int &level) {


	SDL_Rect PlayerRect{
		player.getX() - 200,
		player.getY() - 200,
		500,
		500
	};

	SDL_Rect EnemyRect{
		0,
		0,
		128,
		128
	};

	SDL_Rect TrashRect{
		0,
		0,
		128,
		128
	};

	SDL_Rect AllyRect{
		0,
		0,
		128,
		128
	};

	SDL_Rect HeartRect{
		0,
		0,
		32,
		32
	};
	

	SDL_Texture *shipTexture;

	BackgroundTexture = SDL_CreateTextureFromSurface(Renderer, BackgroundSurface);
	SDL_RenderCopy(Renderer, BackgroundTexture, nullptr, nullptr);
	SDL_DestroyTexture(BackgroundTexture);

	tmp = start;
	while (tmp != nullptr) {
		//std::cout <<"Ship: "<< player.getX() << ", " << player.getY() << std::endl;
		//std::cout <<"Trash: "<< tmp->x << ", " << tmp->y << std::endl;

		if (tmp->x > 50) {
			tmp->x -= tmp->speed;
		}

		TrashRect.x = static_cast<int>(tmp->x);
		TrashRect.y = static_cast<int>(tmp->y);

		TrashTexture = SDL_CreateTextureFromSurface(Renderer, TrashSurface);
		switch (tmp->direction) {
			case 0: SDL_RenderCopyEx(Renderer, TrashTexture, nullptr, &TrashRect, 0, NULL, SDL_FLIP_NONE); break;
			case 1: SDL_RenderCopyEx(Renderer, TrashTexture, nullptr, &TrashRect, 180, NULL, SDL_FLIP_NONE); break;
		}
		SDL_DestroyTexture(TrashTexture);
		
		//std::cout << "DISTANCE: " << sqrt((pow((tmp->x - player.getX()), 2) + pow((tmp->y - player.getY()), 2))) << std::endl;

		if (sqrt((pow((tmp->x - (player.getX())), 2) + pow((tmp->y - (player.getY())), 2))) < 64 && tmp != nullptr) {
			std::cout << "DELETING..." << std::endl;
			deleteTrash(tmp);
			tmp = start;
			score += 50;
			std::cout << "Score: " << score << std::endl;
		}

		if (tmp != nullptr && static_cast<int>(tmp->x) == 50) {
			deleteTrash(tmp);
			tmp = start;
			score -= 50;
			std::cout << "Lives: " << player.getLives() << std::endl;
			player.removeLife(player);
			std::cout << "Lives: " << player.getLives() << std::endl;

			if (player.getLives() == 0) {
				gameState = 7;
				spawn = true;
			}
		}

		if(tmp != nullptr)
			tmp = tmp->next;
	}

	tmp2 = start2;
	while (tmp2 != nullptr) {

		EnemyRect.x = static_cast<int>(tmp2->x);
		EnemyRect.y = static_cast<int>(tmp2->y);

		EnemyTexture = SDL_CreateTextureFromSurface(Renderer, EnemySurface);

		if (rand() % 512 == 16) {
			tmp2->direction = rand() % 4;
		}

		switch (tmp2->direction) {
		case 0:
			if(sqrt((pow((tmp2->x - (player.getX())), 2) + pow((tmp2->y - (player.getY())), 2))) < 150)
				SDL_RenderCopyEx(Renderer, EnemyTexture, nullptr, &EnemyRect, 270, NULL, SDL_FLIP_NONE);
			if (tmp2->y < 920) {
				tmp2->y += tmp2->speed;
			}
			else {
				tmp2->direction = rand() % 4;
			}
			break;
		case 3:
			if (sqrt((pow((tmp2->x - (player.getX())), 2) + pow((tmp2->y - (player.getY())), 2))) < 150)
				SDL_RenderCopyEx(Renderer, EnemyTexture, nullptr, &EnemyRect, 0, NULL, SDL_FLIP_NONE);
			if (tmp2->x > 1500) {
				tmp2->x -= tmp2->speed;
			}
			else {
				tmp2->direction = rand() % 3;
				pushTrash(1400, tmp2->y);
			}
			break;
		case 2:
			if (sqrt((pow((tmp2->x - (player.getX())), 2) + pow((tmp2->y - (player.getY())), 2))) < 150)
				SDL_RenderCopyEx(Renderer, EnemyTexture, nullptr, &EnemyRect, 180, NULL, SDL_FLIP_NONE);
			if (tmp2->x < 1800) {
				tmp2->x += tmp2->speed;
			}
			else {
				tmp2->direction = rand() % 4;
			}
			break;
		case 1:
			if (sqrt((pow((tmp2->x - (player.getX())), 2) + pow((tmp2->y - (player.getY())), 2))) < 150)
				SDL_RenderCopyEx(Renderer, EnemyTexture, nullptr, &EnemyRect, 90, NULL, SDL_FLIP_NONE);
			if (tmp2->y > -32) {
				tmp2->y -= tmp2->speed;
			}
			else {
				tmp2->direction = rand() % 4;
			}
			break;
		}
		SDL_DestroyTexture(EnemyTexture);

		if (sqrt((pow((tmp2->x - (player.getX())), 2) + pow((tmp2->y - (player.getY())), 2))) < 64) {
			Enemy *tmp4;
			tmp4 = start2;
			int i = 0;
			while (tmp4 != nullptr) {
				if (sqrt((pow((tmp4->x - (player.getX())), 2) + pow((tmp4->y - (player.getY())), 2))) < 96) {
					i++;
				}
				//std::cout << i << std::endl;
				tmp4 = tmp4->next;
			}

			if (i > 1) {
				gameState = 7;
				spawn = true;
			}
			else {
				std::cout << "DELETING ENEMY..." << std::endl;
				deleteEnemy(tmp2);
				tmp2 = start2;
				score += 100;
				std::cout << "Score: (+50) " << score << std::endl;
			}			
		}

		
		if(tmp2 != nullptr)
			tmp2 = tmp2->next;
	}
	
	tmp3 = start3;
	while (tmp3 != nullptr) {
	
	AllyRect.x = static_cast<int>(tmp3->x);
	AllyRect.y = static_cast<int>(tmp3->y);
		
	if (rand() % 512 == 16) {
			tmp3->direction = rand() % 4;
		}

	switch (tmp3->direction) {
		case 0:
			if (tmp3->y < 920) {
				tmp3->y += tmp3->speed;
				if (tmp3->x < 1400) {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllySurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 270, NULL, SDL_FLIP_NONE);
				}
				else {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllyGroundSurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 270, NULL, SDL_FLIP_NONE);
				}
			}
			else {
				tmp3->direction = rand() % 4;
			}
			break;
		case 3:
			if (tmp3->x > 100) {
				tmp3->x -= tmp3->speed;
				if (tmp3->x < 1400) {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllySurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 0, NULL, SDL_FLIP_NONE);
				}
				else {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllyGroundSurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 0, NULL, SDL_FLIP_NONE);
				}
			}
			else {
				tmp3->direction = rand() % 4;
			}
			break;
		case 2:
			if (tmp3->x < 1800) {
				tmp3->x += tmp3->speed;

				if (tmp3->x < 1400) {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllySurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 180, NULL, SDL_FLIP_NONE);
				}
				else {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllyGroundSurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 180, NULL, SDL_FLIP_NONE);
				}
			}
			else {
				tmp3->direction = rand() % 4;
			}
			break;
		case 1:
				
			if (tmp3->y > -32) {
				tmp3->y -= tmp3->speed;
				if (tmp3->x < 1400) {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllySurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 90, NULL, SDL_FLIP_NONE);
				}
				else {
					AllyTexture = SDL_CreateTextureFromSurface(Renderer, AllyGroundSurface);
					SDL_RenderCopyEx(Renderer, AllyTexture, nullptr, &AllyRect, 90, NULL, SDL_FLIP_NONE);
				}
			}
			else {
				tmp3->direction = rand() % 4;
			}
			break;
		}
		SDL_DestroyTexture(AllyTexture);

		if (sqrt((pow((tmp3->x - (player.getX())), 2) + pow((tmp3->y - (player.getY())), 2))) < 64) {
			std::cout << "DELETING ALLY..." << std::endl;
			deleteAlly(tmp3);
			player.removeLife(player);
			tmp3 = start3;
			score -= 100;
			std::cout << "Score: (-100) " << score << std::endl;

			if (player.getLives() == 0) {
				gameState = 7;
				spawn = true;
			}
		}
		if(tmp3 != nullptr)
			tmp3 = tmp3->next;
	}


	if (player.getSprite() == 1)
		PlayerTexture = SDL_CreateTextureFromSurface(Renderer, PlayerGroundSurface);
	else
		PlayerTexture = SDL_CreateTextureFromSurface(Renderer, PlayerSurface);

	switch (player.getDir()) {
		case 0: SDL_RenderCopyEx(Renderer, PlayerTexture, nullptr, &PlayerRect, 180, NULL, SDL_FLIP_NONE); break;
		case 1: SDL_RenderCopyEx(Renderer, PlayerTexture, nullptr, &PlayerRect, 90, NULL, SDL_FLIP_NONE); break;
		case 2: SDL_RenderCopyEx(Renderer, PlayerTexture, nullptr, &PlayerRect, 0, NULL, SDL_FLIP_NONE); break;
		case 3: SDL_RenderCopyEx(Renderer, PlayerTexture, nullptr, &PlayerRect, 270, NULL, SDL_FLIP_NONE); break;
	}
	
	if (player.getX()==1450) {
		ShipRect.y = player.getY()-200;
		
	}
	if (player.getX() > 1450) {
		shipTexture = SDL_CreateTextureFromSurface(Renderer, PlayerSurface);
		SDL_RenderCopyEx(Renderer, shipTexture, nullptr, &ShipRect, 0, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(shipTexture);
	}
	SDL_DestroyTexture(PlayerTexture);
	
	HeartTexture = SDL_CreateTextureFromSurface(Renderer, HeartSurface);
	for (int i = player.getLives(); i > 0; i--) {
		HeartRect.x = 150 + i * 35;
		HeartRect.y = 10;
		SDL_RenderCopyEx(Renderer, HeartTexture, nullptr, &HeartRect, 0, NULL, SDL_FLIP_NONE);
	}

	SDL_DestroyTexture(HeartTexture);
	displayScore(Renderer, score);
	SDL_RenderPresent(Renderer);

	
	if (start == nullptr && start2 == nullptr) {
		start3 = nullptr;

		player.setLives(5);
		if (level == 1) {
			gameState = 8;
			spawn2 = true;
		}
		else
			gameState = 9;
		
	}
}


void Player::movePlayer(SDL_Event Event, int direction, SDL_Renderer *Renderer) {
	if (Event.type == SDL_KEYDOWN) {
		switch(Event.key.keysym.sym){
		case (SDLK_LEFT): 
			if (x != 1452) {
				if (x > 150) {
					x -= 2;
					this->setDir(2);
					if (x < 1450)
						this->setSprite(0);
				}
			}
			else if (y > (ShipRect.y - 32 + 200) && y < (ShipRect.y + 32 + 200)) {
				std::cout << y << "---" << ShipRect.y << std::endl;
				if (x > 150) {
					x -= 2;
					this->setDir(2);
					if (x < 1450)
						this->setSprite(0);
					}
				}
				break;

			case SDLK_RIGHT:
				if (x < 1820) {
					x += 2;
					this->setDir(0);
					if (x > 1450) {
						this->setSprite(1);
				}
			} break;
			case SDLK_DOWN: if (y < 1024-56) { y += 2; this->setDir(3); } break;
			case SDLK_UP: if (y > 0) { y -= 2; this->setDir(1); } break;
		}

		if (x > 1450) 
			this->setSprite(1);
			replaySave(x, y, direction);
	}	
}


