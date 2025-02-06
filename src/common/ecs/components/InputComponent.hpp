#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

namespace ecs {

class InputComponent : public Component {
public:
  sf::Vector2i movementDirection;
  bool placeBomb;
  void reset() {
    movementDirection = {0, 0};
    placeBomb = false;
  }

  friend void to_json(nlohmann::json &j, const InputComponent &i) {
    j = nlohmann::json({{"x", i.movementDirection.x}, {"y", i.movementDirection.y}, {"placeBomb", i.placeBomb}});
  }

  InputComponent(const nlohmann::json &j) {
    j.at("x").get_to(movementDirection.x);
    j.at("y").get_to(movementDirection.y);
    j.at("placeBomb").get_to(placeBomb);
  }
};

} // namespace ecs
