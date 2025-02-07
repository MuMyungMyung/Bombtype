#pragma once

#include "IRenderSystem.hpp"
#include "ecs/components/MapComponent.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <nlohmann/json.hpp>

namespace ecs::systems {

class MapRenderSystem : public IRenderSystem {
public:
  void render(EntityManager &entityManager, sf::RenderWindow &window) override {
    auto mapEntities = entityManager.getEntitiesWith<MapComponent>();

    for (auto &entity : mapEntities) {
      auto map = entity->getComponent<MapComponent>();
      sf::Vector2f position = {0, 0};
      map->sprite.setPosition(position);
      window.draw(map->sprite);
    }
  }
};

} // namespace ecs::systems
