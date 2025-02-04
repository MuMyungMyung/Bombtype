#pragma once
#include "ecs/entities/EntityManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace ecs {

class IRenderSystem {
public:
  virtual ~IRenderSystem() = default;
  virtual void render(EntityManager &, sf::RenderWindow &) = 0;
};

} // namespace ecs
