#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "cmp_player_controls.h"
#include "../game.h"
#include "cmp_sound.h"
#include "cmp_timer.h"
using namespace std;
using namespace sf;
using namespace Physics;

int counttttt = 0;
bool trip;
void PlayerPhysicsComponent::update(double dt) {



	const auto pos = _parent->getPosition();

	//Teleport to start if we fall off map. 
	if (pos.y > ls::getHeight() * ls::getTileSize() || pos.x > ls::getWidth() * ls::getTileSize() || pos.x < 0 || pos.y < 0) {
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}

	//This gets the world vector for moving the Entity
	//Currently controlling the speed of the car - something needs done to control speed somehow
	//gets the currend speed in forward direction
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	//Get the defined controls for the player
	auto ctrl = _parent->GetCompatibleComponent<PlayerControls>()[0];

#pragma region Player Movement

	//joystick events 	
	Vector2f didItMove(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	auto t = _parent->GetCompatibleComponent<Timer>()[0];
	auto sndcmp = _parent->GetCompatibleComponent<SoundComponent>()[0];

	if (controlsEnabled) {
		//Handle keyboard input from user
		if (Keyboard::isKeyPressed(forwardA) || Keyboard::isKeyPressed(backA) || sf::Joystick::isButtonPressed(0, 5) || sf::Joystick::isButtonPressed(0, 4)) {

			auto checkGrass = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, 1));
			auto checkGrassReverse = ls::getTileAt(_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getPosition() + Vector2f(0, -1));

			if (Keyboard::isKeyPressed(forwardA) || sf::Joystick::isButtonPressed(0, 5)) {
				if (checkGrass == 'g') {
					dampen({ 0.5f, 0.5f });
					impulse({ -worldVector.x , -worldVector.y });

				/*	if (trip) {
						sndcmp->getSound().play();
						t->getClock().restart();
						trip = false;
					}

					auto passed = t->getClock().getElapsedTime().asMilliseconds();
					if (passed > 7000)
						trip = true;
*/
					
				}
				else {
					/*if (trip) {
						sndcmp->getSound().play();
						t->getClock().restart();
						trip = false;
					}

					auto passed = t->getClock().getElapsedTime().asMilliseconds();
					if (passed > 7000)
						trip = true;
					*/
					impulse({ -worldVector.x, -worldVector.y });
					/*sndcmp->getSound().*/

				}
			}

			else if (Keyboard::isKeyPressed(backA) || sf::Joystick::isButtonPressed(0, 4)) {
				if (checkGrassReverse == 'g') {
					dampen({ 0.5f, 0.5f });
					impulse({ worldVector.x, worldVector.y });
				}
				else {
					impulse({ worldVector.x, worldVector.y });

				}
			}
		}
		else {
			// Dampen X axis movement
			/*if (trip) {
				sndcmp->getSound().play();
				t->getClock().restart();
				trip = false;
			}

			auto passed = t->getClock().getElapsedTime().asMilliseconds();
			if (passed > 7000)
				trip = true;*/
			
			dampen({ 0.015f, 0.015f });
			stopTurning(); //Added
		}

		//Turning
		if (Keyboard::isKeyPressed(leftA) || Keyboard::isKeyPressed(rightA) || didItMove.x > 15 || didItMove.x < -15) {

			if (Keyboard::isKeyPressed(rightA) || didItMove.x > 15) {
				turnRight();
				dampen({ 0.05f, 0.05f });
			}
			else if (Keyboard::isKeyPressed(leftA) || didItMove.x < -15) {
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
		if (Keyboard::isKeyPressed(handbrakeA) || sf::Joystick::isButtonPressed(0, 0)) {
			updateFriction();
		}


		//Respawndsawasaw
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		}


	}
#pragma endregion


	PhysicsComponent::update(dt);
}


PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);

	auto svsize = bv2_to_sv2(_size, true);
	//cout << "b2vec size:" << "\nX: " << _size.x << "\nY: " <<_size.y << "\n---------------------------" << endl;
	//cout << "vector2f size: " << "\nX: " << svsize.x << "\nY: " << svsize.y << "\n---------------------------" << endl;
	maxSpeed = 40.f;
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 60.f;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);

	//Bullet items have higher-res collision detection
	_body->SetBullet(true);

}


