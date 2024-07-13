#pragma once
#include "raylib.h"

class Alien
{
public:
	Alien(int type, Vector2 position);
	void Update();
	void Draw();
	Texture2D image;
	int type;
	Vector2 position;

private:

};

