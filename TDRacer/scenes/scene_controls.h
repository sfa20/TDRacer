#pragma once

#include "engine.h"
#include <vector>
#include <list>
#include <mutex>
#include <map>

using namespace std;

class ControlScreen : public Scene {
public:
	ControlScreen() = default;
	~ControlScreen() override = default;

	std::map<int, std::string> KeyValues;

	int GetPressedItem() { return selectedItemIndex; } //added - sfa20	
	void Load() override;
	void MoveUp(); // added - sfa20
	void MoveDown();  // added - sfa20
	void Update(const double& dt) override;
	
	void ControlScreen::GetKeyValue(int key);

private:
	int selectedItemIndex;
};
