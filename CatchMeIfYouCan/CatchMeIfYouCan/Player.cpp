#include "Player.h"

Player Player::player;

void Player::addScore(int points) {
	score += points;
};

void Player::subtractScore(int points) {
	score -= points;
};

void Player::resetScore() {
	score = 0;
	hitCount = 0;
	clickCount = 0;
};

int Player::getScore() const {
	return score;
};