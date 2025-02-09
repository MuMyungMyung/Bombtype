#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/BombComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/InputComponent.hpp"
#include "ecs/components/PlayerComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <iostream>

namespace ecs::systems {

class BombSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    for (auto &entity : entityManager.getEntitiesWith<InputComponent, PlayerComponent, TransformComponent>()) {
      auto input = entity->getComponent<InputComponent>();
      auto player = entity->getComponent<PlayerComponent>();
      auto position = entity->getComponent<TransformComponent>();
      if (input->placeBomb) {
        auto bombEntity = entityManager.createEntity();
        bombEntity->addComponent<BombComponent>(player->id);
        auto &animation = bombEntity->addComponent<AnimationComponent>();
        animation.frames["default"] = sf::IntRect(0, 0, 32, 32);
        animation.frames["bigwick"] = sf::IntRect(0, 32, 32, 32);
        animation.frames["mediumwick"] = sf::IntRect(32, 0, 32, 32);
        animation.frames["smallwick"] = sf::IntRect(32, 32, 32, 32);
        bombEntity->addComponent<SpriteComponent>(std::string("assets/bomb.png"));
        bombEntity->addComponent<TransformComponent>(position->position);
        input->placeBomb = false;
      }
    }
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
    auto &animation = explosion->addComponent<AnimationComponent>();
    animation.frames["default"] = sf::IntRect(0, 64, 32, 32);
    animation.frames["up"] = sf::IntRect(32, 0, 32, 32);
    animation.frames["down"] = sf::IntRect(32, 64, 32, 32);
    animation.frames["left"] = sf::IntRect(32, 32, 32, 32);
    animation.frames["right"] = sf::IntRect(64, 0, 32, 32);
    animation.frames["vertical"] = sf::IntRect(0, 32, 32, 32);
    animation.frames["horizontal"] = sf::IntRect(0, 0, 32, 32);
    auto sprite = explosion->addComponent<SpriteComponent>(std::string("assets/explosion.png"));
    sprite.sprite.setTextureRect(animation.frames.at("default"));
  }
};
} // namespace ecs::systems
