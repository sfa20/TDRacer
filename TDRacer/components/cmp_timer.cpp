#include "cmp_timer.h"
#include "ecm.h"

using namespace std;
using namespace sf;


//Constructor
Timer::Timer(Entity* p) : Component(p){

	running = false;
	
	mins = 0;
	secs = 0;
	millisecs = 0;

}

sf::Clock Timer::getClock() {
	return timer;
}


#pragma region TimerControls


void Timer::start() {
	if (!running) {
		timer.restart();
		running = true;
	}
}


void Timer::stop() {
	running = false;
}


void Timer::reset() {
	timer.restart();
}


bool Timer::isRunning() {
	return running;
}

#pragma endregion



#pragma region Get Timer details


////Return Minutes, Seconds and Milliseconds
int Timer::getMins() {
	return mins;
}

void Timer::setMins(int newMins) {
	mins = newMins;
	cout << mins << endl;
}

int Timer::getSecs() {
	return secs;
}

void Timer::setSecs(int newSecs) {
	secs = newSecs;
}


int Timer::getMillisecs() {
	return millisecs;
}

void Timer::setMillisecs(int newMillisecs) {
	millisecs = newMillisecs;
}

std::string Timer::getTime() {
	return "Timer: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
}

void Timer::setRunning(bool Running) {
	running = Running;
}


#pragma endregion



#pragma region Update and Render

void Timer::update(double dt) { 
	updateClock(); 

}


void Timer::updateClock() {

	if (this->getClock().getElapsedTime().asMilliseconds() > 60000) {

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


void Timer::render() {};



#pragma endregion

