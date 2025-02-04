#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace ecs {

class MovementComponent : public Component {
public:
  sf::Vector2i direction = {0, 0};
  float speed;
  MovementComponent(float speed = 1.0f) : speed(speed) {
  }
};
} // namespace ecs
