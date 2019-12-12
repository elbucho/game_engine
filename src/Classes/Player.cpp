#include "Player.h"
using namespace GameEngine;

const float PLAYER_HEIGHT = 10;
const float PLAYER_WIDTH = 10;

Player::Player(
	Graphics* graphics, 
	Input* input,
	float startX, 
	float startY
) {
	this->graphics = graphics;
	this->input = input;
	this->x = startX;
	this->y = startY;
}

void Player::MoveX(int delta) {
	this->x += delta; 
}

void Player::MoveY(int delta) {
	this->y += delta;
}

void Player::HandleInput() {
	if (this->input->WasKeyPressed(SDLK_d) || this->input->WasKeyPressed(SDLK_RIGHT)) {
		this->x += 1.0f;

		printf("x,y => %f,%f\n", this->x, this->y);
	}

	if (this->input->WasKeyPressed(SDLK_a) || this->input->WasKeyPressed(SDLK_LEFT)) {
		this->x -= 1.0f;

		printf("x,y => %f,%f\n", this->x, this->y);
	}

	if (this->input->WasKeyPressed(SDLK_w) || this->input->WasKeyPressed(SDLK_UP)) {
		this->y -= 1.0f;

		printf("x,y => %f,%f\n", this->x, this->y);
	}

	if (this->input->WasKeyPressed(SDLK_s) || this->input->WasKeyPressed(SDLK_DOWN)) {
		this->y += 1.0f;

		printf("x,y => %f,%f\n", this->x, this->y);
	}
}

void Player::Update() {
	// Draw the player
	Color playerColor;
	playerColor.red = 0;
	playerColor.green = 255;
	playerColor.blue = 0;
	playerColor.alpha = 255;

	int playerX, playerY;

	playerX = this->x - (PLAYER_WIDTH / 2);
	playerX = playerX < 0 ? 0 : playerX;

	playerY = this->y - (PLAYER_HEIGHT / 2);
	playerY = playerY < 0 ? 0 : playerY;

	SDL_Rect playerPosition;
	playerPosition.x = playerX;
	playerPosition.y = playerY;
	playerPosition.h = PLAYER_HEIGHT;
	playerPosition.w = PLAYER_WIDTH;

	this->graphics->DrawRectangle(playerPosition, playerColor);
}