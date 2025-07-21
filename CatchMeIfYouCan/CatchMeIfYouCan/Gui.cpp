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
	ImGui::Begin("Main Menu", nullptr,
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoBackground);

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetWindowSize(ImVec2(800, 700));
	ImGui::SetWindowPos(ImVec2(center.x - 400, center.y - 350));
	
	//Design the cursor
	Texture texCursor;
	texCursor.loadFromFile("CatchMeIfYouCan/assets/hammer.png");
	sf::Sprite cursor(texCursor);
	sf::Vector2u texSize = texCursor.getSize();
	cursor.setOrigin(ImVec2(texSize.x / 2, texSize.y / 2));
	window.setMouseCursorVisible(false);
	cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

	//Show the GameLogo
	sf::Texture texLogo;
	texLogo.loadFromFile("CatchMeIfYouCan/assets/logo-removebg.png");
	ImTextureID imgLogo = texLogo.getNativeHandle();
	ImGui::SetCursorPos(ImVec2(center.x - 375, center.y - 330));
	ImGui::Image(imgLogo, ImVec2(750, 90));

	//The Design of MainPage 
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.85f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.8f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.6f, 0.9f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 12));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushFont(buttonFont);

	ImGui::Spacing(); ImGui::Spacing();
	ImGui::Spacing(); ImGui::Spacing();

	//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	//ImGui::PushFont(buttonFont);
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

void Gui::EasyModePage(RenderWindow& window) {};
void Gui::MediumModePage(RenderWindow& window) {};
void Gui::HardModePage(RenderWindow& window) {};
void Gui::CustomModePage(RenderWindow& window) {};