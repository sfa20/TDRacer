#include "Box2D\Box2D.h"
#include "system_physics.h"
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

SpriteComponent::SpriteComponent(Entity* p) : Component(p), _sprite(make_shared<sf::Sprite>()) {}


sf::Sprite& SpriteComponent::getSprite() const {
	return *_sprite;
}

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());
}



void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }


ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(make_shared<sf::CircleShape>()) {
	
	//b2Body* body;
	////Define the body
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position = Physics::sv2_to_bv2(Physics::invert_height(p->getPosition()));

	////Create the body
	//body = Physics::GetWorld()->CreateBody(&bodyDef);

	////Create the shape
	//b2PolygonShape shape;
	//shape.SetAsBox(20, 20);  //This is defined from the center of the object 

	////Create the fixture
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &shape;
	//fixtureDef.density = 1;
	//fixtureDef.friction = 0.3;
	//fixtureDef.restitution = 0.5;
	//
	//body->CreateFixture(&fixtureDef);
	//body->SetActive(true);
	
	
	//// Create the body
	//_body = Physics::GetWorld()->CreateBody(&BodyDef);
	//_body->SetActive(true);

	//{
	//	// Create the fixture shape
	//	b2PolygonShape Shape;

	//	// SetAsBox box takes HALF-Widths!
	//	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);


	//	b2FixtureDef FixtureDef;
	//	// Fixture properties
	//	FixtureDef.density = _dynamic ? 10.f : 0.f;
	//	FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
	//	FixtureDef.restitution = .2;
	//	FixtureDef.shape = &Shape;
	//	// Add to body
	//	_fixture = _body->CreateFixture(&FixtureDef);
	//	//_fixture->SetRestitution(.9)
	//	//FixtureDef.restitution = .2;
	//}



}


