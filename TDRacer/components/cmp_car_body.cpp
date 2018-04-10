#include "SFML\Graphics.hpp"
#include "system_physics.h"
#include "cmp_car_body.h"

using namespace std;
using namespace sf;
using namespace Physics;

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

//Constructor
CarBodyComponent::CarBodyComponent(Entity* const p) : Component(p) {
	bodyDef.type = b2_dynamicBody;
	body = Physics::GetWorld()->CreateBody(&bodyDef);
	body->SetAngularDamping(3);

	//Prepare the common joint params
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero(); //Center of tyre

	float maxForwardSpeed = 250;
	float maxReverseSpeed = -40;
	float backTireMaxDriveForce = 300;
	float frontTireMaxDriveForce = 500;
	float backTireMaxLateralImpulse = 8.5;
	float frontTireMaxLateralImpulse = 7.5;

	//Back left tire
	WheelComponent* backLeftWheel;
	backLeftWheel->setCharacteristics(maxForwardSpeed, maxReverseSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = backLeftWheel->body;
	jointDef.localAnchorA.Set(-3, 0.75f);
	Physics::GetWorld()->CreateJoint(&jointDef);
	wheels.push_back(backLeftWheel);

	//Back Right tire
	WheelComponent* backRightWheel;
	backRightWheel->setCharacteristics(maxForwardSpeed, maxReverseSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = backRightWheel->body;
	jointDef.localAnchorA.Set(3, 0.75f);
	Physics::GetWorld()->CreateJoint(&jointDef);
	wheels.push_back(backRightWheel);
	
	//Front Left tire
	WheelComponent* FrontLeftWheel;
	backRightWheel->setCharacteristics(maxForwardSpeed, maxReverseSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = backRightWheel->body;
	jointDef.localAnchorA.Set(-3, 8.5f);
	Physics::GetWorld()->CreateJoint(&jointDef);
	wheels.push_back(backRightWheel);
	
	//Front Right tire
	WheelComponent* FrontRightWheel;
	FrontRightWheel->setCharacteristics(maxForwardSpeed, maxReverseSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
	jointDef.bodyB = FrontRightWheel->body;
	jointDef.localAnchorA.Set(3, 8.5f);
	Physics::GetWorld()->CreateJoint(&jointDef);
	wheels.push_back(FrontRightWheel);





}

void CarBodyComponent::setMass(float m) { 
	fixture->SetDensity(m); 
}

void CarBodyComponent::update(double dt, int controlState) {
	for (int i = 0; i < wheels.size(); i++)
		wheels[i]->updateFriction();
	for (int i = 0; i < wheels.size(); i++)
		wheels[i]->updateDrive(controlState);

	//control steering
	float lockAngle = 35 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;
	switch (controlState & (TDC_LEFT | TDC_RIGHT)) {
	case TDC_LEFT:  desiredAngle = lockAngle;  break;
	case TDC_RIGHT: desiredAngle = -lockAngle; break;
	default:;//nothing
	}
	float angleNow = flJoint->GetJointAngle();
	float angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	float newAngle = angleNow + angleToTurn;
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);
}

void CarBodyComponent::render() {

}

CarBodyComponent::~CarBodyComponent() {
	for (int i = 0; i < wheels.size(); i++) {
		delete wheels[i];
	}
}