#pragma once

#include "engine.h"

class AvatarScreen : public Scene {
public:
	AvatarScreen() = default;
	~AvatarScreen() override = default;

	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void Load() override;
	void MoveUp();
	void MoveDown();
	void Update(const double& dt) override;
private:
	int selectedItemIndex;
};
