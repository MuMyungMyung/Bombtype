#pragma once

#include "Component.hpp"
#include <nlohmann/json.hpp>
#include <string>

namespace ecs {
class BombComponent : public Component {
public:
  float timer;
  int explosionRange;
  std::string ownerId;

  BombComponent(const std::string &owner, float timer = 3.0f, int range = 2)
      : ownerId(owner), timer(timer), explosionRange(range) {
  }

  friend void to_json(nlohmann::json &j, const BombComponent &b) {
    j = nlohmann::json({{"timer", b.timer}, {"explosionRange", b.explosionRange}, {"ownerId", b.ownerId}});
  }

  BombComponent(const nlohmann::json &j) {
    j.at("timer").get_to(timer);
    j.at("explosionRange").get_to(explosionRange);
    j.at("ownerId").get_to(ownerId);
  }
};
} // namespace ecs
