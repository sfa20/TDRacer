#pragma once

#include "engine.h"

class CarSelectScreen : public Scene {
public:
	CarSelectScreen() = default;
	~CarSelectScreen() override = default;

	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void Load() override;
	void MoveUp(); // added - sfa20
	void MoveDown();  // added - sfa20
	void Update(const double& dt) override;

	void setSelection(int selection);
	void PlayGame();
private:
	int selectedItemIndex;
};