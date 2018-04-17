#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_text.h"
#include "../components/cmp_race_timer.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include <system_physics.h>
#include "LevelSystem.h"
#include <fstream>
#include <iostream>
#include "../components/cmp_timer.h"
#include "../components/cmp_lap_timer.h"
#include "../components/cmp_car_body.h"
#include "../components/cmp_player_controls.h"
#include "../components//cmp_ai_physics.h"
#include "../components/cmp_pause_menu.h"

using namespace std;
using namespace sf;
using namespace Resources;

static shared_ptr<Entity> player;
static shared_ptr<Entity> ai;

static shared_ptr<Entity> raceTimer;
static shared_ptr<Entity> WinnerMessage;
static shared_ptr<Entity> pauseMenu;

std::map<int, std::string> KeyValues;

sf::Vector2f scale = { 0.400f, 0.400f };
int counter = 0;

int playeroneLapNo;
int playertwoLapNo;
int playeroneCheckpoint;
int playertwoCheckpoint;
bool active;
int accelIndex = 0;
int reverseIndex = 0;
int brakeIndex = 0;
int leftIndex = 0;
//int sizeOfControls;
int rightIndex = 0;

void Level1Scene::Load() {

	float size = 50.f;

#pragma region Check Screen Resolution
	//CheckScreenRes();

	//cout << to_string(nWidth) << endl;
	//cout << to_string(nHeight) << endl;

	if (nWidth == 1920 && nHeight == 1080) {
		scale = { 0.400f, 0.400f };
		size = 50.f;
	}
	else if (nWidth == 1280 && nHeight == 720) {
		scale = { 0.395f, 0.395f };
		size = 34.f;
		//cout << scale << endl;
		//cout << size << endl;
	}
	else if (nWidth == 1024 && nHeight == 600) {
		scale = { 0.300f, 0.300f };
		size = 28.f;
	}

	//Load Level File
	ls::loadLevelFile("res/track_1.txt", size);
	
#pragma endregion


#pragma region Setup Map


	//////////////Added////////////
	auto startTilesLeft = ls::findTiles(ls::STARTLEFT);
	for each (auto t in startTilesLeft) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_right.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}

	auto startTilesRight = ls::findTiles(ls::STARTRIGHT);
	for each (auto t in startTilesRight) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_left.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}

	auto startTiles = ls::findTiles(ls::START);
	for each (auto t in startTiles) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}


	///////////////////////////////////////


		//Get position of grass tiles and set sprites to each position
		auto grassTiles = ls::findTiles(ls::GRASS);
		for each (auto t in grassTiles)
		{
			static shared_ptr<Entity> grass;
			grass = makeEntity();
			//Add a new sprite component set texture and scale
			auto t3 = grass->addComponent<SpriteComponent>();
			t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t3->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			grass->setPosition(g);
		}
	
		auto wallTiles = ls::findTiles(ls::WALL);
		for each (auto t in wallTiles)
		{

			static shared_ptr<Entity> wall;
			wall = makeEntity();
			//Add a new sprite component set texture and scale
			auto t3 = wall->addComponent<SpriteComponent>();
			t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t3->getSprite().setScale(scale);
			
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			wall->setPosition(g);
	
			auto barrier = wall->addComponent<PhysicsComponent>(false, Vector2f(51.2f, 51.2f));
		}
	
	
		//Get position of TopTrack tiles and set sprites to each postition
		auto peakTiles = ls::findTiles(ls::TOP);
		for each (auto t in peakTiles)
		{
			static shared_ptr<Entity> peak;
			peak = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = peak->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_bottom.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			peak->setPosition(g);
	
		}
	
		//Get position of BottomTrack tiles and set sprites to each postition
		auto bottomTiles = ls::findTiles(ls::BOTTOM);
		for each (auto t in bottomTiles)
		{
			static shared_ptr<Entity> bottom;
			bottom = makeEntity();
	
			//Add a new sprite component set texture and scale
			auto t2 = bottom->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_top.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			bottom->setPosition(g);
	
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
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			right->setPosition(g);
		}
	
		//Get position of LeftTrack tiles and set sprites to each postition
		auto leftTiles = ls::findTiles(ls::LEFT);
		for each (auto t in leftTiles)
		{
			static shared_ptr<Entity> left;
			left = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = left->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_right.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			left->setPosition(g);
	
		}
	
		//Get position of track tiles and set sprites to each postition
		auto trackTiles = ls::findTiles(ls::TRACK);
		for each (auto t in trackTiles)
		{
			static shared_ptr<Entity> track;
			track = makeEntity();
			//Add a new sprite component set texture and scale
			auto t2 = track->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			track->setPosition(g);
	
		}
	
		//Get position of Corner tiles and set sprites to each postition
		auto corner1Tiles = ls::findTiles(ls::CORNER1);
		for each (auto t in corner1Tiles)
		{
			static shared_ptr<Entity> corn1;
			corn1 = makeEntity();
	
			auto t1 = corn1->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn1->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopRight.png"));
			t2->getSprite().setScale(scale);
	
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			corn1->setPosition(g);
	
		}
	
		//Get position of track tiles and set sprites to each postition
		auto corner2Tiles = ls::findTiles(ls::CORNER2);
		for each (auto t in corner2Tiles)
		{
			static shared_ptr<Entity> corn2;
			corn2 = makeEntity();
			auto t1 = corn2->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn2->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopLeft.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			corn2->setPosition(g);
	
		}
	
		//Get position of track tiles and set sprites to each postition
		auto corner3Tiles = ls::findTiles(ls::CORNER3);
		for each (auto t in corner3Tiles)
		{
			static shared_ptr<Entity> corn3;
			corn3 = makeEntity();
			auto t1 = corn3->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn3->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomLeft.png"));
			t2->getSprite().setScale(scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			corn3->setPosition(g);
	
		}
	
		//Get position of track tiles and set sprites to each postition
		auto corner4Tiles = ls::findTiles(ls::CORNER4);
		for each (auto t in corner4Tiles)
		{
			static shared_ptr<Entity> corn4;
			corn4 = makeEntity();
			auto t1 = corn4->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn4->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomRight.png"));
			t2->getSprite().setScale(scale);
	
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			corn4->setPosition(g);
	
		}


#pragma region Testing Checkpoints

		auto checkpoint1Tiles = ls::findTiles(ls::CHECKPOINT1);
		for each (auto t in checkpoint1Tiles)
		{
			static shared_ptr<Entity> chkpt1;
			chkpt1 = makeEntity();
			auto t1 = chkpt1->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = chkpt1->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_right.png"));
			t2->getSprite().setScale(scale);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			chkpt1->setPosition(g);

		}

		auto checkpoint2Tiles = ls::findTiles(ls::CHECKPOINT2);
		for each (auto t in checkpoint2Tiles)
		{
			static shared_ptr<Entity> chkpt2;
			chkpt2 = makeEntity();
			auto t1 = chkpt2->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = chkpt2->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
			t2->getSprite().setScale(scale);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			chkpt2->setPosition(g);

		}

		auto checkpoint3Tiles = ls::findTiles(ls::CHECKPOINT3);
		for each (auto t in checkpoint3Tiles)
		{
			static shared_ptr<Entity> chkpt3;
			chkpt3 = makeEntity();
			auto t1 = chkpt3->addComponent<SpriteComponent>();
			t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
			t1->getSprite().setScale(scale);
			//Add a new sprite component set texture and scale
			auto t2 = chkpt3->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_left.png"));
			t2->getSprite().setScale(scale);


			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			chkpt3->setPosition(g);

		}








#pragma endregion





#pragma endregion


#pragma region Setup Timer

		raceTimer = makeEntity();
		auto c = raceTimer->addComponent<TextComponent>("Timer: ");
		c->setCenterPos(Engine::getWindowSize().x - 400.f, 20.f, 40.f);
		auto c2 = raceTimer->addComponent<Timer>();
		c2->start();
		auto c3 = raceTimer->addComponent<LapTimer>();
		c3->start();

#pragma endregion


#pragma region CreatePlayer 
	 
	//Create an PlayerCar Entity, add component and set texture
	player = makeEntity();

	//Adds a Sprite component & set values
	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component
	t->getSprite().setTexture(*Resources::get<Texture>("Car.png"));
	t->getSprite().setScale(.45f, .45f);
	t->getSprite().setColor(Color::Red);
	t->getSprite().setOrigin(10,0);

	//Add a player controls component - This allows the user to have different controls
	//for accel, brake etc and will allow these to be dynamically changed through an
	//options menu
	auto ctrl = player->addComponent<PlayerControls>();

	//Add a Player Physics Component
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(27.9f, 18.f));
	//p->setMass(10);
	
	//Find the starting position 
	auto l = ls::findTiles(ls::START);
	auto lv = ls::getTilePosition(l[0]);

	//Set the players starting position
	player->setPosition(Vector2f(lv));

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


