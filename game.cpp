#include "game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {
}

void Game::Update() {
	for (auto& laser : spaceship.lasers) {
		laser.Update();
	}

	DeleteInactiveLasers(); // Calling the function defined below
	std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl;
}

void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
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
}
