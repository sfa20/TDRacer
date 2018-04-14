#pragma once

#include "engine.h"

class LoadScreen : public Scene {
public:
	LoadScreen() = default;
	~LoadScreen() override = default;

	void Load() override;
	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void MoveUp();
	void MoveDown();
	void Update(const double& dt) override;

	void AddControls();
private:
	int selectedItemIndex;

};
