
#pragma once

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

/****************Menus*********************************/
extern SplashScreen splashScreen;
extern MenuScreen menuScreen;
extern OptionScreen optionScreen;
extern LoadScreen loadScreen;
extern LoadProfileScreen loadPScreen;
extern AvatarScreen avatarScreen;
extern RaceMenuScreen raceMenuScreen;


/***************Levels********************************/
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
