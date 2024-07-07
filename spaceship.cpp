#include "spaceship.h"
#include <iostream>

Spaceship::Spaceship() {
	image = LoadTexture("spaceship.png");
	position.x = GetScreenWidth()/2;
	position.y = GetScreenHeight()- image.width;
	lastFireTime = 0;
}
Spaceship::~Spaceship() {
	UnloadTexture(image);
 }

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
	position.x -= 7;
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::MoveRight() {
	position.x += 7;
	if (position.x > GetScreenWidth() - image.width) {
		position.x = GetScreenWidth() - image.width;
	}
}

void Spaceship::FireLaser() {
	if(GetTime() - lastFireTime >=0.35){ // makes sure that user can only shoot in short bursts!
		lasers.push_back(Laser({ position.x + image.width / 2 - 2 , position.y }, -6));
		lastFireTime = GetTime();
	}
}