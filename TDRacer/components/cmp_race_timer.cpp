//#include "cmp_race_timer.h"
//#include "ecm.h"
//
//using namespace std;
//using namespace sf;
//
//
//
//RaceTimer::RaceTimer(Entity* p) : Timer(p){
//
//}
//
//void RaceTimer::start() {
//	if (!running) {
//		timer.restart();
//
//		running = true;
//
//
//		//dont' think needed
//		beenReset = false;
//	}
//}
//
//
//void RaceTimer::stop() {
//	running = false;
//	/*if (running) {
//		end = (unsigned long)clock();
//		running = false;
//	}*/
//}
//
//
//void RaceTimer::reset(bool clock) {
//	
//	if (clock) {
//		timer.restart();
//		currentLap++;
//	}
//	else {
//		lapCountTimer.restart();
//	}
//}
//
//
//bool RaceTimer::isRunning() {
//	return running;
//}
//
//
//
//////Return Minutes, Seconds and Milliseconds
//int RaceTimer::getMins() {
//	return mins;
//}
//
//
//int RaceTimer::getSecs() {
//	return secs;
//}
//
//
//int RaceTimer::getMillisecs() {
//	return millisecs;
//}
//
//
//////Update and Render
//void RaceTimer::update(double dt) {
//	
//	temp = lapCountTimer.getElapsedTime().asMilliseconds();
//
//	if (timer.getElapsedTime().asMilliseconds() > 60000) {
//		mins += 1;
//		timer.restart();
//	}
//
//	secs = timer.getElapsedTime().asSeconds();
//
//	millisecs = timer.getElapsedTime().asMilliseconds();
//
//	if (millisecs > 1000) 
//		millisecs = millisecs - secs * 1000;
//	else
//		millisecs = timer.getElapsedTime().asMilliseconds();
//
//};
//
//
//void RaceTimer::render() {};
//
//
//void RaceTimer::setCurrentLap() {
//	currentLap++;
//}
//
//
//////Get lap and set laptimes
//int RaceTimer::getCurrentLap() {
//	return currentLap;
//}
//
//
//void RaceTimer::setLaptime(int lap) {
//
//	switch (lap)
//	{
//	case 1: 
//		lap1 = "Lap 1: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
//		break;
//	case 2:
//		lap2 = "Lap 2: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
//		break;
//
//	case 3:
//		lap3 = "Lap 3: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
//		break;
//
//	case 4: 
//		lap4 = "Lap 4: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
//		break;
//
//	case 5:
//		lap5 = "Lap 5: " + to_string(mins) + ":" + to_string(secs) + ":" + to_string(millisecs);
//		break;
//
//	default:
//		break;
//	}
//}
//
//
//std::string RaceTimer::getLapTimes() {
//	return "\nLap1: " + lap1 + " \n" +
//		"Lap2: " + lap2 + "\n" +
//		"Lap3: " + lap3 + "\n" +
//		"Lap4: " + lap4 + "\n" +
//		"Lap5: " + lap5;
//}
//
//void RaceTimer::setLapCounter(bool value) {
//	lapCounter = value;
//}
//
//bool RaceTimer::getLapCounter() {
//	return lapCounter;
//}