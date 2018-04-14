#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class PlayerProfile : public Component {
private:
	std::string playerName;
	int selectedAvatar;
	int selectedCar;
	
	std::string trackOne[5];
	std::string trackTwo[5];
	std::string trackThree[5];

	sf::Sprite playerAvatar;


public:
	PlayerProfile(Entity* p);

	std::string getPlayerName();
	int getSelectedAvatar();
	int getSelectedCar();

	void setSelectedAvatar(int avatar);
	void setSelectedCar(int car);

	void setPlayerName(std::string name);

	void setTrackOne();
	void setTrackTwo();
	void setTrackThree();

	std::string getTrackTimes(int trackNo);

	//Export Details();

};
