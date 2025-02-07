#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs::systems {
class ExplosionSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    auto entities = entityManager.getEntitiesWith<ExplosionComponent, TransformComponent>();
    for (auto &entity : entities) {
      auto *explosion = entity->getComponent<ExplosionComponent>();
      auto *transform = entity->getComponent<TransformComponent>();

      if (!explosion || !transform)
        continue;

      explosion->duration -= deltaTime;

      if (explosion->duration <= 0.0f) {
        entityManager.removeEntity(entity);
        continue;
      }
      // Check for positions in radius
    }
  }
};

} // namespace ecs::systems
