#include "scene_load_screen.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Audio.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"


using namespace std;
using namespace sf;
using namespace Resources;

Texture loadTexture;
static std::shared_ptr<Entity> txt;

void LoadScreen::Load()
{

	std::cout << "Menu Load \n";
	{
		auto start = makeEntity();
		auto s = start->addComponent<SpriteComponent>();

		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto control = txt->addComponent<TextComponent>("New game");
		auto control1 = txt->addComponent<TextComponent>("Load game");



		//loads background image with error in console (Game still runs) - Ask Kevin 
		loadTexture = *Resources::load<Texture>("background.png");

		s->getSprite().setTexture(loadTexture, true);
		s->getSprite().setScale(2.1f, 2.f);

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!splashTexture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
		std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		control->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
		control1->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);

		control->setColor(255, 0, 0, 255);


	}
	setLoaded(true);
	selectedItemIndex = 1;
}
void LoadScreen::MoveUp() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void LoadScreen::MoveDown() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void LoadScreen::Update(const double & dt)
{
	auto list = txt->GetCompatibleComponent<TextComponent>();

	sf::Event startEvent;;

	sf::RenderWindow& startWindow = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(startWindow);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	startWindow.pollEvent(startEvent);

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
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "New game Pressed!" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&loadPScreen);

		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Load game Pressed!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));


		}

	}
	//Handles Keyboard input and checks against the Menu Options
	if (sf::Event::KeyPressed) {

		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
			if (GetPressedItem() != 0)
				MoveUp();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
			if (GetPressedItem() != 2)
				MoveDown();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
			switch (GetPressedItem()) {

			case 1:
				std::cout << "New game has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&avatarScreen);
				break;
			case 2:
				std::cout << "Load game has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&loadPScreen);
				break;
			}
		}

	}
}




