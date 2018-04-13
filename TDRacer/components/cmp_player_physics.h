#pragma once

#include "cmp_physics.h"
#include "SFML\Window.hpp"

using namespace sf;

enum InputType
{
	KeyboardInput,
	MouseInput,
	JoystickInput
};

struct MyKeys
{
	InputType myInputType;
	sf::Event::EventType myEventType;
	sf::Keyboard::Key myKeyCode;
	sf::Mouse::Button myMouseButton;
};

class PlayerPhysicsComponent : public PhysicsComponent {
private:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	float maxSpeed;
	float _groundspeed;

public:
	void update(double dt) override;
	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
	bool KeyEvent(MyKeys k, sf::Event e);
	void DefineControls();
	void Forward();
	void Back();
	void Left();
	void Right();
	void Handbrake();
	PlayerPhysicsComponent() = delete;
};



