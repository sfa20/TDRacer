#pragma once
#include "SFML\Graphics.hpp"
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_menu _options.h"
#include "scenes/scene_splash_screen.h"
#include "scenes/scene_select_avatar.h"
#include "scenes/scene_load_screen.h"
#include "scenes/scene_load_profile.h"
#include "scenes/scene_race_menu.h"
#include "scenes/scene_track_select.h"
#include "scenes/scene_car_select.h"
#include "scenes/scene_sounds.h"
#include "scenes/scene_controls.h"
#include "scenes/scene_graphics.h"
#include "engine.h"
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include "system_resources.h"
#include "system_physics.h"
#include "components\cmp_player_controls.h"



/************************MENUS*************************/
extern SplashScreen splashScreen;
extern MenuScreen menuScreen;
extern OptionScreen optionScreen;
extern LoadScreen loadScreen;
extern LoadProfileScreen loadPScreen;
extern AvatarScreen avatarScreen;
extern RaceMenuScreen raceMenuScreen;
extern TrackSelectScreen trackSelectScreen;
extern CarSelectScreen carSelectScreen;
extern SoundScreen soundScreen;
extern GraphicScreen graphicScreen;
extern ControlScreen controlScreen;

/******************RACES*****************************/
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;


/****************SETTINGS****************************/
extern bool settingConfirmed;
extern bool nisFullscreen;
extern int nHeight;
extern int nWidth;


extern std::map<int, std::string> KeyValues;
extern std::map<std::string, int > KeyValues2;

extern std::map<std::string, MyKeys> Keys;
extern MyKeys key;

extern int sizeOfControls;
extern std::string * controls;
extern int * controlsReverse;

extern sf::Keyboard::Key forwardA;
extern sf::Keyboard::Key backA;
extern sf::Keyboard::Key leftA;
extern sf::Keyboard::Key rightA;
extern sf::Keyboard::Key forwardB;
extern sf::Keyboard::Key backB;
extern sf::Keyboard::Key leftB;
extern sf::Keyboard::Key rightB;
extern sf::Keyboard::Key handbrakeA;
extern sf::Keyboard::Key handbrakeB;

//extern const int32 velocityIterations;
//extern const int32 positionIterations;