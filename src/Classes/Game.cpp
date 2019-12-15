#include "Game.h"
#include <string>
#include <stdio.h>

using namespace GameEngine;

Game::Game(const char* title, int width, int height) {
	this->graphics = new Graphics();

	if (this->graphics->IsRunning()) {
		this->running = true;

		this->graphics->CreateWindow(title, width, height);

		// Instantiate the Input class to capture user input
		this->input = new Input();

		// Draw the player
		this->player = new Player(this->graphics, this->input, width / 2, height / 2);
	}
}

Game::~Game() {
	this->graphics->~Graphics();
}

void Game::Start() {
	SDL_Event event;

	if (this->level != nullptr) {
		this->running = true;
	}
	else {
		printf("Unable to load level\n");
	}

	while (this->running) {
		float elapsedTime = 0.0f;
		float currentTime = SDL_GetTicks() / 1000;
		bool newEvents = false;

		while (SDL_PollEvent(&event)) {
			this->input->HandleEvent(event);

			// Handle input related to the game
			this->HandleInput();

			if (!this->running) {
				break;
			}

			// Handle input related to the player
			this->player->HandleInput();
			newEvents = true;
		}

		this->input->FlushKeys();
		elapsedTime = (SDL_GetTicks() / 1000) - currentTime;

		if (newEvents) {
			this->Update(elapsedTime);
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
	this->player->Update();
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