#pragma region AI Testing

	//Create an PlayerCar Entity, add component and set texture
	ai = makeEntity();

	//Adds a Sprite component & set values
	auto ait = ai->addComponent<SpriteComponent>(); //Add a sprite component
	ait->getSprite().setTexture(*Resources::get<Texture>("Car.png"));
	ait->getSprite().setScale(.45f, .45f);
	ait->getSprite().setColor(Color::Red);
	ait->getSprite().setOrigin(10, 0);

	//Add a player controls component - This allows the user to have different controls
	//for accel, brake etc and will allow these to be dynamically changed through an
	//options menu
	auto aictrl = player->addComponent<PlayerControls>();
	//aictrl->ChangeControls("Accelerate", KeyValues[2]);  


	//Add a Player Physics Component
	auto aip = ai->addComponent<AIPhysicsComponent>(Vector2f(27.9f, 18.f));
	//p->setMass(10);

	//Find the starting position 
	auto lr = ls::findTiles(ls::STARTRIGHT);
	auto lrv = ls::getTilePosition(lr[0]);

	//Set the players starting position
	ai->setPosition(Vector2f(lrv));


#pragma endregion



#pragma region Testing

	auto winnerText = raceTimer->addComponent<TextComponent>(" ");
	winnerText->setCenterPos(Engine::getWindowSize().x / 2.f, Engine::getWindowSize().y / 2, 60.f);

	pauseMenu = makeEntity();
	pauseMenu->addComponent<PauseMenu>();
	pauseMenu->addComponent<PlayerControls>();
	auto pausecmp = pauseMenu->GetCompatibleComponent<PauseMenu>()[0];
	pausecmp->active = false;
	pausecmp->submenuActive = false;

