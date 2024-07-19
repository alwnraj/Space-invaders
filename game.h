#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"

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
	void AlienshootLaser();
	std::vector<Laser> alienLasers; 
	constexpr static float alienLaserShootInterval = 0.35; // constexpr stands for constant expression
	float TimelastAlienFired;
	Mysteryship mysteryship;
	float mysteryship_spawn_interval;
	float time_last_spawn;
	void Check_Collisions();
};