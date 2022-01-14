#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include "Player.h"
#include "updateWindow.h"

SDL_Surface *GetNameScreenSurface = IMG_Load("getNameScreen.png");
SDL_Surface *LeaderboardSurface = IMG_Load("leaderboard.png");
SDL_Surface *LoadGameSurface = IMG_Load("loadGame.png");
SDL_Surface *SaveGameSurface = IMG_Load("saveGame.png");

SDL_Texture *LeaderboardTexture;
SDL_Texture *GetNameScreenTexture;
SDL_Texture *LoadGameTexture;
SDL_Texture *SaveGameTexture;

struct Score {
	int score;
	char username[20];
};

struct Coordinates {
	int x, y, type;
};


struct Save {
	int score, gamestate, lives, level;
	char username[20];
	Coordinates player;
};

void getName(SDL_Renderer *Renderer, std::string &name, int n, int &gameState) {
	SDL_Event Event;
	TTF_Font *font;
	SDL_PollEvent(&Event);
	int i = 0;
	while (Event.key.keysym.sym != SDLK_RETURN) {
		SDL_Delay(100);
		SDL_PollEvent(&Event);
		if (Event.type == SDL_KEYDOWN) {
			switch (Event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (n == 1) {
					gameState = 1;
					SDL_Delay(100);
					return;
				}
				else if (n == 2) {
					gameState = 1;
					SDL_Delay(100);
					return;
				}
				else {
					gameState = 1;
					SDL_Delay(100);
					return;
				}
				break;
			case SDLK_a:
				if (name.size() < 20) {
					name.push_back('a');
					i++;
				}
				break;
			case SDLK_b:
				if (name.size() < 20) {
					name.push_back('b');
					i++;
				}
				break;
			case SDLK_c:
				if (name.size() < 20) {
					name.push_back('c');
					i++;
				}
				break;
			case SDLK_d:
				if (name.size() < 20) {
					name.push_back('d');
					i++;
				}
				break;
			case SDLK_e:
				if (name.size() < 20) {
					name.push_back('e');
					i++;
				}
				break;
			case SDLK_f:
				if (name.size() < 20) {
					name.push_back('f');
					i++;
				}
				break;
			case SDLK_g:
				if (name.size() < 20) {
					name.push_back('g');
					i++;
				}
				break;
			case SDLK_h:
				if (name.size() < 20) {
					name.push_back('h');
					i++;
				}
				break;
			case SDLK_i:
				if (name.size() < 20) {
					name.push_back('i');
					i++;
				}
				break;
			case SDLK_j:
				if (name.size() < 20) {
					name.push_back('j');
					i++;
				}
				break;
			case SDLK_k:
				if (name.size() < 20) {
					name.push_back('k');
					i++;
				}
				break;
			case SDLK_l:
				if (name.size() < 20) {
					name.push_back('l');
					i++;
				}
				break;
			case SDLK_m:
				if (name.size() < 20) {
					name.push_back('m');
					i++;
				}
				break;
			case SDLK_n:
				if (name.size() < 20) {
					name.push_back('n');
					i++;
				}
				break;
			case SDLK_o:
				if (name.size() < 20) {
					name.push_back('o');
					i++;
				}
				break;
			case SDLK_p:
				if (name.size() < 20) {
					name.push_back('p');
					i++;
				}
				break;
			case SDLK_r:
				if (name.size() < 20) {
					name.push_back('r');
					i++;
				}
				break;
			case SDLK_s:
				if (name.size() < 20) {
					name.push_back('s');
					i++;
				}
				break;
			case SDLK_t:
				if (name.size() < 20) {
					name.push_back('t');
					i++;
				}
				break;
			case SDLK_u:
				if (name.size() < 20) {
					name.push_back('u');
					i++;
				}
				break;
			case SDLK_v:
				if (name.size() < 20) {
					name.push_back('v');
					i++;
				}
				break;
			case SDLK_y:
				if (name.size() < 20) {
					name.push_back('y');
					i++;
				}
				break;
			case SDLK_w:
				if (name.size() < 20) {
					name.push_back('w');
					i++;
				}
				break;
			case SDLK_z:
				if (name.size() < 20) {
					name.push_back('z');
					i++;
				}
				break;
			case SDLK_BACKSPACE:
				if (name.size() > 0) {
					name.pop_back();
				    i--;
				}
				break;
			}
		}
		if (n == 3) {
			GetNameScreenTexture = SDL_CreateTextureFromSurface(Renderer, GetNameScreenSurface);
			SDL_RenderCopy(Renderer, GetNameScreenTexture, nullptr, nullptr);
			SDL_DestroyTexture(GetNameScreenTexture);
		}
		else if (n == 2) {
			LoadGameTexture = SDL_CreateTextureFromSurface(Renderer, LoadGameSurface);
			SDL_RenderCopy(Renderer, LoadGameTexture, nullptr, nullptr);
			SDL_DestroyTexture(LoadGameTexture);
		}
		else if (n == 1) {
			SaveGameTexture = SDL_CreateTextureFromSurface(Renderer, SaveGameSurface);
			SDL_RenderCopy(Renderer, SaveGameTexture, nullptr, nullptr);
			SDL_DestroyTexture(SaveGameTexture);
		}
		
		TTF_Init();

		SDL_Rect nameRect = { 200, 520, 28, 75 };
		nameRect.w = 28*i;
		nameRect.x = 1920 / 2 - 15 * i;
		SDL_Color textColor = { 0, 0, 0, 0 };

		font = TTF_OpenFont("font.ttf", 48);
		SDL_Surface *nameSurface = TTF_RenderText_Solid(font, name.c_str(), textColor);
		SDL_Texture *nameTexture = SDL_CreateTextureFromSurface(Renderer, nameSurface);

		SDL_FreeSurface(nameSurface);

		SDL_RenderCopy(Renderer, nameTexture, NULL, &nameRect);
		SDL_DestroyTexture(nameTexture);
		SDL_RenderPresent(Renderer);
		
	}
}


