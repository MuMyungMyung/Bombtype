#pragma once

#include "Component.hpp"
#include <nlohmann/json.hpp>

namespace ecs {

class HealthComponent : public Component {
public:
  int health;

  HealthComponent(int health = 3) : health(health) {
  }

  friend void to_json(nlohmann::json &j, const HealthComponent &h) {
    j = nlohmann::json({"health", h.health});
  }

  HealthComponent(const nlohmann::json &j) {
    j.at("health").get_to(health);
  }
};

} // namespace ecs
