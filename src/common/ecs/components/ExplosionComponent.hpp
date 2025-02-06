#pragma once

#include "Component.hpp"
#include <nlohmann/json.hpp>

namespace ecs {

class ExplosionComponent : public Component {
public:
  float duration;
  int damage;
  int range;
  ExplosionComponent(float duration = 1.0f, int damage = 1, int range = 2)
      : duration(duration), damage(damage), range(range) {
  }

  friend void to_json(nlohmann::json &j, const ExplosionComponent &e) {
    j = nlohmann::json({{"duration", e.duration}, {"damage", e.damage}, {"range", e.range}});
  }

  ExplosionComponent(const nlohmann::json &j) {
    j.at("duration").get_to(duration);
    j.at("damage").get_to(damage);
    j.at("range").get_to(range);
  }
};
} // namespace ecs
