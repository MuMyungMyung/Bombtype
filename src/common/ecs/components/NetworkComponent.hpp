#pragma once

#include "Component.hpp"
#include <cstring>
#include <nlohmann/json.hpp>
#include <string>

namespace ecs {
class NetworkComponent : public Component {
public:
  std::string id;
  std::string username;
  bool isLocal;
  explicit NetworkComponent(const std::string &netId, const std::string &username, bool isLocal = false)
      : id(netId), username(username), isLocal(isLocal) {
  }

  NetworkComponent(const nlohmann::json &j)
      : NetworkComponent(j.at("id").get<std::string>(), j.at("username").get<std::string>(),
                         j.at("isLocal").get<bool>()) {
  }

  friend void to_json(nlohmann::json &j, const NetworkComponent &n) {
    j = nlohmann::json({{"id", n.id}, {"username", n.username}, {"isLocal", n.isLocal}});
  }
};
} // namespace ecs
