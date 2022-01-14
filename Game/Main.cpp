#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "updateWindow.h"
#include "Player.h"
#include "savingSystem.h"
#include "ReplaySystem.h"

using namespace std;

int main(int argc, char *argv[]){

	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	

	SDL_Window *Window = SDL_CreateWindow("Dol s plastiko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1024, 0);
	SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	Player player;

	SDL_Event Event;
	int gameState = 0, level = 1;
	bool gameRunning = true, spawn = true, spawn2 = false, sum = true;
	int score = 0;
	int x = 0, y = 0;
	Uint32 levelStart, levelEnd, timeTogether = 0;


	while (gameRunning == true) {
		while (gameState == 0) {
			StartScreen2Texture = SDL_CreateTextureFromSurface(Renderer, StartScreen2Surface);
			SDL_RenderCopy(Renderer, StartScreen2Texture, nullptr, nullptr);
			SDL_DestroyTexture(StartScreen2Texture);
			SDL_RenderPresent(Renderer);

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;

			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 540 && x < 1290 && y > 130 && y < 270 && Event.button.button == SDL_BUTTON_LEFT) {
					score = 0;
					gameState = 1;
					level = 1;
					spawn = true;
					spawn2 = false;
					SDL_Delay(100);
				}

				if (x > 540 && x < 1290 && y > 320 && y < 450 && Event.button.button == SDL_BUTTON_LEFT) {
					std::string sname;
					getName(Renderer, sname, 2, gameState);
					char name[20];
					strcpy_s(name, sname.c_str());					
					readSave(player, name, gameState, score, spawn, spawn2, level);
					SDL_Delay(100);
				}

				if (x > 470 && x < 1350 && y > 500 && y < 650 && Event.button.button == SDL_BUTTON_LEFT) {
					readScore(Renderer);
					SDL_Delay(100);
				}

				if (x > 500 && x < 1300 && y > 700 && y < 840 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = -1;
					gameRunning = false;
					SDL_Delay(100);
				}
			}


		}

		if (spawn == true) {
			start = nullptr;
			start2 = nullptr;
			start3 = nullptr;
			player.setX(150);
			player.setY();
			player.setLives(5);
			player.setSprite(2);
			player.setDir(0);
			score = 0;
			replay.clear();
			
			for (int i = 0; i < 5; i++) {
				pushTrash(rand() % 800 + 500, rand() % 750 + 50);
				
			}

			for (int i = 0; i < 3; i++) {
				pushEnemy(rand() % (350) + 1450, rand() % (750) + 50);
				pushAlly(rand() % 1400 + 300, rand() % 750 + 50);
			}

			spawn = false;
		}

		while (gameState == 1) {
			StartScreenTexture = SDL_CreateTextureFromSurface(Renderer, StartScreenSurface);
			SDL_RenderCopy(Renderer, StartScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(StartScreenTexture);
			SDL_RenderPresent(Renderer);

			SDL_PollEvent(&Event);
			if (Event.type == SDL_QUIT) {
				gameState = -1;
			}
			else if (Event.key.keysym.sym == SDLK_ESCAPE) {
				gameState = 0;
			}
			else if (Event.key.keysym.sym == SDLK_SPACE) {
				gameState = 2;
			}
		}

		while (gameState == 2) {
			InfoTexture = SDL_CreateTextureFromSurface(Renderer, InfoSurface);
			SDL_RenderCopy(Renderer, StartScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(InfoTexture);
			SDL_RenderPresent(Renderer);

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 580 && x < 1300 && y > 830 && y < 950 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 3;
					levelStart = SDL_GetTicks();
					std::cout << "LEVEL START: " << levelStart << std::endl;
					SDL_Delay(100);
				}
				if (Event.type == SDL_QUIT) {
					gameState = -1;
				}
				if (Event.key.keysym.sym == SDLK_ESCAPE) {
					gameState = 1;
				}
			}
		}

		while (gameState == 3) {
			SDL_PollEvent(&Event);
			if (Event.type == SDL_QUIT) {
				gameState = -1;
			}
			if (Event.key.keysym.sym == SDLK_ESCAPE) {
				gameState = 6;
			}
			player.movePlayer(Event, player.getDir(), Renderer);
			updateWindow(Window, Renderer, player, gameState, score, spawn, spawn2, level);
		}

		while (gameState == 4) {

			InfoTexture = SDL_CreateTextureFromSurface(Renderer, InfoSurface);
			SDL_RenderCopy(Renderer, StartScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(InfoTexture);
			SDL_RenderPresent(Renderer);


			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 580 && x < 1300 && y > 830 && y < 950 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 3;
					SDL_Delay(100);
				}
			}
			if (Event.type == SDL_QUIT) {
				gameState = -1;
			}
			if (Event.key.keysym.sym == SDLK_ESCAPE) {
				gameState = 6;
			}
		}

		while (gameState == 8) {
			Level2ScreenTexture = SDL_CreateTextureFromSurface(Renderer, Level2ScreenSurface);
			SDL_RenderCopy(Renderer, Level2ScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(Level2ScreenTexture);
			SDL_RenderPresent(Renderer);
			levelEnd = SDL_GetTicks();
			//std::cout << "LEVEL END: " << levelEnd << std::endl;
			
			if (sum == true) {
				timeTogether += levelEnd - levelStart;
				std::cout << "DIFF: " << timeTogether << std::endl;
				sum = false;
			}

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 520 && x < 1280 && y > 330 && y < 500 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 5;
					levelStart = SDL_GetTicks();
					sum = true;
					replay.clear();
					replay.resize(0);
					SDL_Delay(100);
				}
				if (x > 520 && x < 1280 && y > 550 && y < 710 && Event.button.button == SDL_BUTTON_LEFT) {
					replayRead(Renderer);
					SDL_Delay(100);
				}
				if (x > 460 && x < 1360 && y > 780 && y < 930 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 0;
					spawn = true;
					spawn2 = false;
					SDL_Delay(100);
				}
			}
			if (Event.type == SDL_QUIT) {
				gameState = -1;
			}
		}

		if (spawn2 == true) {
			start = nullptr;
			start2 = nullptr;
			start3 = nullptr;
			player.setX(150);
			player.setY();
			player.setLives(5);
			player.setSprite(2);
			player.setDir(0);
			level = 2;

			for (int i = 0; i < 6; i++) {
				pushAlly(rand() % 1400 + 300, rand() % 750 + 50);
				pushEnemy(rand() % (350) + 1450, rand() % (750) + 50);
			}

			for (int i = 0; i < 8; i++) {
				pushTrash(rand() % 800 + 500, rand() % (750) + 50);
			}
			spawn2 = false;
		}


		while (gameState == 5) {
			level = 2;
			SDL_PollEvent(&Event);
			if (Event.type == SDL_QUIT) {
				gameState = -1;
			}
			if (Event.key.keysym.sym == SDLK_ESCAPE) {
				gameState = 6;
			}
			
			player.movePlayer(Event, player.getDir(), Renderer);
			updateWindow(Window, Renderer, player, gameState, score, spawn, spawn2, level);
		}

		while (gameState == 6) {
			PauseScreenTexture = SDL_CreateTextureFromSurface(Renderer, PauseScreenSurface);
			SDL_RenderCopy(Renderer, PauseScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(PauseScreenTexture);
			SDL_RenderPresent(Renderer);

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			std::cout << x << ", " << y << std::endl;
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 390 && x < 1470 && y > 210 && y < 370 && Event.button.button == SDL_BUTTON_LEFT) {
					if (level == 1)
						gameState = 3;
					else
						gameState = 5;
					SDL_Delay(100);
				}


				if (x > 470 && x < 1370 && y > 410 && y < 550 && Event.button.button == SDL_BUTTON_LEFT) {
					saveGame(Renderer, player, score, gameState, level);
					SDL_Delay(100);
				}

				if (x > 470 && x < 1340 && y > 770 && y < 900 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 0;
					timeTogether = 0;
					replay.clear();
					replay.resize(0);
					SDL_Delay(100);
				}
			}
		}

		while (gameState == 7) {
			LoseScreenTexture = SDL_CreateTextureFromSurface(Renderer, LoseScreenSurface);
			SDL_RenderCopy(Renderer, LoseScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(LoseScreenTexture);
			SDL_RenderPresent(Renderer);

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 510 && x < 1270 && y > 450 && y < 610 && Event.button.button == SDL_BUTTON_LEFT) {
					replayRead(Renderer);
					SDL_Delay(100);
				}

				if (x > 460 && x < 1360 && y > 710 && y < 870 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 0;
					SDL_Delay(100);
				}
			}
		}

		while (gameState == 9) {
			WinScreenTexture = SDL_CreateTextureFromSurface(Renderer, WinScreenSurface);
			SDL_RenderCopy(Renderer, WinScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(WinScreenTexture);
			SDL_RenderPresent(Renderer);
			levelEnd = SDL_GetTicks();
			if (sum == true) {
				timeTogether += levelEnd - levelStart;
				std::cout << "DIFF: " << timeTogether << std::endl;
				sum = false;
				//score -= timeTogether / 1000;
			}			

			SDL_PollEvent(&Event);
			SDL_MouseButtonEvent();
			SDL_GetMouseState(&x, &y);
			//std::cout << x << ", " << y << std::endl;
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				if (x > 420 && x < 1380 && y > 300 && y < 470 && Event.button.button == SDL_BUTTON_LEFT) {
					std::string name;
					getName(Renderer, name, 3, gameState);
					insertScore(score, name);
					gameState = 0;
					SDL_Delay(100);
				}

				if (x > 510 && x < 1270 && y > 520 && y < 680 && Event.button.button == SDL_BUTTON_LEFT) {
					replayRead(Renderer);
					SDL_Delay(100);
				}

				if (x > 460 && x < 1360 && y > 780 && y < 930 && Event.button.button == SDL_BUTTON_LEFT) {
					gameState = 0;
					SDL_Delay(100);
				}
			}

		}



	}

	return 0;
}