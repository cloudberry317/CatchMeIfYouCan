#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Game.h"
#include "Gui.h"
#include "GameConfig.h"
#include "Player.h"

using namespace sf;

Game Game::game;

void Game::MainLoop() {
	Gui& gui = Gui::getInstance();
	currentPageEnum& currentPage = gui.getCurrentPage();

	// Create a window
	RenderWindow window(VideoMode({ 1200, 800 }), "Catch Me If You Can");
	window.setFramerateLimit(60);

	// Initialize ImGui-SFML
	ImGui::SFML::Init(window);

	Music bgm;

	if (!bgm.openFromFile("CatchMeIfYouCan/assets/bgm.mp3")) {
		std::cout << "Can't load the music file" << std::endl;
	}

	bgm.setVolume(50.0f);
	bgm.setLooping(true);
	bgm.play();

	//declare a font for button of MainPage
	ImGuiIO& io = ImGui::GetIO();
	ImFont* buttonFont = io.Fonts->AddFontFromFileTTF(
		"CatchMeIfYouCan/assets/bruce-forever/Bruce Forever.ttf",
		30.0f,
		nullptr,
		io.Fonts->GetGlyphRangesDefault()
	);
	ImGui::SFML::UpdateFontTexture();

	// ImGui Clock
	Clock deltaClock;

	// Set the initial page
	currentPage = MainMenu;

	srand(static_cast<unsigned>(time(0)));

	// Reset every mode for the first time
	game.resetGame("Easy");

	// Main loop
	while (window.isOpen()) {
		window.clear(Color::Color(0, 0, 0));
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<Event::Closed>())
				window.close();
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		if (currentPage == MainMenu) {
			gui.MainMenuPage(window, buttonFont);
		}
		else if (currentPage == EasyMode) {
			gui.EasyModePage(window, buttonFont);
		}
		else if (currentPage == MediumMode) {
			gui.MediumModePage(window);
		}
		else if (currentPage == HardMode) {
			gui.HardModePage(window);
		}
		else if (currentPage == CustomMode) {
			gui.CustomModePage(window);
		}
	}
	ImGui::SFML::Shutdown();
};

void Game::resetGame(std::string mode) {
	Gui& gui = Gui::getInstance();
	GameConfig& gameConfig = GameConfig::getInstance();
	Player& player = Player::getInstance();

	gui.gameClock.restart();
	gui.moleSpawnClock.restart();
	player.resetScore();

	gameConfig.loadConfig(mode);
	gui.holeCount = gameConfig.holeCount;
	gui.maxVisibleMoles = gameConfig.maxVisibleMoles;
	gui.moleAppearInterval = gameConfig.moleAppearInterval;
	gui.moleVisibleDuration = gameConfig.moleVisibleDuration;
	gui.intervalIncrement = gameConfig.intervalIncrement;
	gui.maxInterval = gameConfig.maxInterval;
	gui.totalGameTime = gameConfig.totalGameTime;

	gui.newMolePos = -1;
	gui.currentMolesCount = 0;
	gui.totalMoles = 0;

	gui.moles.resize(gui.holeCount);
	for (Mole& mole : gui.moles) {
		mole.setState(false);
	}

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	gui.holesPos.clear();
	if (mode == "Easy") {
		ImVec2 holePos = ImVec2(center.x - 450, center.y - 200);
		gui.holesPos.push_back(ImVec2(holePos.x, holePos.y));
		gui.holesPos.push_back(ImVec2(holePos.x + 360, holePos.y));
		gui.holesPos.push_back(ImVec2(holePos.x + 180, holePos.y + 180));
		gui.holesPos.push_back(ImVec2(holePos.x, holePos.y + 360));
		gui.holesPos.push_back(ImVec2(holePos.x + 360, holePos.y + 360));
	}
};
