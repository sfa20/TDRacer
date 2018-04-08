#include "cmp_race_timer.h"
#include "ecm.h"
using namespace std;
using namespace sf;

RaceTimer::RaceTimer(Entity* p) : Component(p){
	beenReset = true;
	running = false;
	beg = 0;
	end = 0;
	mins = 0;
}

void RaceTimer::start() {
	if (!running) {
		timer.restart();
		/*if (beenReset)
			beg = (unsigned long)clock();
		else
			beg -= end - (unsigned long)clock();*/
		running = true;
		beenReset = false;
	}
}


void RaceTimer::stop() {
	if (running) {
		end = (unsigned long)clock();
		running = false;
	}
}


void RaceTimer::reset() {
	bool wereRunning = running;
	if (wereRunning)
		stop();
	beenReset = true;
	beg = 0;
	end = 0;
	if (wereRunning)
		start();
}


bool RaceTimer::isRunning() {
	return running;
}


sf::Time RaceTimer::getTime() {
	if (running) {
		return timer.getElapsedTime();
	}
		//return Clock::getElapsedTime();
		//return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
}

int RaceTimer::getMins() {
	return mins;
}

int RaceTimer::getSecs() {
	return secs;
}

int RaceTimer::getMillisecs() {
	return millisecs;
}

void RaceTimer::update(double dt) {
	
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

void RaceTimer::render() {};