#include "scene_track_select.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Audio.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_sound.h"
#include <LevelSystem.h>


using namespace std;
using namespace sf;
using namespace Resources;

int trackSelection = 0;

static std::shared_ptr<Entity> txt;
static std::shared_ptr<Entity> selectTrackSound;

void TrackSelectScreen::Load() {

#pragma region Background Setup



	std::cout << "Menu Load \n";
	
		ls::loadLevelFile("res/opening.txt", 50.f);

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
			t2->getSprite().setTexture(*Resources::get<Texture>("stand.png"));
			t2->getSprite().setScale(0.400f, 0.400f);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			/*stand->setPosition(g);*/
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
			/*	tree->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

#pragma endregion

#pragma region Display Tracks





		/*********TRACK ONE****************************/
		auto trackOneEnt = makeEntity();
		auto t1Sprite = trackOneEnt->addComponent<SpriteComponent>();

		t1Sprite->getSprite().setTexture(*Resources::get<Texture>("trackOne.png"));
		t1Sprite->getSprite().setPosition(Engine::getWindowSize().x / 4.5, 300);

		/*********TRACK TWO****************************/
		auto trackTwoEnt = makeEntity();
		auto t2Sprite = trackTwoEnt->addComponent<SpriteComponent>();

		t2Sprite->getSprite().setTexture(*Resources::get<Texture>("trackTwo.png"));
		t2Sprite->getSprite().setPosition(Engine::getWindowSize().x / 2.3, 300);

		/*********TRACK THREE****************************/
		auto trackThreeEnt = makeEntity();
		auto t3Sprite = trackThreeEnt->addComponent<SpriteComponent>();

		t3Sprite->getSprite().setTexture(*Resources::get<Texture>("TrackThree.png"));
		t3Sprite->getSprite().setPosition(Engine::getWindowSize().x / 1.5, 300);

#pragma endregion
	
	{
		/***********************TEXT*****************************************/
		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);

		auto t1Txt = txt->addComponent<TextComponent>("Crazy Turns Raceway");
		t1Txt->setCenterPos(Engine::getWindowSize().x / 3.4, 500, 25);

		auto t2Txt = txt->addComponent<TextComponent>("C-137 Testing Grounds");
		t2Txt->setCenterPos(Engine::getWindowSize().x / 1.95, 500, 25);

		auto t3Txt = txt->addComponent<TextComponent>("Stelvto Circuit");
		t3Txt->setCenterPos(Engine::getWindowSize().x / 1.35, 500, 25);

		auto lapTxt = txt->addComponent<TextComponent>("LAP/S : 1");
		lapTxt->setCenterPos(Engine::getWindowSize().x / 2, 600, 40);

		selectTrackSound = makeEntity();
		auto beep = selectTrackSound->addComponent<SoundComponent>();
		beep->getSound().setBuffer(*Resources::get<SoundBuffer>("beep.wav"));
	}
	setLoaded(true);
	selectedItemIndex = 1;
}



void TrackSelectScreen::MoveUp() {
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void TrackSelectScreen::MoveDown() {
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void TrackSelectScreen::Update(const double & dt)
{
	//getting entity components
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();
	auto sound_cmp = selectTrackSound->GetCompatibleComponent<SoundComponent>();

	sf::Event event;

	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));



	window.pollEvent(event);

#pragma region MouseControls


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
	}

	//Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (txt_cmp[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 1 Pressed!" << endl;
			selectedItemIndex = 1;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&carSelectScreen);
		}

		if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 2 Pressed!" << endl;
			selectedItemIndex = 2;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&carSelectScreen);
		}

		if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 3 Pressed!" << endl;
			selectedItemIndex = 3;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}

	}

#pragma endregion

#pragma region KeyboardControls


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
				sound_cmp[0]->getSound().play();
				trackSelection = 1;
				Engine::ChangeScene(&carSelectScreen);
				break;
			case 2:
				std::cout << "Track 2 Options button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				sound_cmp[0]->getSound().play();
				trackSelection = 2;
				Engine::ChangeScene(&carSelectScreen);
				break;
			case 3:
				std::cout << "Track 3 button has been pressed" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				trackSelection = 3;
				Engine::ChangeScene(&carSelectScreen);
				break;
			}
		}
	}
#pragma endregion


}

