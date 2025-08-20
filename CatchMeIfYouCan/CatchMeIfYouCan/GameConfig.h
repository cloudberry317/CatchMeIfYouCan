#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "json/json.hpp"

using json = nlohmann::json;
using namespace std;

class GameConfig {
private:
	static GameConfig gameConfig;
	json configData;
public:
	int holeCount;
	int maxVisibleMoles;
	float moleAppearInterval;
	float moleVisibleDuration;
	float intervalIncrement;
	float maxInterval;
	float totalGameTime;

	GameConfig() {};
	~GameConfig() {};

	static GameConfig& getInstance() {
		return gameConfig;
	};

	void loadConfig(string mode);
};
