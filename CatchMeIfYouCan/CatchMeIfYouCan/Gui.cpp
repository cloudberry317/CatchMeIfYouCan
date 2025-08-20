#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "GameConfig.h"
#include "Gui.h"
#include "Player.h"
#include "Mole.h"

using namespace sf;

Gui Gui::gui;

Font font("CatchMeIfYouCan/assets/supply-center/Supply Center.ttf");
unsigned int fontsize = 35;

void Gui::MainMenuPage(RenderWindow& window, ImFont* buttonFont) {
	window.clear(Color::Color(0, 0, 0));
	ImGui::Begin("Main Menu Page", nullptr,
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoBackground);

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetWindowSize(ImVec2(1200, 800));
	ImGui::SetWindowPos(ImVec2(center.x - 600, center.y - 400));

	// Design the cursor
	sf::Sprite cursor(texCursor);
	sf::Vector2u texSize = texCursor.getSize();
	cursor.setOrigin(ImVec2(texSize.x / 2, texSize.y / 2));
	window.setMouseCursorVisible(false);
	cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

	// Show the GameLogo
	ImTextureID imgLogo = texLogo.getNativeHandle();
	ImGui::SetCursorPos(ImVec2(center.x - 375, center.y - 330));
	ImGui::Image(imgLogo, ImVec2(750, 90));

	// Random mole design
	ImTextureID imgHole = texHole.getNativeHandle();
	ImGui::SetCursorPos(ImVec2(center.x - 560, center.y - 390));
	ImGui::Image(imgHole, ImVec2(150, 100));
	ImGui::SetCursorPos(ImVec2(center.x + 430, center.y - 390));
	ImGui::Image(imgHole, ImVec2(150, 100));
	ImGui::SetCursorPos(ImVec2(center.x + 430, center.y + 270));
	ImGui::Image(imgHole, ImVec2(150, 100));
	ImGui::SetCursorPos(ImVec2(center.x - 560, center.y + 270));
	ImGui::Image(imgHole, ImVec2(150, 100));

	if (moleTimer.getElapsedTime().asSeconds() >= 1.5f) {
		do {
			currentMolePosition = rand() % 4 + 1;
		} while (currentMolePosition == lastMolePosition);

		lastMolePosition = currentMolePosition;
		moleTimer.restart();
	}
	if (currentMolePosition > 0) {
		ImTextureID imgMole = texMole.getNativeHandle();
		switch (currentMolePosition) {
		case 1:
			ImGui::SetCursorPos(ImVec2(center.x - 560, center.y - 390));
			break;
		case 2:
			ImGui::SetCursorPos(ImVec2(center.x + 430, center.y - 390));
			break;
		case 3:
			ImGui::SetCursorPos(ImVec2(center.x + 430, center.y + 270));
			break;
		case 4:
			ImGui::SetCursorPos(ImVec2(center.x - 560, center.y + 270));
			break;
		}
		ImGui::Image(imgMole, ImVec2(150, 100));
	}
	
	// The Design of MainMenu 
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.85f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.8f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.6f, 0.9f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 12));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushFont(buttonFont);

	ImGui::Spacing(); ImGui::Spacing();
	ImGui::Spacing(); ImGui::Spacing();

	ImGui::SetCursorPos(ImVec2(center.x + 50, center.y - 210));
	if (ImGui::Button("Easy Mode", ImVec2(320, 70))) {
		currentPage = EasyMode;
	}
	ImGui::SetCursorPos(ImVec2(center.x + 50, center.y - 100));
	if (ImGui::Button("Medium Mode", ImVec2(320, 70))) {
		currentPage = MediumMode;
	}
	ImGui::SetCursorPos(ImVec2(center.x + 50, center.y + 10));
	if (ImGui::Button("Hard Mode", ImVec2(320, 70))) {
		currentPage = HardMode;
	}
	ImGui::SetCursorPos(ImVec2(center.x + 50, center.y + 120));
	if (ImGui::Button("Custom Mode", ImVec2(320, 70))) {
		currentPage = CustomMode;
	}
	ImGui::SetCursorPos(ImVec2(center.x + 50, center.y + 230));
	if (ImGui::Button("Quit", ImVec2(320, 70))) {
		window.close();
	}
	ImGui::PopFont();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);

	ImGui::End();
	ImGui::Render();
	ImGui::SFML::Render(window);
	window.draw(cursor);
	window.display();
};

