#include "scene_track_select.h"
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

Texture grassTexture8;
Texture roadTexture8;
Texture peakTexture8;
Texture bottomTexture8;
Texture cornerTexture29;
Texture cornerTexture30;
Texture cornerTexture31;
Texture cornerTexture32;
Texture rightTexture8;
Texture leftTexture8;

static std::shared_ptr<Entity> txt;

void TrackSelectScreen::Load() {


	std::cout << "Menu Load \n";
	{
		ls::loadLevelFile("res/menu.txt", 50.f);

		//Loads background imagae WITHOUT error (unless file is non-existent)
		if (!roadTexture8.loadFromFile("res/img/Straights/straight_noBorder.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!peakTexture8.loadFromFile("res/img/Straights/straight_horizontal_noBorder_bottom.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!bottomTexture8.loadFromFile("res/img/Straights/straight_horizontal_noBorder_top.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!grassTexture8.loadFromFile("res/img/grass.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!cornerTexture29.loadFromFile("res/img/Corners/90DegreeTopRight.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!cornerTexture30.loadFromFile("res/img/Corners/90DegreeTopLeft.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!cornerTexture31.loadFromFile("res/img/Corners/90DegreeBottomLeft.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!cornerTexture32.loadFromFile("res/img/Corners/90DegreeBottomRight.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!rightTexture8.loadFromFile("res/img/Straights/straight_vertical_noBorder_left.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}
		if (!leftTexture8.loadFromFile("res/img/Straights/straight_vertical_noBorder_right.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}

		//Get position of grass tiles and set sprites to each position
		auto grassTiles = ls::findTiles(ls::GRASS);
		for each (auto t in grassTiles)
		{
			static shared_ptr<Entity> grass;
			grass = makeEntity();
			//Add a new sprite component set texture and scale
			auto t3 = grass->addComponent<SpriteComponent>();
			t3->getSprite().setTexture(grassTexture8);
			t3->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			//grass->setPosition(g);
			t3->getSprite().setPosition(g);

		}
		auto peakTiles = ls::findTiles(ls::TOP);
		for each (auto t in peakTiles)
		{
			static shared_ptr<Entity> peak;
			peak = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = peak->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(peakTexture8);
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			//peak->setPosition(g);
			t2->getSprite().setPosition(g);


		}
		auto bottomTiles = ls::findTiles(ls::BOTTOM);
		for each (auto t in bottomTiles)
		{
			static shared_ptr<Entity> bottom;
			bottom = makeEntity();

			//Add a new sprite component set texture and scale
			auto t2 = bottom->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(bottomTexture8);
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*bottom->setPosition(g);*/

			t2->getSprite().setPosition(g);

		}
		auto trackTiles = ls::findTiles(ls::TRACK);
		for each (auto t in trackTiles)
		{
			static shared_ptr<Entity> track;
			track = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = track->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(roadTexture8);
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*track->setPosition(g);*/
			t2->getSprite().setPosition(g);

		}
		//Get position of Corner tiles and set sprites to each postition
		auto corner1Tiles = ls::findTiles(ls::CORNER1);
		for each (auto t in corner1Tiles)
		{
			static shared_ptr<Entity> corn1;
			corn1 = makeEntity();

			auto t1 = corn1->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(grassTexture8);
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn1->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(cornerTexture29);
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn1->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		//Get position of track tiles and set sprites to each postition
		auto corner2Tiles = ls::findTiles(ls::CORNER2);
		for each (auto t in corner2Tiles)
		{
			static shared_ptr<Entity> corn2;
			corn2 = makeEntity();
			auto t1 = corn2->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(grassTexture8);
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn2->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(cornerTexture30);
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn2->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		//Get position of track tiles and set sprites to each postition
		auto corner3Tiles = ls::findTiles(ls::CORNER3);
		for each (auto t in corner3Tiles)
		{
			static shared_ptr<Entity> corn3;
			corn3 = makeEntity();
			auto t1 = corn3->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(grassTexture8);
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn3->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(cornerTexture31);
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn3->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		//Get position of track tiles and set sprites to each postition
		auto corner4Tiles = ls::findTiles(ls::CORNER4);
		for each (auto t in corner4Tiles)
		{
			static shared_ptr<Entity> corn4;
			corn4 = makeEntity();
			auto t1 = corn4->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(grassTexture8);
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn4->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(cornerTexture32);
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn4->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}
		//Get position of RightTrack tiles and set sprites to each postition
		auto rightTiles = ls::findTiles(ls::RIGHT);
		for each (auto t in rightTiles)
		{
			static shared_ptr<Entity> right;
			right = makeEntity();

			//Add a new sprite component set texture and scale
			auto t2 = right->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(rightTexture8);
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*right->setPosition(g);*/
			t2->getSprite().setPosition(g);

		}

		//Get position of LeftTrack tiles and set sprites to each postition
		auto leftTiles = ls::findTiles(ls::LEFT);
		for each (auto t in leftTiles)
		{
			static shared_ptr<Entity> left;
			left = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = left->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(leftTexture8);
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*left->setPosition(g);*/
			t2->getSprite().setPosition(g);

		}

		//creates entitys for splash and adds text components
		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto track1 = txt->addComponent<TextComponent>("TRACK 1");
		auto track2 = txt->addComponent<TextComponent>("TRACK 2");
		auto track3 = txt->addComponent<TextComponent>("TRACK 3");

		//sets text position
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50);
		track1->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50);
		track2->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50);
		track3->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50);

		track1->setColor(255, 0, 0, 255);

	}
	setLoaded(true);
	selectedItemIndex = 1;
}

void TrackSelectScreen::MoveUp() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void TrackSelectScreen::MoveDown() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void TrackSelectScreen::Update(const double & dt)
{
	sf::Event event;

	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	//getting entity components
	auto list = txt->GetCompatibleComponent<TextComponent>();

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
	}

	//Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 1 Pressed!" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&carSelectScreen);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 2 Pressed!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&carSelectScreen);
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 3 Pressed!" << endl;
			selectedItemIndex = 3;
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
			if (GetPressedItem() != 3)
				MoveDown();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
			switch (GetPressedItem()) {

			case 1:
				std::cout << "Track 1 button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&carSelectScreen);
				break;
			case 2:
				std::cout << "Track 2 Options button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&carSelectScreen);
				break;
			case 3:
				std::cout << "Track 3 button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			}
		}
	}
}

