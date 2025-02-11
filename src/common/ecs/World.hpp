#pragma once
#include "ecs/entities/EntityManager.hpp"
#include "ecs/systems/SystemManager.hpp"
#include <SFML/Graphics.hpp>

namespace ecs {

class World {
public:
  void updateSystems(float deltaTime);

  void handleEvents(std::optional<sf::Event> event);

  void render(sf::RenderWindow &window);

protected:
  EntityManager m_entityManager;
  SystemManager m_systemManager;
};

} // namespace ecs
