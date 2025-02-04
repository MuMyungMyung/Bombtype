#pragma once
#include "Entity.hpp"
#include <vector>

namespace ecs {

class EntityManager {
public:
  std::shared_ptr<Entity> createEntity() {
    auto entity = std::make_shared<Entity>();
    m_entities.push_back(entity);
    return entity;
  };

  template <typename... Components> [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntitiesWith() {
    std::vector<std::shared_ptr<Entity>> results;
    for (auto &entity : m_entities) {
      if (hasComponents<Components...>(entity)) {
        results.push_back(entity);
      }
    }
    return results;
  }

  void removeEntity(std::shared_ptr<Entity> entity) {
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
  }

private:
  std::vector<std::shared_ptr<Entity>> m_entities;

  template <typename... Components> bool hasComponents(std::shared_ptr<Entity> entity) {
    return (entity->hasComponent<Components>() && ...);
  }
};

} // namespace ecs
