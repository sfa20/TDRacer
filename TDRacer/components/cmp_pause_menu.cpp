#include "cmp_pause_menu.h"
#include "engine.h"
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

PauseMenu::PauseMenu(Entity* p) : Component(p) {
	
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");

	auto textComps = _parent->GetCompatibleComponent<TextComponent>();

	textComps[0]->setCenterPos(Engine::getWindowSize().x / 2.f, 200.f, 50.f);
	textComps[1]->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
	textComps[2]->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
	textComps[3]->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);
	textComps[4]->setCenterPos(Engine::getWindowSize().x / 2.f, 670.f, 50.f);
	textComps[1]->setColor(255, 0, 0, 255);


	selectedItemIndex = 1;
}

void PauseMenu::MoveUp() {
	auto txt_cmp = _parent->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 > 0) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex--;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void PauseMenu::MoveDown() {
	auto txt_cmp = _parent->GetCompatibleComponent<TextComponent>();

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 < 5) {
		txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
		selectedItemIndex++;
		txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}


void PauseMenu::update(double dt) {
	auto textComps = _parent->GetCompatibleComponent<TextComponent>();

	if (active) {

		textComps[0]->SetText("PAUSED");
		textComps[1]->SetText("Resume");
		textComps[2]->SetText("Restart");
		textComps[3]->SetText("Controls");
		textComps[4]->SetText("Quit");

	}
	else {
		textComps[0]->SetText("");
		textComps[1]->SetText("");
		textComps[2]->SetText("");
		textComps[3]->SetText("");
		textComps[4]->SetText("");
	}

}

void PauseMenu::render() {
}

PauseMenu::~PauseMenu() {

}