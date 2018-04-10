#include "cmp_physics.h"
#include "system_physics.h"
#include "cmp_player_physics.h"


using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
	currentForwardSpeed = 0;
  _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
  _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}


PhysicsComponent::PhysicsComponent(Entity* p, bool dyn, const Vector2f& size) : Component(p), _dynamic(dyn) {

	 b2BodyDef BodyDef;
	 // Is Dynamic(moving), or static(Stationary)
	 BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
	 BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));
	 
	 // Create the body
	 _body = Physics::GetWorld()->CreateBody(&BodyDef);
	 _body->SetActive(true);
	 _body->SetAngularDamping(0.1f);
	 {
	   // Create the fixture shape
	   b2PolygonShape Shape;
		
	   // SetAsBox box takes HALF-Widths!
	   Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	 
		
		b2FixtureDef FixtureDef;
	   // Fixture properties
	   FixtureDef.density = _dynamic ? 10.f : 0.f;
	   FixtureDef.friction = _dynamic ? 0.05f : 0.8f;
	   FixtureDef.restitution = .2;
	   FixtureDef.shape = &Shape;
	   // Add to body
	   _fixture = _body->CreateFixture(&FixtureDef);
	   //_fixture->SetRestitution(.9)

	 }

	 //Impulse Variables
	 maxForwardSpeed = 20.f;
	 maxBackwardSpeed = -10.f;
	 desiredSpeed = 20.f;
	 maxDriveForce = 5.0f;

	 //Friction Variables
	 maxLateralImpulse = 5.5f;
	 driftFriction = 0.1;
	 dragModifier = 0.01;
	 currentTraction = 0.1f;



	 

  // An ideal Pod/capusle shape should be used for the player,
  // this isn't built into B2d, but we can combine two shapes to do so.
  // This would allow the player to go up steps
  
    BodyDef.bullet = true;
    b2PolygonShape shape1;
    shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    {
      b2PolygonShape poly ;
      poly.SetAsBox(0.45f, 1.4f);
      b2FixtureDef FixtureDefPoly;

      FixtureDefPoly.shape = &poly;
      _body->CreateFixture(&FixtureDefPoly);

    }
    {
      b2CircleShape circle;
      circle.m_radius = 0.45f;
      circle.m_p.Set(0, -1.4f);
      b2FixtureDef FixtureDefCircle;
      FixtureDefCircle.shape = &circle;
      _body->CreateFixture(&FixtureDefCircle);
    }
  
}


void PhysicsComponent::setFriction(float r) { 




	_fixture->SetFriction(r); 
}


void PhysicsComponent::setMass(float m) { 
	_fixture->SetDensity(m); 
}


void PhysicsComponent::teleport(const sf::Vector2f& v) {
  _body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

//added
b2Vec2 PhysicsComponent::getForwardVelocity() {
	b2Vec2 currentForwardVelocity = _body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardVelocity, _body->GetLinearVelocity()) * currentForwardVelocity;
}

b2Vec2 PhysicsComponent::getLateralVelocity() {
	b2Vec2 currentLateralVelocity = _body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentLateralVelocity, _body->GetLinearVelocity()) * currentLateralVelocity;
}

b2Vec2 PhysicsComponent::getDirection() {
	return _body->GetWorldVector(b2Vec2(0, 1));
}

////////////////

const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}


void PhysicsComponent::setVelocity(const sf::Vector2f& v) {

  _body->SetLinearVelocity(sv2_to_bv2(v, true));
}


b2Fixture* const PhysicsComponent::getFixture() const { 
	return _fixture; 
}


PhysicsComponent::~PhysicsComponent() {
  auto a = Physics::GetWorld();
  _body->SetActive(false);
  Physics::GetWorld()->DestroyBody(_body);
  // delete _body;
  _body = nullptr;
}


void PhysicsComponent::render() {}


void PhysicsComponent::impulse(const sf::Vector2f& i) {
	//updateFriction();

	b2Vec2 curForwardSpeed = { i.x,i.y * -1.0f };
	float currentSpeed = b2Dot(getForwardVelocity(), curForwardSpeed);

	float force = (desiredSpeed > currentSpeed) ? maxDriveForce : -maxDriveForce;

	if (desiredSpeed != currentSpeed) {
		_body->ApplyForceToCenter(20 * force * curForwardSpeed, true);
		currentForwardNormal = getForwardVelocity();
		currentForwardSpeed = currentForwardNormal.Normalize();
	}
	else {
		currentForwardNormal = getForwardVelocity();
		currentForwardSpeed = currentForwardNormal.Normalize();
	}
}

//ADDED


void PhysicsComponent::updateFriction() {

	b2Vec2 i = _body->GetMass() * -getLateralVelocity();
	if (i.Length() > maxLateralImpulse)
		i *= maxLateralImpulse / i.Length();

	//apply the impulse
	_body->ApplyLinearImpulse(driftFriction * i, _body->GetWorldCenter(), true);

	//angular velocity
	_body->ApplyAngularImpulse(8 * 0.1f *_body->GetInertia() *_body->GetAngularVelocity(),true);

	
	float dragForceMagnitude = -2 * currentForwardSpeed * dragModifier;
	
	currentForwardNormal = getForwardVelocity();
	currentForwardSpeed = currentForwardNormal.Normalize();
	_body->ApplyForce(currentTraction * dragForceMagnitude * currentForwardNormal, _body->GetWorldCenter(), true);
}


void PhysicsComponent::turnRight() {

	if (currentForwardSpeed > .5f)
		_body->SetAngularVelocity(1.5);

	
	//////testing
	//float steerTorque = 0.01;
	//float steerTorqueOffset = 0.004;
	//float desiredTorque = 0;

	//float torque = steerTorque + steerTorqueOffset;

	//desiredTorque = -torque;
	//_body->ApplyTorque(desiredTorque, true);
}


void PhysicsComponent::turnLeft() {
	if (currentForwardSpeed > .5f)
		_body->SetAngularVelocity(-1.5);		
}


void PhysicsComponent::stopTurning() {
	//Stop Turning
	_body->SetAngularVelocity(0);
	_body->ApplyAngularImpulse(0, true);
}

////////////////////////

void PhysicsComponent::dampen(const sf::Vector2f& i) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= i.x;
  vel.y *= i.y;

  _body->ApplyLinearImpulseToCenter(-vel, true);

}


bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
  b2Contact* bc;
  return isTouching(pc, bc);
}


bool PhysicsComponent::isTouching(const PhysicsComponent& pc, b2Contact const* bc) const {
  const auto _otherFixture = pc.getFixture();
  const auto& w = *Physics::GetWorld();
  const auto contactList = w.GetContactList();
  const auto clc = w.GetContactCount();
  for (int32 i = 0; i < clc; i++) {
    const auto& contact = (contactList[i]);
    if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
                                  contact.GetFixtureA() == _otherFixture) ||
                                 (contact.GetFixtureA() == _otherFixture &&
                                  contact.GetFixtureA() == _fixture))) {
      bc = &contact;
      return true;
    }
  }
  return false;
}


std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  std::vector<const b2Contact const*> ret;

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != NULL) {
    const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}


void PhysicsComponent::setRestitution(float r) {
  _fixture->SetRestitution(r);
}
