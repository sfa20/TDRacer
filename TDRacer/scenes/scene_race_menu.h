#pragma once

#include "engine.h"

class RaceMenuScreen : public Scene {
public:
	RaceMenuScreen() = default;
	~RaceMenuScreen() override = default;

	void Load() override;
	void Update(const double& dt) override;
};
