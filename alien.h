#pragma once
#include "raylib.h"

class Alien
{
public:
	Alien(int type, Vector2 position);
	void Update();
	void Draw();
	int GetType();
	//Texture2D image;
	static Texture2D alienImages[3];// Going to store the three alien images in this array
	static void UnloadImages();
	int type;
	Vector2 position;

private:

};

