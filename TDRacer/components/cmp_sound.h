#pragma once

#include "ecm.h"
#include "SFML/Audio.hpp"

class SoundComponent : public Component {
protected:
	std::shared_ptr<sf::Sound> _sound;

public:
	SoundComponent() = delete;

	explicit SoundComponent(Entity* p);
	void update(double dt) override;
	void render() override;
	sf::Sound& getSound() const;

	template <typename... Targs> void setSound(Targs... params) {
		_sound.reset(new sf::Sound(params...));
	}
};

