#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include <system_physics.h>
#include "LevelSystem.h"
#include <fstream>
#include <iostream>

#include "../components/cmp_car_body.h"

using namespace std;
using namespace sf;
using namespace Resources;

Texture texture1;
Texture roadTexture;
Texture peakTexture;
Texture rightTexture;
Texture leftTexture;
Texture bottomTexture;
Texture cornerTexture1;
Texture cornerTexture2;
Texture cornerTexture3;
Texture cornerTexture4;
Texture grassTexture;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
	//Load Level File
	ls::loadLevelFile("res/maze.txt", 50.f);
	

#pragma region LoadTextures

	//Loads background imagae WITHOUT error (unless file is non-existent)
	if (!roadTexture.loadFromFile("res/img/Straights/straight_noBorder.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!peakTexture.loadFromFile("res/img/Straights/straight_horizontal_noBorder_bottom.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!rightTexture.loadFromFile("res/img/Straights/straight_vertical_noBorder_left.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!leftTexture.loadFromFile("res/img/Straights/straight_vertical_noBorder_right.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!bottomTexture.loadFromFile("res/img/Straights/straight_horizontal_noBorder_top.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!cornerTexture1.loadFromFile("res/img/Corners/90DegreeTopRight.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!cornerTexture2.loadFromFile("res/img/Corners/90DegreeTopLeft.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!cornerTexture3.loadFromFile("res/img/Corners/90DegreeBottomLeft.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!cornerTexture4.loadFromFile("res/img/Corners/90DegreeBottomRight.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}
	if (!grassTexture.loadFromFile("res/img/grass.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cerr << "failed to load spritesheet!" << std::endl;
	}


#pragma endregion


#pragma region MapSetup

	//Get position of grass tiles and set sprites to each position
	auto grassTiles = ls::findTiles(ls::GRASS);
	for each (auto t in grassTiles)
	{
		static shared_ptr<Entity> grass;
		grass = makeEntity();
		//Add a new sprite component set texture and scale
		auto t3 = grass->addComponent<SpriteComponent>();
		t3->getSprite().setTexture(grassTexture);
		t3->getSprite().setScale(0.400f,0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		grass->setPosition(g);
//		t3->getSprite().setPosition(g);

	}

	auto wallTiles = ls::findTiles(ls::WALL);
	for each (auto t in wallTiles)
	{
		static shared_ptr<Entity> wall;
		wall = makeEntity();
		//Add a new sprite component set texture and scale
		auto t3 = wall->addComponent<SpriteComponent>();
		t3->getSprite().setTexture(grassTexture);
		t3->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		wall->setPosition(g);
//		t3->getSprite().setPosition(g);

	}

	//Get position of TopTrack tiles and set sprites to each postition
	auto peakTiles = ls::findTiles(ls::TOP);
	for each (auto t in peakTiles)
	{
		static shared_ptr<Entity> peak;
		peak = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = peak->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(peakTexture);
		t2->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		peak->setPosition(g);
//		t2->getSprite().setPosition(g);
		

	}

	//Get position of BottomTrack tiles and set sprites to each postition
	auto bottomTiles = ls::findTiles(ls::BOTTOM);
	for each (auto t in bottomTiles)
	{
		static shared_ptr<Entity> bottom;
		bottom = makeEntity();

		//Add a new sprite component set texture and scale
		auto t2 = bottom->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(bottomTexture);
		t2->getSprite().setScale(0.400f, 0.400f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		bottom->setPosition(g);

//		t2->getSprite().setPosition(g);

	}

	//Get position of RightTrack tiles and set sprites to each postition
	auto rightTiles = ls::findTiles(ls::RIGHT);
	for each (auto t in rightTiles)
	{
		static shared_ptr<Entity> right;
		right = makeEntity();

		//Add a new sprite component set texture and scale
		auto t2 = right->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(rightTexture);
		t2->getSprite().setScale(0.195f, 0.195f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		right->setPosition(g);
//		t2->getSprite().setPosition(g);

	}

	//Get position of LeftTrack tiles and set sprites to each postition
	auto leftTiles = ls::findTiles(ls::LEFT);
	for each (auto t in leftTiles)
	{
		static shared_ptr<Entity> left;
		left = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = left->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(leftTexture);
		t2->getSprite().setScale(0.195f, 0.195f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		left->setPosition(g);
//		t2->getSprite().setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto trackTiles = ls::findTiles(ls::TRACK);
	for each (auto t in trackTiles)
	{
		static shared_ptr<Entity> track;
		track = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = track->addComponent<SpriteComponent>(); 
		t2->getSprite().setTexture(roadTexture);
		t2->getSprite().setScale(0.195f, 0.195f);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		track->setPosition(g);
//		t2->getSprite().setPosition(g);
	
	}
	
	//Get position of Corner tiles and set sprites to each postition
	auto corner1Tiles = ls::findTiles(ls::CORNER1);
	for each (auto t in corner1Tiles)
	{
		static shared_ptr<Entity> corn1;
		corn1 = makeEntity();

		auto t1 = corn1->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(grassTexture);
		t1->getSprite().setScale(0.195f, 0.195f);
		//Add a new sprite component set texture and scale
		auto t2 = corn1->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(cornerTexture1);
		t2->getSprite().setScale(0.195f, 0.195f);
		

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn1->setPosition(g);
//		t1->getSprite().setPosition(g);
		t2->getSprite().setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto corner2Tiles = ls::findTiles(ls::CORNER2);
	for each (auto t in corner2Tiles)
	{
		static shared_ptr<Entity> corn2;
		corn2 = makeEntity();
		auto t1 = corn2->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(grassTexture);
		t1->getSprite().setScale(0.195f, 0.195f);
		//Add a new sprite component set texture and scale
		auto t2 = corn2->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(cornerTexture2);
		t2->getSprite().setScale(0.195f, 0.195f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn2->setPosition(g);
//		t1->getSprite().setPosition(g);
//		t2->getSprite().setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto corner3Tiles = ls::findTiles(ls::CORNER3);
	for each (auto t in corner3Tiles)
	{
		static shared_ptr<Entity> corn3;
		corn3 = makeEntity();
		auto t1 = corn3->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(grassTexture);
		t1->getSprite().setScale(0.195f, 0.195f);
		//Add a new sprite component set texture and scale
		auto t2 = corn3->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(cornerTexture3);
		t2->getSprite().setScale(0.195f, 0.195f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn3->setPosition(g);
//		t1->getSprite().setPosition(g);
//		t2->getSprite().setPosition(g);

	}
	
	//Get position of track tiles and set sprites to each postition
	auto corner4Tiles = ls::findTiles(ls::CORNER4);
	for each (auto t in corner4Tiles)
	{
		static shared_ptr<Entity> corn4;
		corn4 = makeEntity();
		auto t1 = corn4->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(grassTexture);
		t1->getSprite().setScale(0.195f, 0.195f);
		//Add a new sprite component set texture and scale
		auto t2 = corn4->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(cornerTexture4);
		t2->getSprite().setScale(0.195f, 0.195f);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn4->setPosition(g);
//		t1->getSprite().setPosition(g);
//		t2->getSprite().setPosition(g);

	}
	//Get vector2f position of the first tile in startpos
//	test2->setPosition(ls::getTilePosition(corner1Tiles[0]));


#pragma endregion


#pragma region CreatePlayer 

//	Create an PlayerCar Entity, add component and set texture
	player = makeEntity();

	//Adds a Sprite component
	auto t = player->addComponent<SpriteComponent>(); //Add a sprite component
//  	t->setBody(); //Set the b2d body
	texture1 = *Resources::load<Texture>("car_green_small_2.png");
	t->getSprite().setTexture(texture1);
	t->getSprite().setScale(0.5f, 0.5);
	t->getSprite().setColor(Color::Red);

	//Find the starting position (will update once start line is added
	auto l = ls::findTiles(ls::CORNER1);
	auto lv = ls::getTilePosition(l[0]);

	//Add a Player Physics Component
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
	p->setMass(400.f);
	p->setFriction(400.f);
	p->setRestitution(400.f);
	//Set the players starting position
	player->setPosition(lv);


	//Testing with multiple shapes
	//player = makeEntity();
	//auto s1 = player->addComponent<ShapeComponent>();
	//s1->setShape<RectangleShape>(RectangleShape(Vector2f(100.f,100.f)));
	//s1->getShape().setFillColor(Color::Green);
	//auto s2 = player->addComponent<ShapeComponent>();
	//s2->setShape<CircleShape>(CircleShape(50.f));
	//s2->getShape().setFillColor(Color::Red);
	//auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));
	//player->setPosition(lv);

#pragma endregion

}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;

	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	Scene::Update(dt);
}

void Level1Scene::Render() {

	ls::render(Engine::GetWindow());
	Scene::Render();
}
