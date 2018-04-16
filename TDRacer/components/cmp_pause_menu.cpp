#include "cmp_pause_menu.h"
#include "engine.h"
#include "../components/cmp_player_controls.h"
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

int tempcount = 0;
PauseMenu::PauseMenu(Entity* p) : Component(p) {
	
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	_parent->addComponent<TextComponent>("");
	//Text compononts for the Dynamic controls
	_parent->addComponent<TextComponent>("");	//5
	_parent->addComponent<TextComponent>("");	//6
	_parent->addComponent<TextComponent>("");	//7	
	_parent->addComponent<TextComponent>("");	//8
	_parent->addComponent<TextComponent>("");	//9
	_parent->addComponent<TextComponent>("");

	auto textComps = _parent->GetCompatibleComponent<TextComponent>();

	//Main menu
	textComps[0]->setCenterPos(Engine::getWindowSize().x / 2.f, 200.f, 50.f);
	textComps[1]->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
	textComps[2]->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
	textComps[3]->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);
	textComps[4]->setCenterPos(Engine::getWindowSize().x / 2.f, 670.f, 50.f);
	textComps[1]->setColor(255, 0, 0, 255);
	
	//Submenu
	textComps[5]->setCenterPos(Engine::getWindowSize().x / 2.f, 470.f, 50.f);
	textComps[6]->setCenterPos(Engine::getWindowSize().x / 2.f, 520.f, 50.f);
	textComps[7]->setCenterPos(Engine::getWindowSize().x / 2.f, 570.f, 50.f);
	textComps[8]->setCenterPos(Engine::getWindowSize().x / 2.f, 620.f, 50.f);
	textComps[9]->setCenterPos(Engine::getWindowSize().x / 2.f, 670.f, 50.f);
	textComps[10]->setCenterPos(Engine::getWindowSize().x / 2.f, 720, 50.f);
	textComps[5]->setColor(255, 0, 0, 255);

	selectedItemIndex = 1;
}

void PauseMenu::MoveUp() {
	auto txt_cmp = _parent->GetCompatibleComponent<TextComponent>();
	if (active) {
		//used for keyboard movement in menus
		if (selectedItemIndex - 1 > 0) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex--;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
		}
	}
	else if (submenuActive) {
		if (selectedItemIndex - 1 > 4) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex--;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
		}
	}
}

void PauseMenu::MoveDown() {
	auto txt_cmp = _parent->GetCompatibleComponent<TextComponent>();
	if (active) {
		//used for keyboard movement in menus
		if (selectedItemIndex + 1 < 5) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex++;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
		}
	}
	else if (submenuActive) {
		//used for keyboard movement in menus
		if (selectedItemIndex + 1 < 11) {
			txt_cmp[selectedItemIndex]->setColor(255, 255, 255, 255);
			selectedItemIndex++;
			txt_cmp[selectedItemIndex]->setColor(255, 0, 0, 255);
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
		}
	}
}


void PauseMenu::update(double dt) {
	auto textComps = _parent->GetCompatibleComponent<TextComponent>();
	auto ctrlComp = _parent->GetCompatibleComponent<PlayerControls>()[0];


	if (active) {
		textComps[0]->SetText("PAUSED");
		textComps[1]->SetText("Resume");
		textComps[2]->SetText("Restart");
		textComps[3]->SetText("Controls");
		textComps[4]->SetText("Quit");

		textComps[5]->SetText("");
		textComps[6]->SetText("");
		textComps[7]->SetText("");
		textComps[8]->SetText("");
		textComps[9]->SetText("");
		textComps[10]->SetText("");

	}
	else if (submenuActive ) {
		textComps[0]->SetText("");
		textComps[1]->SetText("");
		textComps[2]->SetText("");
		textComps[3]->SetText("");
		textComps[4]->SetText("");

		if (tempcount == 0) {
			textComps[5]->SetText("Accelerate : " + ctrlComp->KeyValues[stoi(ctrlComp->getAccelerateControl())]);
			textComps[6]->SetText("Reverse:    " + ctrlComp->KeyValues[stoi(ctrlComp->getReverseControl())]);
			textComps[7]->SetText("Handbrake:" + ctrlComp->KeyValues[stoi(ctrlComp->getHandBrakeControl())]);
			textComps[8]->SetText("Turn Left:    " + ctrlComp->KeyValues[stoi(ctrlComp->getTurnLeftControl())]);
			textComps[9]->SetText("Turn Right:   " + ctrlComp->KeyValues[stoi(ctrlComp->getTurnRightControl())]);
			textComps[10]->SetText("Main Menu");
			tempcount++;
		}

		
	}
	else {
		textComps[0]->SetText("");
		textComps[1]->SetText("");
		textComps[2]->SetText("");
		textComps[3]->SetText("");
		textComps[4]->SetText("");

		textComps[5]->SetText("");
		textComps[6]->SetText("");
		textComps[7]->SetText("");
		textComps[8]->SetText("");
		textComps[9]->SetText("");
		textComps[10]->SetText("");
	}

}


void PauseMenu::render() {
}

PauseMenu::~PauseMenu() {

}