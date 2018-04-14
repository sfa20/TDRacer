#pragma once
#include "cmp_timer.h"
#include "cmp_text.h"
#include "cmp_physics.h"
#include <ecm.h>

class CountDown : public Timer {
private:
	
public:

	CountDown(Entity* p);

	void update(double dt) override;

	void render() override;
	


};
