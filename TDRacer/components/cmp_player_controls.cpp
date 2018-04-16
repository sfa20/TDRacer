#pragma once
#include "cmp_physics.h"
#include "cmp_sound.h"
#include "system_physics.h"
#include "cmp_player_controls.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "system_resources.h"
#include "engine.h"

using namespace std;
using namespace sf;
using namespace Physics;

std::map<std::string, MyKeys> Keys;
MyKeys key;

int count1 = 0;

void PlayerControls::DefineControls() {

	// bind forward key
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::Up;
	Keys["Accelerate"] = key;

	// bind back key
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::Down;
	Keys["Reverse"] = key;

	// bind left key
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::Left;
	Keys["Left"] = key;

	// bind right key
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::Right;
	Keys["Right"] = key;

	// bind handbrake key
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::Space;
	Keys["Handbrake"] = key;
}


sf::Keyboard::Key PlayerControls::getControl(std::string control) {
	return Keys[control].myKeyCode;
}


PlayerControls::PlayerControls(Entity* p) : Component(p ) {
	DefineControls();
}


//This could come in handy when testing the dynamic key changes
void PlayerControls::ChangeControls(std::string control, int e) {

	//auto test = Engine::GetEvent();
	
		//cout << "Event Type: " << to_string(test.type) << endl;
		cout << control << " before: " << Keys[control].myKeyCode << endl;

		/*auto a = e.key.code;*/
		//Keys[control].myKeyCode = Keyboard::W;

		Keys[control].myKeyCode = static_cast<sf::Keyboard::Key>(e);

		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		cout << control <<" after: " << Keys[control].myKeyCode << endl;
		

}


void PlayerControls::Forward() {

	//auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
	//auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//if (checkGrass == 'g') {
	//	dampen({ 0.5f, 0.5f });
	//	impulse({ -worldVector.x , -worldVector.y });
	//}
	//else {
	//	impulse({ -worldVector.x, -worldVector.y });
	//}
}


void PlayerControls::Back() {

	//auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));
	//auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//if (checkGrassReverse == 'g') {
	//	dampen({ 0.5f, 0.5f });
	//	impulse({ worldVector.x, worldVector.y });
	//}
	//else {
	//	impulse({ worldVector.x, worldVector.y });
	//}
}


bool PlayerControls::KeyEvent(MyKeys k, sf::Event e)
{
	// Mouse event
	if (k.myInputType == MouseInput &&
		k.myEventType == e.type &&
		k.myMouseButton == e.mouseButton.button)
	{
		return (true);
	}
	// Keyboard event
	if (k.myInputType == KeyboardInput &&
		k.myEventType == e.type &&
		k.myKeyCode == e.key.code)
	{
		return (true);
	}
	return (false);
}


