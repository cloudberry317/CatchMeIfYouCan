#include "GameConfig.h"

using namespace std;

GameConfig GameConfig::gameConfig;

void GameConfig::loadConfig(string mode) {
	ifstream fs;
	fs.open("CatchMeIfYouCan/config.json");

	if (!fs.is_open()) {
		throw runtime_error("Failed to open config file");
	}
	try {
		fs >> configData;
		json gameSetting = configData[mode];
		holeCount = gameSetting["holeCount"].get<int>();
		maxVisibleMoles = gameSetting["maxVisibleMoles"].get<int>();
		moleAppearInterval = gameSetting["moleAppearInterval"].get<float>();
		moleVisibleDuration = gameSetting["moleVisibleDuration"].get<float>();
		intervalIncrement = gameSetting["intervalIncrement"].get<float>();
		maxInterval = gameSetting["maxInterval"].get<float>();
		totalGameTime = gameSetting["totalGameTime"].get<float>();
	}
	catch (const json::parse_error& e) {
		throw runtime_error("Failed to parse config file: " + string(e.what()));
	}
	catch (const json::type_error& e) {
		throw runtime_error("Failed to parse config file: " + string(e.what()));
	}
	catch (const std::exception& e) {
		throw runtime_error("Failed to parse config file: " + string(e.what()));
	}
	fs.close();
};
