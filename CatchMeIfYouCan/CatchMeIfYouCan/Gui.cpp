#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include "Game.h"
#include "Gui.h"

using namespace sf;

Gui Gui::gui;

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

	//Design the cursor
	sf::Sprite cursor(texCursor);
	sf::Vector2u texSize = texCursor.getSize();
	cursor.setOrigin(ImVec2(texSize.x / 2, texSize.y / 2));
	window.setMouseCursorVisible(false);
	cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

	//Show the GameLogo
	ImTextureID imgLogo = texLogo.getNativeHandle();
	ImGui::SetCursorPos(ImVec2(center.x - 375, center.y - 330));
	ImGui::Image(imgLogo, ImVec2(750, 90));

	//Random mole design
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
	
	//The Design of MainMenu 
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
}

void Gui::EasyModePage(RenderWindow& window) {
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

	//Design the cursor
	sf::Sprite cursor(texCursor);
	sf::Vector2u texSize = texCursor.getSize();
	cursor.setOrigin(ImVec2(texSize.x / 2, texSize.y / 2));
	window.setMouseCursorVisible(false);
	cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

	ImGui::End();
	ImGui::Render();
	ImGui::SFML::Render(window);
	window.draw(cursor);
	window.display();
};

void Gui::MediumModePage(RenderWindow& window) {};
void Gui::HardModePage(RenderWindow& window) {};
void Gui::CustomModePage(RenderWindow& window) {};