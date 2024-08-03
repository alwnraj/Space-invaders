#include "game.h"
#include <iostream>

Game::Game() {

	InitGame();
}

Game::~Game() {
	Alien::UnloadImages(); 
}

void Game::Update() {

	if (run) { //basically checks if the game is running. If we run out lives, the game freezes

		double currentTime = GetTime();
		if (currentTime - time_last_spawn > mysteryship_spawn_interval) {
			mysteryship.Spawn();
			time_last_spawn = GetTime();
			mysteryship_spawn_interval = GetRandomValue(10, 20);
		}

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

		mysteryship.Update();

		Check_Collisions();
	}

	else
	{
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	}

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

	mysteryship.Draw();
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
	float gap = (GetScreenWidth() - (4 * Obstaclewidth))/2.8; //Here, we have 4 obstacles and there are 5 gaps
	
	for (int i = 0; i < 4; i++) {
		float OffsetX = (i * 0.8) * gap + i * Obstaclewidth + 35; //Places the obstacles in the right place
		obstacles.push_back(Obstacle({ OffsetX, float(GetScreenHeight() - 200) })); //adds the Obstacle object into the obstacles vector
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

void Game::Check_Collisions()
{
	//Spaceship lasers
	for (auto& laser : spaceship.lasers) {
		auto it = aliens.begin(); //iterator to point towards the beginning of the aliens vector
		while (it != aliens.end()) {
			if (CheckCollisionRecs(it->getRect(), laser.getRect())) //The CheckCollisionRecs, a built-in function in raylib, checks if there is a collision between two rectangles
			{
				it = aliens.erase(it); // removes the alien in the iterator and points to the next alien in the vector
				laser.active = false;

				if (it->type == 1) // if the spaceship laser hits alien of type 1 user gets 10 points, etc. etc.
				{
					score += 10;
				}
				else if (it->type == 2)
				{
					score += 20;
				}
				else if (it->type == 3) {

					score += 30;
				}
			}
			else {
				++it; //if there was no collision the iterator moves to the next item in the vector
			}
		}

		// Checks the collisions for the four obstacles
		for (auto& obstacle : obstacles) {  
			auto it = obstacle.blocks.begin();
			while ( it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) { 
					it = obstacle.blocks.erase(it);// As soon as the laser hits the block, the block get removed from the vector
					laser.active = false; // After hitting the block the laser becomes inactive and dissapears
				}
				else
				{
					++it;
				}
			}
		}
		//Checks collisions with Mystery alien ship
		if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
			mysteryship.alive = false;
			laser.active = false;
			score += 50;
		}
	}

	// Alien Lasers

	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
			//std::cout<<"Spaceship hit!"<< std::endl;
			laser.active = false;
			Lives += -1;
			if (Lives == 0) {
				GameOver();
			}
		}

		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
					it = obstacle.blocks.erase(it);// As soon as the laser hits the block, the block get removed from the vector
					laser.active = false; // After hitting the block the laser becomes inactive and dissapears
				}
				else
				{
					++it;
				}
			}
		}
	}

	//Aliens colliding with the obstacle blocks
	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end()) {
				if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
					it = obstacle.blocks.erase(it); //This obstacles basically get wiped out block-by-block
				}
				else
				{
					++it;
				}
			}
		}
		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
			//std::cout << "Spaceship got hit by Alien ship!" << std::endl;
			GameOver();
		}
	}
}

void Game::GameOver()
{
	//std::cout << "Game over!" << std::endl;
	run = false;
}

void Game::InitGame()
{
	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliendirection = 1;
	TimelastAlienFired = 0;
	mysteryship.Spawn();
	time_last_spawn = 0.0;
	mysteryship_spawn_interval = GetRandomValue(10, 20);
	Lives = 3;
	run = true;
	score = 0;

}

void Game::MoveAliens() {
	for (auto& alien : aliens) {

		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
			aliendirection = - 1;
			MoveDownAliens(4);
		}
		if (alien.position.x < 25) {
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

void Game::Reset() {	//Resets the game
	spaceship.Reset();
	alienLasers.clear();
	obstacles.clear();
	aliens.clear();
}