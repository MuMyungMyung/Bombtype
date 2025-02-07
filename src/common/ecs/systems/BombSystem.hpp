#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/BombComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs::systems {

class BombSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    auto entities = entityManager.getEntitiesWith<BombComponent, SpriteComponent, AnimationComponent>();
    for (auto &entity : entities) {
      auto bomb = entity->getComponent<BombComponent>();
      auto animation = entity->getComponent<AnimationComponent>();
      auto sprite = entity->getComponent<SpriteComponent>();

      bomb->timer -= deltaTime;
      sf::IntRect rect = animation->frames.at("default");
      if (bomb->timer <= 0.25f) {
        rect = animation->frames.at("smallwick");
      } else if (bomb->timer <= 0.5f) {
        rect = animation->frames.at("mediumwick");
      } else if (bomb->timer <= 0.75f) {
        rect = animation->frames.at("bigwick");
      }
      sprite->sprite.setTextureRect(rect);
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
    auto animation = explosion->addComponent<AnimationComponent>();
    auto sprite = explosion->addComponent<SpriteComponent>(std::string("assets/explosion.png"));
    sprite.sprite.setTextureRect(animation.frames.at("default"));
  }
};
} // namespace ecs::systems
