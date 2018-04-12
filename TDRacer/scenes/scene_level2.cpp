#include "scene_level2.h"
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

static shared_ptr<Entity> player;
static shared_ptr<Entity> raceTimer;


void Level2Scene::Load() {
	cout << "Scene 2 Load" << endl;
	float size = 50.f;
#pragma region CheckResolution
	//CheckScreenRes();

	//cout << to_string(nWidth) << endl;
	//cout << to_string(nHeight) << endl;

	//if (nWidth == 1920 && nHeight == 1080) {
	//	scale = { 0.400f, 0.400f };
	//	size = 50.f;
	//}
	//else if (nWidth == 1280 && nHeight == 720) {
	//	scale = { 0.395f, 0.395f };
	//	size = 34.f;
	//	cout << scale << endl;
	//	cout << size << endl;
	//}
	//else if (nWidth == 1024 && nHeight == 600) {
	//	scale = { 0.300f, 0.300f };
	//	size = 28.f;
	/*}*/

#pragma endregion


#pragma region Setup Map

	//Load Level File
	ls::loadLevelFile("res/track_2.txt", size);
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
	
	//
	//#pragma region CreatePlayer 
	//
	//	//Create an PlayerCar Entity, add component and set texture
	//	player = makeEntity();
	//
	//	//Adds a Sprite component
	//	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component
	//
	//	t->getSprite().setTexture(*Resources::get<Texture>("Black_viper.png"));
	//	t->getSprite().setScale(.45f, .45f);
	//	t->getSprite().setColor(Color::Red);
	//
	//	t->getSprite().setOrigin(20, 0);
	//
	//	//Add a Player Physics Component
	//	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
	//	p->setMass(10);
	//
	//	//Find the starting position 
	//	auto l = ls::findTiles(ls::START);
	//	auto lv = ls::getTilePosition(l[0]);
	//
	//	//Set the players starting position
	//	player->setPosition(Vector2f(200, 200));
	//
#pragma endregion


#pragma region Testing





#pragma endregion



	setLoaded(true);
}

void Level2Scene::UnLoad() {
	cout << "Scene 2 UnLoad" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
	Scene::Update(dt);
	//const auto pp = player->getPosition();
	//if (ls::getTileAt(pp) == ls::TRACK) {
	//	Engine::ChangeScene((Scene*)&level3);
	//}
	//else if (!player->isAlive()) {
	//	Engine::ChangeScene((Scene*)&level2);
	//}
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
