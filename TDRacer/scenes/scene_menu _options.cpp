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

static shared_ptr<Entity> options;
static shared_ptr<Entity> optionsSound;

void OptionScreen::Load() {

	cout << "Menu Load \n"; {

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

		options = makeEntity();
		////creates text entitys
		options->addComponent<TextComponent>("TD Championship Racer");
		options->addComponent<TextComponent>("Controls");
		options->addComponent<TextComponent>("Graphics");
		options->addComponent<TextComponent>("Sound");
		options->addComponent<TextComponent>("Main Menu");

		/**************************************************************************************/
		optionsSound = makeEntity();
		auto beep = optionsSound->addComponent<SoundComponent>();
		beep->getSound().setBuffer(*Resources::get<SoundBuffer>("beep.wav"));

		////sets positions and size of menu entitys
		auto list = options->GetCompatibleComponent<TextComponent>();

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
	auto list = options->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void OptionScreen::MoveDown() {
	auto list = options->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void OptionScreen::Update(const double& dt) {

	auto list = options->GetCompatibleComponent<TextComponent>();
	auto sound_cmp = optionsSound->GetCompatibleComponent<SoundComponent>();

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
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&controlScreen);
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Graphics Pressed!" << endl;
			selectedItemIndex = 2;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&graphicScreen);
		}

		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Sound Pressed!" << endl;
			selectedItemIndex = 3;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&soundScreen);
		}

		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Main menu!" << endl;
			sound_cmp[0]->getSound().play();
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
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&controlScreen);
				break;
			case 2:
				std::cout << "Graphics button has been pressed" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&graphicScreen);
				break;
			case 3:
				std::cout << "Sound button has been pressed" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&soundScreen);
				break;
			case 4:
				std::cout << "Sound button has been pressed" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&menuScreen);
				break;
			}
		}
	}

}





