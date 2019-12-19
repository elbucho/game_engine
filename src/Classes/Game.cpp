#include "Game.h"
#include <string>
#include <stdio.h>
#include <chrono>

using namespace GameEngine;

Game::Game(const char* title, int width, int height) {
	this->graphics = new Graphics();

	if (this->graphics->IsRunning()) {
		this->running = true;

		this->graphics->CreateWindow(title, width, height);

		// Instantiate the Input class to capture user input
		this->input = new Input();
	}
}

Game::~Game() {
	this->graphics->~Graphics();
}

void Game::Start() {
	SDL_Event event;
	std::chrono::high_resolution_clock::time_point currentTime, newTime;
	std::chrono::duration<double> elapsedTime;

	if (this->level != nullptr) {
		this->running = true;
	}
	else {
		printf("Unable to load level\n");
	}

	this->Draw();
	currentTime = std::chrono::high_resolution_clock::now();

	while (this->running) {
		bool newEvents = false;

		while (SDL_PollEvent(&event)) {
			this->input->HandleEvent(event);

			// Handle input related to the game
			this->HandleInput();

			if (!this->running) {
				break;
			}

			if (this->input->IsKeyboardInput(event)) {
				newEvents = true;
			}
		}

		this->input->FlushKeys();
		newTime = std::chrono::high_resolution_clock::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime - currentTime);
		currentTime = newTime;

		if (newEvents) {
			printf("Game Elapsed Time: %f\n", elapsedTime.count());
			this->Update(elapsedTime.count());
			this->Draw();
		}
	}
}

void Game::Draw() {
	this->level->Draw();
	this->player->Draw();
	this->graphics->Render();
}

void Game::Update(float elapsedTime) {
	this->level->Update();
	this->player->Update(elapsedTime);
}

void Game::HandleInput()
{
	if (!this->input->IsGameRunning) {
		this->running = false;

		return;
	}
}

void Game::LoadLevel(const char* level) {
	std::string levelPath = "src/Levels/";
	levelPath += level;
	levelPath += ".xml";

	this->level = new Level(this->graphics, levelPath.c_str());

	if (!this->level->IsLoaded()) {
		this->level->~Level();
		this->level = nullptr;
		this->running = false;
	}
}

void Game::AddPlayer(Player* player, float playerX, float playerY) {
	this->player = player;
	this->player->AddInput(this->input);
	this->player->AddGraphicsEngine(this->graphics);
	this->player->SetPosition(playerX, playerY);
}