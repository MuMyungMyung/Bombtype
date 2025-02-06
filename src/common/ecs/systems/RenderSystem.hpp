#pragma once

#include "IRenderSystem.hpp"
#include "ecs/components/MapComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <nlohmann/json.hpp>

namespace ecs::systems {

class RenderSystem : public IRenderSystem {
public:
  void render(EntityManager &entityManager, sf::RenderWindow &window) override {
    auto mapEntities = entityManager.getEntitiesWith<MapComponent>();
    int tileSize = 32;

    for (auto &entity : mapEntities) {
      auto map = entity->getComponent<MapComponent>();
      sf::Vector2f position = {0, 0};
      map->sprite.setPosition(position);
      tileSize = map->tileSize;
      window.draw(map->sprite);
    }

    auto entities = entityManager.getEntitiesWith<TransformComponent, SpriteComponent>();
    for (auto &entity : entities) {
      auto sprite = entity->getComponent<SpriteComponent>();
      auto position = entity->getComponent<TransformComponent>();

      sprite->sprite.setPosition(position->position.x * tileSize, position->position.y * tileSize);
      window.draw(sprite->sprite);
    }
  }
};

} // namespace ecs::systems
