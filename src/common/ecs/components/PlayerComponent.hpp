#pragma once

#include "Component.hpp"
#include <nlohmann/json.hpp>
#include <string>

namespace ecs {

class PlayerComponent : public Component {
public:
  std::string id;

  PlayerComponent(const std::string &id) : id(id) {
  }

  PlayerComponent(const nlohmann::json &j) : PlayerComponent(j.at("id").get<std::string>()) {
  }

  friend void to_json(nlohmann::json &j, const PlayerComponent &p) {
    j = nlohmann::json({"id", p.id});
  }
};

} // namespace ecs
