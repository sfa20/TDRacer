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

	//float size = 50.f;

	////CheckScreenRes();

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
	//}

	//Load Level File
	ls::loadLevelFile("res/track_1.txt", 50.f);


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
	//
	//	auto startTilesRight = ls::findTiles(ls::STARTRIGHT);
	//	for each (auto t in startTilesRight) {
	//		static shared_ptr<Entity> start;
	//		start = makeEntity();
	//		//add a new sprite component, set texture and scale
	//		auto c = start->addComponent<SpriteComponent>();
	//		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_left.png"));
	//		c->getSprite().setScale(scale);
	//
	//		//get tile position - vector 2f
	//		auto p = ls::getTilePosition(t);
	//		start->setPosition(p);
	//	}
	//
	//	auto startTiles = ls::findTiles(ls::START);
	//	for each (auto t in startTiles) {
	//		static shared_ptr<Entity> start;
	//		start = makeEntity();
	//		//add a new sprite component, set texture and scale
	//		auto c = start->addComponent<SpriteComponent>();
	//		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder.png"));
	//		c->getSprite().setScale(scale);
	//
	//		//get tile position - vector 2f
	//		auto p = ls::getTilePosition(t);
	//		start->setPosition(p);
	//	}
	//
	//
	//	///////////////////////////////////////
	//
	//
	//	//Get position of grass tiles and set sprites to each position
	//	auto grassTiles = ls::findTiles(ls::GRASS);
	//	for each (auto t in grassTiles)
	//	{
	//		static shared_ptr<Entity> grass;
	//		grass = makeEntity();
	//		//Add a new sprite component set texture and scale
	//		auto t3 = grass->addComponent<SpriteComponent>();
	//		t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t3->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		grass->setPosition(g);
	//
	//	}
	//
	//	auto wallTiles = ls::findTiles(ls::WALL);
	//	for each (auto t in wallTiles)
	//	{
	//		static shared_ptr<Entity> wall;
	//		wall = makeEntity();
	//		//Add a new sprite component set texture and scale
	//		auto t3 = wall->addComponent<SpriteComponent>();
	//		t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t3->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		wall->setPosition(g);
	//
	//	}
	//
	//
	//	//Get position of TopTrack tiles and set sprites to each postition
	//	auto peakTiles = ls::findTiles(ls::TOP);
	//	for each (auto t in peakTiles)
	//	{
	//		static shared_ptr<Entity> peak;
	//		peak = makeEntity();
	//		//Add a new sprite component set texture and scale
	//		auto t2 = peak->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_bottom.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		peak->setPosition(g);
	//
	//	}
	//
	//	//Get position of BottomTrack tiles and set sprites to each postition
	//	auto bottomTiles = ls::findTiles(ls::BOTTOM);
	//	for each (auto t in bottomTiles)
	//	{
	//		static shared_ptr<Entity> bottom;
	//		bottom = makeEntity();
	//
	//		//Add a new sprite component set texture and scale
	//		auto t2 = bottom->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_top.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		bottom->setPosition(g);
	//
	//	}
	//
	//	//Get position of RightTrack tiles and set sprites to each postition
	//	auto rightTiles = ls::findTiles(ls::RIGHT);
	//	for each (auto t in rightTiles)
	//	{
	//		static shared_ptr<Entity> right;
	//		right = makeEntity();
	//
	//		//Add a new sprite component set texture and scale
	//		auto t2 = right->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_left.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		right->setPosition(g);
	//	}
	//
	//	//Get position of LeftTrack tiles and set sprites to each postition
	//	auto leftTiles = ls::findTiles(ls::LEFT);
	//	for each (auto t in leftTiles)
	//	{
	//		static shared_ptr<Entity> left;
	//		left = makeEntity();
	//		//Add a new sprite component set texture and scale
	//		auto t2 = left->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_right.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		left->setPosition(g);
	//
	//	}
	//
	//	//Get position of track tiles and set sprites to each postition
	//	auto trackTiles = ls::findTiles(ls::TRACK);
	//	for each (auto t in trackTiles)
	//	{
	//		static shared_ptr<Entity> track;
	//		track = makeEntity();
	//		//Add a new sprite component set texture and scale
	//		auto t2 = track->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		track->setPosition(g);
	//
	//	}
	//
	//	//Get position of Corner tiles and set sprites to each postition
	//	auto corner1Tiles = ls::findTiles(ls::CORNER1);
	//	for each (auto t in corner1Tiles)
	//	{
	//		static shared_ptr<Entity> corn1;
	//		corn1 = makeEntity();
	//
	//		auto t1 = corn1->addComponent<SpriteComponent>();
	//		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t1->getSprite().setScale(scale);
	//		//Add a new sprite component set texture and scale
	//		auto t2 = corn1->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopRight.png"));
	//		t2->getSprite().setScale(scale);
	//
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		corn1->setPosition(g);
	//
	//	}
	//
	//	//Get position of track tiles and set sprites to each postition
	//	auto corner2Tiles = ls::findTiles(ls::CORNER2);
	//	for each (auto t in corner2Tiles)
	//	{
	//		static shared_ptr<Entity> corn2;
	//		corn2 = makeEntity();
	//		auto t1 = corn2->addComponent<SpriteComponent>();
	//		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t1->getSprite().setScale(scale);
	//		//Add a new sprite component set texture and scale
	//		auto t2 = corn2->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopLeft.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		corn2->setPosition(g);
	//
	//	}
	//
	//	//Get position of track tiles and set sprites to each postition
	//	auto corner3Tiles = ls::findTiles(ls::CORNER3);
	//	for each (auto t in corner3Tiles)
	//	{
	//		static shared_ptr<Entity> corn3;
	//		corn3 = makeEntity();
	//		auto t1 = corn3->addComponent<SpriteComponent>();
	//		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t1->getSprite().setScale(scale);
	//		//Add a new sprite component set texture and scale
	//		auto t2 = corn3->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomLeft.png"));
	//		t2->getSprite().setScale(scale);
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		corn3->setPosition(g);
	//
	//	}
	//
	//	//Get position of track tiles and set sprites to each postition
	//	auto corner4Tiles = ls::findTiles(ls::CORNER4);
	//	for each (auto t in corner4Tiles)
	//	{
	//		static shared_ptr<Entity> corn4;
	//		corn4 = makeEntity();
	//		auto t1 = corn4->addComponent<SpriteComponent>();
	//		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
	//		t1->getSprite().setScale(scale);
	//		//Add a new sprite component set texture and scale
	//		auto t2 = corn4->addComponent<SpriteComponent>();
	//		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomRight.png"));
	//		t2->getSprite().setScale(scale);
	//
	//
	//		//get tile position - vector2f
	//		auto g = ls::getTilePosition(t);
	//		corn4->setPosition(g);
	//
	//	}
	//
	//
	//
	//#pragma endregion
	//
	//
	//#pragma region Setup Timer
	//
	//	raceTimer = makeEntity();
	//	auto c = raceTimer->addComponent<TextComponent>("Timer: ");
	//	c->setCenterPos(Engine::getWindowSize().x - 400.f, 20.f, 40.f);
	//	auto c2 = raceTimer->addComponent<Timer>();
	//	c2->start();
	//	auto c3 = raceTimer->addComponent<LapTimer>();
	//	c3->start();
	//
	//#pragma endregion
	//
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
	/*Scene::Update(dt);
	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::TRACK) {
		Engine::ChangeScene((Scene*)&level3);
	}
	else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level2);
	}*/
}

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
