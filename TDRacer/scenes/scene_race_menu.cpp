#include "LevelSystem.h"
#include "scene_splash_screen.h"
#include "engine.h"
#include "ecm.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sound.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace sf;
using namespace Resources;

static shared_ptr<Entity> raceMenu;
static shared_ptr<Entity> raceMenuSound;

int gameMode;

void RaceMenuScreen::Load()
{
	std::cout << "Menu Load \n";
	{
		ls::loadLevelFile("res/menu.txt", 50.f);

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
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_bottom.png"));
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
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_top.png"));
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
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*track->setPosition(g);*/
			t2->getSprite().setPosition(g);

		}

		////Get position of Corner tiles and set sprites to each postition
		auto corner1Tiles = ls::findTiles(ls::CORNER1);
		for each (auto t in corner1Tiles)
		{
			static shared_ptr<Entity> corn1;
			corn1 = makeEntity();

			auto t1 = corn1->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn1->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopRight.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn1->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		////Get position of track tiles and set sprites to each postition
		auto corner2Tiles = ls::findTiles(ls::CORNER2);
		for each (auto t in corner2Tiles)
		{
			static shared_ptr<Entity> corn2;
			corn2 = makeEntity();
			auto t1 = corn2->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn2->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopLeft.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn2->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		////Get position of track tiles and set sprites to each postition
		auto corner3Tiles = ls::findTiles(ls::CORNER3);
		for each (auto t in corner3Tiles)
		{
			static shared_ptr<Entity> corn3;
			corn3 = makeEntity();
			auto t1 = corn3->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn3->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomLeft.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*corn3->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		////Get position of track tiles and set sprites to each postition
		auto corner4Tiles = ls::findTiles(ls::CORNER4);
		for each (auto t in corner4Tiles)
		{
			static shared_ptr<Entity> corn4;
			corn4 = makeEntity();
			auto t1 = corn4->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = corn4->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomRight.png"));
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
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_left.png"));
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*right->setPosition(g);*/
			t2->getSprite().setPosition(g);

		}

		////Get position of LeftTrack tiles and set sprites to each postition
		auto leftTiles = ls::findTiles(ls::LEFT);
		for each (auto t in leftTiles)
		{
			static shared_ptr<Entity> left;
			left = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = left->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_right.png"));
			t2->getSprite().setScale(0.400f, 0.400f);

			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*left->setPosition(g);*/
			t2->getSprite().setPosition(g);

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
			/*blue->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

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
			/*red->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

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
			t2->getSprite().setTexture(*Resources::get<Texture>("standP.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*stand->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		auto standDwnTiles = ls::findTiles(ls::STANDDWN);
		for each (auto t in standDwnTiles)
		{
			static shared_ptr<Entity> standDwn;
			standDwn = makeEntity();

			auto t1 = standDwn->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(0.400f, 0.400f);
			//Add a new sprite component set texture and scale
			auto t2 = standDwn->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("standD.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*	standDwn->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

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
			/*tree->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		raceMenu = makeEntity();
		auto c1 = raceMenu->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto c2 = raceMenu->addComponent<TextComponent>("HEAD 2 HEAD");
		auto c3 = raceMenu->addComponent<TextComponent>("TIME TRIALS");
		auto c4 = raceMenu->addComponent<TextComponent>("LEADERBOARD");

		raceMenuSound = makeEntity();
		auto beep = raceMenuSound->addComponent<SoundComponent>();
		beep->getSound().setBuffer(*Resources::get<SoundBuffer>("beep.wav"));


		c1->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);
		c2->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
		c3->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
		c4->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);

		c2->setColor(255, 0, 0, 255);
	}
	setLoaded(true);
	selectedItemIndex = 1;
}

void RaceMenuScreen::MoveUp() {
	auto txt_cmp = raceMenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void RaceMenuScreen::MoveDown() {
	auto txt_cmp = raceMenu->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void RaceMenuScreen::Update(const double& dt) {

	auto txt_cmp = raceMenu->GetCompatibleComponent<TextComponent>();
	auto sound_cmp = raceMenuSound->GetCompatibleComponent<SoundComponent>();

	sf::Event newEvent;


	sf::RenderWindow& newWindow = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(newWindow);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	newWindow.pollEvent(newEvent);

	//joystick events 	
	Vector2f didItMove(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Y));


	if (didItMove.x > 15) {
		cout << " joystick right pressed" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	if (didItMove.x < -15) {
		cout << " joystick left pressed" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	if (didItMove.y < -15) {
		if (selectedItemIndex - 1 > 0) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex--;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		cout << " joystick up pressed" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	if (didItMove.y > 15) {
		if (selectedItemIndex + 1 < 4) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex++;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		cout << " joystick down pressed" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	//Handles this mouse hovering over the menu options
	if (sf::Event::MouseMoved) {

		if (txt_cmp[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 1;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 2;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 3;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}


		//Handles the Button controls against the menu options
		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (txt_cmp[1]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "HEAD 2 HEAD Pressed!" << endl;
				sound_cmp[0]->getSound().play();
				selectedItemIndex = 1;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&trackSelectScreen);
			}
			if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "TIME TRIALS Pressed!" << endl;
				sound_cmp[0]->getSound().play();
				selectedItemIndex = 2;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&trackSelectScreen);
			}
			if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
				cout << "LEADERBOARD Pressed!" << endl;
				sound_cmp[0]->getSound().play();
				selectedItemIndex = 3;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}
		}
		////Handles Keyboard input and checks against the Menu Options
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
					std::cout << "HEAD 2 HEAD button has been pressed" << std::endl;
					sound_cmp[0]->getSound().play();
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					gameMode = 1;
					Engine::ChangeScene(&trackSelectScreen);
					break;
				case 2:
					std::cout << "TIME TRIALS button has been pressed" << std::endl;
					sound_cmp[0]->getSound().play();
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					gameMode = 2;
					Engine::ChangeScene(&trackSelectScreen);
					break;
				case 3:
					std::cout << "LEADERBOARD  button has been pressed" << std::endl;
					sound_cmp[0]->getSound().play();
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					break;
				}
			}
		}
	}
	if (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 7)) {

		switch (GetPressedItem()) {

		case 1:
			std::cout << "HEAD 2 HEAD button has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&trackSelectScreen);
			break;
		case 2:
			std::cout << "TIME TRIALS has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&trackSelectScreen);
			break;
		case 3:
			std::cout << "LEADERBOARD button has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			break;

		}

	}
}

