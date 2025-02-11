#pragma once

#include "IRenderSystem.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/BombComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

namespace ecs::systems {

class RenderSystem : public IRenderSystem {
public:
  void render(EntityManager &entityManager, sf::RenderWindow &window) override {
    auto entities = entityManager.getEntitiesWith<TransformComponent, SpriteComponent>();
    for (auto &entity : entities) {
      auto sprite = entity->getComponent<SpriteComponent>();
      auto position = entity->getComponent<TransformComponent>();

      auto animation = entity->getComponent<AnimationComponent>();
      if (animation && !entity->getComponent<ExplosionComponent>() && !entity->getComponent<BombComponent>()) {
        sprite->sprite.setTextureRect(animation->frames.at("default"));
      }
      if (!entity->getComponent<ExplosionComponent>()) {
        sprite->sprite.setPosition(sf::Vector2f(position->position.x * 32, position->position.y * 32));
        window.draw(sprite->sprite);
      }
    }
  }
};

} // namespace ecs::systems
