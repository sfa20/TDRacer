#pragma once

#include "cmp_physics.h"
#include "SFML\Window.hpp"
#include <map>

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

class PlayerControls : public Component {
public:
	explicit PlayerControls(Entity* p);
	bool KeyEvent(MyKeys k, sf::Event e);
	
	void DefineControls();
	void ChangeControls(std::string control, int e);

	void update(double dt) override;
	void render();

	void Forward();
	void Back();
	void Left();
	void Right();
	void Handbrake();

	std::map<int, std::string> KeyValues;


	std::string getAccelerateControl();
	std::string getReverseControl();
	std::string getHandBrakeControl();
	std::string getTurnRightControl();
	std::string getTurnLeftControl();

	sf::Keyboard::Key PlayerControls::getControl(std::string control);


	~PlayerControls();
};