void PlayerControls::update(double dt) {

	//stops keys being redefined when update called 
	//if (count1 == 1)
	//{
	//	DefineControls();
	//	count1++;
	//}

	//const auto pos = _parent->getPosition();
	//*const auto snd = _parent->GetCompatibleComponent<SoundComponent>()[0];*/

	//auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//auto test = Engine::GetEvent();
	//
	////if (test.type == Event::KeyPressed) {
	////	//cout << "Event Type: " << to_string(test.type) << endl;
	////	cout << "Before: " << Keys["Forward"].myKeyCode << endl;
	////	
	////	auto a = test.key.code;
	//	Keys["Forward"].myKeyCode = Keyboard::W;
	//	//Keys["Forward"].myKeyCode = a;

	//	//std::this_thread::sleep_for(std::chrono::milliseconds(300));

	////	cout << "After" << Keys["Forward"].myKeyCode << endl;
	////	test.type = Event::KeyPressed;
	////};

	///*cout << a << endl;*/
	//
	//if (sf::Keyboard::isKeyPressed(Keys["Forward"].myKeyCode)) {
	//	cout << test.key.code << endl;
	//	Forward();
	//}
	//else {
	//	dampen({ 0.015f, 0.015f });
	//}

	////if (test.key.code == Keys["Forward"].myKeyCode)
	////{
	////	// You can use a function
	////	//cout << "we are in " << Keys["Forward"].myKeyCode << endl;
	////}


	////if (KeyEvent(Keys["Forward"], test))
	////{
	////	// You can use a function
	////	Forward();
	////	cout << "we are in " << Keys["Forward"].myKeyCode << endl;
	////}
	////if (KeyEvent(Keys["Back"], test))
	////{
	////	Back();
	////}


	////
	////Teleport to start if we fall off map. 
	//if (pos.y > ls::getHeight() * ls::getTileSize() || pos.x > ls::getWidth() * ls::getTileSize() || pos.x < 0 || pos.y < 0) {
	//	teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	//}

	//////This gets the world vector for moving the Entity
	//////Currently controlling the speed of the car - something needs done to control speed somehow
	//////gets the currend speed in forward direction
	////auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//////Handle keyboard input from user
	////if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S)) {

	////	auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
	////	auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));


	////	if (Keyboard::isKeyPressed(Keyboard::W)) {
	////		snd->getSound().play();
	////		/*if (getVelocity().x < _maxVelocity.x) {*/
	////			//updateFriction();
	////		if (checkGrass == 'g') {
	////			dampen({ 0.5f, 0.5f });
	////			impulse({ -worldVector.x , -worldVector.y });
	////		}
	////		else {
	////			impulse({ -worldVector.x, -worldVector.y });
	////		}
	////	}
	////	else if (Keyboard::isKeyPressed(Keyboard::S)) {
	////		//if (getVelocity().x < _maxVelocity.x) {
	////			//updateFriction();
	////		if (checkGrassReverse == 'g') {
	////			dampen({ 0.5f, 0.5f });
	////			impulse({ worldVector.x, worldVector.y });
	////		}
	////		else {
	////			impulse({ worldVector.x, worldVector.y });

	////		}
	////		//stopTurning();
	////	//}

	////	}
	////}
	////else {
	////	// Dampen X axis movement
	////	dampen({ 0.015f, 0.015f });
	////	stopTurning(); //Added
	////}

	//////Turning
	////if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) {

	////	if (Keyboard::isKeyPressed(Keyboard::D)) {

	////		turnRight();
	////		dampen({ 0.05f, 0.05f });
	////		//impulse({ -worldVector.x, -worldVector.y }); 
	////		//updateFriction();

	////	}
	////	else if (Keyboard::isKeyPressed(Keyboard::A)) {
	////		//cout << getVelocity() << en5dl;
	////		//impulse({ -worldVector.x, -worldVector.y });
	////		turnLeft();
	////		dampen({ 0.05f, 0.05f });

	////		//updateFriction();

	////	}

	////}
	////else {
	////	// Dampen X axis movement
	////	dampen({ 0.015f, 0.015f });
	////	stopTurning(); //Added
	////}


	//////Handbrake
	////if (Keyboard::isKeyPressed(Keyboard::Space)) {
	////	updateFriction();
	////}


	////Respawn
	//if (Keyboard::isKeyPressed(Keyboard::R)) {
	//	teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//}

	////Old Impulse
	////		//impulse({0, -(float)(dt * _groundspeed) });

	//// Clamp velocity.
	////auto v = getVelocity();
	////v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	////v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	////setVelocity(v);

	//PhysicsComponent::update(dt);
}


void PlayerControls::render(){}


std::string PlayerControls::getAccelerateControl() {
	return to_string(Keys["Accelerate"].myKeyCode);
}

std::string PlayerControls::getReverseControl() {
	return to_string(Keys["Reverse"].myKeyCode);
}

std::string PlayerControls::getHandBrakeControl() {
	return to_string(Keys["Handbrake"].myKeyCode);
}

std::string PlayerControls::getTurnLeftControl() {
	return to_string(Keys["Left"].myKeyCode);
}

std::string PlayerControls::getTurnRightControl(){
	return to_string(Keys["Right"].myKeyCode);
}





PlayerControls::~PlayerControls() {

}
//Engine::GetWindow().mapPixelToCoords