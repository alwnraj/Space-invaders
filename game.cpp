#include "game.h"
#include <iostream>

Game::Game() {
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliendirection = 1;
	TimelastAlienFired = 0;
}

Game::~Game() {
	Alien::UnloadImages(); 
}

void Game::Update() {
	for (auto& laser : spaceship.lasers) {
		laser.Update();
	}

	MoveAliens();


	AlienshootLaser();

	for (auto& laser : alienLasers) {
		laser.Update();
	}


	DeleteInactiveLasers(); // Calling the function defined below
	//std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl; 
	/*Vector size increases as we fire lasers but when they move outside the screen they get killed off and the size goes to zero*/
}

void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& aliens : aliens) { // Draws the purple aliens
		aliens.Draw();
	}

	for (auto& laser : alienLasers) {
		laser.Draw();
	}
}


void Game::HandleInput() {
	if (IsKeyDown(KEY_LEFT)) {
		spaceship.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		spaceship.MoveRight();
	}
	else if (IsKeyDown(KEY_DOWN)) {
		spaceship.FireLaser();
	}
}

void Game::DeleteInactiveLasers()
{
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) { //Created an 'it' vector and an iterator to go through it.
		if (!it->active) {						//The iterator go through and sees if any of the lasers are active or not.  
			it = spaceship.lasers.erase(it); //If is any inactive lasers, it gets removed
		}
		else { // if the element is active, iterator moves to the next element
			++it;
		}
	}

	for (auto it = alienLasers.begin(); it != alienLasers.end();) { //Created an 'it' vector and an iterator to go through it.
		if (!it->active) {						//The iterator go through and sees if any of the lasers are active or not.  
			it = alienLasers.erase(it); //If is any inactive lasers, it gets removed
		}
		else { // if the element is active, iterator moves to the next element
			++it;
		}
	}
}

std::vector<Obstacle> Game::CreateObstacles()
{
	int Obstaclewidth = Obstacle::grid[0].size() * 3; //i.e the grid has grid[0].size() no. of coluomns.
	float gap = (GetScreenWidth() - (4 * Obstaclewidth))/3; //Here, we have 4 obstacles and there are 5 gaps
	
	for (int i = 0; i < 4; i++) {
		float OffsetX = (i * 1) * gap + i * Obstaclewidth; //Places the obstacles in the right place
		obstacles.push_back(Obstacle({ OffsetX, float(GetScreenHeight() - 100) })); //adds the Obstacle object into the obstacles vector
	}

	return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {

			int alienType;
			if (row == 0) {
				alienType = 3;
			}
			else if (row==1 || row== 2)
			{
				alienType = 2;
			}
			else
			{
				alienType = 1;
			}


			float x = 75+ column * 55; // 55 acts as the cellsize of the alien
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, {x,y}));
		}
	}
	return aliens;
}

void Game::AlienshootLaser()
{
	double currentTime = GetTime();
	if (currentTime - TimelastAlienFired >= alienLaserShootInterval && !aliens.empty()) 
	{
		int randomindex = GetRandomValue(0, aliens.size() - 1);//creates random no. to index for the aliens
		Alien& alien = aliens[randomindex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));// Needs more clarification?

		TimelastAlienFired = GetTime();

	}


}

void Game::MoveAliens() {
	for (auto& alien : aliens) {

		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()) {
			aliendirection = - 1;
			MoveDownAliens(4);
		}
		if (alien.position.x < 0) {
			aliendirection = 1;
			MoveDownAliens(4);
		}

		alien.Update(aliendirection);
	}
}

void Game::MoveDownAliens(int distance)
{
	for(auto& alien:aliens)
	{
		alien.position.y += distance;
	}
}
