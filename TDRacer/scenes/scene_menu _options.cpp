#include "engine.h"
#include "ecm.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "scene_menu _options.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <chrono>


using namespace std;
using namespace sf;
using namespace Resources;

Texture textureuy;
static shared_ptr<Entity> _Options;

void OptionScreen::Load() {

	cout << "Menu Load \n"; {

		//entitys are created in layer order
		//cretes entity for background image

		//********* LAYER 1 *********
		_Options = makeEntity();
		auto s = _Options->addComponent<SpriteComponent>();

		////********* LAYER 2 *********
		////loads background image with error in console (Game still runs) - Ask Kevin 
		textureuy = *Resources::load<Texture>("background.png");

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!textureuy.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		////sets background image
		s->getSprite().setTexture(textureuy, true);
		s->getSprite().setScale(2.1f, 2.f);

		////creates text entitys
		_Options->addComponent<TextComponent>("TD Championship Racer");
		_Options->addComponent<TextComponent>("Controls");
		_Options->addComponent<TextComponent>("Graphics");
		_Options->addComponent<TextComponent>("Sound");
		_Options->addComponent<TextComponent>("Main Menu");

		////sets positions and size of menu entitys
		auto list = _Options->GetCompatibleComponent<TextComponent>();

		list[0]->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		list[1]->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
		list[2]->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
		list[3]->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);
		list[4]->setCenterPos(Engine::getWindowSize().x / 2.f, 670.f, 50.f);

		list[1]->setColor(255, 0, 0, 255);

	}
	selectedItemIndex = 1; //added - sfa20

	setLoaded(true);
}

void OptionScreen::MoveUp() {
	auto list = _Options->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void OptionScreen::MoveDown() {
	auto list = _Options->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void OptionScreen::Update(const double& dt) {

	auto list = _Options->GetCompatibleComponent<TextComponent>();

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

		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 4;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
	}

	//Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Controls Pressed!" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&controlScreen);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Graphics Pressed!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&graphicScreen);
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Sound Pressed!" << endl;
			selectedItemIndex = 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&soundScreen);
		}

		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Main menu!" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			Engine::ChangeScene(&menuScreen);
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
				std::cout << "Controls button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&controlScreen);
				break;
			case 2:
				std::cout << "Graphics button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&graphicScreen);
				break;
			case 3:
				std::cout << "Sound button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&soundScreen);
				break;
			case 4:
				std::cout << "Sound button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&menuScreen);
				break;
			}
		}
	}

}





