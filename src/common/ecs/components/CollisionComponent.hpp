#pragma once

#include "Component.hpp"
#include <nlohmann/json.hpp>

namespace ecs {
class CollisionComponent : public Component {
public:
  bool isSolid;

  CollisionComponent(bool solid = true) : isSolid(solid) {
  }

  friend void to_json(nlohmann::json &j, const CollisionComponent &c) {
    j = nlohmann::json({"isSolid", c.isSolid});
  }

  CollisionComponent(const nlohmann::json &j) {
    j.at("isSolid").get_to(isSolid);
  }
};
} // namespace ecs
