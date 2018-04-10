#pragma once

#include "cmp_wheel.h"
#include "system_physics.h"

//Constructor
WheelComponent::WheelComponent(Entity* p) : Component(p) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	body = Physics::GetWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 1.25f);
	b2Fixture* fixture = body->CreateFixture(&polygonShape, 1);
	fixture->SetUserData(new CarTireFUD());

	body->SetUserData(this);
	currentTraction = 1;
}

WheelComponent::~WheelComponent() {
	body->GetWorld()->DestroyBody(body);
}

void WheelComponent::setCharacteristics(float _maxForwardSpeed, float _maxBackwardSpeed, float _maxDriveForce, float _maxLateralImpulse) {
	maxForwardSpeed = _maxForwardSpeed;
	maxBackwardSpeed = _maxBackwardSpeed;
	maxDriveForce = _maxDriveForce;
	maxLateralImpulse = _maxLateralImpulse;
}

void WheelComponent::addGroundArea(GroundAreaFUD* ga) { 
	groundAreas.insert(ga); updateTraction(); 
}

void WheelComponent::removeGroundArea(GroundAreaFUD* ga) { 
	groundAreas.erase(ga); updateTraction(); 
}


//Update Details
void WheelComponent::updateTraction()
{
	if (groundAreas.empty())
		currentTraction = 1;
	else {
		//find area with highest traction
		currentTraction = 0;
		std::set<GroundAreaFUD*>::iterator it = groundAreas.begin();
		while (it != groundAreas.end()) {
			GroundAreaFUD* ga = *it;
			if (ga->frictionModifier > currentTraction)
				currentTraction = ga->frictionModifier;
			++it;
		}
	}
}

void WheelComponent::updateFriction() {
	//lateral linear velocity
	b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length();

	body->ApplyLinearImpulse(currentTraction * impulse, body->GetWorldCenter(), true);

	//angular velocity
	body->ApplyAngularImpulse(currentTraction * 0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);

	//forward linear velocity
	b2Vec2 currentForwardNormal = getForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -2 * currentForwardSpeed;
	body->ApplyForce(currentTraction * dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void WheelComponent::updateDrive(int controlState) {

	//find desired speed
	float desiredSpeed = 0;
	switch (controlState & (TDC_UP | TDC_DOWN)) {
	case TDC_UP:   desiredSpeed = maxForwardSpeed;  break;
	case TDC_DOWN: desiredSpeed = maxBackwardSpeed; break;
	default: return;//do nothing
	}

	//find current speed in forward direction
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

	//apply necessary force
	float force = 0;
	if (desiredSpeed > currentSpeed)
		force = maxDriveForce;
	else if (desiredSpeed < currentSpeed)
		force = -maxDriveForce;
	else
		return;
	body->ApplyForce(currentTraction * force * currentForwardNormal, body->GetWorldCenter(), true);
}

void WheelComponent::updateTurn(int controlState) {
	float desiredTorque = 0;
	switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
	case TDC_LEFT:  desiredTorque = 15;  break;
	case TDC_RIGHT: desiredTorque = -15; break;
	default:;//nothing
	}
	body->ApplyTorque(desiredTorque, true);
}


//getDetails
b2Vec2 WheelComponent::getLateralVelocity() {
	b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 WheelComponent::getForwardVelocity() {
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}




