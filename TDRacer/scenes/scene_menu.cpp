#include "engine.h"
#include "ecm.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "scene_menu.h"
#include "../components/cmp_player_physics.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "LevelSystem.h"

using namespace std;
using namespace sf;
using namespace Resources;

Texture texture;
static shared_ptr<Entity> mainmenu;

void MenuScene::Load() {

	cout << "Menu Load \n"; {

		//entitys are created in layer order
		//cretes entity for background image

		//********* LAYER 1 *********
		mainmenu = makeEntity();
		auto s = mainmenu->addComponent<SpriteComponent>();

		//********* LAYER 2 *********
		//loads background image with error in console (Game still runs) - Ask Kevin 
		texture = *Resources::load<Texture>("background.png");

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!texture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		//sets background image
		s->getSprite().setTexture(texture, true);
		s->getSprite().setScale(1.4, 1.4);

		//creates text entitys
		mainmenu->addComponent<TextComponent>("TD Championship Racer");
		mainmenu->addComponent<TextComponent>("Single Player");
		mainmenu->addComponent<TextComponent>("MultiPlayer");
		mainmenu->addComponent<TextComponent>("Options");
		mainmenu->addComponent<TextComponent>("Exit");

		//sets positions and size of menu entitys
		auto list = mainmenu->GetCompatibleComponent<TextComponent>();
		list[0]->setPos(430, 50, 50);
		list[1]->setPos(500, 280, 30);
		list[2]->setPos(500, 330, 30);
		list[3]->setPos(500, 370, 30);
		list[4]->setPos(500, 420, 30);

		//sets colours of entitys
		list[0]->setColor(255, 0, 0, 200);
		list[1]->setColor(255, 0, 0, 255);

	}
	selectedItemIndex = 1; //added - sfa20
	setLoaded(true);
}

void MenuScene::MoveUp() {
	auto list = mainmenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void MenuScene::MoveDown() {
	auto list = mainmenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void MenuScene::Update(const double& dt) {

	sf::Event event;

	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	//getting entity components
	auto list = mainmenu->GetCompatibleComponent<TextComponent>();

	window.pollEvent(event);

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

		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 4;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
	}

	//Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Single Player Pressed!" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&level1);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Multiplayer Pressed!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Options Pressed!" << endl;
			selectedItemIndex = 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}

		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Exit!" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			window.close();
		}
	}

	//Handles Keyboard input and checks against the Menu Options
	if (sf::Event::KeyPressed) {

		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
			if (GetPressedItem() != 0)
				MoveUp();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
			if (GetPressedItem() != 5)
				MoveDown();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
			switch (GetPressedItem()) {

			case 1:
				std::cout << "Single player button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&level1);
				break;
			case 2:
				std::cout << "Multiplayer button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			case 3:
				std::cout << "Options button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			case 4:
				window.close();
				break;
			}
		}
	}
}




