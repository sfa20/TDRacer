#include "engine.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "scene_menu.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

sf::Sprite sprite;
sf::Texture texture;


void MenuScene::Load() {

	cout << "Menu Load \n";
	{
		auto bck = makeEntity();
		auto k = bck->addComponent<SpriteComponent>();

		//loads background image
		if (!texture.loadFromFile("res/img/background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}


		k->getSprite().setTexture(texture, true);



		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"TD Championship Racer");


	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&level1);
	}

	Scene::Update(dt);
}