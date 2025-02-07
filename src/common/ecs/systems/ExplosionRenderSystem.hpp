#pragma once

#include "IRenderSystem.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/CollisionComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs::systems {
class ExplosionRenderSystem : public IRenderSystem {
public:
  void render(EntityManager &entityManager, sf::RenderWindow &window) override {
    auto entities =
        entityManager.getEntitiesWith<TransformComponent, AnimationComponent, ExplosionComponent, SpriteComponent>();

    for (auto &entity : entities) {
      auto explosion = entity->getComponent<ExplosionComponent>();
      auto sprite = entity->getComponent<SpriteComponent>();
      auto position = entity->getComponent<TransformComponent>();
      auto animation = entity->getComponent<AnimationComponent>();

      int radius = explosion->range;
      auto nearbyEntities = getNearbyEntities(entityManager, position, radius);

      for (int y = position->position.y - 1; y > position->position.y - radius && y > 0; y--) {
        if (drawExplosionTile(window, sprite, animation, nearbyEntities, sf::Vector2i(position->position.x, y),
                              Direction::DOWN))
          break;
      }
      for (int y = position->position.y + 1; y < position->position.y + radius; y++) {
        if (drawExplosionTile(window, sprite, animation, nearbyEntities, sf::Vector2i(position->position.x, y),
                              Direction::UP))
          break;
      }
      for (int x = position->position.x - 1; x > position->position.x - radius && x > 0; x--) {
        if (drawExplosionTile(window, sprite, animation, nearbyEntities, sf::Vector2i(x, position->position.y),
                              Direction::LEFT))
          break;
      }
      for (int x = position->position.x + 1; x < position->position.x + radius; x++) {
        if (drawExplosionTile(window, sprite, animation, nearbyEntities, sf::Vector2i(x, position->position.y),
                              Direction::RIGHT))
          break;
      }
    }
  }

private:
  enum class Direction { UP, DOWN, LEFT, RIGHT };
  std::string getExplosionEndAssetName(Direction d) {
    switch (d) {

    case Direction::UP: return "up";
    case Direction::DOWN: return "down";
    case Direction::LEFT: return "left";
    case Direction::RIGHT: return "right";
    }
  }

  bool drawExplosionTile(sf::RenderWindow &window, SpriteComponent *sprite, AnimationComponent *animation,
                         const std::vector<std::shared_ptr<Entity>> &nearbyEntities, sf::Vector2i position,
                         Direction d) {
    std::string explosionEndString = getExplosionEndAssetName(d);
    auto tileEntity = getEntityAt(nearbyEntities, position.x, position.y);
    if (tileEntity) {
      auto collision = tileEntity->getComponent<CollisionComponent>();
      if (collision && collision->isSolid) {
        sprite->sprite.setTextureRect(animation->frames.at(explosionEndString));
        window.draw(sprite->sprite);
        return true;
      }
    }
    sprite->sprite.setTextureRect(
        animation->frames.at(d == Direction::UP || d == Direction::DOWN ? "vertical" : "horizontal"));
    window.draw(sprite->sprite);
    return false;
  }

  std::vector<std::shared_ptr<Entity>> getNearbyEntities(EntityManager &entityManager, TransformComponent *position,
                                                         int radius) {
    return entityManager.getEntitiesWithP<TransformComponent>([radius, position](TransformComponent *c) {
      int cX = c->position.x;
      int cY = c->position.y;
      int x = position->position.x;
      int y = position->position.y;

      if ((cX >= x - 1 && cX <= x + 1) && (cY >= y && cY <= y + radius))
        return true;
      if ((cY >= y - 1 && cY <= y - 1) && (cX >= x && cX <= x + radius))
        return true;
      return false;
    });
  }

  std::shared_ptr<Entity> getEntityAt(const std::vector<std::shared_ptr<Entity>> &nearbyEntities, int x, int y) {
    for (const auto &i : nearbyEntities) {
      auto *pos = i->getComponent<TransformComponent>();
      if (pos->position.x == x && pos->position.y == y) {
        return i;
      }
    }
    return nullptr;
  }
};
} // namespace ecs::systems
