#pragma once
#include<ctime>
#include<cstdlib>
#include<list>

class Player{
	int x, y, shipPosX, shipPosY, direction, sprite, lives;
public:
	Player(){ 
		sprite = 0;
		direction = 0;
		x = 150;
		y = rand() % (1024 - 128);
		lives = 5;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int a) {
		x = a;
	}
	void setY() {
		y = rand() % (1024 - 128);
	}
	void setY(int a) {
		y = a;
	}
	void setY2(int a) {
		y = a;
	}
	int getDir() {
		return direction;
	}
	void setDir(int dir) {
		direction = dir;
	}
	void setSprite(int spr) {
		sprite = spr;
	}
	int getSprite() {
		return sprite;
	}
	void removeLife(Player &) {
		lives--;
	}
	int getLives() {
		return lives;
	}
	void setLives(int a) {
		lives = a;
	}
	void movePlayer(SDL_Event Event, int direction, SDL_Renderer *Renderer);
};

struct Trash {
	float x, y, speed = (float)(rand() % 20) / 50.0 + 0.1;
	int direction = rand() % 2;
	Trash *next, *prev;
}*start = NULL, *tmp, *endd = NULL;

struct Enemy {
	float x, y, speed = (float)(rand() % 20) / 50.0 + 0.2;
	int direction = rand() % 4;
	Enemy *next, *prev;
}*start2 = NULL, *tmp2, *end2 = NULL;

struct Ally {
	float x, y, speed = (float)(rand() % 20) / 50.0 + 0.2;
	int direction = rand() % 4;
	Ally *next, *prev;
}*start3 = NULL, *tmp3, *end3 = NULL;



void pushTrash(int x, int y) {
	tmp = new Trash;
	tmp->x = x;
	tmp->y = y;

	if (start == NULL) {
		start = tmp;
		endd = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	else {
		tmp->next = start;
		start->prev = tmp;
		start = tmp;
		start->prev = NULL;
	}
}

void pushEnemy(int x, int y) {
	tmp2 = new Enemy;
	tmp2->x = x;
	tmp2->y = y;

	if (start2 == NULL) {
		start2 = tmp2;
		end2 = tmp2;
		tmp2->next = NULL;
		tmp2->prev = NULL;
	}
	else {
		tmp2->next = start2;
		start2->prev = tmp2;
		start2 = tmp2;
		start2->prev = NULL;
	}
}

void pushAlly(int x, int y) {
	tmp3 = new Ally;
	tmp3->x = x;
	tmp3->y = y;

	if (start3 == NULL) {
		start3 = tmp3;
		end3 = tmp3;
		tmp3->next = NULL;
		tmp3->prev = NULL;
	}
	else {
		tmp3->next = start3;
		start3->prev = tmp3;
		start3 = tmp3;
		start3->prev = NULL;
	}
}

void deleteTrash(Trash *tmp) {
	if (tmp == start && start == endd) {
		start->next = nullptr;
		start->prev = nullptr;
		delete tmp;
		start = nullptr;
	}
	else if (tmp == start) {
		start = start->next;
		start->prev = nullptr;
		tmp->next = nullptr;
		delete tmp;
	}
	else if (tmp == endd) {
		endd = tmp->prev;
		endd->next = nullptr;
		tmp->prev = nullptr;
		delete tmp;
	}
	else {
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		delete tmp;
	}
}

void deleteEnemy(Enemy *tmp2) {
	if (tmp2 == start2 && start2 == end2) {
		start2->next = nullptr;
		start2->prev = nullptr;
		delete tmp2;
		start2 = nullptr;
	}
	else if (tmp2 == start2) {
		start2 = tmp2->next;
		start2->prev = nullptr;
		tmp2->next = nullptr;
		delete tmp2;
	}
	else if (tmp2 == end2) {
		end2 = tmp2->prev;
		end2->next = nullptr;
		tmp2->prev = nullptr;
		delete tmp2;
	}
	else {
		tmp2->next->prev = tmp2->prev;
		tmp2->prev->next = tmp2->next;
		delete tmp2;
	}
}

void deleteAlly(Ally *tmp3) {
	if (tmp3 == start3 && start3 == end3) {
		start3->next = nullptr;
		start3->prev = nullptr;
		delete tmp3;
		start3 = nullptr;
	}
	else if (tmp3 == start3) {
		start3 = tmp3->next;
		start3->prev = nullptr;
		tmp3->next = nullptr;
		delete tmp3;
	}
	else if (tmp3 == end3) {
		end3 = tmp3->prev;
		end3->next = nullptr;
		tmp3->prev = nullptr;
		delete tmp3;
	}
	else {
		tmp3->next->prev = tmp3->prev;
		tmp3->prev->next = tmp3->next;
		delete tmp3;
	}
}

