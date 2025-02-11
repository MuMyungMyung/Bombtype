#pragma once

#include "IEventSystem.hpp"
#include "ecs/components/InputComponent.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace ecs {
namespace systems {

class InputSystem : public IEventSystem {
public:
  void handleEvent(EntityManager &entityManager, std::optional<sf::Event> event) override {
    if (!event->is<sf::Event::KeyPressed>())
      return;
    auto entities = entityManager.getEntitiesWith<InputComponent>();
    for (auto &entity : entities) {
      auto input = entity->getComponent<InputComponent>();

      input->reset();

      switch (event->getIf<sf::Event::KeyPressed>()->code) {
      case sf::Keyboard::Key::Z: input->movementDirection.y = -1; break;
      case sf::Keyboard::Key::S: input->movementDirection.y = 1; break;
      case sf::Keyboard::Key::Q: input->movementDirection.x = -1; break;
      case sf::Keyboard::Key::D: input->movementDirection.x = 1; break;
      case sf::Keyboard::Key::Space: input->placeBomb = true; break;
      default: break;
      }
    }
  }
};

} // namespace systems
} // namespace ecs
