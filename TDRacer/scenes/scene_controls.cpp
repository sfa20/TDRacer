#pragma once
#include "LevelSystem.h"
#include "scene_splash_screen.h"
#include "engine.h"
#include "ecm.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sound.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_controls.h"
#include "../game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace sf;
using namespace Resources;

string * controls;
int * controlsReverse;
int accelIndex = 0;
int reverseIndex = 0;
int brakeIndex = 0;
int leftIndex = 0;
int rightIndex = 0;

int sizeOfControls;
static shared_ptr<Entity> control;
//static shared_ptr<Entity> controlSound;

void ControlScreen::Load() {

	auto getControls = testPlayer->GetCompatibleComponent<PlayerControls>()[0];
	
	auto b = getControls->getAccelerateControl();


#pragma region Background Setup

	std::cout << "Menu Load \n";
	
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

#pragma endregion


#pragma region SetKeyValues


		KeyValues[0] = "A";
		KeyValues[1] = "B";
		KeyValues[2] = "C";
		KeyValues[3] = "D";
		KeyValues[4] = "E";
		KeyValues[5] = "F";
		KeyValues[6] = "G";
		KeyValues[7] = "H";
		KeyValues[8] = "I";
		KeyValues[9] = "J";
		KeyValues[10] = "K";
		KeyValues[11] = "L";
		KeyValues[12] = "M";
		KeyValues[13] = "N";
		KeyValues[14] = "O";
		KeyValues[15] = "P";
		KeyValues[16] = "Q";
		KeyValues[17] = "R";
		KeyValues[18] = "S";
		KeyValues[19] = "T";
		KeyValues[20] = "U";
		KeyValues[21] = "V";
		KeyValues[22] = "W";
		KeyValues[23] = "X";
		KeyValues[24] = "Y";
		KeyValues[25] = "Z";
		KeyValues[37] = "Left Ctl";
		KeyValues[38] = "Left Shift";
		KeyValues[39] = "Left Alt";
		KeyValues[41] = "Right Ctrl";
		KeyValues[42] = "Right Shift";
		KeyValues[43] = "Right Alt";
		KeyValues[49] = "Comma";
		KeyValues[50] = "Period";
		KeyValues[52] = "Forward Slash (/)";
		KeyValues[53] = "Back Slash ('\')";
		KeyValues[57] = "Space";
		KeyValues[59] = "Backspace";
		KeyValues[71] = "Left";
		KeyValues[72] = "Right";
		KeyValues[73] = "Up";
		KeyValues[74] = "Down";
		KeyValues[75] = "NumPad 0";
		KeyValues[76] = "NumPad 1";
		KeyValues[77] = "NumPad 2";
		KeyValues[78] = "NumPad 3";
		KeyValues[79] = "NumPad 4";
		KeyValues[80] = "NumPad 5";
		KeyValues[81] = "NumPad 6";
		KeyValues[82] = "NumPad 7";
		KeyValues[83] = "NumPad 8";
		KeyValues[84] = "NumPad 9";

#pragma endregion


	auto bo = stoi(getControls->getAccelerateControl());
	cout << "stoi: " << bo << endl;
	auto bb = KeyValues[bo];
	cout << "BB: " << endl;
	
	{
		//creates entitys for splash and adds text components
		control = makeEntity();
		auto title = control->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto selectTrack = control->addComponent<TextComponent>("placeholder SELECTED TRACK");
		auto accel = control->addComponent<TextComponent>("Accelerate : " + KeyValues[stoi(getControls->getAccelerateControl())]);
		auto reverse = control->addComponent<TextComponent>("Reverse:    " + KeyValues[stoi(getControls->getReverseControl())]);
		auto handbrake = control->addComponent<TextComponent>("Handbrake:" + KeyValues[stoi(getControls->getHandBrakeControl())]);
		auto turnl = control->addComponent<TextComponent>("Turn Left:    " + KeyValues[stoi(getControls->getTurnLeftControl())]);
		auto turnr = control->addComponent<TextComponent>("Turn Right:   " + KeyValues[stoi(getControls->getTurnRightControl())]);
		auto main = control->addComponent<TextComponent>("Main Menu");


		//controlSound = makeEntity();
		/*auto beep = controlSound->addComponent<SoundComponent>();
		beep->getSound().setBuffer(*Resources::get<SoundBuffer>("beep.wav"));*/

		//sets text position
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 50);
		
		accel->setCenterPos(Engine::getWindowSize().x / 2.1f , 500.f, 50);
		reverse->setCenterPos(Engine::getWindowSize().x / 2.1f , 560.f, 50);	
		handbrake->setCenterPos(Engine::getWindowSize().x / 2.1f, 620.f, 50);
		turnl->setCenterPos(Engine::getWindowSize().x / 2.1f, 680.f, 50);
		turnr->setCenterPos(Engine::getWindowSize().x / 2.1f , 740.f, 50);
		main->setCenterPos(Engine::getWindowSize().x / 2.1f, 880.f, 50);

		accel->setColor(255, 0, 0, 255);
	}
	

	sizeOfControls = KeyValues.size();
	controls = new string[sizeOfControls];
	controlsReverse = new int[sizeOfControls];

	int i = 0;

	for each (auto key in KeyValues) {
		
		controls[i] = "Accelerate: "  + KeyValues[key.first];
		controlsReverse[i] = key.first;
		i++;
	}

	for (std::size_t i = 0; i < sizeOfControls; i++) {
		cout << controlsReverse[i] << endl;
	}


	setLoaded(true);
	selectedItemIndex = 2;
}

