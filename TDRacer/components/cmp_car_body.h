#pragma once

#include "ecm.h"
#include "cmp_wheel.h"
#include <Box2D/Dynamics/b2Body.h>

class CarBodyComponent : public Component {
protected:
	b2Body* body;
	std::vector<WheelComponent*> wheels;
	b2RevoluteJoint *flJoint;
	b2RevoluteJoint *frJoint;

	b2Fixture* fixture;
	b2Vec2 bodySize;

public:

	b2BodyDef bodyDef;
	

	CarBodyComponent() = delete;
	CarBodyComponent(Entity* p);

	void setMass(float m);
	//void setRestitution(float r);

	void update(double dt, int controlstate);
	void render() override;
	
	//Destructor
	~CarBodyComponent();
	
	
};




class MyDestructionListener : public b2DestructionListener
{
	void SayGoodbye(b2Fixture* fixture)
	{
		if (FixtureUserData* fud = (FixtureUserData*)fixture->GetUserData())
			delete fud;
	}

	//(unused but must implement all pure virtual functions)
	void SayGoodbye(b2Joint* joint) {}
};
