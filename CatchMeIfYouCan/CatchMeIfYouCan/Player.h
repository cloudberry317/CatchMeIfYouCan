#pragma once

class Player {
private:
	static Player player;
	int score;
public:
	int clickCount;
	int hitCount;
	float accuracy;

	Player() : score(0), clickCount(0), hitCount(0){};
	~Player() {};

	static Player& getInstance() {
		return player;
	}

	void addScore(int points);
	void subtractScore(int points);
	void resetScore();
	int getScore() const;
};
