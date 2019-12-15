#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "SDL.h"
#include "Structs/Color.h"

namespace GameEngine {
	class Graphics {
	public:
		Graphics();
		~Graphics();
		void CreateWindow(const char* title, int width, int height, bool fullscreen = false);
		void SetBackgroundSolid(Color &color);
		void DrawRectangle(SDL_Rect &rectangle, Color &color);
		void Render();

		bool IsRunning() { return this->running; }
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		bool running = false;
	};
}

#endif