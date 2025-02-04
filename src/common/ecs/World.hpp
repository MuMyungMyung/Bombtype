#pragma once
#include "ecs/entities/EntityManager.hpp"
#include "ecs/systems/SystemManager.hpp"
#include <SFML/Graphics.hpp>

namespace ecs {

class World {
public:
  void updateSystems(float deltaTime);

  void handleEvents(const sf::Event &event);

  void render(sf::RenderWindow &window);

private:
  EntityManager m_entityManager;
  SystemManager m_systemManager;
};

} // namespace ecs
