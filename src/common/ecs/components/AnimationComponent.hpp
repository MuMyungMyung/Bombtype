#pragma once

#include "Component.hpp"
#include "ecs/serialization/IntRect.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <nlohmann/json.hpp>

namespace ecs {
class AnimationComponent : public Component {
public:
  std::unordered_map<std::string, sf::IntRect> frames;

  AnimationComponent(const nlohmann::json &j)
      : frames(j.at("frames").get<std::unordered_map<std::string, sf::IntRect>>()) {
  }

  friend void to_json(nlohmann::json &j, const AnimationComponent &a) {
    j = nlohmann::json({"frames", a.frames});
  }
};
} // namespace ecs