#pragma endregion

}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;

	Scene::UnLoad();
}


void Level1Scene::Update(const double& dt) {

#pragma region Handle RaceTimer

	//Update the RaceTimer
	raceTimer->update(dt);

	//Get the race timer
	auto timer = raceTimer->GetCompatibleComponent<Timer>()[0];

	//Get the current time
	string time = timer->getTime();

	//Get the text component and set this to the time string created above
	auto textBox = raceTimer->GetCompatibleComponent<TextComponent>()[0];
	textBox->SetText(time);
	//End of Race Timer

#pragma endregion


#pragma region CheckRaceStatus


#pragma region PauseMenu Test
	auto pausecmp = pauseMenu->GetCompatibleComponent<PauseMenu>()[0];
	auto mainTimer = raceTimer->GetCompatibleComponent<Timer>()[0];
	auto lapsTimer = raceTimer->GetCompatibleComponent<LapTimer>()[0];
	auto playercmp = player->GetCompatibleComponent<PlayerPhysicsComponent>()[0];

	auto aicmp = ai->GetCompatibleComponent<AIPhysicsComponent>()[0];
	auto txt_cmp = pauseMenu->GetCompatibleComponent<TextComponent>();


	if (Keyboard::isKeyPressed(Keyboard::P)) {
		pausecmp->active = true;
		playercmp->dampen(Vector2f(10, 10));
		playercmp->controlsEnabled = false;
		aicmp->dampen(Vector2f(10, 10));
		aicmp->controlsEnabled = false;
	}
	
	if(pausecmp->active || pausecmp->submenuActive) {
		if (sf::Event::KeyPressed) {
			
			if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
				if (pausecmp->GetPressedItem() != 1) {
					pausecmp->MoveUp();
				}
			}

			if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
				if (pausecmp->GetPressedItem() != 11)
					pausecmp->MoveDown();
			}

			if (sf::Keyboard::isKeyPressed(Keyboard::Return)) {
				switch (pausecmp->GetPressedItem()) {

#pragma region Main Menu
				case 1:
					std::cout << "Resume control pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					pausecmp->active = false;
					playercmp->controlsEnabled = true;
					aicmp->controlsEnabled = true;
					break;
				case 2:
					std::cout << "Restart pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					pausecmp->active = false;
					Engine::ChangeScene(&level1);
					break;
				case 3:
					std::cout << "Controls 3 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					pausecmp->active = false;
					pausecmp->submenuActive = true;
					pausecmp->selectedItemIndex = 5;
					break;
				case 4:
					std::cout << "Exit Menu 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					pausecmp->active = false;
					Engine::ChangeScene(&menuScreen);
					break;

#pragma endregion


#pragma region Controls Menu
				case 5:
					std::cout << "Option 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					if (accelIndex >= 0)
					{
						txt_cmp[5]->SetText("Accelerate: " + controls[accelIndex]);
						accelIndex++;
						cout << "test press" << controls[accelIndex] << endl;
					}

					if (accelIndex == sizeOfControls)
					{
						accelIndex = 0;
						txt_cmp[5]->SetText("Accelerate: " + controls[accelIndex]);
					}
					break;
				case 6:
					std::cout << "Option 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					if (reverseIndex >= 0)
					{
						txt_cmp[6]->SetText("Reverse: " + controls[reverseIndex]);
						reverseIndex++;
						cout << "test press" << controls[reverseIndex] << endl;
					}

					if (reverseIndex == sizeOfControls)
					{
						reverseIndex = 0;
						txt_cmp[6]->SetText("Reverse: " + controls[reverseIndex]);
					}
					break;
				case 7:
					std::cout << "Option 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					if (brakeIndex >= 0)
					{
						txt_cmp[7]->SetText("Brake: " + controls[brakeIndex]);
						brakeIndex++;
						cout << "test press" << controls[brakeIndex] << endl;
					}

					if (brakeIndex == sizeOfControls)
					{
						brakeIndex = 0;
						txt_cmp[7]->SetText("Brake: " + controls[brakeIndex]);
					}
					break;
				case 8:
					std::cout << "Option 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					if (leftIndex >= 0)
					{
						txt_cmp[8]->SetText("Turn Left: " + controls[leftIndex]);
						leftIndex++;

					}

					if (leftIndex == sizeOfControls)
					{
						leftIndex = 0;
						txt_cmp[8]->SetText("Turn Left: " + controls[leftIndex]);
					}
					break;
				case 9:
					std::cout << "Option 4 pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					if (rightIndex >= 0)
					{
						txt_cmp[9]->SetText("Turn Right" + controls[rightIndex]);
						rightIndex++;
					}

					if (rightIndex == sizeOfControls)
					{
						rightIndex = 0;
						txt_cmp[9]->SetText("Turn Right:" + controls[rightIndex]);
					}
					break;
				case 10:
					std::cout << "Exit Menu pressed" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					pausecmp->active = false;
					pausecmp->active = true;
					pausecmp->submenuActive = false;
					playercmp->controlsEnabled = true;
					aicmp->controlsEnabled = true;
					break;

#pragma endregion

				}

			}
		}
	}
	
