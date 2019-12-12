#ifndef PLAYER_H_
#define PLAYER_H_

#include "Graphics.h"
#include "Input.h"
#include "Structs/Color.h"

namespace GameEngine {
	class Player {
	public:
		Player(Graphics* graphics, Input* input, float startX, float startY);
		~Player() {};

		void MoveX(int delta);
		void MoveY(int delta);
		void HandleInput();
		void Update();
	private:
		Graphics* graphics;
		Input* input;
		float x, y;
	};
}

#endif