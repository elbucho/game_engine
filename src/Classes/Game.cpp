#include "Game.h";
using namespace GameEngine;

Game::Game(const char* title, int width, int height) {
	this->graphics = new Graphics();

	if (this->graphics->isRunning()) {
		this->running = true;

		// Set background to a solid color - black
		Color bgColor;
		bgColor.red = 0;
		bgColor.green = 0;
		bgColor.blue = 0;
		bgColor.alpha = 255;

		this->graphics->CreateWindow(title, width, height);
		this->graphics->SetBackgroundSolid(bgColor);

		// Instantiate the Input class to capture user input
		this->input = new Input();

		// Draw the player
		this->player = new Player(this->graphics, this->input, width / 2, height / 2);

		this->GameLoop();
	}
}

Game::~Game() {
	this->graphics->~Graphics();
}

void Game::GameLoop() {
	SDL_Event event;

	while (this->running) {
		float elapsedTime = 0.0f;
		float currentTime = SDL_GetTicks() / 1000;

		while (SDL_PollEvent(&event)) {
			this->input->HandleEvent(event);

			// Handle input related to the game
			this->HandleInput();

			if (!this->running) {
				break;
			}

			// Handle input related to the player
			this->player->HandleInput();
		}

		this->input->FlushKeys();
		elapsedTime = (SDL_GetTicks() / 1000) - currentTime;

		this->Update(elapsedTime);
		this->Draw();
	}
}

void Game::Draw() {
	this->graphics->Render();
}

void Game::Update(float elapsedTime) {
	this->player->Update();
}

void Game::HandleInput()
{
	if (!this->input->IsGameRunning) {
		this->running = false;

		return;
	}
}