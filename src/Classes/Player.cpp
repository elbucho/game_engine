#include "Player.h"
using namespace GameEngine;

const int PLAYER_HEIGHT = 10;
const int PLAYER_WIDTH = 10;

Player::Player(Graphics* graphics, int startX, int startY) {
	this->graphics = graphics;
	this->x = startX;
	this->y = startY;

	// Draw the player
	Color playerColor;
	playerColor.red = 0;
	playerColor.green = 255;
	playerColor.blue = 0;
	playerColor.alpha = 255;

	int playerX, playerY;

	playerX = startX - (PLAYER_WIDTH / 2);
	playerX = playerX < 0 ? 0 : playerX;

	playerY = startY - (PLAYER_HEIGHT / 2);
	playerY = playerY < 0 ? 0 : playerY;

	SDL_Rect playerPosition;
	playerPosition.x = playerX;
	playerPosition.y = playerY;
	playerPosition.h = PLAYER_HEIGHT;
	playerPosition.w = PLAYER_WIDTH;

	this->graphics->DrawRectangle(playerPosition, playerColor);
	this->graphics->Render();
}

void Player::MoveX(int delta) {
	this->x += delta; 
	this->graphics->Render();
}

void Player::MoveY(int delta) {
	this->y += delta;
	this->graphics->Render();
}