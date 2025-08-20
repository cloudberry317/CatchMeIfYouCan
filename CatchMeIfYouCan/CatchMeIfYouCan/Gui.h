#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include "Mole.h"

using namespace sf;

enum currentPageEnum {
	MainMenu,
	EasyMode,
	MediumMode,
	HardMode,
	CustomMode
};

class Gui {
private:
	static Gui gui;
	currentPageEnum currentPage;
	Texture texCursor;
	Texture texLogo;
	Texture texMole;
	Texture texHole;
	//for MainMenuPage
	Clock moleTimer;
	int currentMolePosition = 0; 
	int lastMolePosition = 0;
public:
	int holeCount;
	int maxVisibleMoles;
	float moleAppearInterval;
	float moleVisibleDuration;
	float intervalIncrement;
	float maxInterval;
	float totalGameTime;

	Clock gameClock;
	Clock moleSpawnClock;
	float elapsedTime = 0.0f;

	int newMolePos;
	int currentMolesCount;
	int totalMoles;
	std::vector<Mole> moles;
	std::vector<ImVec2> holesPos;

	Gui() : currentPage(MainMenu) {
		texCursor.loadFromFile("CatchMeIfYouCan/assets/hammer.png");
		texLogo.loadFromFile("CatchMeIfYouCan/assets/logo.png");
		texMole.loadFromFile("CatchMeIfYouCan/assets/mole.png");
		texHole.loadFromFile("CatchMeIfYouCan/assets/hole.png");
		gameClock.stop();
		moleSpawnClock.stop();
	};
	~Gui() {};

	static Gui& getInstance() {
		return gui;
	};

	currentPageEnum& getCurrentPage() {
		return currentPage;
	};

	void MainMenuPage(RenderWindow& window, ImFont* buttonFont);
	void EasyModePage(RenderWindow& window, ImFont* buttonFont);
	void MediumModePage(RenderWindow& window);
	void HardModePage(RenderWindow& window);
	void CustomModePage(RenderWindow& window);
};
