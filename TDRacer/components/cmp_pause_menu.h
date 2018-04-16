#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class PauseMenu : public Component {
public:
	explicit PauseMenu(Entity* p);
	bool active;
	bool submenuActive;
	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void MoveUp();
	void MoveDown();

	int selectedItemIndex;


	void update(double dt) ;
	void render();
	
	~PauseMenu();

private:
};
