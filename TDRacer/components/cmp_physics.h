#pragma once

#include "cmp_sprite.h"
#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

class PhysicsComponent : public Component {
protected:
	b2Body * _body;
	const bool _dynamic;
	b2Fixture* _fixture;

public:
	PhysicsComponent(Entity* p, bool dyn, const sf::Vector2f& size);

	b2Fixture* const getFixture() const;
	bool isTouching(const PhysicsComponent& pc) const;
	bool isTouching(const PhysicsComponent& pc, b2Contact const* bc) const;
	std::vector<const b2Contact*> getTouching() const;

	const sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& v);

	void setRestitution(float r);
	void setFriction(float r);
	void setMass(float m);

	////////Added
	bool controlsEnabled;

	void turnRight();					//added
	void turnLeft();					//added
	void stopTurning();				//added
	void updateFriction();

	//Impulse Variables
	float maxForwardSpeed;
	float maxBackwardSpeed;
	float desiredSpeed;
	float maxDriveForce;


	//Friction variables
	float maxLateralImpulse;
	float driftFriction;
	float dragModifier;
	float currentTraction;

	b2Vec2 getForwardVelocity();
	b2Vec2 getLateralVelocity();
	b2Vec2 getDirection();

	b2Vec2 currentForwardNormal;
	float currentForwardSpeed;

	/////////////

	void update(double dt) override;
	void render() override;
	void impulse(const sf::Vector2f& i);

	void dampen(const sf::Vector2f& s);

	void teleport(const sf::Vector2f& v);

	~PhysicsComponent() override;
};
