#include "mysteryship.h"

Mysteryship::Mysteryship()
{
	image = LoadTexture("mystery_ship.png");
	alive = false;
}

Mysteryship::~Mysteryship() { // Destructor to unload the image when shipis destroyed
	UnloadTexture(image);
}

void Mysteryship::Spawn() {
	position.y = 90;
	int side = GetRandomValue(0, 1); //the mystery ship will spawn randomly on either side of the screen; left = 0 and right =1

	if (side == 0) {
		position.x = 0;
		speed = 3;
	}
	else
	{
		position.x = GetScreenWidth() - image.width;
		speed = -3;
	}
	alive = true;
}

Rectangle Mysteryship::getRect()
{
	if (alive) {
		return { position.x, position.y, float(image.width), float(image.height) };
	}
	else {
		return { position.x, position.y, 0, 0 };
	}
}

void Mysteryship::Update() {
	if (alive) {
		position.x += speed;
		if (position.x > GetScreenWidth() - image.width || position.x < 0) { //If the ship goes out of the frame, ship dies
			alive = false;
		}
	}
}

void Mysteryship::Draw() {
	if (alive) {
		DrawTextureV(image, position, WHITE);
	}
}