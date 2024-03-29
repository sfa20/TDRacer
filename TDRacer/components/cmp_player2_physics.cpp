#include "cmp_player2_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "cmp_player_controls.h"
#include "../game.h"

using namespace std;
using namespace sf;
using namespace Physics;

PlayerTwoPhysicsComponent::PlayerTwoPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	teleport(ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]));
	auto svsize = bv2_to_sv2(_size, true);
	maxSpeed = 40.f;
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 60.f;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);

	//Bullet items have higher-res collision detection
	_body->SetBullet(true);

}


void PlayerTwoPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	//Teleport to start if we fall off map. 
	if (pos.y > ls::getHeight() * ls::getTileSize() || pos.x > ls::getWidth() * ls::getTileSize() || pos.x < 0 || pos.y < 0) {
		teleport(ls::getTilePosition(ls::findTiles(ls::STARTRIGHT)[0]));
	}

	//This gets the world vector for moving the Entity
	//Currently controlling the speed of the car - something needs done to control speed somehow
	//gets the currend speed in forward direction
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//Get the defined controls for the player
	//auto ctrl = _parent->GetCompatibleComponent<PlayerControls>()[0];

#pragma region Player Movement

	//joystick events 	
	Vector2f didItMove(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

	if (controlsEnabled) {
		sf::Keyboard::Key a = static_cast<sf::Keyboard::Key>(1);
		//Handle keyboard input from user
		if (Keyboard::isKeyPressed(forwardB) || Keyboard::isKeyPressed(backB) || sf::Joystick::isButtonPressed(1, 5) || sf::Joystick::isButtonPressed(1, 4)) {

			auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
			auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));


			if (Keyboard::isKeyPressed(forwardB) || sf::Joystick::isButtonPressed(1, 5)) {
				/*if (getVelocity().x < _maxVelocity.x) {*/
				//updateFriction();
				if (checkGrass == 'g') {
					dampen({ 0.5f, 0.5f });
					impulse({ -worldVector.x , -worldVector.y });
				}
				else {
					impulse({ -worldVector.x, -worldVector.y });
				}
			}

			else if (Keyboard::isKeyPressed(backB) || sf::Joystick::isButtonPressed(1, 4)) {
				//if (getVelocity().x < _maxVelocity.x) {
				//updateFriction();
				if (checkGrassReverse == 'g') {
					dampen({ 0.5f, 0.5f });
					impulse({ worldVector.x, worldVector.y });
				}
				else {
					impulse({ worldVector.x, worldVector.y });

				}
				//stopTurning();
				//}

			}
		}
		else {
			// Dampen X axis movement
			dampen({ 0.015f, 0.015f });
			stopTurning(); //Added
		}

		//Turning
		if (Keyboard::isKeyPressed(leftB) || Keyboard::isKeyPressed(rightB) || didItMove.x > 15 || didItMove.x < -15) {

			if (Keyboard::isKeyPressed(rightB) || didItMove.x > 15) {
				turnRight();
				dampen({ 0.05f, 0.05f });
			}
			else if (Keyboard::isKeyPressed(leftB) || didItMove.x < -15) {
				turnLeft();
				dampen({ 0.05f, 0.05f });
			}
		}
		else {
			// Dampen X axis movement
			dampen({ 0.015f, 0.015f });
			stopTurning(); //Added
		}


		//Handbrake
		if (Keyboard::isKeyPressed(handbrakeB) || sf::Joystick::isButtonPressed(1, 0)) {
			updateFriction();
		}


		//Respawndsawasaw
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			/*teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));*/
		}


	}
#pragma endregion


	PhysicsComponent::update(dt);
}



