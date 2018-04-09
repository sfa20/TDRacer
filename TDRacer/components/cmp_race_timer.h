//#pragma once
//#include "cmp_timer.h"
//#include "cmp_physics.h"
//#include <ecm.h>
//
//class RaceTimer : public Timer {
//private:
//	
//	sf::Clock timer;
//	
//public:
//	RaceTimer(Entity* p);
//
//	int temp;
//	
//	void start();
//	void stop();
//	void reset(bool clock); //true for race timer false for lap timer
//
//	void update(double dt) override;
//	void render() override;
//	
//	bool isRunning();
//
//	void setLaptime(int lap);
//	
//	void setCurrentLap();
//	int getCurrentLap();
//
//	bool getLapCounter();
//	void setLapCounter(bool value);
//
//	std::string getLapTimes();
//
//	int getMins();
//	int getSecs();
//	int getMillisecs();
//};
