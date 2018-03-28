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


sf::Texture texture;

int countt;


void MenuScene::Load() {

	cout << "Menu Load \n";
	{
		//cretes entity for background image
		auto bck = makeEntity();
		auto k = bck->addComponent<SpriteComponent>();

		//loads background image
		if (!texture.loadFromFile("res/img/background.png", sf::IntRect(0, 0, 1000, 1000)))
		{
			std::cerr << "failed to load spritesheet!" << std::endl;
		}

		//sets background image
		k->getSprite().setTexture(texture, true);
		k->getSprite().setScale(1.4, 1.4);



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

		t->setPos(450, 50);
		sg->setPos(500, 280);
		mu->setPos(500, 330);
		o->setPos(500, 370);
		e->setPos(500, 420);




	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt, RenderWindow) {
	// cout << "Menu Update "<<dt<<"\n";










	Scene::Update(dt);
}

