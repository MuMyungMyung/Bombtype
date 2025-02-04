#pragma once

#include "IEventSystem.hpp"
#include "ecs/components/InputComponent.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace ecs {
namespace systems {

class InputSystem : public IEventSystem {
public:
  void handleEvent(EntityManager &entityManager, const sf::Event &event) override {
    if (event.type != sf::Event::KeyReleased)
      return;
    auto entities = entityManager.getEntitiesWith<InputComponent>();
    for (auto &entity : entities) {
      auto input = entity->getComponent<InputComponent>();

      input->reset();

      switch (event.key.code) {
      case sf::Keyboard::Z: input->movementDirection.y = -1; break;
      case sf::Keyboard::S: input->movementDirection.y = 1; break;
      case sf::Keyboard::Q: input->movementDirection.x = -1; break;
      case sf::Keyboard::D: input->movementDirection.x = 1; break;
      case sf::Keyboard::Space: input->placeBomb = true; break;
      default: break;
      }
    }
  }
};

} // namespace systems
} // namespace ecs
