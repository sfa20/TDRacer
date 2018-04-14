#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class Timer : public Component {
private:
	
	bool running;
	
	sf::Clock timer;
	
	int mins;
	int secs;
	int millisecs;
	
public:
	Timer(Entity* p);

	sf::Clock getClock();

	void start();
	void stop();
	void reset(); //true for race timer false for lap timer

	void update(double dt);
	void render() override;
	
	bool isRunning();

	int getMins();
	void setMins(int newMins);

	int getSecs();
	void setSecs(int newSecs);

	int getMillisecs();
	void setMillisecs(int newMillisecs);

	std::string getTime();
	
	void updateClock();

	void setRunning(bool);
};
