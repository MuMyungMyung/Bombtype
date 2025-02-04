#pragma once
#include "ecs/components/Component.hpp"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace ecs {

class Entity {

public:
  using EntityID = uint64_t;
  Entity() : m_id(m_nextId++) {};

  template <typename T, typename... Args> T &addComponent(Args &&...args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    auto &ref = *component;
    m_components[std::type_index(typeid(T))] = std::move(component);
    return ref;
  }

  template <typename T> T *getComponent() {
    auto it = m_components.find(std::type_index(typeid(T)));
    return it != m_components.end() ? dynamic_cast<T *>(it->second.get()) : nullptr;
  }

  template <typename T> bool removeComponent() {
    auto it = m_components.find(std::type_index(typeid(T)));
    if (it != m_components.end()) {
      m_components.erase(it);
      return true;
    }
    return false;
  }

  template <typename T> bool hasComponent() {
    return m_components.find(std::type_index(typeid(T))) != m_components.end();
  }

  EntityID getId() {
    return m_id;
  }

private:
  static inline EntityID m_nextId = 1;
  EntityID m_id;
  std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
};

} // namespace ecs
