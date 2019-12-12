#include "Graphics.h"
using namespace GameEngine;

Graphics::Graphics() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		this->running = true;
	} 
}

Graphics::~Graphics() {
	if (this->window != nullptr) {
		SDL_DestroyWindow(this->window);
	}

	if (this->renderer != nullptr) {
		SDL_DestroyRenderer(this->renderer);
	}

	SDL_Quit();
}

void Graphics::CreateWindow(const char* title, int width, int height, bool fullscreen) {
	if (this->running) {
		int flags = SDL_WINDOW_SHOWN;

		if (fullscreen) {
			flags = flags | SDL_WINDOW_FULLSCREEN;
		}

		this->window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			flags
		);

		this->renderer = SDL_CreateRenderer(
			this->window,
			-1,
			SDL_RENDERER_ACCELERATED
		);
	}
}

void Graphics::SetBackgroundSolid(Color& color) {
	if (this->running) {
		SDL_SetRenderDrawColor(
			this->renderer,
			color.red,
			color.green,
			color.blue,
			color.alpha
		);

		SDL_RenderClear(this->renderer);
	}
}

void Graphics::DrawRectangle(SDL_Rect& rectangle, Color& color) {
	if (this->running) {
		SDL_SetRenderDrawColor(
			this->renderer,
			color.red,
			color.green,
			color.blue,
			color.alpha
		);

		SDL_RenderFillRect(this->renderer, &rectangle);
	}
}

void Graphics::Render() {
	if (this->running) {
		SDL_RenderPresent(this->renderer);
	}
}
