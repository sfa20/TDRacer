#include "cmp_player_profile.h"
#include "ecm.h"


PlayerProfile::PlayerProfile(Entity* p) : Component(p) {

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

void PlayerProfile::setSelectedResWidth(int width)
{
	selectedResWidth = width;
}

int PlayerProfile::getSelectedResWidth()
{
	return selectedResWidth;
}

void PlayerProfile::setSelectedResHeight(int height)
{
	selectedResHeight = height;
}

int PlayerProfile::getSelectedResHeight()
{
	return selectedResHeight;
}

void PlayerProfile::setSelectedVsync(bool isOn)
{
	selectedVsync = isOn;
}

int PlayerProfile::getSelectedVSync()
{
	return selectedVsync;
}


int PlayerProfile::getSelectedCar() {
	return selectedCar;
}








