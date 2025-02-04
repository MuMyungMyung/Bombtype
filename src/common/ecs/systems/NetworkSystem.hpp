#pragma once

#include "IUpdateSystem.hpp"
#include "ecs/components/NetworkComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

namespace ecs {
namespace systems {

class NetworkSystem : public IUpdateSystem {
public:
  void update(EntityManager &entityManager, float deltaTime) override {
    auto entities = entityManager.getEntitiesWith<NetworkComponent>();
    // TODO 1 integrate networking and then chose to iterate over packet or entities
    // TODO 2 refactor into private methods
    for (auto &entity : entities) {
      auto net = entity->getComponent<NetworkComponent>();
      auto transform = entity->getComponent<TransformComponent>();

      if (net->isLocal) {
        if (transform) {
          // send position update;
        }
      } else {
        if (transform) {
          // receive position update;
        }
      }
    }
  }
};

} // namespace systems
} // namespace ecs
