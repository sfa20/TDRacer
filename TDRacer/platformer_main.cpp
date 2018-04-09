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
	/*****************TEXTURES*****************/
	*Resources::load<Texture>("grass.png");
	*Resources::load<Texture>("Straights/straight_noBorder.png");
	*Resources::load<Texture>("Straights/straight_horizontal_noBorder_bottom.png");
	*Resources::load<Texture>("Straights/straight_horizontal_noBorder_top.png");
	*Resources::load<Texture>("Corners/90DegreeTopRight.png");
	*Resources::load<Texture>("Corners/90DegreeTopLeft.png");
	*Resources::load<Texture>("Corners/90DegreeBottomLeft.png");
	*Resources::load<Texture>("Corners/90DegreeBottomRight.png");
	*Resources::load<Texture>("Straights/straight_vertical_noBorder_right.png");
	*Resources::load<Texture>("Straights/straight_vertical_noBorder_left.png");
	*Resources::load<Texture>("sfml.png");
	*Resources::load<Texture>("box2d.png");
	*Resources::load<Texture>("Straights/startLine_vertical_noBorder_left.png");
	*Resources::load<Texture>("Straights/startLine_vertical_noBorder.png");
	*Resources::load<Texture>("Straights/startLine_vertical_noBorder_right.png");
}


	/*****************SOUND EFFECTS*****************/
	*Resources::load<SoundBuffer>("opening.wav");
	*Resources::load<SoundBuffer>("beep.wav");

	Engine::Start(1920, 1080, "TD Championship Racer", &splashScreen, nisFullscreen);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Engine::Start(nWidth, nHeight, "TD Championship Racer", &splashScreen, nisFullscreen);
	}



}

