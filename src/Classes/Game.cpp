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

		// Draw the player
		this->player = new Player(this->graphics, width / 2, height / 2);

		this->GameLoop();
	}
}

Game::~Game() {
	this->graphics->~Graphics();
}

void Game::GameLoop() {
	SDL_Event event;

	while (this->running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				this->running = false;

				return;
			}
		}
	}
}

void Game::Draw() {

}

void Game::Update(float elapsedTime) {

}