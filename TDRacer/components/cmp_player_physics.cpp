#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

//bool PlayerPhysicsComponent::isGrounded() const {
//  auto touch = getTouching();
//  const auto& pos = _body->GetPosition();
//  const float halfPlrHeigt = _size.y * .5f;
//  const float halfPlrWidth = _size.x * .52f;
//  b2WorldManifold manifold;
//  for (const auto& contact : touch) {
//    contact->GetWorldManifold(&manifold);
//    const int numPoints = contact->GetManifold()->pointCount;
//    bool onTop = numPoints > 0;
//    // If all contacts are below the player.
//    for (int j = 0; j < numPoints; j++) {
//      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
//    }
//    if (onTop) {
//      return true;
//    }
//  }
//
//  return false;
//}

void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();
	//
	//Teleport to start if we fall off map. 
	if (pos.y > ls::getHeight() * ls::getTileSize() || pos.x > ls::getWidth() * ls::getTileSize() || pos.x < 0 || pos.y < 0) {
		teleport(ls::getTilePosition(ls::findTiles(ls::CORNER1)[0]));
	}

	//This gets the world vector for moving the Entity
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 0.2));

	//Handle keyboard input from user
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S)) {

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (getVelocity().x < _maxVelocity.x) {
				impulse({ -worldVector.x, -worldVector.y });
				stopTurning(); 
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			impulse({ worldVector.x, worldVector.y });
			stopTurning(); 
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			dampen({ 0.1f, 0.1f });
			impulse({ -worldVector.x, -worldVector.y }); 
			turnRight(); 
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			cout << getVelocity() << endl;
			dampen({ 0.1f, 0.1f }); 
			impulse({ -worldVector.x, -worldVector.y });
			turnLeft(); 
		}
	}
	else {
		// Dampen X axis movement
		dampen({ 0.1f, 0.1f });
		stopTurning(); //Added
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		dampen({ 1, 1 });
	}


	//Old Impulse
	//		//impulse({0, -(float)(dt * _groundspeed) });

	
	//Not Used
	// Handle Jump
	/*if (Keyboard::isKeyPressed(Keyboard::Up)) {
		_grounded = isGrounded();
		if (_grounded) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			teleport(Vector2f(pos.x, pos.y - 2.0f));
			impulse(Vector2f(0, -6.f));
		}
	}*/

	//Are we in air?
	//Not Used
	//if (!_grounded) {
	//  // Check to see if we have landed yet
	//  _grounded = isGrounded();
	//  // disable friction while jumping
	//  setFriction(0.f);
	//} else {
	//  setFriction(0.1f);
	//}
	
	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);

	//float timeStep = 1 / 20.0;
	//int velocityIterations = 8;
	//int positionIterations = 3;

	//Physics::GetWorld()->Step(timeStep, velocityIterations, positionIterations);

	PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) : PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	maxSpeed = 30.f;
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 30.f;
//  _grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);



}


//Engine::GetWindow().mapPixelToCoords