#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Game.h"
#include "Gui.h"

using namespace sf;

Game Game::game;

void Game::GameLoop() {
	Gui& gui = Gui::getInstance();
	currentPageEnum& currentPage = gui.getCurrentPage();

	// Create a window
	RenderWindow window(VideoMode({1200, 800}), "Catch Me If You Can");
	window.setFramerateLimit(60);

	// Initialize ImGui-SFML
	ImGui::SFML::Init(window);

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
			gui.EasyModePage(window);
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
}
