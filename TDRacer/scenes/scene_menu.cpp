#include "engine.h"
#include "ecm.h"
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


sf::Texture texture;


void MenuScene::Load() {

	cout << "Menu Load \n"; {

		//entitys are created in layer order
		//cretes entity for background image

		//********* LAYER 1 *********
		auto bck = makeEntity();
		auto k = bck->addComponent<SpriteComponent>();

		//********* LAYER 2 *********
		//loads background image
		if (!texture.loadFromFile("res/img/background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}

		//sets background image
		k->getSprite().setTexture(texture, true);
		k->getSprite().setScale(1.4, 1.4);


		//creates text entitys
		auto title = makeEntity();
		auto t = title->addComponent<TextComponent>("TD Championship Racer");

		auto sgp = makeEntity();
		auto sg = sgp->addComponent<TextComponent>("Single Player");

		auto mup = makeEntity();
		auto mu = mup->addComponent<TextComponent>("MultiPlayer");

		auto op = makeEntity();
		auto o = op->addComponent<TextComponent>("Options");

		auto ex = makeEntity();
		auto e = ex->addComponent<TextComponent>("Exit");

		//sets positions and size of menu entitys
		t->setPos(430, 50, 50);
		sg->setPos(500, 280, 30);
		mu->setPos(500, 330, 30);
		o->setPos(500, 370, 30);
		e->setPos(500, 420, 30);

		//sets colours of entitys
		t->setColor(255, 0, 0, 200);
		sg->setColor(255, 0, 0, 255);



	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {


	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&level1);


	}

	Scene::Update(dt);
}