void insertScore(int score, std::string name) {

	Score tmp, player;
	player.score = score;
	strcpy_s(player.username, name.c_str());
	int location = 0;

	std::ofstream scoreOut("Temp.bin", std::ios::binary);
	std::ifstream scoreIn("Scores.bin", std::ios::binary);
	
	int i = 0;
	bool vpisan = 0;

	scoreIn.seekg(0, std::ios::end);
	if (scoreIn.tellg() == 0) {
		scoreOut.write((char*)& player, sizeof(player));
	}
	else {
		scoreIn.seekg(0, std::ios::beg);
		while (scoreIn.read((char*)& tmp, sizeof(tmp)) && i < 5) {
			if (tmp.score < player.score && vpisan == 0) {
				scoreOut.write((char*)& player, sizeof(player));
				vpisan = 1;
				i++;
			}
			scoreOut.write((char*)&tmp, sizeof(tmp));
			i++;
		}
	}
	if (vpisan == 0 && scoreOut.tellp() < 5 * sizeof(player)) {
		scoreOut.write((char*)& player, sizeof(player));
	}
	scoreOut.close();
	scoreOut.close();
	scoreIn.close();
	remove("Scores.bin");
	rename("Temp.bin", "Scores.bin");
}

void readScore(SDL_Renderer *Renderer) {
	Score player;

	SDL_Event Event;
	TTF_Font *font;
	SDL_PollEvent(&Event);
	std::ifstream in("Scores.bin", std::ios::binary);
	LeaderboardTexture = SDL_CreateTextureFromSurface(Renderer, LeaderboardSurface);
	SDL_RenderCopy(Renderer, LeaderboardTexture, nullptr, nullptr);
	SDL_DestroyTexture(LeaderboardTexture);

	while (Event.key.keysym.sym != SDLK_ESCAPE) {
		SDL_PollEvent(&Event);
		SDL_Rect nameRect = { 500, 500, 28, 75 };
		int i = 0;
		TTF_Init();
		if (in.is_open()) {
			while (in.read((char *)&player, sizeof(player))) {
				SDL_PollEvent(&Event);
				i++;
				nameRect.y = 200 + 125 * i;
				SDL_Color textColor = { 0, 0, 0, 0 };

				font = TTF_OpenFont("font.ttf", 48);
				strcat_s(player.username, ": ");
				strcat_s(player.username, std::to_string(player.score).c_str());
				nameRect.w = strlen(player.username)*28;
				SDL_Surface *nameSurface = TTF_RenderText_Solid(font, player.username, textColor);
				SDL_Texture *nameTexture = SDL_CreateTextureFromSurface(Renderer, nameSurface);
				SDL_RenderCopy(Renderer, nameTexture, NULL, &nameRect);
				
				SDL_FreeSurface(nameSurface);
				SDL_DestroyTexture(nameTexture);
			}
		}
		SDL_RenderPresent(Renderer);
	}
}

