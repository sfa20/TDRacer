#include "scene_race_menu.h"
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

Texture splashTex;
static std::shared_ptr<Entity> txt;

void RaceMenuScreen::Load()
{
	std::cout << "Menu Load \n";
	{
		auto splash = makeEntity();
		auto s = splash->addComponent<SpriteComponent>();

		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");


		//loads background image with error in console (Game still runs) - Ask Kevin 
		splashTex = *Resources::load<Texture>("background.png");

		s->getSprite().setTexture(splashTex, true);
		s->getSprite().setScale(2.1f, 2.f);

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!splashTexture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
		std::cerr << "failed to load spritesheet!" << std::endl;
		}*/


	}
	setLoaded(true);
}


void RaceMenuScreen::Update(const double & dt)
{
	// cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Engine::ChangeScene(&level1);
	}

	Scene::Update(dt);
}

