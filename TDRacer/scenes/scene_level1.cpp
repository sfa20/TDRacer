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
Vector2f Scale;

void Level1Scene::Load() {
	//Load Level File
	ls::loadLevelFile("res/maze.txt", 50.f);
	

#pragma region Setup Map

	Scale = { 0.400f, 0.400f };

	//////////////Added////////////
	auto startTilesLeft = ls::findTiles(ls::STARTLEFT);
	for each (auto t in startTilesLeft) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_right.png"));
		c->getSprite().setScale(Scale);

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
		c->getSprite().setScale(Scale);

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
		c->getSprite().setScale(Scale);

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
			t3->getSprite().setScale(Scale);
	
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
			t3->getSprite().setScale(Scale);
	
			//get tile position - vector2f
			auto g = ls::getTilePosition(t);
			wall->setPosition(g);
	
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
			t2->getSprite().setScale(Scale);
	
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
			t2->getSprite().setScale(Scale);
	
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
			t2->getSprite().setScale(Scale);
	
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
			t2->getSprite().setScale(Scale);
	
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
			t2->getSprite().setScale(Scale);
	
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
			t1->getSprite().setScale(Scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn1->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopRight.png"));
			t2->getSprite().setScale(Scale);
	
	
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
			t1->getSprite().setScale(Scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn2->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopLeft.png"));
			t2->getSprite().setScale(Scale);
	
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
			t1->getSprite().setScale(Scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn3->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomLeft.png"));
			t2->getSprite().setScale(Scale);
	
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
			t1->getSprite().setScale(Scale);
			//Add a new sprite component set texture and scale
			auto t2 = corn4->addComponent<SpriteComponent>();
			t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomRight.png"));
			t2->getSprite().setScale(Scale);
	
	
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
		auto c3 = raceTimer->addComponent<LapTimer>();
		c3->start();
		/*
		auto c3 = raceTimer->addComponent<RaceTimer>();*/
		c2->start();
		/*	c3->start();*/

#pragma endregion


		
#pragma region CreatePlayer 

	//Create an PlayerCar Entity, add component and set texture
	player = makeEntity();

	//Adds a Sprite component
	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component

	t->getSprite().setTexture(*Resources::load<Texture>("car_green_small_2.png"));
	t->getSprite().setScale(0.5f, 0.5);
	t->getSprite().setColor(Color::Red);

	//Add a Player Physics Component
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));

	//Find the starting position 
	auto l = ls::findTiles(ls::START);
	auto lv = ls::getTilePosition(l[0]);

	//Set the players starting position
	player->setPosition(Vector2f(200,200));

#pragma endregion

}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;

	Scene::UnLoad();
}


void Level1Scene::Update(const double& dt) {

	//Update the RaceTimer
	raceTimer->update(dt);
	
	//Get the race timer
	auto a = raceTimer->GetCompatibleComponent<Timer>()[0];

	//Get the current time
	string time = a->getTime();

	//Get the text component and set this to the time string created above
	auto b = raceTimer->GetCompatibleComponent<TextComponent>()[0];
	b->SetText(time);

	//End of Race Timer


	//testing player going over finish
	
	auto s1 = ls::getTilePosition(ls::findTiles(ls::START)[0]);
	auto s2 = ls::getTilePosition(ls::findTiles(ls::STARTLEFT)[0]);
	auto s3 = ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]);

	auto tileSize = ls::getTileSize();

	//get the second race timer added to entity
	auto lt = raceTimer->GetCompatibleComponent<LapTimer>()[0];
	
	//New Lap Incrementor - will increment when player goes over the finsih
	if (player->getPosition().y > s2.y - tileSize / 2 && player->getPosition().y < s3.y + tileSize / 2) {
		if (player->getPosition().x > s2.x - tileSize / 2 && player->getPosition().x < s3.x + tileSize / 2) {
			
			auto j = lt->getLapCounter();
			
			if (j) {
				
				lt->setLapCounter(false);
				lt->setLaptime(lt->getCurrentLap());

				lt->reset();
				lt->increaseLapCounter();
				
				cout << "Current Lap: " << lt->getCurrentLap() << endl;
				cout << lt->getLapTimes() << endl;
			}
		}
	}

	lt->temp = lt->getClock().getElapsedTime().asMilliseconds();
	if (lt->temp > 10000) {
		lt->setLapCounter(true);
	}

	//cout << to_string(lt->temp) << endl;

	//auto s11 = ls::getTileAt(playerpos);
		//cout << p << endl;

	//Lap Incrementer - will be replaced with player going over the line
	/*if (a->getMins() >= a->getCurrentLap()) {
		if (a->getSecs() <= 1) {
			a->setLaptime(a->getCurrentLap());
			a->setCurrentLap();
		}
	}*/

	/*cout << a->getLapTimes() << endl;*/




	Scene::Update(dt);
}

void Level1Scene::Render() {

	ls::render(Engine::GetWindow());
	Scene::Render();
}
