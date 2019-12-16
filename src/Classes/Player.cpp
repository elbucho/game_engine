#include "Player.h"
#include <math.h>
#include <stdio.h>
using namespace GameEngine;

const float PLAYER_HEIGHT = 10;
const float PLAYER_WIDTH = 10;

const float GROUND_SPEED_MIN = 4.0f;	// Speed on the ground when a direction key is initially held down
const float GROUND_SPEED_MAX = 12.0f;	// Maximum ground speed
const float GROUND_SPEED_LAG = 0.5f;	// Amount of time holding the direction key down in seconds
										// before the ground speed reaches maximum velocity

const float GRAVITY_MIN = 1.0f;			// Initial falling speed when not on ground
const float GRAVITY_MAX = 8.0f;			// Maximum falling speed when not on the ground
const float GRAVITY_SPEED_LAG = 0.75f;	// Amount of time it takes in seconds to reach maximum falling speed

void Player::MoveX(Direction direction, float elapsedTime) {
	if (direction != Direction::LEFT && direction != Direction::RIGHT) {
		return;
	}

	int multiplier = (direction == Direction::LEFT) ? -1 : 1;

	/**
	 * Using a sin wave to generate an asymptotic curve representing player movement
	 * as they approach GROUND_SPEED_MAX.  Since I only want to represent the first quarter
	 * of the sin wave from 0 -> 1, I'm dividing or multiplying by 90.0f (π/4).  This will
	 * give me my percentage of movement speed of the GROUND_SPEED_MAX.  I am capping
	 * movement speed at GROUND_SPEED_MAX, and setting a floor at GROUND_SPEED_MIN.
	 */

	if (abs(this->velocityX) < GROUND_SPEED_MIN) {
		this->velocityX = GROUND_SPEED_MIN * multiplier;
	}
	else if (abs(this->velocityX) >= GROUND_SPEED_MAX) {
		this->velocityX = GROUND_SPEED_MAX * multiplier;
	}
	else {
		// Find out how long the movement button has been held so far
		double velocityPct = abs(this->velocityX) / (GROUND_SPEED_MAX - GROUND_SPEED_MIN);
		double totalElapsedTime = (asin(velocityPct) / 90.0f) * GROUND_SPEED_LAG;
		elapsedTime += totalElapsedTime;

		if (elapsedTime >= GROUND_SPEED_LAG) {
			// We have been holding the key down as long or longer than GROUND_SPEED_LAG
			this->velocityX = GROUND_SPEED_MAX * multiplier;
		}
		else {
			// Convert the new elapsed time to velocity
			double elapsedTimePct = ((double) elapsedTime / GROUND_SPEED_LAG) * 90.0f;
			double newVelocity = sin(elapsedTimePct) * ((double) GROUND_SPEED_MAX - GROUND_SPEED_MIN);
			this->velocityX = newVelocity * multiplier;
		}
	}

	this->x += this->velocityX;
}

void Player::MoveY(Direction direction, float elapsedTime) {
	if (direction != Direction::UP && direction != Direction::DOWN) {
		return;
	}

	int multiplier = (direction == Direction::UP) ? -1 : 1;

	/**
	 * Using a sin wave to generate an asymptotic curve representing player movement
	 * as they approach GROUND_SPEED_MAX.  Since I only want to represent the first quarter
	 * of the sin wave from 0 -> 1, I'm dividing or multiplying by 90.0f (π/4).  This will
	 * give me my percentage of movement speed of the GROUND_SPEED_MAX.  I am capping
	 * movement speed at GROUND_SPEED_MAX, and setting a floor at GROUND_SPEED_MIN.
	 */

	if (abs(this->velocityY) < GROUND_SPEED_MIN) {
		this->velocityY = GROUND_SPEED_MIN * multiplier;
	}
	else if (abs(this->velocityY) >= GROUND_SPEED_MAX) {
		this->velocityY = GROUND_SPEED_MAX * multiplier;
	}
	else {
		// Find out how long the movement button has been held so far
		double velocityPct = abs(this->velocityY) / (GROUND_SPEED_MAX - GROUND_SPEED_MIN);
		double totalElapsedTime = (asin(velocityPct) / 90.0f) * GROUND_SPEED_LAG;
		elapsedTime += totalElapsedTime;

		if (elapsedTime >= GROUND_SPEED_LAG) {
			// We have been holding the key down as long or longer than GROUND_SPEED_LAG
			this->velocityY = GROUND_SPEED_MAX * multiplier;
		}
		else {
			// Convert the new elapsed time to velocity
			double elapsedTimePct = ((double) elapsedTime / GROUND_SPEED_LAG) * 90.0f;
			double newVelocity = sin(elapsedTimePct) * ((double) GROUND_SPEED_MAX - GROUND_SPEED_MIN);
			this->velocityY = newVelocity * multiplier;
		}
	}

	this->y += this->velocityY;
}

void Player::Update(float elapsedTime) {
	if (this->input->IsKeyHeld(SDLK_d) || this->input->IsKeyHeld(SDLK_RIGHT)) {
		this->MoveX(Direction::RIGHT, elapsedTime);
	}

	if (this->input->IsKeyHeld(SDLK_a) || this->input->IsKeyHeld(SDLK_LEFT)) {
		this->MoveX(Direction::LEFT, elapsedTime);
	}

	if (this->input->IsKeyHeld(SDLK_w) || this->input->IsKeyHeld(SDLK_UP)) {
		this->MoveY(Direction::UP, elapsedTime);
	}

	if (this->input->IsKeyHeld(SDLK_s) || this->input->IsKeyHeld(SDLK_DOWN)) {
		this->MoveY(Direction::DOWN, elapsedTime);
	}
}

void Player::Draw() {
	// Draw the player
	Color playerColor;
	playerColor.red = 0;
	playerColor.green = 255;
	playerColor.blue = 0;
	playerColor.alpha = 255;

	float playerX, playerY;

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