#ifndef PLAYER_H_
#define PLAYER_H_

#include "Graphics.h"
#include "Input.h"
#include "Structs/Color.h"

namespace GameEngine {
	class Player {
	public:
		enum class Direction {
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		Player() {};
		~Player() {};

		void AddInput(Input* input) { this->input = input; }
		void AddGraphicsEngine(Graphics* graphics) { this->graphics = graphics; }
		void SetPosition(float x, float y) { this->x = x; this->y = y; }

		void MoveX(Direction direction, float elapsedTime);
		void MoveY(Direction direction, float elapsedTime);
		void Update(float elapsedTime);
		void Draw();
	private:
		Graphics* graphics = nullptr;
		Input* input = nullptr;
		float x = 0.0f;
		float y = 0.0f;
		float velocityX = 0.0f;
		float velocityY = 0.0f;
	};
}

#endif