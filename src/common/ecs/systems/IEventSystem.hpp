#pragma once

#include "ecs/entities/EntityManager.hpp"
#include <SFML/Window/Event.hpp>
#include <optional>

namespace ecs {
namespace systems {

class IEventSystem {
public:
  virtual ~IEventSystem() = default;
  virtual void handleEvent(EntityManager &, std::optional<sf::Event>) = 0;
};

} // namespace systems
} // namespace ecs
