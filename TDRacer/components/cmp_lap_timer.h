#pragma once
#include "cmp_timer.h"
#include "cmp_physics.h"
#include <ecm.h>

class LapTimer : public Timer {
private:
	bool lapCounter;
	
	int currentLap;

	std::string lap1;
	std::string lap2;
	std::string lap3;
	std::string lap4;
	std::string lap5;

	
public:
	LapTimer(Entity* p);

	int temp;

	void update(double dt) override;
	void render() override;
	
	bool isRunning();

	void setLaptime(int lap);
	
	void increaseLapCounter();
	int getCurrentLap();

	bool getLapCounter();
	void setLapCounter(bool value);

	std::string getLapTimes();

};