void saveGame(SDL_Renderer *Renderer, Player &p, int score, int gamestate, int level) {

	Save player;
	Coordinates c;
	std::string name;
	player.level = level;
	player.score = score;
	player.gamestate = gamestate;
	player.lives = p.getLives();
	player.player.x = p.getX();
	player.player.y = p.getY();
	getName(Renderer, name, 1, gamestate);

	strcpy_s(player.username, name.c_str());
	strcat_s(player.username, ".bin");
	remove(player.username);
	std::ofstream out(player.username, std::ios::binary | std::ios::app);

	out.write((char *)&player, sizeof(player));

	tmp3 = start3;
	for (int i = 0; tmp3 != nullptr; i++) {

		c.x = static_cast<int>(tmp3->x);
		c.y = static_cast<int>(tmp3->y);
		c.type = 3;
		out.write((char *)&c, sizeof(c));
		std::cout << tmp3->x <<", "<< tmp3->y << std::endl;
		if (tmp3!= nullptr)
			tmp3 = tmp3->next;
	}

	tmp2 = start2;
	for (int i = 0; tmp2 != nullptr; i++) {
		c.x = static_cast<int>(tmp2->x);
		c.y = static_cast<int>(tmp2->y);
		c.type = 2;
		out.write((char *)&c, sizeof(c));
		std::cout << tmp2->x << ", " << tmp2->y << std::endl;
		if (tmp2 != nullptr)
			tmp2 = tmp2->next;
	}

	tmp = start;
	for (int i = 0; tmp != nullptr; i++) {
		c.x = static_cast<int>(tmp->x);
		c.y = static_cast<int>(tmp->y); 
		c.type = 1;
		std::cout << tmp->x << ", " << tmp->y << std::endl;
		out.write((char *)&c, sizeof(c));
		if (tmp != nullptr)
			tmp = tmp->next;
	}

	/*std::cout <<"VECTOR ALLY:"<< std::endl;
	std::vector<Coordinates>::iterator it;
	for (it = player.allies.begin(); it != player.allies.end(); it++) {
		std::cout << it->x << ", " << it->y <<", "<< it->type << std::endl;
	}	*/
	
}

void readSave(Player &p, char string[], int &gameState, int &score, bool &spawn, bool &spawn2, int &level) {
	Save player;
	Coordinates c;
	char name[20];
	strcpy_s(name, string);
	strcat_s(name, ".bin");
	std::cout << name << std::endl;

	std::ifstream in(name, std::ios::binary);
	if (in.is_open()) {
		in.read((char *)&player, sizeof(player));
		std::cout << player.gamestate << std::endl;
		gameState = player.gamestate;
		score = player.score;
		level = player.level;
		start = nullptr;
		start2 = nullptr;
		start3 = nullptr;
		std::cout <<"Player: "<< player.player.x << ", " << player.player.y << std::endl;
		p.setX(player.player.x);
		p.setY(player.player.y);
		p.setLives(player.lives);
		while (in.read((char *)&c, sizeof(c))) {
			std::cout << c.x << ", " << c.y << ", " << c.type << std::endl;

			switch (c.type) {
				case 1: pushTrash(c.x, c.y); break;
				case 2: pushEnemy(c.x, c.y); break;
				case 3: pushAlly(c.x, c.y); break;
			}
			

			/*for (int i = 0; i < player.enemies.size(); i++) {
				pushAlly(player.enemies[i].x, player.enemies[i].y);
			}
			for (int i = 0; i < player.trash.size(); i++) {
				pushAlly(player.trash[i].x, player.trash[i].y);
			}*/
		}
	}
	spawn = false;
	spawn2 = false;
		
	}
