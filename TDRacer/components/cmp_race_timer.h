#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class RaceTimer : public Component {
private:
	bool beenReset;
	bool running;
	unsigned long beg;
	unsigned long end;
	sf::Clock timer;

	int mins;
	int secs;
	int millisecs;


public:
	RaceTimer(Entity* p);
	
	void start();
	void stop();
	void reset();

	void update(double dt) override;
	void render() override;
	
	bool isRunning();
	
	sf::Time getTime();

	int getMins();
	int getSecs();
	int getMillisecs();
};
