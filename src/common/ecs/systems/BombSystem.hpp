#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/BombComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs::systems {

class BombSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    auto entities = entityManager.getEntitiesWith<BombComponent, TransformComponent>();
    for (auto &entity : entities) {
      auto bomb = entity->getComponent<BombComponent>();

      bomb->timer -= deltaTime;
      if (bomb->timer <= 0.0f) {
        spawnExplosion(entityManager, entity);
        entityManager.removeEntity(entity);
      }
    }
  }

private:
  void spawnExplosion(EntityManager &entityManager, std::shared_ptr<Entity> bombEntity) {
    auto bomb = bombEntity->getComponent<BombComponent>();
    auto position = bombEntity->getComponent<TransformComponent>();

    auto explosion = entityManager.createEntity();
    explosion->addComponent<TransformComponent>(position->position);
    explosion->addComponent<ExplosionComponent>();
  }
};
} // namespace ecs::systems
