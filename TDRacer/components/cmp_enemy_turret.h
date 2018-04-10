#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class EnemyTurretComponent : public Component {
protected:
  void fire() const;
  float _firetime;

public:
  void update(double dt) override;
  void impulse(const sf::Vector2f& i, bool controlState);
  void render() override {}
  explicit EnemyTurretComponent(Entity* p);
  EnemyTurretComponent() = delete;
};
