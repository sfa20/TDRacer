#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_menu _options.h"
#include "scenes\scene_splash_screen.h"
#include "SFML\Audio.hpp"

using namespace std;

MenuScene menu;
OptionScene optionsMenu;
SplashScreen splash;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

sf::Music music;

int main() {

	//loads music
	if (!music.openFromFile("res/opening.wav"))
	{
		std::cerr << "failed to load music!" << std::endl;
	}

	music.play();
	music.setVolume(50);

	Engine::Start(1280, 720, "TD Championship Racer", &splash);
}