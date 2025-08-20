#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Mole.h"
#include "Player.h"

void Mole::setState(bool s) {
	state = s;
};

bool Mole::getState() const {
	return state;
};

void Mole::show(const sf::Time& now) {
	state = true;
	appearTime = now;
}

void Mole::hide() {
	state = false;
};

void Mole::getHit() {
	if (state) {
		Player::getInstance().addScore(1);
		Player::getInstance().clickCount++;
		Player::getInstance().hitCount++;
	}
	else {
		if (Player::getInstance().getScore() >= 1) {
			Player::getInstance().subtractScore(1);
		}
		Player::getInstance().clickCount++;
	}
	state = false;
};

void Mole::update(const sf::Time& now, sf::Time duration) {
	if (state && now - appearTime > duration) {
		hide();
	}
}