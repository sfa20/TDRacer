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
		//loads background image
		texture = *Resources::load<Texture>("background.png");

		//sets background image
		s->getSprite().setTexture(texture, true);
		s->getSprite().setScale(1.4, 1.4);


		//creates text entitys
	//	auto menu = makeEntity();
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
	previousItemIndex = 1;
	setLoaded(true);
}

void MenuEvents() {
	//sf::Event event;
	//sf::Vector2i mousePos = sf::Mouse::getPosition();
	//sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
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

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		/*	Scene::Update(dt);*/
	}

	sf::Event event;


	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	
	auto list = mainmenu->GetCompatibleComponent<TextComponent>();
	auto a = list[1]->GetText();
	window.pollEvent(event);


	if (sf::Event::MouseMoved) {
		selectedItemIndex = 1;
		if (a.getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
			
			
		};

	}


	if (Mouse::isButtonPressed(Mouse::Left)) {

		
		auto b = list[2]->GetText();

		

		if (a.getGlobalBounds().contains(mousePosF)) {
			list[1]->setColor(255, 0, 0, 255);
			list[2]->setColor(255, 255, 255, 255);
			list[3]->setColor(255,255, 255, 255);
			list[4]->setColor(255, 255, 255, 255);

		}
	}
	
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

			case 0:
				std::cout << "Single player button has been pressed" << std::endl;
				break;
			case 1:
				std::cout << "Multiplayer button has been pressed" << std::endl;
				break;
			case 2:
				std::cout << "Options button has been pressed" << std::endl;
				break;
			case 3:
				window.close();
				break;
			}
			Scene::Update(dt);
		}
	}

		

	
			/*case sf::Event::MouseMoved:
			{
				if (list[0].getGlobalBounds().contains(mousePosF)) {
					menu[0].setFillColor(sf::Color(255, 0, 0, 255));
					menu[1].setFillColor(sf::Color(255, 255, 255, 255));
					menu[2].setFillColor(sf::Color(255, 255, 255, 255));
					menu[3].setFillColor(sf::Color(255, 255, 255, 255));
					selectedItemIndex = 0;
				}

				if (menu[1].getGlobalBounds().contains(mousePosF)) {
					menu[1].setFillColor(sf::Color(255, 0, 0, 255));
					menu[0].setFillColor(sf::Color(255, 255, 255, 255));
					menu[2].setFillColor(sf::Color(255, 255, 255, 255));
					menu[3].setFillColor(sf::Color(255, 255, 255, 255));
					selectedItemIndex = 1;
				}

				if (menu[2].getGlobalBounds().contains(mousePosF)) {
					menu[2].setFillColor(sf::Color(255, 0, 0, 255));
					menu[0].setFillColor(sf::Color(255, 255, 255, 255));
					menu[1].setFillColor(sf::Color(255, 255, 255, 255));
					menu[3].setFillColor(sf::Color(255, 255, 255, 255));
					selectedItemIndex = 2;
				}

				if (menu[3].getGlobalBounds().contains(mousePosF)) {
					menu[3].setFillColor(sf::Color(255, 0, 0, 255));
					menu[0].setFillColor(sf::Color(255, 255, 255, 255));
					menu[1].setFillColor(sf::Color(255, 255, 255, 255));
					menu[2].setFillColor(sf::Color(255, 255, 255, 255));
					selectedItemIndex = 3;
				}
				break; */
		
	
}




