#include "scene_splash_screen.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Audio.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"
#include "../components//cmp_sound.h"
#include <LevelSystem.h>
#include "engine.h"


using namespace std;
using namespace sf;
using namespace Resources;

static std::shared_ptr<Entity> txt;

bool joystick1 = false;
bool joystick2 = false;

int j1buttonCount = 0;
int j2buttonCount = 0;

bool Left = false;
bool right = false;
bool up = false;
bool down = false;
bool idle = true;

bool hasAxis;

void SplashScreen::Load() {

	bool hasAxis = sf::Joystick::hasAxis(0, sf::Joystick::PovY);

	bool one = sf::Joystick::hasAxis(0, sf::Joystick::Axis::X);



	if (sf::Joystick::isConnected(0) || sf::Joystick::isConnected(1))
	{
		if (sf::Joystick::isConnected(0)) {
			cout << "joystick 0  connected" << endl;
			j1buttonCount = sf::Joystick::getButtonCount(0);
			joystick1 = true;
		}

		if (sf::Joystick::isConnected(1)) {
			cout << "joystick 1  connected" << endl;
			j2buttonCount = sf::Joystick::getButtonCount(1);
			joystick2 = true;
		}


	}

	ls::loadLevelFile("res/opening.txt", 50.f);

	//adds sound effect entity to splash screen menu
	auto openingSoundEntity = makeEntity();
	auto openingSound = openingSoundEntity->addComponent<SoundComponent>();

	openingSound->getSound().setBuffer(*Resources::get<SoundBuffer>("opening.wav"));
	openingSound->getSound().play();

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

	auto blueTiles = ls::findTiles(ls::BLUETENT);
	for each (auto t in blueTiles)
	{
		static shared_ptr<Entity> blue;
		blue = makeEntity();

		auto t1 = blue->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(0.400f, 0.400f);
		//Add a new sprite component set texture and scale
		auto t2 = blue->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("blue_tent.png"));
		t2->getSprite().setScale(0.400f, 0.400f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		blue->setPosition(g);
		/*t1->getSprite().setPosition(g);
		t2->getSprite().setPosition(g);*/

	}

	auto redTiles = ls::findTiles(ls::REDTENT);
	for each (auto t in redTiles)
	{
		static shared_ptr<Entity> red;
		red = makeEntity();

		auto t1 = red->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(0.400f, 0.400f);
		//Add a new sprite component set texture and scale
		auto t2 = red->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("red_tent.png"));
		t2->getSprite().setScale(0.400f, 0.400f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		red->setPosition(g);
		/*t1->getSprite().setPosition(g);
		t2->getSprite().setPosition(g);*/

	}

	auto standTiles = ls::findTiles(ls::STANDUP);
	for each (auto t in standTiles)
	{
		static shared_ptr<Entity> stand;
		stand = makeEntity();

		auto t1 = stand->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(0.400f, 0.400f);
		//Add a new sprite component set texture and scale
		auto t2 = stand->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("stand.png"));
		t2->getSprite().setScale(0.400f, 0.400f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		stand->setPosition(g);
		/*t1->getSprite().setPosition(g);
		t2->getSprite().setPosition(g);*/

	}

	auto treeTiles = ls::findTiles(ls::TREEL);
	for each (auto t in treeTiles)
	{
		static shared_ptr<Entity> tree;
		tree = makeEntity();

		auto t1 = tree->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(0.400f, 0.400f);
		//Add a new sprite component set texture and scale
		auto t2 = tree->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("tree_large.png"));
		t2->getSprite().setScale(0.400f, 0.400f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		tree->setPosition(g);
		/*t1->getSprite().setPosition(g);
		t2->getSprite().setPosition(g);*/

	}


	std::cout << "Menu Load \n";
	{

		//creates entitys for splash and adds sprite component
		auto splash = makeEntity();
		auto t = splash->addComponent<SpriteComponent>();
		t->getSprite().setTexture(*Resources::get<Texture>("box2d.png"));
		splash->setPosition(sf::Vector2f(Engine::getWindowSize().y / 2.f + 400, 800));

		auto splash1 = makeEntity();
		auto s = splash1->addComponent<SpriteComponent>();
		s->getSprite().setTexture(*Resources::get<Texture>("sfml.png"));
		splash1->setPosition(sf::Vector2f(Engine::getWindowSize().y / 2.f - 100, 890));


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
	//joystick controls
	if (joystick1 == true || joystick2 == true)
	{
		if (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 7) || sf::Joystick::isButtonPressed(1, 0) || sf::Joystick::isButtonPressed(1, 7))
		{
			cout << " joystick button pressed" << endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&menuScreen);
		}
	}

	//keyboard and mouse controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		Engine::ChangeScene(&menuScreen);
	}

	Scene::Update(dt);
}

/////
// a = 0
// b = 1
// x = 2
// y = 3
// lb = 4
// rb = 5
// select = 6
// start = 7
// l3 = 8
// r3 = 9

