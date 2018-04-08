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




#pragma endregion



#pragma region Update and Render

void Timer::update(double dt) {

	if (timer.getElapsedTime().asMilliseconds() > 60000) {
		mins += 1;
		timer.restart();
	}

	secs = timer.getElapsedTime().asSeconds();

	millisecs = timer.getElapsedTime().asMilliseconds();

	if (millisecs > 1000)
		millisecs = millisecs - secs * 1000;
	else
		millisecs = timer.getElapsedTime().asMilliseconds();

};


void Timer::render() {};



#pragma endregion

