#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

namespace ecs {

class TransformComponent : public Component {
public:
  sf::Vector2i position;

  TransformComponent(sf::Vector2i position = {0, 0}) : position(position) {
  }

  TransformComponent(const nlohmann::json &j)
      : TransformComponent(sf::Vector2i{j.at("x").get<int>(), j.at("y").get<int>()}) {
  }

  friend void to_json(nlohmann::json &j, const TransformComponent &t) {
    j = nlohmann::json({{"x", t.position.x}, {"y", t.position.y}});
  }
};

} // namespace ecs
