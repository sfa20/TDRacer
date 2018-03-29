#pragma once

#include "engine.h"


class MenuScene : public Scene {
public:
	MenuScene() = default;
	~MenuScene() override = default;


	int GetPressedItem() { return selectedItemIndex; } //added - sfa20
	void MenuEvents(sf::RenderWindow window); // added - sfa20
	void Load() override;

	void Update(const double& dt) override;

private:
	int index;
	int selectedItemIndex;

};