#pragma endregion

	

#pragma region Lap Checker


	//Get locations of checkpoint1
	auto s1 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT1)[0]);
	auto s2 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT2)[0]);
	auto s3 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT3)[0]);

	//Get locations of checkpoint2
	auto s4 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT1)[1]);
	auto s5 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT2)[1]);
	auto s6 = ls::getTilePosition(ls::findTiles(ls::CHECKPOINT3)[1]);
	
	//get Finish Tiles
	auto f1 = ls::getTilePosition(ls::findTiles(ls::START)[0]);
	auto f2 = ls::getTilePosition(ls::findTiles(ls::STARTLEFT)[0]);
	auto f3 = ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]);

	auto tileSize = ls::getTileSize();
	auto lt = raceTimer->GetCompatibleComponent<LapTimer>()[0];

	//Check for player crossing 2nd checkpoint
	if (player->getPosition().y > s1.y - tileSize / 2 && player->getPosition().y < s1.y + tileSize / 2) {
		
		if (player->getPosition().x > s1.x - tileSize / 2 && player->getPosition().x < s3.x + tileSize / 2) {
			playeroneCheckpoint = 1;
			//cout << "Checkpoint " << playeroneCheckpoint << " reached" << endl;
		}
	}

	//Check for player crossing 2nd checkpoint
	if (player->getPosition().y > s4.y - tileSize / 2 && player->getPosition().y < s4.y + tileSize / 2) {
		
		if (player->getPosition().x > s4.x - tileSize / 2 && player->getPosition().x < s6.x + tileSize / 2) {

			playeroneCheckpoint = 2;
			//cout << "Checkpoint " << playeroneCheckpoint << " reached" << endl;
		}
	}

	//Check for finish only if both checkpoints have been passed
	if (playeroneCheckpoint == 2) {
		if (player->getPosition().y > f1.y - tileSize / 2 && player->getPosition().y < f3.y + tileSize / 2) {
			if (player->getPosition().x > f1.x - tileSize / 2 && player->getPosition().x < f3.x + tileSize / 2) {

				lt->increaseLapCounter();
				playeroneCheckpoint = 0;

				lt->setLaptime(lt->getCurrentLap());

				lt->reset();

				//Displays current lap times
				//cout << "Current Lap: " << lt->getCurrentLap() << endl;
				//cout << lt->getLapTimes() << endl;

			}
		}
	}


#pragma endregion


#pragma region Check Game End


	//Checks if game is over - will be changed for a variable depending on what player selects when
	//selecting the track - Either 3 or 5
	if (lt->getCurrentLap() == 5) {
		cout << "Race Over" << endl;
		player->setForDelete();
		auto text = raceTimer->GetCompatibleComponent<TextComponent>()[1];
		text->SetText("WINNER!");

		if (counter <= 10) {
			if (counter == 2 || counter == 4 || counter == 6 ) {
				text->SetText("WINNER!");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			}
			else {
				text->SetText("");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			}
		}
		
		if (counter > 6) {
			Engine::ChangeScene(&menuScreen);
		}
		counter++;


		//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
#pragma endregion


#pragma endregion

	Scene::Update(dt);
}

void Level1Scene::Render() {

	ls::render(Engine::GetWindow());
	Scene::Render();
}
