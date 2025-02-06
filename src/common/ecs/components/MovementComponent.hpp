#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

namespace ecs {

class MovementComponent : public Component {
public:
  sf::Vector2i direction = {0, 0};
  float speed;
  MovementComponent(sf::Vector2i direction = {0, 0}, float speed = 1.0f) : direction(direction), speed(speed) {
  }

  MovementComponent(const nlohmann::json &j)
      : MovementComponent(sf::Vector2i{j.at("x").get<int>(), j.at("y").get<int>()}, j.at("speed").get<float>()) {
  }

  friend void to_json(nlohmann::json &j, const MovementComponent &m) {
    j = nlohmann::json({{"x", m.direction.x}, {"y", m.direction.y}, {"speed", m.speed}});
  }
};
} // namespace ecs
