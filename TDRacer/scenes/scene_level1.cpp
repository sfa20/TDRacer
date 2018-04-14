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
//#include "../components/cmp_race_countdown.h"

using namespace std;
using namespace sf;
using namespace Resources;

static shared_ptr<Entity> player;
static shared_ptr<Entity> timers;
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


#pragma region Setup Timers

	////	Race Timer	////
	timers = makeEntity();
	//Adds the countdown textbox and timer
	auto textBox1 = timers->addComponent<TextComponent>("3");
	textBox1->setCenterPos(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2, 80.f);
	auto timer1 = timers->addComponent<Timer>();
	timer1->start();

	//Testing
	//auto timer1 = timers->addComponent<CountDown>();
	//timer1->start();

	////
	//Add the RaceTimer Textbox and timer
	auto raceTimerTextBox = timers->addComponent<TextComponent>("Timer: ");
	raceTimerTextBox->setCenterPos(Engine::getWindowSize().x - 400.f, 20.f, 40.f);
	auto timer = timers->addComponent<Timer>();
	////timer->start();
	//Add the lapTimer
	auto lapTimer = timers->addComponent<LapTimer>();
	//lapTimer->start();

#pragma endregion

#pragma region CreatePlayers

	//Create an PlayerCar Entity, add component and set texture
	player = makeEntity();

	//Adds a Sprite component
	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component

	//t->getSprite().setTexture(*Resources::get<Texture>("Black_viper.png"));
	//t->getSprite().setScale(.45f, .45f);

	t->getSprite().setTexture(*Resources::get<Texture>("car_green_small_2.png"));
	t->getSprite().setScale(.45f, .45f);
	t->getSprite().setColor(Color::Red);
	t->getSprite().setOrigin(10,0);

	//Add a Player Physics Component
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(27.9f, 18.f));
	//p->setMass(10);
	
	//Find the starting position 
	p->teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	
	//auto l = ls::findTiles(ls::START);
	//auto lv = ls::getTilePosition(l[0]);

	////Set the players starting position
	//player->setPosition(Vector2f(lv));
	//player->render();

	
#pragma endregion


#pragma region Testing

	auto winnerText = timers->addComponent<TextComponent>(" ");
	winnerText->setCenterPos(Engine::getWindowSize().x / 2.f, Engine::getWindowSize().y / 2, 60.f);

#pragma endregion

	setLoaded(true);
}


void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}


void Level1Scene::Update(const double& dt) {

#pragma region CountDown and StartRace

	auto timer1 = timers->GetCompatibleComponent<Timer>();
	auto textBox1 = timers->GetCompatibleComponent<TextComponent>()[0];
	
	if (timer1[0]->getClock().getElapsedTime().asSeconds() <= 6) {

		auto condition = timer1[0]->getSecs();
		
		cout << condition << endl;
		switch (condition) {
		case 1:
			textBox1->SetText("3");
			break;
		case 2:
			textBox1->SetText("2");
			break;
		case 3:
			textBox1->SetText("1");
			break;
		case 4:
			textBox1->SetText("Go!");
			timer1[1]->reset();
			break;
		case 5:
			textBox1->SetText(" ");
			//timer1[1]->render();
			//player->isEnabled = true;
			break;
		}
	}
	else {
		player->isEnabled = true;
	}


#pragma endregion

	//Only runs once the isenabled is set in the timer section above	
	if (player->isEnabled) {

#pragma region Handle RaceTimer

		//Update the RaceTimer
		timers->update(dt);

		//Get the race timer
		auto timer = timers->GetCompatibleComponent<Timer>()[1];

		//Get the current time
		string time = timer->getTime();

		//Get the text component and set this to the time string created above
		auto timetextBox = timers->GetCompatibleComponent<TextComponent>()[1];
		timetextBox->SetText(time);

		//End of Race Timer

#pragma endregion


#pragma region CheckRaceStatus

	//Player crossing finish triggers new laptime and increments lap counter

		auto s1 = ls::getTilePosition(ls::findTiles(ls::START)[0]);
		auto s2 = ls::getTilePosition(ls::findTiles(ls::STARTLEFT)[0]);
		auto s3 = ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]);

		auto tileSize = ls::getTileSize();

		//get the lap timer added to entity
		auto lt = timers->GetCompatibleComponent<LapTimer>()[0];

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
			auto text = timers->GetCompatibleComponent<TextComponent>()[2];
			text->SetText("WINNER!");

			if (counter <= 10) {
				if (counter == 2 || counter == 4 || counter == 6) {
					text->SetText("WINNER!");
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				}
				else {
					text->SetText("");
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				}
			}

			if (counter > 6) {
				UnLoad();
				Engine::ChangeScene(&level2);
			}
			counter++;


			//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}


#pragma endregion


	}

	Scene::Update(dt);

}

void Level1Scene::Render() {

	ls::render(Engine::GetWindow());
	Scene::Render();
}
