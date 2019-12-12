#ifndef GAME_H_
#define GAME_H_

#include "Graphics.h"
#include "Player.h"
#include "Input.h"
#include <stdio.h>

namespace GameEngine {
	class Game {
	public:
		Game(const char* title, int width, int height);
		~Game();

		bool isRunning() { return this->running; }
	private:
		Graphics* graphics = nullptr;
		Player* player = nullptr;
		Input* input = nullptr;

		bool running = false;
		void GameLoop();
		void Draw();
		void Update(float elapsedTime);
		void HandleInput();
	};
}

#endif