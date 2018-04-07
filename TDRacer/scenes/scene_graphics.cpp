#include "scene_graphics.h"
#include <iostream>
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Audio.hpp"
#include "../game.h"
#include "../components/cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../components/cmp_sprite.h"
#include <LevelSystem.h>
#include <vector>


using namespace std;
using namespace sf;
using namespace Resources;

static std::shared_ptr<Entity> txt;

//INFORMATION FOR SETTINGS MENU
string vSyncSetting[2]{ "OFF","ON" };
string * res;
string windowModeSetting[2]{ "FULLSCREEN"," WINDOWED" };

int vSyncIndex = 0;
int resIndex = 0;
int windowModeIndex = 0;
int sizeOfModes;
int stringCount = 0;
int nHeight;
int nWidth;



void GraphicScreen::Load() {

	// Display the list of all the video modes available for fullscreen
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	sizeOfModes = modes.size();
	res = new string[sizeOfModes];

	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];

		std::string s = std::to_string(mode.width);
		std::string a = std::to_string(mode.height);

		res[i] = s + " x " + a;

		std::cout << "Mode #" << i << ": "
			<< mode.width << "x" << mode.height << " - "
			<< mode.bitsPerPixel << " bpp" << std::endl;
	}


	// Create a window with the same pixel depth as the desktop
	/*sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML window");*/



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

		//converts current desktop mode to display in control3 
		auto a = VideoMode::getDesktopMode().width;
		auto b = VideoMode::getDesktopMode().height;
		std::string currentWidth = std::to_string(a);
		std::string currentHeight = std::to_string(b);

		//creates entitys for splash and adds text components
		txt = makeEntity();
		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
		auto control1 = txt->addComponent<TextComponent>("V-SYNC : " + vSyncSetting[vSyncIndex]);
		auto control2 = txt->addComponent<TextComponent>("RESOLUTION : " + currentWidth + " x " + currentHeight);
		auto control3 = txt->addComponent<TextComponent>("WINDOW MODE : " + windowModeSetting[windowModeIndex]);
		auto control4 = txt->addComponent<TextComponent>("BACK TO MENU");



		//sets text position
		title->setCenterPos(Engine::getWindowSize().x / 2.f, 100.f, 60);
		control1->setCenterPos(Engine::getWindowSize().x / 2.f, 500.f, 40);
		control2->setCenterPos(Engine::getWindowSize().x / 2.f, 550.f, 40);
		control3->setCenterPos(Engine::getWindowSize().x / 2.f, 600.f, 40);
		control4->setCenterPos(Engine::getWindowSize().x / 2.f, 650.f, 40);
		control1->setColor(255, 0, 0, 255);
	}
	setLoaded(true);
	selectedItemIndex = 1;
}

void GraphicScreen::MoveUp() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

void GraphicScreen::MoveDown() {
	auto list = txt->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		list[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		list[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}


void GraphicScreen::Update(const double & dt)
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
		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			list[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex = 4;
			list[selectedItemIndex]->setColor(255, 0, 0, 255);
		}

	}

	//Handles the Button controls against the menu options
	if (Mouse::isButtonPressed(Mouse::Left)) {

		//controls vsync selection for mouse
		if (list[1]->GetText().getGlobalBounds().contains(mousePosF)) {

			if (vSyncIndex == 0)
			{
				vSyncIndex++;
				list[1]->SetText("V-SYNC : " + vSyncSetting[vSyncIndex]);
				Engine::setVsync(true);
			}
			else
			{
				vSyncIndex--;
				list[1]->SetText("V-SYNC : " + vSyncSetting[vSyncIndex]);
				Engine::setVsync(false);
			}
			cout << "vSync pressed" << endl;
			selectedItemIndex = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}

		if (list[2]->GetText().getGlobalBounds().contains(mousePosF)) {

			int sizeRes = res->max_size();
			auto convertRes = res[resIndex];

			if (resIndex >= 0)
			{
				list[2]->SetText("RESOLUTION : " + res[resIndex]);
				resIndex++;

			}
			if (resIndex == sizeOfModes)
			{
				resIndex = 0;
				list[2]->SetText("RESOLUTION : " + res[resIndex]);
			}

			cout << "RESOLUTION PRESSED!" << endl;
			selectedItemIndex = 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		if (list[3]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "WINDOW MODE PRESSED!" << endl;
			selectedItemIndex = 3;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		if (list[4]->GetText().getGlobalBounds().contains(mousePosF)) {
			cout << "OPTIONS MENU PRESSED!" << endl;
			selectedItemIndex = 4;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			window.close();

			std::string masterString = res[resIndex];
			std::stringstream iss(masterString);


			while (iss.good())
			{
				stringCount++;

				std::string resString;
				getline(iss, resString, 'x');

				if (stringCount == 1)
					nWidth = atoi(resString.c_str());
				else
					nHeight = atoi(resString.c_str());
			}

			Engine::Start(nWidth, nHeight, "TD Championship Racer", &menuScreen);
			/*Engine::ChangeScene(&menuScreen);*/
		}
	}

	//Handles Keyboard input and checks against the Menu Options
	if (sf::Event::KeyPressed) {

		if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
			if (GetPressedItem() != 1)
				MoveUp();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
			if (GetPressedItem() != 7)
				MoveDown();
		}

		if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
			switch (GetPressedItem()) {

			case 1:
				//controls vsync selection for keyboard
				std::cout << "vSync button has been pressed" << std::endl;
				if (vSyncIndex == 0)
				{
					vSyncIndex++;
					list[1]->SetText("V-SYNC : " + vSyncSetting[vSyncIndex]);
					Engine::setVsync(true);
				}
				else
				{
					vSyncIndex--;
					list[1]->SetText("V-SYNC : " + vSyncSetting[vSyncIndex]);
					Engine::setVsync(false);
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			case 2:
				std::cout << "Track 2 Options button has been pressed" << std::endl;
				if (resIndex >= 0)
				{
					list[2]->SetText("RESOLUTION : " + res[resIndex]);
					resIndex++;
				}
				if (resIndex == sizeOfModes)
				{
					resIndex = 0;
					list[2]->SetText("RESOLUTION : " + res[resIndex]);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			case 3:
				std::cout << "Track 3 button has been pressed" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				break;
			}
		}
	}
}