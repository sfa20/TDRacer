#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class PauseMenu : public Component {
public:
	explicit PauseMenu(Entity* p);

	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void MoveUp();
	void MoveDown();

	void update(double dt) ;
	void render();
	
	~PauseMenu();

private:
	int selectedItemIndex;
};
