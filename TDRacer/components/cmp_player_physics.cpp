#include "cmp_player_physics.h"
#include "cmp_sound.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "system_resources.h"
#include "engine.h"
#include "../components/cmp_player_controls.h"

using namespace std;
using namespace sf;
using namespace Physics;

//std::map<std::string, MyKeys> Keys;
//MyKeys key;

//int count1 = 0;

/*void PlayerPhysicsComponent::DefineControls()*/// {

	// bind forward key
	//key.myInputType = KeyboardInput;
	//key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Keyboard::Up;
	//Keys["Forward"] = key;

	//// bind back key
	//key.myInputType = KeyboardInput;
	//key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Keyboard::Down;
	//Keys["Back"] = key;

	//// bind left key
	//key.myInputType = KeyboardInput;
	//key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Keyboard::Left;
	//Keys["Left"] = key;

	//// bind right key
	//key.myInputType = KeyboardInput;
	//key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Keyboard::Right;
	//Keys["Right"] = key;

	//// bind handbrake key
	//key.myInputType = KeyboardInput;
	//key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Keyboard::Space;
	//Keys["Handbrake"] = key;
//}

void PlayerPhysicsComponent::Forward() {

	auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	if (checkGrass == 'g') {
		dampen({ 0.5f, 0.5f });
		impulse({ -worldVector.x , -worldVector.y });
	}
	else {
		impulse({ -worldVector.x, -worldVector.y });
	}
}

void PlayerPhysicsComponent::Back() {

	auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	if (checkGrassReverse == 'g') {
		dampen({ 0.5f, 0.5f });
		impulse({ worldVector.x, worldVector.y });
	}
	else {
		impulse({ worldVector.x, worldVector.y });
	}
}


//bool PlayerPhysicsComponent::KeyEvent(MyKeys k, sf::Event e)
//{
//	// Mouse event
//	if (k.myInputType == MouseInput &&
//		k.myEventType == e.type &&
//		k.myMouseButton == e.mouseButton.button)
//	{
//		return (true);
//	}
//	// Keyboard event
//	if (k.myInputType == KeyboardInput &&
//		k.myEventType == e.type &&
//		k.myKeyCode == e.key.code)
//	{
//		return (true);
//	}
//	return (false);
//}


void PlayerPhysicsComponent::update(double dt) {

	//stops keys being redefined when update called 
	/*if (count1 == 1)
	{
		DefineControls();
		count1++;
	}*/

	const auto pos = _parent->getPosition();
	//const auto snd = _parent->GetCompatibleComponent<SoundComponent>()[0];

	//auto t = _parent->GetCompatibleComponent<PlayerControls>()[0];
	////t->ChangeControls("Forward", test);
	//
	auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
	auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));

	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//auto a = t->getAccelerateControl();
	//if (sf::Keyboard::isKeyPressed(t->getControl("Forward"))) {
	//	if (checkGrass == 'g') {
	//		dampen({ 0.5f, 0.5f });
	//		impulse({ -worldVector.x , -worldVector.y });
	//	}
	//	else {
	//		impulse({ -worldVector.x, -worldVector.y });
	//	}
	//}
	//else if (Keyboard::isKeyPressed(t->getControl("Reverse"))) {
	//	if (checkGrassReverse == 'g') {
	//		dampen({ 0.5f, 0.5f });
	//		impulse({ worldVector.x, worldVector.y });
	//	}
	//	else {
	//		impulse({ worldVector.x, worldVector.y });
	//	}
	//	//Forward();

	//}
	//else {
	//	dampen({ 0.015f, 0.015f });
	//}

	//
	//Teleport to start if we fall off map. 
	//if (pos.y > ls::getHeight() * ls::getTileSize() || pos.x > ls::getWidth() * ls::getTileSize() || pos.x < 0 || pos.y < 0) {
	//	teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	//}

	////This gets the world vector for moving the Entity
	////Currently controlling the speed of the car - something needs done to control speed somehow
	////gets the currend speed in forward direction
	//auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	////Handle keyboard input from user
	//if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S)) {

	//	auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
	//	auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));


	//	if (Keyboard::isKeyPressed(Keyboard::W)) {
	//		snd->getSound().play();
	//		/*if (getVelocity().x < _maxVelocity.x) {*/
	//			//updateFriction();
	//		if (checkGrass == 'g') {
	//			dampen({ 0.5f, 0.5f });
	//			impulse({ -worldVector.x , -worldVector.y });
	//		}
	//		else {
	//			impulse({ -worldVector.x, -worldVector.y });
	//		}
	//	}
	//	else if (Keyboard::isKeyPressed(Keyboard::S)) {
	//		//if (getVelocity().x < _maxVelocity.x) {
	//			//updateFriction();
	//		if (checkGrassReverse == 'g') {
	//			dampen({ 0.5f, 0.5f });
	//			impulse({ worldVector.x, worldVector.y });
	//		}
	//		else {
	//			impulse({ worldVector.x, worldVector.y });

	//		}
	//		//stopTurning();
	//	//}

	//	}
	//}
	//else {
	//	// Dampen X axis movement
	//	dampen({ 0.015f, 0.015f });
	//	stopTurning(); //Added
	//}

	////Turning
	//if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) {

	//	if (Keyboard::isKeyPressed(Keyboard::D)) {

	//		turnRight();
	//		dampen({ 0.05f, 0.05f });
	//		//impulse({ -worldVector.x, -worldVector.y }); 
	//		//updateFriction();

	//	}
	//	else if (Keyboard::isKeyPressed(Keyboard::A)) {
	//		//cout << getVelocity() << en5dl;
	//		//impulse({ -worldVector.x, -worldVector.y });
	//		turnLeft();
	//		dampen({ 0.05f, 0.05f });

	//		//updateFriction();

	//	}

	//}
	//else {
	//	// Dampen X axis movement
	//	dampen({ 0.015f, 0.015f });
	//	stopTurning(); //Added
	//}


	////Handbrake
	//if (Keyboard::isKeyPressed(Keyboard::Space)) {
	//	updateFriction();
	//}


	//Respawn
	//if (Keyboard::isKeyPressed(Keyboard::R)) {
	//	teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	//}

	//Old Impulse
	//		//impulse({0, -(float)(dt * _groundspeed) });

	// Clamp velocity.
	//auto v = getVelocity();
	//v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	//v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	//setVelocity(v);

	PhysicsComponent::update(dt);
}



PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);

	auto svsize = bv2_to_sv2(_size, true);
	cout << "b2vec size:" << "\nX: " << _size.x << "\nY: " << _size.y << "\n---------------------------" << endl;
	cout << "vector2f size: " << "\nX: " << svsize.x << "\nY: " << svsize.y << "\n---------------------------" << endl;
	maxSpeed = 40.f;
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 60.f;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);

	//Bullet items have higher-res collision detection
	_body->SetBullet(true);

}



//Engine::GetWindow().mapPixelToCoords