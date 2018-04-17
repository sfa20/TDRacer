#pragma once

#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_menu _options.h"
#include "scenes/scene_splash_screen.h"
#include "scenes/scene_select_avatar.h"
#include "scenes/scene_load_screen.h"
#include "scenes/scene_load_profile.h"
#include "scenes/scene_race_menu.h"
#include "scenes/scene_track_select.h"
#include "scenes/scene_car_select.h"
#include "scenes/scene_controls.h"
#include "scenes/scene_graphics.h"
#include "scenes/scene_sounds.h"
#include "system_resources.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window/Joystick.hpp"

using namespace std;
using namespace sf;
using namespace Resources;

/****************MENUS*********************************/
SplashScreen splashScreen;
MenuScreen menuScreen;
OptionScreen optionScreen;
AvatarScreen avatarScreen;
LoadScreen loadScreen;
LoadProfileScreen loadPScreen;
RaceMenuScreen raceMenuScreen;
TrackSelectScreen trackSelectScreen;
CarSelectScreen carSelectScreen;
GraphicScreen graphicScreen;
ControlScreen controlScreen;
SoundScreen soundScreen;


/***************LEVELS********************************/
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

bool settingConfirmed = false;
bool nisFullscreen = false;
int nHeight;
int nWidth;

int main() {

	Engine::Start(1980, 1080, "TD Championship Racer", &level1, false);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Engine::Start(nWidth, nHeight, "TD Championship Racer", &splashScreen, nisFullscreen);
	}

}

