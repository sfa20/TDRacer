#include "cmp_lap_timer.h"
#include "ecm.h"

using namespace std;
using namespace sf;



LapTimer::LapTimer(Entity* p) : Timer(p){

	currentLap = 1;

	lap1 = "0:00:00";
	lap2 = "0:00:00";
	lap3 = "0:00:00";
	lap4 = "0:00:00";
	lap5 = "0:00:00";
}

#pragma region Update and Render

void LapTimer::update(double dt) {

	//auto minTimer = this->getClock().getElapsedTime().asMilliseconds();

	//cout << this->getClock().getElapsedTime().asMilliseconds() << endl;

	if (this->getClock().getElapsedTime().asMilliseconds() > 12000) {

		this->setMins(this->getMins() + 1);
		this->reset();
	}

	setSecs(this->getClock().getElapsedTime().asSeconds());

	setMillisecs(this->getClock().getElapsedTime().asMilliseconds());

	if (getMillisecs() > 1000)
		setMillisecs(getMillisecs() - getSecs() * 1000);
	else
		setMillisecs(this->getClock().getElapsedTime().asMilliseconds());

};


void LapTimer::render() {};





#pragma endregion


void LapTimer::increaseLapCounter() {
	currentLap++;
}


////Get lap and set laptimes
int LapTimer::getCurrentLap() {
	return currentLap;
}


void LapTimer::setLaptime(int lap) {

	switch (lap)	
	{
	case 1: 
		lap1 = "Lap 1: " + to_string(getMins()) + ":" + to_string(getSecs()) + ":" + to_string(getMillisecs());
		setMins(0);
		setSecs(0);
		setMins(0);
		break;
	case 2:
		lap2 = "Lap 2: " + to_string(getMins()) + ":" + to_string(getSecs()) + ":" + to_string(getMillisecs());
		setMins(0);
		setSecs(0);
		setMins(0); 
		break;

	case 3:
		lap3 = "Lap 3: " + to_string(getMins()) + ":" + to_string(getSecs()) + ":" + to_string(getMillisecs());
		break;

	case 4: 
		lap4 = "Lap 4: " + to_string(getMins()) + ":" + to_string(getSecs()) + ":" + to_string(getMillisecs());
		break;

	case 5:
		lap5 = "Lap 5: " + to_string(getMins()) + ":" + to_string(getSecs()) + ":" + to_string(getMillisecs());
		break;

	default:
		break;
	}
}


std::string LapTimer::getLapTimes() {
	return "\nLap1: " + lap1 + " \n" +
		"Lap2: " + lap2 + "\n" +
		"Lap3: " + lap3 + "\n" +
		"Lap4: " + lap4 + "\n" +
		"Lap5: " + lap5;
}



void LapTimer::setLapCounter(bool value) {
	lapCounter = value;
}


bool LapTimer::getLapCounter() {
	return lapCounter;
}