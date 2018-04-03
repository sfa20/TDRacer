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

Texture mainTex;
static shared_ptr<Entity> mainMenu;


void MenuScreen::Load() {

	cout << "Menu Load \n"; {

		//entitys are created in layer order
		//cretes entity for background image

		//********* LAYER 1 *********
		mainMenu = makeEntity();
		auto s = mainMenu->addComponent<SpriteComponent>();

		//********* LAYER 2 *********
		//loads background image with error in console (Game still runs) - Ask Kevin 
		mainTex = *Resources::load<Texture>("background.png");

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!texture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		//sets background image
		s->getSprite().setTexture(mainTex, true);
		s->getSprite().setScale(2.1f, 2.f);

		//creates text entitys
		mainMenu->addComponent<TextComponent>("TD Championship Racer");
		mainMenu->addComponent<TextComponent>("Play game");
		mainMenu->addComponent<TextComponent>("Options");
		mainMenu->addComponent<TextComponent>("Credits");
		mainMenu->addComponent<TextComponent>("Exit");
		/**************************************************************************************/
		auto a = mainMenu->addComponent<ShapeComponent>();
		a->setShape<RectangleShape>(RectangleShape(Vector2f(100.f, 100.f)));



		//sets positions and size of menu entitys
		auto list = mainMenu->GetCompatibleComponent<TextComponent>();
		list[0]->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		list[1]->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
		list[2]->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
		list[3]->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);
		list[4]->setCenterPos(Engine::getWindowSize().x / 2.f, 670.f, 50.f);

		//sets colours of entitys
		list[0]->setColor(255, 0, 0, 200);
		list[1]->setColor(255, 0, 0, 255);

	}
	selectedItemIndex = 1; //added - sfa20
	setLoaded(true);
}

void MenuScreen::MoveUp() {
	auto list = mainMenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void MenuScreen::MoveDown() {
	auto list = mainMenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void MenuScreen::Update(const double& dt) {

	sf::Event event;

	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	//getting entity components
	auto list = mainMenu->GetCompatibleComponent<TextComponent>();

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
			cout << "Play game Pressed!" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&loadScreen);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Options Pressed!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&optionScreen);
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Credits Pressed!" << endl;
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
				std::cout << "Play game button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&loadScreen);
				break;
			case 2:
				std::cout << "Options button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&optionScreen);
				break;
			case 3:
				std::cout << "Credits button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			case 4:
				window.close();
				break;
			}
		}
	}
}




