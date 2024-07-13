#include "alien.h"

Alien::Alien(int type, Vector2 position)
{
	this->type = type;
	this->position = position;

	switch (type) {
		case 1:
			image = LoadTexture("alien_1.png");
			break;
		case 2:
			image = LoadTexture("alien_2.png");
			break;
		case 3:
			image = LoadTexture("alien_3.png");
			break;
		default:
			image = LoadTexture("alien_1.png");
			break;
	}
}

void Alien::Draw() {
	DrawTextureV(image, position, WHITE); //Draws the aliens
}

int Alien::GetType() {
	return type;
}