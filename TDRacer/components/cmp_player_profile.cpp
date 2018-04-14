#include "cmp_player_profile.h"
#include "ecm.h"


PlayerProfile::PlayerProfile(Entity* p) : Component(p){

}

void PlayerProfile::setPlayerName(std::string name) {
	playerName = name;
}

std::string PlayerProfile::getPlayerName() {
	return playerName;
}

void PlayerProfile::setSelectedAvatar(int avatar) {
	selectedAvatar = avatar;
}

int PlayerProfile::getSelectedAvatar() {
	return selectedAvatar;
}

void PlayerProfile::setSelectedCar(int car) {
	selectedCar = car;
}

int PlayerProfile::getSelectedCar() {
	return selectedCar;
}



