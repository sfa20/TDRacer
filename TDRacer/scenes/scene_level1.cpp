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

using namespace std;
using namespace sf;
using namespace Resources;

static shared_ptr<Entity> player;
static shared_ptr<Entity> ai;

static shared_ptr<Entity> raceTimer;
static shared_ptr<Entity> WinnerMessage;

std::map<int, std::string> KeyValues;





sf::Vector2f scale = { 0.400f, 0.400f };
int counter = 0;


void Level1Scene::Load() {

	float size = 50.f;

#pragma region Check Screen Resolution
	//CheckScreenRes();

	cout << to_string(nWidth) << endl;
	cout << to_string(nHeight) << endl;

	if (nWidth == 1920 && nHeight == 1080) {
		scale = { 0.400f, 0.400f };
		size = 50.f;
	}
	else if (nWidth == 1280 && nHeight == 720) {
		scale = { 0.395f, 0.395f };
		size = 34.f;
		cout << scale << endl;
		cout << size << endl;
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
	t->getSprite().setTexture(*Resources::get<Texture>("car_green_small_2.png"));
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
	ait->getSprite().setTexture(*Resources::get<Texture>("car_green_small_2.png"));
	ait->getSprite().setScale(.45f, .45f);
	ait->getSprite().setColor(Color::Red);
	ait->getSprite().setOrigin(10, 0);

	//Add a player controls component - This allows the user to have different controls
	//for accel, brake etc and will allow these to be dynamically changed through an
	//options menu
	auto aictrl = player->addComponent<PlayerControls>();
	//aictrl->ChangeControls("Accelerate", KeyValues[2]);
	//KeyValues[2];

	//aictrl->
	//auto a = KeyValues[1];

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

	//Player crossing finish triggers new laptime and increments lap counter
	auto s1 = ls::getTilePosition(ls::findTiles(ls::START)[0]);
	auto s2 = ls::getTilePosition(ls::findTiles(ls::STARTLEFT)[0]);
	auto s3 = ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]);

	auto tileSize = ls::getTileSize();

	//get the race timer added to entity
	auto lt = raceTimer->GetCompatibleComponent<LapTimer>()[0];

	//New Lap Incrementor - will increment when player goes over the finsih
	if (player->getPosition().y > s2.y - tileSize / 2 && player->getPosition().y < s3.y + tileSize / 2) {
		if (player->getPosition().x > s2.x - tileSize / 2 && player->getPosition().x < s3.x + tileSize / 2) {

			auto lapCounter = lt->getLapCounter();

			if (lapCounter) {

				lt->setLapCounter(false);
				lt->setLaptime(lt->getCurrentLap());

				lt->reset();
				lt->increaseLapCounter();

				//Displays current lap times
				cout << "Current Lap: " << lt->getCurrentLap() << endl;
				cout << lt->getLapTimes() << endl;
			}
		}
	}

	//Prevents a player going back and forward over the line  //Need a better way to handle this
	lt->temp = lt->getClock().getElapsedTime().asMilliseconds();
	if (lt->temp > 10000) {
		lt->setLapCounter(true);
	}


	//Checks if game is over - will be changed for a variable depending on what player selects when
	//selecting the track - Either 3 or 5
	if (lt->getCurrentLap() == 3) {
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

	Scene::Update(dt);
}

void Level1Scene::Render() {

	ls::render(Engine::GetWindow());
	Scene::Render();
}
