#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();

private:
	Spaceship spaceship; 
	void DeleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	std::vector<Obstacle> obstacles;
	std::vector<Obstacle> CreateObstacles();
	std::vector<Alien> aliens;
	std::vector<Alien> CreateAliens();
	int aliendirection;
	std::vector<Laser>AlienshootLaser();
	std::vector<Laser> alienLasers;
};