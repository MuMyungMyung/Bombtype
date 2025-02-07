#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/HealthComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs::systems {
class ExplosionSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    auto entities = entityManager.getEntitiesWith<ExplosionComponent, TransformComponent>();
    for (auto &entity : entities) {
      auto *explosion = entity->getComponent<ExplosionComponent>();
      auto *transform = entity->getComponent<TransformComponent>();

      explosion->duration -= deltaTime;

      if (explosion->duration <= 0.0f) {
        entityManager.removeEntity(entity);
        continue;
      }
      // Check for positions in radius
      auto nearbyEntities = getNearbyEntities(entityManager, transform, explosion->range);

      for (auto &entity : nearbyEntities) {
        auto health = entity->getComponent<HealthComponent>();
        if (!health) {
          continue;
        }

        health->health -= explosion->damage;
        if (health->health <= 0) {
          entityManager.removeEntity(entity);
        }
      }
    }
  }

private:
  std::vector<std::shared_ptr<Entity>> getNearbyEntities(EntityManager &entityManager, TransformComponent *position,
                                                         int range) {
    return entityManager.getEntitiesWithP<TransformComponent>([range, position](TransformComponent *c) {
      int cX = c->position.x;
      int cY = c->position.y;
      int x = position->position.x;
      int y = position->position.y;

      if ((cX == x) && (cY >= y - range && cY <= y + range))
        return true;
      if ((cY == y) && (cX >= x - range && cX <= x + range))
        return true;
      return false;
    });
  }
};
} // namespace ecs::systems
