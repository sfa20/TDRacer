
#include "cmp_sound.h"
#include "system_renderer.h"

using namespace std;

SoundComponent::SoundComponent(Entity* p) : Component(p), _sound(make_shared<sf::Sound>()) {}

void SoundComponent::update(double dt)
{
}

void SoundComponent::render()
{
}

sf::Sound& SoundComponent::getSound() const { return *_sound; }

