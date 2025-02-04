#pragma once

#include "ecs/entities/EntityManager.hpp"
#include <SFML/Window/Event.hpp>

namespace ecs {

class IEventSystem {
public:
  virtual ~IEventSystem() = default;
  virtual void handleEvent(EntityManager &, const sf::Event &) = 0;
};

} // namespace ecs
