#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

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
	Clock moleTimer;
	int currentMolePosition = 0; // 當前地鼠位置 (0表示沒有地鼠)
	int lastMolePosition = 0;
public:
	Gui() : currentPage(MainMenu) {
		texCursor.loadFromFile("CatchMeIfYouCan/assets/hammer.png");
		texLogo.loadFromFile("CatchMeIfYouCan/assets/logo-removebg.png");
		texMole.loadFromFile("CatchMeIfYouCan/assets/mole.jpg");
		texHole.loadFromFile("CatchMeIfYouCan/assets/hole.jpg");
	};
	~Gui() {};

	static Gui& getInstance() {
		return gui;
	};

	currentPageEnum& getCurrentPage() {
		return currentPage;
	};

	void MainMenuPage(RenderWindow& window, ImFont* font);
	void EasyModePage(RenderWindow& window);
	void MediumModePage(RenderWindow& window);
	void HardModePage(RenderWindow& window);
	void CustomModePage(RenderWindow& window);
};
