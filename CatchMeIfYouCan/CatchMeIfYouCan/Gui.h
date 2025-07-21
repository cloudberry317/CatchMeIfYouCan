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
public:
	Gui() : currentPage(MainMenu) {};
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
