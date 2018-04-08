#pragma once

#include "engine.h"


class OptionScreen : public Scene {
public:
	OptionScreen() = default;
	~OptionScreen() override = default;


	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void Load() override;
	void MoveUp(); // added - sfa20
	void MoveDown();  // added - sfa20
	void Update(const double& dt) override;

private:
	int index;
	int selectedItemIndex;
};
