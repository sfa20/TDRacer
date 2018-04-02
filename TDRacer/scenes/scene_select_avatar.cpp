#include "scene_select_avatar.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"


using namespace std;
using namespace sf;
using namespace Resources;

Texture startGameTex;
static std::shared_ptr<Entity> txt;

void AvatarScreen::Load()
{
	std::cout << "Menu Load \n";
	{
		auto start = makeEntity();
		auto s = start->addComponent<SpriteComponent>();

		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto control = txt->addComponent<TextComponent>(" SELECT AVATAR COMING SOON");



		//loads background image with error in console(Game still runs) - Ask Kevin
		startGameTex = *Resources::load<Texture>("background.png");

		s->getSprite().setTexture(startGameTex, true);
		s->getSprite().setScale(2.1f, 2.f);

		//Loads background imagae WITHOUT error(unless file is non - existent)
		/*if (!splashTexture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		control->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);

	}
	setLoaded(true);
}

void AvatarScreen::MoveUp() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));

	}
}

void AvatarScreen::MoveDown() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));

	}
}

void AvatarScreen::Update(const double & dt)
{


	sf::Event AvatarEvent;;

	sf::RenderWindow& startWindow = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(startWindow);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	startWindow.pollEvent(AvatarEvent);


	//Handles Keyboard input and checks against the Menu Options
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		Engine::ChangeScene(&raceMenuScreen);
	}

}

