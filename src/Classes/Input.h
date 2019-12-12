#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include "SDL.h"

namespace GameEngine {
	class Input {
	public:
		Input();
		~Input();

		void HandleEvent(SDL_Event &event);
		void FlushKeys();

		bool WasKeyPressed(SDL_Keycode code);
		bool WasKeyReleased(SDL_Keycode code);
		bool IsKeyHeld(SDL_Keycode code);
		bool IsGameRunning = true;
	private:
		std::map<SDL_Keycode, bool> pressedKeys;
		std::map<SDL_Keycode, bool> releasedKeys;
		std::map<SDL_Keycode, bool> heldKeys;
	};
}

#endif