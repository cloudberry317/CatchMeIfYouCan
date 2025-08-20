#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

using namespace sf;

class Game {
private:
	static Game game;
public:
	bool ifGaming;

	Game() : ifGaming(false) {};
	~Game() {};

	static Game& getInstance() {
		return game;
	};

	void MainLoop();

	void resetGame(std::string mode);
};