// * *
//  *
// * *

void Gui::EasyModePage(RenderWindow& window, ImFont* buttonFont) {
	Game& game = Game::getInstance();
	Player& player = Player::getInstance();

	window.clear(Color::Color(0, 0, 0));
	ImGui::Begin("Main Menu Page", nullptr,
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoBackground);

	// Design the cursor
	sf::Sprite cursor(texCursor);
	sf::Vector2u texSize = texCursor.getSize();
	cursor.setOrigin(ImVec2(texSize.x / 2, texSize.y / 2));
	window.setMouseCursorVisible(false);
	cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetWindowSize(ImVec2(1200, 800));
	ImGui::SetWindowPos(ImVec2(center.x - 600, center.y - 400));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.85f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.8f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.6f, 0.9f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 12));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushFont(buttonFont);

	ImGui::SetCursorPos(ImVec2(center.x + 250, center.y + 200));
	if (ImGui::Button("Start Game", ImVec2(320, 70))) {
		game.ifGaming = true;
		game.resetGame("Easy");
	}

	ImGui::SetCursorPos(ImVec2(center.x + 250, center.y + 300));
	if (ImGui::Button("Quit Game", ImVec2(320, 70))) {
		game.ifGaming = false;
		currentPage = MainMenu;
	}
	ImGui::PopFont();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);

	//gamePage before starting game
	if (!game.ifGaming) {
		//Just show the positions of hole (imagebutton to do nothing)
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.85f, 1.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 12));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		ImVec2 holePos = ImVec2(center.x - 450, center.y - 200);
		ImGui::SetCursorPos(ImVec2(holePos.x, holePos.y));
		ImGui::ImageButton("hole1", texHole, ImVec2(150, 100));
		ImGui::SetCursorPos(ImVec2(holePos.x + 360, holePos.y));
		ImGui::ImageButton("hole2", texHole, ImVec2(150, 100));
		ImGui::SetCursorPos(ImVec2(holePos.x + 180, holePos.y + 180));
		ImGui::ImageButton("hole3", texHole, ImVec2(150, 100));
		ImGui::SetCursorPos(ImVec2(holePos.x, holePos.y + 360));
		ImGui::ImageButton("hole4", texHole, ImVec2(150, 100));
		ImGui::SetCursorPos(ImVec2(holePos.x + 360, holePos.y + 360));
		ImGui::ImageButton("hole5", texHole, ImVec2(150, 100));

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(4);

		Text scoreText(font, "");
		scoreText.setFont(font);
		scoreText.setString("Score : " + std::to_string(player.getScore()) + " pts");
		scoreText.setCharacterSize(fontsize);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(ImVec2(center.x - 560, center.y - 320));
		window.draw(scoreText);

		Text accuracyText(font, "");
		accuracyText.setFont(font);
		accuracyText.setString("Accuracy : 0%");
		accuracyText.setCharacterSize(fontsize);
		accuracyText.setFillColor(sf::Color::White);
		accuracyText.setPosition(ImVec2(center.x - 200, center.y - 320));
		window.draw(accuracyText);

		Text timerText(font, "");
		timerText.setFont(font);
		timerText.setString("Time : " + std::to_string(static_cast<int>(ceil(totalGameTime))) + " sec");
		timerText.setCharacterSize(fontsize);
		timerText.setFillColor(sf::Color::White);
		timerText.setPosition(ImVec2(center.x + 260, center.y - 320));
		window.draw(timerText);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.5f, 0.7f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
		ImGui::SetCursorPos(ImVec2(center.x - 580, center.y - 370));
		ImGui::ProgressBar(0.0f, ImVec2(1160, 20), "");
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
	}
	// the Loop of a Game
	if (game.ifGaming) {
		elapsedTime = gameClock.getElapsedTime().asSeconds();
		float remainingTime = totalGameTime - elapsedTime;
		Text timerText(font, "");
		timerText.setFont(font);
		timerText.setString("Time : " + std::to_string(static_cast<int>(ceil(remainingTime))) + " sec");
		timerText.setCharacterSize(fontsize);
		if (remainingTime <= 10)
			timerText.setFillColor(Color::Red);
		else 
			timerText.setFillColor(Color::White);
		timerText.setPosition(ImVec2(center.x + 260, center.y - 320));

		
		if (remainingTime <= 0) {
			gameClock.stop();
			moleSpawnClock.stop();
		}
		
		if (remainingTime <= 30) {
			moleAppearInterval = maxInterval;
		}
		else if (remainingTime <= 45) {
			moleAppearInterval = maxInterval + intervalIncrement;
		}

		sf::Time now = gameClock.getElapsedTime();
		sf::Time moleVisibleTime = sf::seconds(moleVisibleDuration);

		currentMolesCount = 0;
		for (Mole& mole : moles) {
			mole.update(now, moleVisibleTime);
			if (mole.getState()) {
				currentMolesCount++;
			}
		}

		if (moleSpawnClock.getElapsedTime().asSeconds() >= moleAppearInterval 
			&& currentMolesCount < maxVisibleMoles) {
			do {
				newMolePos = rand() % holeCount;
			} while (moles[newMolePos].getState());
			totalMoles++;
			moles[newMolePos].show(now);
			moleSpawnClock.restart();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.85f, 1.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 12));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		for (size_t i = 0; i < holeCount; i++) {
			ImGui::SetCursorPos(holesPos[i]);
			std::string id = "mole" + std::to_string(i);
			if (moles[i].getState()) {
				if (ImGui::ImageButton(id.c_str(), texMole, ImVec2(150, 100)) && remainingTime > 0) {
					moles[i].getHit();
				}
			}
			else {
				if (ImGui::ImageButton(id.c_str(), texHole, ImVec2(150, 100)) && remainingTime > 0) {
					moles[i].getHit();
				}
			}
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(4);

		Text scoreText(font, "");
		scoreText.setFont(font);
		scoreText.setString("Score : " + std::to_string(player.getScore()) + " pts");
		scoreText.setCharacterSize(fontsize);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(ImVec2(center.x - 560, center.y - 320));

		if (player.clickCount != 0) {
			player.accuracy = (float)player.hitCount / player.clickCount;
		}
		else {
			player.accuracy = 0;
		}

		Text accuracyText(font, "");
		accuracyText.setFont(font);
		accuracyText.setString("Accuracy : " + std::to_string(static_cast<int>(round(player.accuracy * 100))) + "%");
		accuracyText.setCharacterSize(fontsize);
		accuracyText.setFillColor(sf::Color::White);
		accuracyText.setPosition(ImVec2(center.x - 200, center.y - 320));

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
		if (remainingTime <= 10) {
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.5f, 0.7f, 0.9f, 1.0f));
		}
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
		ImGui::SetCursorPos(ImVec2(center.x - 580, center.y - 370));
		ImGui::ProgressBar(remainingTime / totalGameTime, ImVec2(1160, 20), "");
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();

		window.draw(timerText);
		window.draw(scoreText);
		window.draw(accuracyText);
	}

	ImGui::End();
	ImGui::Render();
	ImGui::SFML::Render(window);
	window.draw(cursor);
	window.display();
};

// ***
// ***
//  *
//  *

void Gui::MediumModePage(RenderWindow& window) {};

//    *
//   * *
//  * * *
// * * * *

void Gui::HardModePage(RenderWindow& window) {};

void Gui::CustomModePage(RenderWindow& window) {};