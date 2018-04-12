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

using namespace std;
using namespace sf;
using namespace Resources;

static shared_ptr<Entity> player;
static shared_ptr<Entity> raceTimer;
static shared_ptr<Entity> WinnerMessage;

sf::Vector2f scale = { 0.400f, 0.400f };
int counter = 0;

void Level1Scene::Load() {

	float size = 50.f;


#pragma region CheckScreen Resolution
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


#pragma endregion


#pragma region Setup Map
	//Load Level File
	ls::loadLevelFile("res/track_1.txt", size);
	MapSetup();

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

	//Adds a Sprite component
	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component

	//t->getSprite().setTexture(*Resources::get<Texture>("Black_viper.png"));
	//t->getSprite().setScale(.45f, .45f);

	t->getSprite().setTexture(*Resources::get<Texture>("car_green_small_2.png"));
	t->getSprite().setScale(.45f, .45f);
	t->getSprite().setColor(Color::Red);
	 
	auto spritesize = t->getSprite().getGlobalBounds();
	Vector2f spritesize2 = { 27.9f, 18.f };

	t->getSprite().setOrigin(10,0);

	//Add a Player Physics Component
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(27.9f, 18.f));
	//p->setMass(10);
	
	//Find the starting position 
	auto l = ls::findTiles(ls::START);
	auto lv = ls::getTilePosition(l[0]);

	//Set the players starting position
	player->setPosition(Vector2f(lv));

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

	//get the second race timer added to entity

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
