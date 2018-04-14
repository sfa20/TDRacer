#include "cmp_race_countdown.h"
#include "cmp_text.h"
#include "engine.h"
#include "ecm.h"

using namespace std;
using namespace sf;


//Constructor
CountDown::CountDown(Entity* p) : Timer(p) {

	setRunning(false);
	setMins(0);
	setSecs(0);
	setMillisecs(0);
	auto textBox1 = _parent->addComponent<TextComponent>("3");
	textBox1->setCenterPos(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2, 80.f);

}

#pragma region Update and Render

void CountDown::update(double dt) {
	
	//updateClock();
	
	auto textComp = _parent->GetCompatibleComponent<TextComponent>()[0];

	if (this->getClock().getElapsedTime().asSeconds() < 6) {
		auto condition = static_cast<int>(this->getClock().getElapsedTime().asSeconds());

		//cout << condition << endl;
		//cout << _parent->isEnabled << endl;

		switch (condition) {
		case 1:
			textComp->SetText("3");
			break;
		case 2:
			textComp->SetText("2");
			break;
		case 3:
			textComp->SetText("1");
			break;
		case 4:
			textComp->SetText("Go!");
			break;
		case 5:
			textComp->SetText(" ");
			break;
		}
	}
	else {
		//_parent->isEnabled = true;
		//cout << _parent->isEnabled << endl;

	};
}


void CountDown::render() {};



#pragma endregion

