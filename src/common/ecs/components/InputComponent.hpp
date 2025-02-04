#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace ecs {

class InputComponent : public Component {
public:
  sf::Vector2i movementDirection;
  bool placeBomb;
  void reset() {
    movementDirection = {0, 0};
    placeBomb = false;
  }
};

} // namespace ecs