void ControlScreen::MoveUp() {
	auto txt_cmp = control->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void ControlScreen::MoveDown() {
	auto txt_cmp = control->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 8) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void ControlScreen::GetKeyValue(int key) {

	
}

void ControlScreen::Update(const double & dt)
{
	sf::Event event;

	sf::RenderWindow& window = Engine::GetWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	//getting entity components
	auto txt_cmp = control->GetCompatibleComponent<TextComponent>();
	//auto sound_cmp = controlSound->GetCompatibleComponent<SoundComponent>();

	window.pollEvent(event);

#pragma region MouseControls


	//Handles this mouse hovering over the menu options
	/*if (sf::Event::MouseMoved) {

		if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 1;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 2;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

		if (txt_cmp[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 3;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		}
	}
*/
	//Handles the Button controls against the menu options
	/*if (Mouse::isButtonPressed(Mouse::Left)) {

		if (txt_cmp[2]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 1 Pressed!" << endl;
			selectedItemIndex = 1;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&loadScreen);
		}

		if (txt_cmp[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 2 Pressed!" << endl;
			selectedItemIndex = 2;
			sound_cmp[0]->getSound().play();
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			Engine::ChangeScene(&optionScreen);
		}

		if (txt_cmp[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "Track 3 Pressed!" << endl;
			sound_cmp[0]->getSound().play();
			selectedItemIndex = 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}*/

#pragma endregion


#pragma region KeyboardControls


	//Handles Keyboard input and checks against the Menu Options
	if (sf::Event::KeyPressed) {

		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
			if (GetPressedItem() != 2)
				MoveUp();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
			if (GetPressedItem() != 7)
				MoveDown();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
			switch (GetPressedItem()) {

			case 2:
				std::cout << "Accelerate Btn has been pressed" << std::endl;
				//sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				if (accelIndex >= 0)
				{
					txt_cmp[2]->SetText(controls[accelIndex]);
					accelIndex++;
				}

				if (accelIndex == sizeOfControls)
				{
					accelIndex = 0;
					txt_cmp[2]->SetText(controls[accelIndex]);
				}
				break;
			case 3:
				std::cout << "Reverse button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				//sound_cmp[0]->getSound().play();
				if (reverseIndex >= 0)
				{
					txt_cmp[3]->SetText(controls[reverseIndex]);
					reverseIndex++;

				}

				if (reverseIndex == sizeOfControls)
				{
					reverseIndex = 0;
					txt_cmp[3]->SetText(controls[reverseIndex]);
				}
				//Engine::ChangeScene(&level1);
				break;
			case 4:
				std::cout << "HandBrake button has been pressed" << std::endl;
				//sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				if (brakeIndex >= 0)
				{
					txt_cmp[4]->SetText(controls[brakeIndex]);
					brakeIndex++;

				}

				if (brakeIndex == sizeOfControls)
				{
					brakeIndex = 0;
					txt_cmp[4]->SetText(controls[brakeIndex]);
				}
				break;
			case 5:
				std::cout << "Turn Left button has been pressed" << std::endl;
				//sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				if (leftIndex >= 0)
				{
					txt_cmp[5]->SetText(controls[leftIndex]);
					leftIndex++;

				}

				if (leftIndex == sizeOfControls)
				{
					leftIndex = 0;
					txt_cmp[5]->SetText(controls[leftIndex]);
				}
				break;
			case 6:
				std::cout << "Turn Right button has been pressed" << std::endl;
				//sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				if (rightIndex >= 0)
				{
					txt_cmp[6]->SetText(controls[rightIndex]);
					rightIndex++;

				}

				if (rightIndex == sizeOfControls)
				{
					rightIndex = 0;
					txt_cmp[6]->SetText(controls[rightIndex]);
				}
				break;
			case 7:
				std::cout << "Main Menu button has been pressed" << std::endl;
				//sound_cmp[0]->getSound().play();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));

				auto updatecontrols = testPlayer->GetCompatibleComponent<PlayerControls>()[0];

				updatecontrols->ChangeControls("Accelerate", controlsReverse[accelIndex]);
				updatecontrols->ChangeControls("Reverse", controlsReverse[reverseIndex]);
				updatecontrols->ChangeControls("Handbrake", controlsReverse[brakeIndex]);
				updatecontrols->ChangeControls("Left", controlsReverse[leftIndex]);
				updatecontrols->ChangeControls("Right", controlsReverse[rightIndex]);



				Engine::ChangeScene(&menuScreen);
				break;
			}
		}
	}

#pragma endregion

}