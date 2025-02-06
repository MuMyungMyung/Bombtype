#pragma once

#include "Component.hpp"
#include <functional>
#include <nlohmann/json.hpp>

namespace ecs {
class ComponentFactory {
public:
  using ComponentCreator = std::function<std::unique_ptr<Component>(const nlohmann::json &)>;

  static ComponentFactory &getInstance() {
    static ComponentFactory instance;
    return instance;
  }

  template <typename T> void registerComponent(const std::string &name) {
    creators[name] = [](const nlohmann::json &data) { return std::make_unique<T>(data); };
  }

  std::unique_ptr<Component> createComponent(const std::string &name, const nlohmann::json &data) {
    if (creators.find(name) != creators.end()) {
      return creators[name](data);
    }
    return nullptr;
  }

private:
  ComponentFactory() = default;
  std::unordered_map<std::string, ComponentCreator> creators;
};
} // namespace ecs
