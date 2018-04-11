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
	//Currently controlling the speed of the car - something needs done to control speed somehow
	//gets the currend speed in forward direction
	auto worldVector = _body->GetWorldVector(b2Vec2(0, 1));

	

	//Handle keyboard input from user
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S)) {

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			/*if (getVelocity().x < _maxVelocity.x) {*/
				//updateFriction();
				impulse({ -worldVector.x, -worldVector.y });
				//stopTurning();
				cout << getVelocity().x << endl;
			//}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			//if (getVelocity().x < _maxVelocity.x) {
				//updateFriction();
				impulse({ worldVector.x, worldVector.y });
				//stopTurning();
			//}
			
		}
		
	}
	else {
		// Dampen X axis movement
		dampen({ 0.015f, 0.015f });
		stopTurning(); //Added
	}

	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) {
	
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			
			turnRight();
			dampen({ 0.05f, 0.05f });
			//impulse({ -worldVector.x, -worldVector.y }); 
			//updateFriction();

		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			//cout << getVelocity() << en5dl;
			//impulse({ -worldVector.x, -worldVector.y });
			turnLeft();
			dampen({ 0.05f, 0.05f });

			//updateFriction();

		}
	
	}
	else {
		// Dampen X axis movement
		dampen({ 0.015f, 0.015f });
		stopTurning(); //Added
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		updateFriction();
	}

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
	maxSpeed = 60.f;
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 60.f;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);

}


//Engine::GetWindow().mapPixelToCoords