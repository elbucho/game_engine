#include "Input.h"

using namespace GameEngine;

Input::Input() {

}

Input::~Input() {

}

void Input::HandleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT) {
		this->IsGameRunning = false;

		return;
	}

	if (event.type == SDL_KEYDOWN) {
		this->pressedKeys[event.key.keysym.sym] = true;
		this->heldKeys[event.key.keysym.sym] = true;
	}

	if (event.type == SDL_KEYUP) {
		this->releasedKeys[event.key.keysym.sym] = true;
		this->heldKeys[event.key.keysym.sym] = false;
	}
}

void Input::FlushKeys() {
	for (const auto& keyPair : this->pressedKeys) {
		this->pressedKeys[keyPair.first] = false;
	}

	for (const auto& keyPair : this->releasedKeys) {
		this->releasedKeys[keyPair.first] = false;
	}
}

bool Input::WasKeyPressed(SDL_Keycode code) {
	if (this->pressedKeys.find(code) == this->pressedKeys.end()) {
		return false;
	}

	return this->pressedKeys[code];
}

bool Input::WasKeyReleased(SDL_Keycode code) {
	if (this->releasedKeys.find(code) == this->releasedKeys.end()) {
		return false;
	}

	return this->releasedKeys[code];
}

bool Input::IsKeyHeld(SDL_Keycode code) {
	if (this->heldKeys.find(code) == this->heldKeys.end()) {
		return false;
	}

	return this->heldKeys[code];
}
