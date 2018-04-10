#include "SFML\Graphics.hpp"
#include "system_physics.h"
#include "cmp_car_body.h"

using namespace std;
using namespace sf;
using namespace Physics;




CarBodyComponent::CarBodyComponent(Entity* const p, const Vector2f& size) : Component(p) {
	
	bodySize = sv2_to_bv2(size, true);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

	body = Physics::GetWorld()->CreateBody(&bodyDef);
	body->SetActive(true);
/*
	RectangleShape rect;
	rect.setSize(size);
	rect.setFillColor(sf::Color::Red);
*/
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(bodySize.x * 0.5f, bodySize.y * 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 10.f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = .2f;
	fixtureDef.shape = &bodyShape;

	fixture = body->CreateFixture(&fixtureDef);
}

void CarBodyComponent::setMass(float m) { 
	fixture->SetDensity(m); 
}

void CarBodyComponent::update(double dt) {

}

void CarBodyComponent::render() {

}
