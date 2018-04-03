#include "scene_race_menu.h"
#include <iostream>
#include "SFML/Window/Keyboard.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"


using namespace std;
using namespace sf;
using namespace Resources;

Texture raceTex;
static std::shared_ptr<Entity> txt;

void RaceMenuScreen::Load()
{
	std::cout << "Menu Load \n";
	{
		auto splash = makeEntity();
		auto s = splash->addComponent<SpriteComponent>();

		txt = makeEntity();
		auto c1 = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto c2 = txt->addComponent<TextComponent>("HEAD 2 HEAD");
		auto c3 = txt->addComponent<TextComponent>("TIME TRIALS");
		auto c4 = txt->addComponent<TextComponent>("LEADERBOARD");

		//loads background image with error in console (Game still runs) - Ask Kevin 
		raceTex = *Resources::load<Texture>("background.png");

		s->getSprite().setTexture(raceTex, true);
		s->getSprite().setScale(2.1f, 2.f);

		c1->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		c2->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
		c3->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
		c4->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);

		c2->setColor(255, 0, 0, 255);
	}
	setLoaded(true);
	selectedItemIndex = 1;
}

void RaceMenuScreen::MoveUp() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void RaceMenuScreen::MoveDown() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void RaceMenuScreen::Update(const double& dt) {

	auto list = txt->GetCompatibleComponent<TextComponent>();

	sf::Event newEvent;


	sf::RenderWindow& newWindow = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(newWindow);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	newWindow.pollEvent(newEvent);

	//Handles this mouse hovering over the menu options
	if (sf::Event::MouseMoved) {

		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 1;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 2;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 3;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}


		//Handles the Button controls against the menu options
		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "HEAD 2 HEAD Pressed!" << endl;
				selectedItemIndex = 1;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&trackSelectScreen);
			}
			if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "TIME TRIALS Pressed!" << endl;
				selectedItemIndex = 2;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&trackSelectScreen);
			}
			if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "LEADERBOARD Pressed!" << endl;
				selectedItemIndex = 3;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}
		}
		////Handles Keyboard input and checks against the Menu Options
		if (sf::Event::KeyPressed) {

			if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
				if (GetPressedItem() != 0)
					MoveUp();
			}
			if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
				if (GetPressedItem() != 3)
					MoveDown();
			}
			if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
				switch (GetPressedItem()) {

				case 1:
					std::cout << "HEAD 2 HEAD button has been pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					Engine::ChangeScene(&trackSelectScreen);
					break;
				case 2:
					std::cout << "TIME TRIALS button has been pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					Engine::ChangeScene(&trackSelectScreen);
					break;
				case 3:
					std::cout << "LEADERBOARD  button has been pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					break;
				}
			}
		}
	}
}

