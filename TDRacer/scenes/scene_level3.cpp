#include "scene_level3.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level3Scene::Load() {
	cout << "Scene 3 Load" << endl;
	ls::loadLevelFile("res/level_3.txt", 40.0f);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	// Create player


	

	cout << " Scene 3 Load Done" << endl;
	setLoaded(true);
}

void Level3Scene::UnLoad() {
	cout << "Scene 3 UnLoad" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}



void Level3Scene::Update(const double& dt) {
	Scene::Update(dt);


}

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
