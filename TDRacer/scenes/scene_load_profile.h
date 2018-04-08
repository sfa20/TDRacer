#pragma once

#include "engine.h"

class LoadProfileScreen : public Scene {
public:
	LoadProfileScreen() = default;
	~LoadProfileScreen() override = default;

	void Load() override;
	void Update(const double& dt) override;
};
