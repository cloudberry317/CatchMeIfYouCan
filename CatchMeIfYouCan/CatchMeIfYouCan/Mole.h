#pragma once

class Mole {
private:
	bool state; // false : hidden, true : visible
	sf::Time appearTime;
public:
	Mole() : state(false) {};
	~Mole() {};

	void setState(bool s);
	bool getState() const;
	void show(const sf::Time& now);
	void hide();
	void getHit();
	void update(const sf::Time& now, sf::Time duration);
};
