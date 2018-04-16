#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;




void EnemyAIComponent::update(double dt) {
 
	
	
#pragma region Original


	auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
    _direction *= -1.f;
  }

  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);

#pragma endregion


}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
#pragma region Original

#pragma endregion

	
	_direction = Vector2f(1.0f, 0);
  _speed = 100.0f;
}
