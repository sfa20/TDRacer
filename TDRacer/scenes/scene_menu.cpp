#include "engine.h"
#include "ecm.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "scene_menu.h"
#include "../components/cmp_player_physics.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;
using namespace Resources;

Texture texture;

static shared_ptr<Entity> mainmenu;

void MenuScene::Load() {

	cout << "Menu Load \n"; {

		//entitys are created in layer order
		//cretes entity for background image

		//********* LAYER 1 *********
		mainmenu = makeEntity();
		auto s = mainmenu->addComponent<SpriteComponent>();

		//********* LAYER 2 *********
		//loads background image
		texture = *Resources::load<Texture>("background.png");

		//sets background image
		s->getSprite().setTexture(texture, true);
		s->getSprite().setScale(1.4, 1.4);


		//creates text entitys
	//	auto menu = makeEntity();
		mainmenu->addComponent<TextComponent>("TD Championship Racer");
		mainmenu->addComponent<TextComponent>("Single Player");
		mainmenu->addComponent<TextComponent>("MultiPlayer");
		mainmenu->addComponent<TextComponent>("Options");	
		mainmenu->addComponent<TextComponent>("Exit");

		//sets positions and size of menu entitys
		auto list = mainmenu->GetCompatibleComponent<TextComponent>();
		list[0]->setPos(430, 50, 50);
		list[1]->setPos(500, 280, 30);
		list[2]->setPos(500, 330, 30);
		list[3]->setPos(500, 370, 30);
		list[4]->setPos(500, 420, 30);

		//sets colours of entitys
		list[0]->setColor(255, 0, 0, 200);
		list[1]->setColor(255, 0, 0, 255);

	}
	selectedItemIndex = 0; //added - sfa20
	setLoaded(true);
}

void MenuEvents() {
	//sf::Event event;

	//sf::Vector2i mousePos = sf::Mouse::getPosition();
	//sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void MenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Scene::Update(dt);
	}

	//Scene::Update(dt);
}



