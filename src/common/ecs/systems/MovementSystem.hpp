#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/CollisionComponent.hpp"
#include "ecs/components/MovementComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs {
namespace systems {

class MovementSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    m_ellapsedTime += deltaTime;

    auto entities = entityManager.getEntitiesWith<TransformComponent, MovementComponent>();
    for (auto &entity : entities) {
      auto transform = entity->getComponent<TransformComponent>();
      auto movement = entity->getComponent<MovementComponent>();

      if (m_ellapsedTime < 1000.0f / movement->speed)
        continue;

      sf::Vector2i newPosition = transform->position;
      // Single direction hack
      if (movement->direction.y != 0)
        newPosition.y += movement->direction.y;
      else
        newPosition.x += movement->direction.x;

      for (auto &collider : entityManager.getEntitiesWith<CollisionComponent, TransformComponent>()) {
        auto colliderTransform = collider->getComponent<TransformComponent>();
        auto collision = collider->getComponent<CollisionComponent>();

        if (collision->isSolid && colliderTransform->position == newPosition) {
          newPosition = transform->position;
          break;
        }
      }
      transform->position = newPosition;
    }

    if (m_ellapsedTime >= 1000)
      m_ellapsedTime = 0;
  }

private:
  float m_ellapsedTime = 0;
};

} // namespace systems
} // namespace ecs
