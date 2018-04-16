#include "scene_select_avatar.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"
#include "LevelSystem.h"
#include "../components/cmp_sound.h"


using namespace std;
using namespace sf;
using namespace Resources;

static std::shared_ptr<Entity> txt;
static std::shared_ptr<Entity> selectAvatarSound;

void AvatarScreen::Load()
{
	std::cout << "Menu Load \n";
	{
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
			/*	blue->setPosition(g);*/
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
			/*tree->setPosition(g);*/
			t1->getSprite().setPosition(g);
			t2->getSprite().setPosition(g);

		}

		/*********AVATAR ONE****************************/
		auto ninjaEnt = makeEntity();
		auto nSprite = ninjaEnt->addComponent<SpriteComponent>();

		nSprite->getSprite().setTexture(*Resources::get<Texture>("Ninja.png"));
		nSprite->getSprite().setPosition(Engine::getWindowSize().x / 3.7, 280);

		/*********AVATAR TWO****************************/
		auto guyEnt = makeEntity();
		auto gSprite = guyEnt->addComponent<SpriteComponent>();

		gSprite->getSprite().setTexture(*Resources::get<Texture>("Guy.png"));
		gSprite->getSprite().setPosition(Engine::getWindowSize().x / 2.6, 280);

		/*********AVATAR THREE****************************/
		auto clownEnt = makeEntity();
		auto cSprite = clownEnt->addComponent<SpriteComponent>();

		cSprite->getSprite().setTexture(*Resources::get<Texture>("Clown.png"));
		cSprite->getSprite().setPosition(Engine::getWindowSize().x / 2, 280);

		/*********AVATAR FOUR****************************/
		auto vampEnt = makeEntity();
		auto vSprite = vampEnt->addComponent<SpriteComponent>();

		vSprite->getSprite().setTexture(*Resources::get<Texture>("Vamp.png"));
		vSprite->getSprite().setPosition(Engine::getWindowSize().x / 1.6, 280);


		/***********************TEXT*****************************************/
		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50.f);

		auto nTxt = txt->addComponent<TextComponent>("Ninja");
		nTxt->setCenterPos(Engine::getWindowSize().x / 3.15, 500, 25);

		auto gTxt = txt->addComponent<TextComponent>("Guy");
		gTxt->setCenterPos(Engine::getWindowSize().x / 2.3, 500, 25);

		auto cTxt = txt->addComponent<TextComponent>("Clown");
		cTxt->setCenterPos(Engine::getWindowSize().x / 1.83, 500, 25);

		auto vTxt = txt->addComponent<TextComponent>("Vamp");
		vTxt->setCenterPos(Engine::getWindowSize().x / 1.49, 500, 25);


		selectAvatarSound = makeEntity();
		auto beep = selectAvatarSound->addComponent<SoundComponent>();
		beep->getSound().setBuffer(*Resources::get<SoundBuffer>("beep.wav"));
	}
	setLoaded(true);
}

void AvatarScreen::MoveUp() {
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));

	}
}

void AvatarScreen::MoveDown() {
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));

	}
}

void AvatarScreen::Update(const double & dt)
{
	auto txt_cmp = txt->GetCompatibleComponent<TextComponent>();
	auto sound_cmp = selectAvatarSound->GetCompatibleComponent<SoundComponent>();

	sf::Event AvatarEvent;;

	sf::RenderWindow& avatarWindow = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(avatarWindow);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	avatarWindow.pollEvent(AvatarEvent);

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
		if (selectedItemIndex + 1 < 5) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex++;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		cout << " joystick down pressed" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

	////Handles this mouse hovering over the menu options
	if (sf::Event::MouseMoved) {

		if (txt_cmp[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 1;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
		else if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 2;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
		else if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 3;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
		else if (txt_cmp[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 4;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
	}

	//////Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (txt_cmp[1]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Ninja selected!" << endl;
			selectedItemIndex = 1;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
		}

		if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Guy Selected!" << endl;
			selectedItemIndex = 2;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
		}

		if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Clown Selected!" << endl;
			selectedItemIndex = 3;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
		}

		if (txt_cmp[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Vamp Selected!" << endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
		}
	}

	////Handles Keyboard input and checks against the Menu Options
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
				std::cout << "Ninja selected" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&raceMenuScreen);
				break;
			case 2:
				std::cout << "Guy Selected" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&raceMenuScreen);
				break;
			case 3:
				std::cout << "Clown Selected" << std::endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&raceMenuScreen);
				break;
			case 4:
				cout << "Vamp Selected!" << endl;
				sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				Engine::ChangeScene(&raceMenuScreen);
				break;
			}
		}
	}

	if (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 7)) {

		switch (GetPressedItem()) {

		case 1:
			std::cout << "Ninja button has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
			break;
		case 2:
			std::cout << "Guy button has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
			break;
		case 3:
			std::cout << "clown button has been pressed joystick" << std::endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
			break;
		case 4:
			cout << "Vamp Selected!" << endl;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&raceMenuScreen);
			break;
		}
	}
}