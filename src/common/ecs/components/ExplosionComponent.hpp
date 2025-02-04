#pragma once

#include "Component.hpp"

namespace ecs {

class ExplosionComponent : public Component {
public:
  float duration;
  int damage;
  ExplosionComponent(float duration = 1.0f, int damage = 1) : duration(duration), damage(damage) {
  }
};
} // namespace ecs
