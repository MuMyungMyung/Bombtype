#pragma once

#include "Component.hpp"

namespace ecs {
class BombComponent : public Component {
public:
  float timer;
  int explosionRange;
  int ownerId;

  BombComponent(int owner, float timer = 3.0f, int range = 2) : ownerId(owner), timer(timer), explosionRange(range) {
  }
};
} // namespace ecs
