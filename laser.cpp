#include "laser.h"
#include <iostream>

Laser::Laser(Vector2 position, int speed) {
	this->position = position;
	this->speed = speed;
	active = true;
}

void Laser::Draw() {
	if (active)
		DrawRectangle(position.x, position.y, 4,15, YELLOW);
}

Rectangle Laser::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}

void Laser::Update() {
	position.y += speed;
	if (active) {
		if (position.y > (GetScreenHeight() - 85 )|| position.y < 25) {
			active = false;
			//std::cout << "Laser Inactive" << std::endl; // Displays that laser is inactive when it goes out of frame
		}
	}

}