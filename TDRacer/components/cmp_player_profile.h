#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class PlayerProfile : public Component {
private:
	std::string playerName;
	int selectedAvatar;
	int selectedCar;
	//settings
	int selectedResWidth;
	int selectedResHeight;
	int selectedVsync;

	std::string trackOne[5];
	std::string trackOne[5];
	std::string trackOne[5];


public:
	PlayerProfile(Entity* p);

	std::string getPlayerName();
	int getSelectedAvatar();
	int getSelectedCar();
	int getSelectedResWidth();
	int getSelectedResHeight();
	int getSelectedVSync();

	void setSelectedAvatar(int avatar);
	void setSelectedCar(int car);
	void setSelectedResWidth(int width);
	void setSelectedResHeight(int height);
	void setSelectedVsync(bool isOn);

	void setPlayerName(std::string name);

	void setTrackOne();
	void setTrackTwo();
	void setTrackThree();

	std::string getTrackTimes(int trackNo);

	//Export Details();

};
