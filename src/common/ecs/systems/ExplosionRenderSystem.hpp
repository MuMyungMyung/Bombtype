#pragma once

#include "IRenderSystem.hpp"
#include "ecs/components/AnimationComponent.hpp"
#include "ecs/components/CollisionComponent.hpp"
#include "ecs/components/ExplosionComponent.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <iostream>

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
                              Direction::UP))
          break;
      }
      for (int y = position->position.y + 1; y < position->position.y + radius; y++) {
        if (drawExplosionTile(window, sprite, animation, nearbyEntities, sf::Vector2i(position->position.x, y),
                              Direction::DOWN))
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
        std::cout << "Drawing " << explosionEndString << " at " << position.x << ":" << position.y << std::endl;
        sprite->sprite.setTextureRect(animation->frames.at(explosionEndString));
        sprite->sprite.setPosition(position.x * 32, position.y * 32);
        window.draw(sprite->sprite);
        return true;
      }
    }
    std::string index = d == Direction::UP || d == Direction::DOWN ? "vertical" : "horizontal";
    sf::IntRect rect = animation->frames.at(index);
    std::cout << index << " " << explosionEndString << std::endl;
    sprite->sprite.setPosition(position.x * 32, position.y * 32);
    sprite->sprite.setTextureRect(rect);
    window.draw(sprite->sprite);
    return false;
  }

  std::vector<std::shared_ptr<Entity>> getNearbyEntities(EntityManager &entityManager, TransformComponent *position,
                                                         int range) {
    return entityManager.getEntitiesWithP<TransformComponent>([range, position](TransformComponent *c) {
      int cX = c->position.x;
      int cY = c->position.y;
      int x = position->position.x;
      int y = position->position.y;

      if ((cX >= x - 1 && cX <= x + 1) && (cY >= y - range && cY <= y + range))
        return true;
      if ((cY >= y - 1 && cY <= y - 1) && (cX >= x - range && cX <= x + range))
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
