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

const float QUARTER_PI_RAD = 1.5708f;	// 90 degrees expressed in radians (sin / asin, etc only work with rad)

void Player::MoveX(Direction direction) {
	if (direction != Direction::LEFT && direction != Direction::RIGHT) {
		return;
	}

	float multiplier = (direction == Direction::LEFT) ? -1.0f : 1.0f;

	/**
	 * Using a sin wave to generate an asymptotic curve representing player movement
	 * as they approach GROUND_SPEED_MAX.  Since I only want to represent the first quarter
	 * of the sin wave from 0 -> 1, I'm dividing or multiplying by 90.0f (π/4).  This will
	 * give me my percentage of movement speed of the GROUND_SPEED_MAX.  I am capping
	 * movement speed at GROUND_SPEED_MAX, and setting a floor at GROUND_SPEED_MIN.
	 */

	double elapsedTime = this->elapsedHoldTime[direction];

	printf("Current Elapsed Time for %d: %f\n", direction, elapsedTime);

	double elapsedPct = elapsedTime == 0.0f ? 0.0f : (abs(elapsedTime) / GROUND_SPEED_LAG);
	double velocity = elapsedTime >= 1.0f ? 
		GROUND_SPEED_MAX : 
		sin(elapsedPct * QUARTER_PI_RAD) * GROUND_SPEED_MAX;

	velocity = velocity < GROUND_SPEED_MIN ? GROUND_SPEED_MIN : velocity;

	this->velocityX = velocity * multiplier;
	this->x += this->velocityX;

	printf("Current X velocity: %f\n", this->velocityX);
}

void Player::MoveY(Direction direction) {
	if (direction != Direction::UP && direction != Direction::DOWN) {
		return;
	}

	float multiplier = (direction == Direction::UP) ? -1.0f : 1.0f;

	/**
	 * Using a sin wave to generate an asymptotic curve representing player movement
	 * as they approach GROUND_SPEED_MAX.  Since I only want to represent the first quarter
	 * of the sin wave from 0 -> 1, I'm dividing or multiplying by 90.0f (π/4).  This will
	 * give me my percentage of movement speed of the GROUND_SPEED_MAX.  I am capping
	 * movement speed at GROUND_SPEED_MAX, and setting a floor at GROUND_SPEED_MIN.
	 */

	double elapsedTime = this->elapsedHoldTime[direction];

	printf("Current Elapsed Time for %d: %f\n", direction, elapsedTime);

	double elapsedPct = elapsedTime == 0.0f ? 0.0f : (abs(elapsedTime) / GROUND_SPEED_LAG);
	double velocity = elapsedTime >= 1.0f ?
		GROUND_SPEED_MAX :
		sin(elapsedPct * QUARTER_PI_RAD) * GROUND_SPEED_MAX;

	velocity = velocity < GROUND_SPEED_MIN ? GROUND_SPEED_MIN : velocity;

	this->velocityY = velocity * multiplier;
	this->y += this->velocityY;

	printf("Current Y velocity: %f\n", this->velocityY);
}

void Player::Update(double elapsedTime) {
	if (this->input->IsKeyHeld(SDLK_d) || this->input->IsKeyHeld(SDLK_RIGHT)) {
		this->elapsedHoldTime[Direction::RIGHT] += elapsedTime;
		this->MoveX(Direction::RIGHT);
	}
	else {
		this->elapsedHoldTime[Direction::RIGHT] = 0.0f;
	}

	if (this->input->IsKeyHeld(SDLK_a) || this->input->IsKeyHeld(SDLK_LEFT)) {
		this->elapsedHoldTime[Direction::LEFT] += elapsedTime;
		this->MoveX(Direction::LEFT);
	}
	else {
		this->elapsedHoldTime[Direction::LEFT] = 0.0f;
	}

	if (this->input->IsKeyHeld(SDLK_w) || this->input->IsKeyHeld(SDLK_UP)) {
		this->elapsedHoldTime[Direction::UP] += elapsedTime;
		this->MoveY(Direction::UP);
	}
	else {
		this->elapsedHoldTime[Direction::UP] = 0.0f;
	}

	if (this->input->IsKeyHeld(SDLK_s) || this->input->IsKeyHeld(SDLK_DOWN)) {
		this->elapsedHoldTime[Direction::DOWN] += elapsedTime;
		this->MoveY(Direction::DOWN);
	}
	else {
		this->elapsedHoldTime[Direction::DOWN] = 0.0f;
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