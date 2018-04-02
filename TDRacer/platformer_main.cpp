#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_menu _options.h"
#include "scenes/scene_splash_screen.h"
#include "scenes/scene_select_avatar.h"
#include "scenes/scene_load_screen.h"
#include "scenes/scene_load_profile.h"
#include "scenes/scene_race_menu.h"
#include "SFML/Audio.hpp"

using namespace std;

/****************Menus*********************************/
SplashScreen splashScreen;
MenuScreen menuScreen;
OptionScreen optionScreen;
AvatarScreen avatarScreen;
LoadScreen loadScreen;
LoadProfileScreen loadPScreen;
RaceMenuScreen raceMenuScreen;


/***************Levels********************************/
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;


int main() {

	Engine::Start(1920, 1080, "TD Championship Racer", &splashScreen);
}