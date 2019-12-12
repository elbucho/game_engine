#ifndef PLAYER_H_
#define PLAYER_H_

#include "Graphics.h"
#include "Structs/Color.h"

namespace GameEngine {
	class Player {
	public:
		Player(Graphics* graphics, int startX, int startY);
		~Player() {};

		void MoveX(int delta);
		void MoveY(int delta);
	private:
		Graphics* graphics;
		int x, y;
	};
}

#endif