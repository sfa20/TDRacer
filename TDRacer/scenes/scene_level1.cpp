#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;
using namespace Resources;

Texture texture1;
static shared_ptr<Entity> test;

void Level1Scene::Load() {

	ls::loadLevelFile("res/maze_2.txt", 10.f);


	/*test = makeEntity();
	auto t = test->addComponent<SpriteComponent>();

	texture1 = *Resources::load<Texture>("car_green_small_2.png");

	t->getSprite().setTexture(texture1);
*/

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
