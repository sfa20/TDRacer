#include "scene_splash_screen.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Audio.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"
#include <LevelSystem.h>


using namespace std;
using namespace sf;
using namespace Resources;

SoundBuffer buffer;
Sound sound;

static std::shared_ptr<Entity> txt;

void SplashScreen::Load() {

	ls::loadLevelFile("res/opening.txt", 50.f);

	//loads sound
	if (!buffer.loadFromFile("res/opening.wav"))
	{
		std::cerr << "failed to load music!" << std::endl;
	}


	//Get position of grass tiles and set sprites to each position
	auto grassTiles = ls::findTiles(ls::GRASS);
	for each (auto t in grassTiles)
	{
		static shared_ptr<Entity> grass;
		grass = makeEntity();
		//Add a new sprite component set texture and scale
		auto t3 = grass->addComponent<SpriteComponent>();
		t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t3->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		grass->setPosition(g);
		/*t3->getSprite().setPosition(g);*/

	}

	auto trackTiles = ls::findTiles(ls::TRACK);
	for each (auto t in trackTiles)
	{
		static shared_ptr<Entity> track;
		track = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = track->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
		t2->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		track->setPosition(g);
		//		t2->getSprite().setPosition(g);

	}
	auto peakTiles = ls::findTiles(ls::TOP);
	for each (auto t in peakTiles)
	{
		static shared_ptr<Entity> peak;
		peak = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = peak->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_bottom.png"));
		t2->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		peak->setPosition(g);
		//		t2->getSprite().setPosition(g);


	}
	auto bottomTiles = ls::findTiles(ls::BOTTOM);
	for each (auto t in bottomTiles)
	{
		static shared_ptr<Entity> bottom;
		bottom = makeEntity();

		//Add a new sprite component set texture and scale
		auto t2 = bottom->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_top.png"));
		t2->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		bottom->setPosition(g);

		//		t2->getSprite().setPosition(g);

	}

	sound.setBuffer(buffer);

	sound.play();

	std::cout << "Menu Load \n";
	{

		//creates entitys for splash and adds sprite component
		auto splash = makeEntity();
		auto t = splash->addComponent<SpriteComponent>();
		t->getSprite().setTexture(*Resources::get<Texture>("box2d.png"));
		splash->setPosition(sf::Vector2f(Engine::getWindowSize().y / 2.f + 400, 700));

		auto splash1 = makeEntity();
		auto s = splash1->addComponent<SpriteComponent>();
		s->getSprite().setTexture(*Resources::get<Texture>("sfml.png"));
		splash1->setPosition(sf::Vector2f(Engine::getWindowSize().y / 2.f - 100, 790));




		////creates entitys for splash and adds text components
		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto start = txt->addComponent<TextComponent>("PRESS SPACE OR CLICK MOUSE TO START");

		//sets text position
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50);
		start->setCenterPos(Engine::getWindowSize().x / 2.f, 600.f, 50);

	}
	setLoaded(true);
}

void SplashScreen::Update(const double & dt)
{
	/*auto test = txt->GetCompatibleComponent<TextComponent>();*/

	// cout << "Menu Update "<<dt<<"\n";	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		sound.stop();
		Engine::ChangeScene(&menuScreen);
	}

	Scene::Update(dt);
}

