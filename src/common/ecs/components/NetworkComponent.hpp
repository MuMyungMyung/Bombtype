#pragma once

#include "Component.hpp"
#include <cstring>
#include <string>

namespace ecs {
class NetworkComponent : public Component {
public:
  std::string id;
  bool isLocal;
  explicit NetworkComponent(const std::string &netId, bool isLocal = false) : id(netId), isLocal(isLocal) {
  }
};
} // namespace ecs
