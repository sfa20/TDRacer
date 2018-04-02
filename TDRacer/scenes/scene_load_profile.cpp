#include "scene_load_profile.h"
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

Texture loadProfileTex;
static std::shared_ptr<Entity> txt;

void LoadProfileScreen::Load()
{
	std::cout << "Menu Load \n";
	{
		auto splash = makeEntity();
		auto s = splash->addComponent<SpriteComponent>();

		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto start = txt->addComponent<TextComponent>("LOAD PROFILE COMING SOON");



		//loads background image with error in console (Game still runs) - Ask Kevin 
		loadProfileTex = *Resources::load<Texture>("background.png");

		s->getSprite().setTexture(loadProfileTex, true);
		s->getSprite().setScale(2.1f, 2.f);

		//Loads background imagae WITHOUT error (unless file is non-existent)
		/*if (!splashTexture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}*/

		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		start->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);


	}
	setLoaded(true);
}


void LoadProfileScreen::Update(const double & dt)
{
	auto test = txt->GetCompatibleComponent<TextComponent>();

	// cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		Engine::ChangeScene(&raceMenuScreen);
	}

	Scene::Update(dt);
}

