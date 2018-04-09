#pragma once

#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

class CarBodyComponent : public Component {
protected:
  b2Body* body;
  b2Fixture* fixture;

  b2Vec2 bodySize;

public:
	CarBodyComponent() = delete;
	CarBodyComponent(Entity* p, const sf::Vector2f& size);

	void setMass(float m);
	//void setRestitution(float r);

	void update(double dt) override;
	void render() override;
	
	//Destructor
	~CarBodyComponent() override = default;
	
	
};
