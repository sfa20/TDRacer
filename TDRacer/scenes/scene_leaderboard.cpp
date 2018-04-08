//#include "splashScreen.h"
//#include <iostream>
//#include "SFML\Window\Keyboard.hpp"
//#include "../game.h"
//#include "../components/cmp_text.h"
//#include <system_renderer.h>
//#include <system_resources.h>
//#include "../components/cmp_sprite.h"
//
//
//using namespace std;
//using namespace sf;
//using namespace Resources;
//
//Texture splashTexture;
//static std::shared_ptr<Entity> txt;
//
//void SplashScreen::Load()
//{
//	std::cout << "Menu Load \n";
//	{
//		auto splash = makeEntity();
//		auto s = splash->addComponent<SpriteComponent>();
//
//		txt = makeEntity();
//		auto title = txt->addComponent<TextComponent>("TD CHAMPIONSHIP RACER");
//		auto start = txt->addComponent<TextComponent>("PRESS SPACE/CLICK MOUSE TO START");
//
//
//
//		//loads background image with error in console (Game still runs) - Ask Kevin 
//		splashTexture = *Resources::load<Texture>("background.png");
//
//		s->getSprite().setTexture(splashTexture, true);
//		s->getSprite().setScale(1.4, 1.4);
//
//		//Loads background imagae WITHOUT error (unless file is non-existent)
//		/*if (!splashTexture.loadFromFile("background.png", sf::IntRect(0, 0, 1000, 1000)))
//		{
//		std::cerr << "failed to load spritesheet!" << std::endl;
//		}*/
//
//		title->setPos(Engine::getWindowSize().y / 2 + 30, 80, 50);
//		start->setPos(Engine::getWindowSize().y / 2 - 80, 400, 50);
//
//
//	}
//	setLoaded(true);
//}
//
//
//void SplashScreen::Update(const double & dt)
//{
//	auto test = txt->GetCompatibleComponent<TextComponent>();
//
//
//
//	// cout << "Menu Update "<<dt<<"\n";
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//		Engine::ChangeScene(&menu);
//	}
//
//	Scene::Update(dt);
//}
//
