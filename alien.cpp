#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
	this->type = type;
	this->position = position;

	if (alienImages[type - 1].id == 0) { //Used the type of an alien as images. This basically allows us to load the images just once improving performance 
		switch (type) {
		case 1:
			alienImages[0] = LoadTexture("alien_1.png");
			break;
		case 2:
			alienImages[1] = LoadTexture("alien_2.png");
			break;
		case 3:
			alienImages[2] = LoadTexture("alien_3.png");
			break;
		default:
			alienImages[0] = LoadTexture("alien_1.png");
			break;

		}
	}

}

void Alien::Draw() {
	DrawTextureV(alienImages[type-1], position, WHITE); //Draws the aliens
}

int Alien::GetType() {
	return type;
}

void Alien::UnloadImages()
{
	for (int i = 0; i < 4; i++) {
		UnloadTexture(alienImages[i]);
	}
}
