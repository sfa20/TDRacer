#pragma once

#include "cmp_physics.h"

class PlayerTwoPhysicsComponent : public PhysicsComponent {
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
  explicit PlayerTwoPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerTwoPhysicsComponent() = delete;
};

