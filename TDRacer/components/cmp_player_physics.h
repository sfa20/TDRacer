#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
private:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  float maxSpeed;
 
  //bool _grounded;
  float _groundspeed;

  //Not Used
  //bool isGrounded() const;

public:
  void update(double dt) override;
  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
  //bool controlsEnabled;

  PlayerPhysicsComponent() = delete;
};

