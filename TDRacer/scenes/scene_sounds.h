#pragma once

#include "engine.h"

class SoundScreen : public Scene {
public:
	SoundScreen() = default;
	~SoundScreen() override = default;


	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void Load() override;
	void MoveUp(); // added - sfa20
	void MoveDown();  // added - sfa20
	void Update(const double& dt) override;

private:
	int selectedItemIndex;
};
